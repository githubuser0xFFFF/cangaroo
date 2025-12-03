#pragma once

#include <stdint.h>

#include <QString>
#include <QDateTime>
#include <driver/CanDriver.h>

class CanMessage {
public:
    CanMessage();
    CanMessage(uint32_t can_id);
    CanMessage(const CanMessage &msg);
    void cloneFrom(const CanMessage &msg);

    bool isTx() const;
    void setTx(bool Tx);

    uint32_t getRawId() const;
    void setRawId(const uint32_t raw_id);

    uint32_t getId() const;
    void setId(const uint32_t id);

    bool isExtended() const;
    void setExtended(const bool isExtended);

    bool isRTR() const;
    void setRTR(const bool isRTR);

    bool isFD() const;
    void setFD(const bool isFD);

    bool isBRS() const;
    void setBRS(const bool isFD);

    bool isErrorFrame() const;
    void setErrorFrame(const bool isErrorFrame);

    CanInterfaceId getInterfaceId() const;
    void setInterfaceId(CanInterfaceId interface);

    uint8_t getLength() const;
    void setLength(const uint8_t dlc);

    uint8_t getByte(const uint8_t index) const;
    void setByte(const uint8_t index, const uint8_t value);

    uint64_t extractRawSignal(uint8_t start_bit, const uint8_t length, const bool isBigEndian) const;

    void setDataAt(uint8_t position, uint8_t data);
    void setData(const uint8_t d0);
    void setData(const uint8_t d0, const uint8_t d1);
    void setData(const uint8_t d0, const uint8_t d1, const uint8_t d2);
    void setData(const uint8_t d0, const uint8_t d1, const uint8_t d2, const uint8_t d3);
    void setData(const uint8_t d0, const uint8_t d1, const uint8_t d2, const uint8_t d3, const uint8_t d4);
    void setData(const uint8_t d0, const uint8_t d1, const uint8_t d2, const uint8_t d3, const uint8_t d4, const uint8_t d5);
    void setData(const uint8_t d0, const uint8_t d1, const uint8_t d2, const uint8_t d3, const uint8_t d4, const uint8_t d5, const uint8_t d6);
    void setData(const uint8_t d0, const uint8_t d1, const uint8_t d2, const uint8_t d3, const uint8_t d4, const uint8_t d5, const uint8_t d6, const uint8_t d7);

    // Qt-based timestamp
    quint64 getTimestampUsec() const;
    void setTimestampUsec(quint64 usec);
    void setTimestamp(quint64 seconds, uint32_t micro_seconds);
    void setCurrentTimestamp();

    double getFloatTimestamp() const;     // seconds.microseconds format
    QDateTime getDateTime() const;

    QString getIdString() const;
    QString getDataHexString() const;

private:
    uint32_t _raw_id;
    uint8_t _dlc;
    bool _isFD;
    bool _isBRS;
    bool _isTx= false;
    CanInterfaceId _interface;
    union {
        uint8_t  _u8[8*8];
        uint16_t _u16[4*8];
        uint32_t _u32[2*8];
        uint64_t _u64[8];
    };

    // store microseconds since epoch instead of struct timeval
    quint64 _timestamp_usec;
};
