#pragma once

#include "../CanInterface.h"
#include <core/MeasurementInterface.h>
#include <QtNetwork/QUdpSocket>
#include <QTimer>
#include <QElapsedTimer>  // Qt replacement for timeval
#include <QDateTime>

class CANBlasterDriver;

typedef struct {
    bool supports_canfd;
    bool supports_timing;
    uint32_t state;
    uint32_t base_freq;
    uint32_t sample_point;
    uint32_t ctrl_mode;
    uint32_t restart_ms;
} can_config_t;

typedef struct {
    uint32_t can_state;
    uint64_t rx_count;
    int rx_errors;
    uint64_t rx_overruns;

    uint64_t tx_count;
    int tx_errors;
    uint64_t tx_dropped;
} can_status_t;

class CANBlasterInterface: public CanInterface {
public:
    CANBlasterInterface(CANBlasterDriver *driver, int index, QString name, bool fd_support);
    virtual ~CANBlasterInterface();

        QString getDetailsStr() const;
    virtual QString getName() const;
    void setName(QString name);

    virtual QList<CanTiming> getAvailableBitrates();
    virtual void applyConfig(const MeasurementInterface &mi);

    bool supportsTimingConfiguration();
    bool supportsCanFD();
    bool supportsTripleSampling();

    virtual unsigned getBitrate();
    virtual uint32_t getCapabilities();

    virtual void open();
    virtual void close();
    virtual bool isOpen();

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

    int getIfIndex();
```

    private:
              typedef enum {
                  ts_mode_SIOCSHWTSTAMP,
                  ts_mode_SIOCGSTAMPNS,
                  ts_mode_SIOCGSTAMP
              } ts_mode_t;

    ```
        int _idx;
    bool _isOpen;
    QString _name;

    MeasurementInterface _settings;

    can_config_t _config;
    can_status_t _status;
    ts_mode_t _ts_mode;

    // Qt replacement for timeval
    QElapsedTimer _heartbeat_timer;

    QUdpSocket* _socket;
    const char *cname();
    ```

};

/* Duplicated from Linux can.h for compilation on Windows. Not a great solution. */

/* special address description flags for the CAN_ID */
#define CAN_EFF_FLAG 0x80000000U /* EFF/SFF is set in the MSB */
#define CAN_RTR_FLAG 0x40000000U /* remote transmission request */
#define CAN_ERR_FLAG 0x20000000U /* error message frame */

/* valid bits in CAN ID for frame formats */
#define CAN_SFF_MASK 0x000007FFU /* standard frame format (SFF) */
#define CAN_EFF_MASK 0x1FFFFFFFU /* extended frame format (EFF) */
#define CAN_ERR_MASK 0x1FFFFFFFU /* omit EFF, RTR, ERR flags */

typedef uint32_t canid_t;

#define CAN_SFF_ID_BITS 11
#define CAN_EFF_ID_BITS 29
typedef uint32_t can_err_mask_t;

/* CAN payload length and DLC definitions */
#define CAN_MAX_DLC 8
#define CAN_MAX_RAW_DLC 15
#define CAN_MAX_DLEN 8
#define CANFD_MAX_DLC 15
#define CANFD_MAX_DLEN 64

struct can_frame {
    canid_t can_id;
    union {
        uint8_t len;
        uint8_t can_dlc; /* deprecated */
    } **attribute**((packed));
    uint8_t __pad;
    uint8_t __res0;
    uint8_t len8_dlc;
    uint8_t data[CAN_MAX_DLEN] **attribute**((aligned(8)));
};

#define CANFD_BRS 0x01
#define CANFD_ESI 0x02
#define CANFD_FDF 0x04

struct canfd_frame {
    canid_t can_id;
    uint8_t len;
    uint8_t flags;
    uint8_t __res0;
    uint8_t __res1;
    uint8_t data[CANFD_MAX_DLEN] **attribute**((aligned(8)));
};

#define CAN_MTU  sizeof(struct can_frame)
#define CANFD_MTU sizeof(struct canfd_frame)
