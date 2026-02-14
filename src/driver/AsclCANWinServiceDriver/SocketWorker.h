#pragma once

#include <QObject>
#include <QTcpSocket>
#include <QThread>
#include <QMutex>
#include <QWaitCondition>
#include <QQueue>
#include <QTimer>
#include "core/CanMessage.h"
#include "CANServiceDef.h"

class SocketWorker : public QObject
{
    Q_OBJECT

public:
    explicit SocketWorker(QObject *parent = nullptr);
    ~SocketWorker();

public slots:
    void connectToService();
    void disconnectFromService();
    void sendMessage(const CanMessage &msg);
    void startReceiving();
    void stopReceiving();

signals:
    void connected();
    void disconnected();
    void errorOccurred(const QString &errorString);
    void messageReceived(const CanMessage &msg);
    void messageSent();

private slots:
    void onConnected();
    void onDisconnected();
    void onSocketError(QAbstractSocket::SocketError error);
    void onReadyRead();
    void onReceiveTimer();

private:
    QTcpSocket *_socket;
    QByteArray _rxBuffer;
    QTimer *_receiveTimer;
    bool _isReceiving;
    
    static constexpr int FRAME_SIZE = sizeof(CANServiceCommon::CanMsgBytes);
    static constexpr int RECEIVE_INTERVAL = 10; // ms
};