#include "SocketWorker.h"
#include <QHostAddress>
#include <QThread>
#include <QDebug>
#include "core/CanMessageOperators.h"

SocketWorker::SocketWorker(QObject *parent)
    : QObject(parent)
    , _socket(nullptr)
    , _receiveTimer(nullptr)
    , _isReceiving(false)
{
}

SocketWorker::~SocketWorker()
{
    if (_socket) {
        _socket->close();
        _socket->deleteLater();
    }
    if (_receiveTimer) {
        _receiveTimer->deleteLater();
    }
}

void SocketWorker::connectToService()
{
    if (_socket) {
        _socket->deleteLater();
    }

    _socket = new QTcpSocket(this);
    connect(_socket, &QTcpSocket::connected, this, &SocketWorker::onConnected);
    connect(_socket, &QTcpSocket::disconnected, this, &SocketWorker::onDisconnected);
    connect(_socket, QOverload<QAbstractSocket::SocketError>::of(&QAbstractSocket::errorOccurred),
            this, &SocketWorker::onSocketError);
    connect(_socket, &QTcpSocket::readyRead, this, &SocketWorker::onReadyRead);

    qDebug() << "Socket worker connecting from thread:" << QThread::currentThread();
    
    _socket->connectToHost(
        QHostAddress(QString::fromStdString(CANServiceCommon::ServiceAddr)),
        CANServiceCommon::ServicePort
    );
}

void SocketWorker::disconnectFromService()
{
    stopReceiving();
    
    if (_socket && _socket->state() == QAbstractSocket::ConnectedState) {
        _socket->disconnectFromHost();
        if (_socket->state() != QAbstractSocket::UnconnectedState) {
            _socket->waitForDisconnected(3000);
        }
    }
}

void SocketWorker::sendMessage(const CanMessage &msg)
{
    if (!_socket || _socket->state() != QAbstractSocket::ConnectedState) {
        qWarning() << "Cannot send message: socket not connected";
        return;
    }

    CANServiceCommon::CANMessage tx_msg;
    tx_msg.id = msg.getId();
    tx_msg.size = msg.getLength();
    for (int i = 0; i < tx_msg.size; ++i) {
        tx_msg.data[i] = msg.getByte(i);
    }
    
    CANServiceCommon::CanMsgBytes buffer;
    CANServiceCommon::pack(tx_msg, buffer);

    QByteArray data(reinterpret_cast<const char*>(buffer.data()), buffer.size());
    qint64 written = _socket->write(data);
    
    if (written == data.size()) {
        qDebug() << "TX:" << QThread::currentThread() << msg;
        emit messageSent();
    } else {
        qWarning() << "Failed to send complete message";
    }
}

void SocketWorker::startReceiving()
{
    if (_isReceiving) return;
    
    _isReceiving = true;
    
    // Create timer for periodic receive processing 
    if (!_receiveTimer) {
        _receiveTimer = new QTimer(this);
        connect(_receiveTimer, &QTimer::timeout, this, &SocketWorker::onReceiveTimer);
    }
    
    _receiveTimer->start(RECEIVE_INTERVAL);
    qDebug() << "Started receiving in thread:" << QThread::currentThread();
}

void SocketWorker::stopReceiving()
{
    _isReceiving = false;
    
    if (_receiveTimer) {
        _receiveTimer->stop();
    }
}

void SocketWorker::onConnected()
{
    qDebug() << "Socket connected in thread:" << QThread::currentThread();
    emit connected();
}

void SocketWorker::onDisconnected()
{
    qDebug() << "Socket disconnected in thread:" << QThread::currentThread();
    stopReceiving();
    emit disconnected();
}

void SocketWorker::onSocketError(QAbstractSocket::SocketError error)
{
    QString errorString = _socket ? _socket->errorString() : "Unknown error";
    qWarning() << "Socket error:" << error << errorString;
    emit errorOccurred(errorString);
}

void SocketWorker::onReadyRead()
{
    if (!_socket) return;
    
    _rxBuffer.append(_socket->readAll());
}

void SocketWorker::onReceiveTimer()
{
    if (!_isReceiving || _rxBuffer.size() < FRAME_SIZE) {
        return;
    }
    
    // Process all complete frames in buffer
    while (_rxBuffer.size() >= FRAME_SIZE) {
        QByteArray frame = _rxBuffer.left(FRAME_SIZE);
        _rxBuffer.remove(0, FRAME_SIZE);

        CANServiceCommon::CANMessage canMsg;
        memcpy(&canMsg, frame.data(), sizeof(CANServiceCommon::CANMessage));

        CanMessage rx_msg(canMsg.id);
        rx_msg.setLength(canMsg.size);
        rx_msg.setCurrentTimestamp();
        for (int i = 0; i < canMsg.size; ++i) {
            rx_msg.setDataAt(i, canMsg.data[i]);
        }

        qDebug() << "RX:" << QThread::currentThread() << rx_msg;
        emit messageReceived(rx_msg);
    }
}

#include "SocketWorker.moc"