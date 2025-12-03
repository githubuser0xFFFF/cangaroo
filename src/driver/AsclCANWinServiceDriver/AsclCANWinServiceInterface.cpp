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

#include <QString>
#include <QStringList>
#include <QHostAddress>
#include <QThread>
#include "CANServiceDef.h"

static constexpr int FRAME_SIZE = sizeof(CANServiceCommon::CanMsgBytes);

AsclCANWinServiceInterface::AsclCANWinServiceInterface(AsclCANWinServiceDriver *driver)
  : CanInterface((CanDriver *)driver)
{
}

AsclCANWinServiceInterface::~AsclCANWinServiceInterface()
{
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
    if (isOpen())
    {
        return;
    }
    _socket = new QTcpSocket();
    _socket->connectToHost(
        QHostAddress(QString::fromStdString(CANServiceCommon::ServiceAddr)),
        CANServiceCommon::ServicePort
        );
    _socket->waitForConnected(1000);
    qDebug() << "socket state: " << _socket->state();
}

bool AsclCANWinServiceInterface::isOpen()
{
    return _socket && _socket->state() == QAbstractSocket::ConnectedState;
}

void AsclCANWinServiceInterface::close() {
    if (!isOpen())
    {
        return;
    }

    _socket->close();
    delete _socket;
    _socket = nullptr;
}

void AsclCANWinServiceInterface::sendMessage(const CanMessage &msg) {
    if (!isOpen())
    {
        return;
    }

    CANServiceCommon::CANMessage tx_msg;
    tx_msg.id = msg.getId();
    tx_msg.size = msg.getLength();
    for (int i = 0; i < tx_msg.size; ++i)
    {
        tx_msg.data[i] = msg.getByte(i);
    }
    CANServiceCommon::CanMsgBytes buffer;
    CANServiceCommon::pack(tx_msg, buffer);

    QByteArray Data(reinterpret_cast<const char*>(buffer.data()), buffer.size());
    _socket->write(Data);
    _status.tx_count++;

    //_rxBuffer.append(Data);
}

bool AsclCANWinServiceInterface::readMessage(QList<CanMessage> &msglist, unsigned int timeout_ms) {
    if (!_socket->waitForReadyRead(timeout_ms))
    {
        return false;
    }

    _rxBuffer.append(_socket->readAll());
    // Process full frames only
    while (_rxBuffer.size() >= FRAME_SIZE)
    {
        QByteArray frame = _rxBuffer.left(FRAME_SIZE);
        _rxBuffer.remove(0, FRAME_SIZE);

        CANServiceCommon::CANMessage msg;
        memcpy(&msg, frame.data(), sizeof(CANServiceCommon::CANMessage));

        CanMessage rx_msg(msg.id);
        rx_msg.setLength(msg.id);
        rx_msg.setCurrentTimestamp();
        rx_msg.setInterfaceId(getId());
        for (int i = 0; i < msg.size; ++i)
        {
            rx_msg.setDataAt(i, msg.data[i]);
        }

        msglist.append(rx_msg);
        _status.rx_count++;
    }

    return true;
}
