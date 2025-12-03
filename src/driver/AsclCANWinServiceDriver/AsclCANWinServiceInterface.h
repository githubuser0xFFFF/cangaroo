#pragma once

#include "../CanInterface.h"
#include <QTcpSocket>

class AsclCANWinServiceDriver;

typedef struct {
    uint32_t can_state;

    uint64_t rx_count;
    int rx_errors;
    uint64_t rx_overruns;

    uint64_t tx_count;
    int tx_errors;
    uint64_t tx_dropped;
} can_status_t;



class AsclCANWinServiceInterface: public CanInterface {
    Q_OBJECT
public:
    AsclCANWinServiceInterface(AsclCANWinServiceDriver *driver);
    virtual ~AsclCANWinServiceInterface();

    virtual QString getName() const;

    virtual QList<CanTiming> getAvailableBitrates();

    virtual void applyConfig(const MeasurementInterface &mi);

    virtual unsigned getBitrate();
    virtual uint32_t getCapabilities();


	virtual void open();
    virtual bool isOpen();
	virtual void close();

    virtual void sendMessage(const CanMessage &msg);
    virtual bool readMessage(QList<CanMessage> &msglist, unsigned int timeout_ms);

    virtual bool updateStatistics();
    virtual uint32_t getState();
    virtual int getNumRxFrames();
    virtual int getNumRxErrors();
    virtual int getNumRxOverruns();

    virtual int getNumTxFrames();
    virtual int getNumTxErrors();
    virtual int getNumTxDropped();

private:
    can_status_t _status;
    QTcpSocket* _socket = nullptr;
    QByteArray _rxBuffer;
};
