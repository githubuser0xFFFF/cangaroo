/*

  Copyright (c) 2015, 2016 Hubert Denkmair

  This file is part of cangaroo.

  cangaroo is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 2 of the License, or
  (at your option) any later version.

  cangaroo is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with cangaroo.  If not, see <http://www.gnu.org/licenses/>.

*/

#include "AsclCANWinServiceInterface.h"

#include <core/Backend.h>
#include <core/MeasurementInterface.h>
#include <core/CanMessage.h>
#include <core/CanMessageOperators.h>

#include <QString>
#include <QStringList>
#include <QHostAddress>
#include <QThread>
#include "SocketWorker.h"

AsclCANWinServiceInterface::AsclCANWinServiceInterface(AsclCANWinServiceDriver *driver)
  : CanInterface((CanDriver *)driver)
  , _workerThread(nullptr)
  , _socketWorker(nullptr)
  , _isConnected(false)
{
    memset(&_status, 0, sizeof(_status));
    qDebug() << "Interface created in thread:" << QThread::currentThread();
}

AsclCANWinServiceInterface::~AsclCANWinServiceInterface()
{
    closeImpl();
}

QString AsclCANWinServiceInterface::getName() const
{
    return "AsclCANWinService";
}


QList<CanTiming> AsclCANWinServiceInterface::getAvailableBitrates()
{
    QList<CanTiming> retval;
    retval << CanTiming(0, 500000, 0, 500);
    return retval;
}


void AsclCANWinServiceInterface::applyConfig(const MeasurementInterface &mi)
{
    Q_UNUSED(mi);
    return;
}


unsigned AsclCANWinServiceInterface::getBitrate() {
    return 500000;
}

uint32_t AsclCANWinServiceInterface::getCapabilities()
{
    return 0;
}

bool AsclCANWinServiceInterface::updateStatistics()
{
    return true;
}

uint32_t AsclCANWinServiceInterface::getState()
{
    return state_ok;
}

int AsclCANWinServiceInterface::getNumRxFrames()
{
    return _status.rx_count;
}

int AsclCANWinServiceInterface::getNumRxErrors()
{
    return _status.rx_errors;
}

int AsclCANWinServiceInterface::getNumTxFrames()
{
    return _status.tx_count;
}

int AsclCANWinServiceInterface::getNumTxErrors()
{
    return _status.tx_errors;
}

int AsclCANWinServiceInterface::getNumRxOverruns()
{
    return _status.rx_overruns;
}

int AsclCANWinServiceInterface::getNumTxDropped()
{
    return _status.tx_dropped;
}



void AsclCANWinServiceInterface::open() {
    if (isOpen()) {
        return;
    }
    
    // Create worker thread
    _workerThread = new QThread(this);
    _socketWorker = new SocketWorker();
    _socketWorker->moveToThread(_workerThread);
    
    // Connect signals for thread communication
    connect(_socketWorker, &SocketWorker::connected, this, &AsclCANWinServiceInterface::onSocketConnected);
    connect(_socketWorker, &SocketWorker::disconnected, this, &AsclCANWinServiceInterface::onSocketDisconnected);
    connect(_socketWorker, &SocketWorker::errorOccurred, this, &AsclCANWinServiceInterface::onSocketError);
    connect(_socketWorker, &SocketWorker::messageReceived, this, &AsclCANWinServiceInterface::onMessageReceived);
    connect(_socketWorker, &SocketWorker::messageSent, this, &AsclCANWinServiceInterface::onMessageSent);
    
    // Connect thread lifecycle
    connect(_workerThread, &QThread::started, _socketWorker, &SocketWorker::connectToService);
    connect(_workerThread, &QThread::finished, _socketWorker, &QObject::deleteLater);
    
    // Start worker thread
    _workerThread->start();
    
    qDebug() << "Interface opened from thread:" << QThread::currentThread();
}

bool AsclCANWinServiceInterface::isOpen()
{
    return _workerThread != nullptr;
}

void AsclCANWinServiceInterface::close() {
    closeImpl();
}


void AsclCANWinServiceInterface::closeImpl()
{
    if (!_workerThread) {
        return;
    }

    // Signal worker to disconnect and stop receiving
    QMetaObject::invokeMethod(_socketWorker, "disconnectFromService", Qt::QueuedConnection);

    // Wait for thread to finish
    if (_workerThread->isRunning()) {
        _workerThread->quit();
        _workerThread->wait(3000);
    }

    _workerThread->deleteLater();
    _workerThread = nullptr;
    _socketWorker = nullptr;

    _isConnected = false;

    // Clear any pending messages
    QMutexLocker locker(&_receivedMessagesMutex);
    _receivedMessages.clear();
}


void AsclCANWinServiceInterface::sendMessage(const CanMessage &msg) {
    if (!isOpen()) {
        return;
    }
    
    // Queue the message for sending in worker thread
    QMetaObject::invokeMethod(_socketWorker, "sendMessage", Qt::QueuedConnection,
                             Q_ARG(const CanMessage&, msg));
}

bool AsclCANWinServiceInterface::readMessage(QList<CanMessage> &msglist, unsigned int timeout_ms) {
    QMutexLocker locker(&_receivedMessagesMutex);
    
    // Wait for messages if none available
    if (_receivedMessages.isEmpty()) {
        if (!_messagesAvailable.wait(&_receivedMessagesMutex, timeout_ms)) {
            return false; // Timeout
        }
    }
    
    // Move all available messages to the output list
    while (!_receivedMessages.isEmpty()) {
        msglist.append(_receivedMessages.dequeue());
    }
    
    return !msglist.isEmpty();
}

// Signal handlers for SocketWorker
void AsclCANWinServiceInterface::onSocketConnected()
{
    _isConnected = true;
    qDebug() << "Interface connected, starting receive";
    
    // Start receiving messages
    QMetaObject::invokeMethod(_socketWorker, "startReceiving", Qt::QueuedConnection);
}

void AsclCANWinServiceInterface::onSocketDisconnected()
{
    _isConnected = false;
    qDebug() << "Interface disconnected";
}

void AsclCANWinServiceInterface::onSocketError(const QString &errorString)
{
    qWarning() << "Socket error:" << errorString;
    _isConnected = false;
}

void AsclCANWinServiceInterface::onMessageReceived(const CanMessage &msg)
{
    QMutexLocker locker(&_receivedMessagesMutex);
    
    // Set interface ID for the received message
    CanMessage rxMsg = msg;
    rxMsg.setInterfaceId(getId());
    
    _receivedMessages.enqueue(rxMsg);
    _status.rx_count++;
    
    // Wake up any threads waiting for messages
    _messagesAvailable.wakeAll();
}

void AsclCANWinServiceInterface::onMessageSent()
{
    _status.tx_count++;
}
