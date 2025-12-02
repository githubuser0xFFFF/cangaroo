#include "CanMessage.h"
#include <QtEndian>        // replacement for portable_endian
#include <QDateTime>

enum {
    id_flag_extended = 0x80000000,
    id_flag_rtr      = 0x40000000,
    id_flag_error    = 0x20000000,
    id_mask_extended = 0x1FFFFFFF,
    id_mask_standard = 0x7FF
};

CanMessage::CanMessage()
  : _raw_id(0), _dlc(0), _isFD(false), _isBRS(false),
    _interface(0), _timestamp_usec(0)
{
    // data array already zero-initialized
}

CanMessage::CanMessage(uint32_t can_id)
  : _dlc(0), _isFD(false), _isBRS(false),
    _interface(0), _timestamp_usec(0)
{
    setId(can_id);
}

CanMessage::CanMessage(const CanMessage &msg)
{
    cloneFrom(msg);
}

void CanMessage::cloneFrom(const CanMessage &msg)
{
    _raw_id = msg._raw_id;
    _dlc = msg._dlc;
    _isFD = msg._isFD;
    _isBRS = msg._isBRS;

    for (int i = 0; i < 64; i++)
        _u8[i] = msg._u8[i];

    _interface = msg._interface;
    _timestamp_usec = msg._timestamp_usec;
}

/* --- ID functions (unchanged) -------------------------------------------- */

uint32_t CanMessage::getRawId() const {
    return _raw_id;
}

void CanMessage::setRawId(const uint32_t raw_id) {
    _raw_id = raw_id;
}

uint32_t CanMessage::getId() const {
    return isExtended() ? (_raw_id & id_mask_extended)
                        : (_raw_id & id_mask_standard);
}

void CanMessage::setId(const uint32_t id) {
    _raw_id &= ~id_mask_extended;
    _raw_id = id;
    if (id > 0x7FF) setExtended(true);
}

bool CanMessage::isExtended() const {
    return (_raw_id & id_flag_extended) != 0;
}

void CanMessage::setExtended(const bool isExtended) {
    if (isExtended) _raw_id |= id_flag_extended;
    else            _raw_id &= ~id_flag_extended;
}

bool CanMessage::isRTR() const {
    return (_raw_id & id_flag_rtr) != 0;
}

void CanMessage::setRTR(const bool isRTR) {
    if (isRTR) _raw_id |= id_flag_rtr;
    else       _raw_id &= ~id_flag_rtr;
}

bool CanMessage::isFD() const { return _isFD; }
void CanMessage::setFD(const bool isFD) { _isFD = isFD; }

bool CanMessage::isBRS() const { return _isBRS; }
void CanMessage::setBRS(const bool isBRS) { _isBRS = isBRS; }

bool CanMessage::isErrorFrame() const {
    return (_raw_id & id_flag_error) != 0;
}

void CanMessage::setErrorFrame(const bool isErrorFrame) {
    if (isErrorFrame) _raw_id |= id_flag_error;
    else              _raw_id &= ~id_flag_error;
}

CanInterfaceId CanMessage::getInterfaceId() const {
    return _interface;
}

void CanMessage::setInterfaceId(CanInterfaceId interface) {
    _interface = interface;
}

/* --- Data access ----------------------------------------------------------- */

uint8_t CanMessage::getLength() const {
    return _dlc;
}

void CanMessage::setLength(const uint8_t dlc) {
    _dlc = (dlc <= 64) ? dlc : 8;
}

uint8_t CanMessage::getByte(const uint8_t index) const {
    return (index < sizeof(_u8)) ? _u8[index] : 0;
}

void CanMessage::setByte(const uint8_t index, const uint8_t value) {
    if (index < sizeof(_u8)) _u8[index] = value;
}

/* --- Extract CAN signal ---------------------------------------------------- */

uint64_t CanMessage::extractRawSignal(uint8_t start_bit,
                                      const uint8_t length,
                                      const bool isBigEndian) const
{
    uint64_t data = qFromLittleEndian<quint64>(_u64[0]);  // replaces le64toh

    data >>= start_bit;

    uint64_t mask = 0xFFFFFFFFFFFFFFFFULL;
    mask <<= length;
    mask = ~mask;

    data &= mask;

    // Big-endian multi-byte signal handling
    if (isBigEndian && (length > 8)) {
        data = qbswap(data);         // replaces __builtin_bswap64
        data >>= (64 - length);
    }

    return data;
}

/* --- Data setters ---------------------------------------------------------- */

void CanMessage::setDataAt(uint8_t position, uint8_t data) {
    if (position < 64)
        _u8[position] = data;
}

void CanMessage::setData(const uint8_t d0) {
    _dlc = 1; _u8[0] = d0;
}

void CanMessage::setData(const uint8_t d0, const uint8_t d1) {
    _dlc = 2; _u8[0] = d0; _u8[1] = d1;
}

void CanMessage::setData(const uint8_t d0, const uint8_t d1, const uint8_t d2) {
    _dlc = 3; _u8[0] = d0; _u8[1] = d1; _u8[2] = d2;
}

void CanMessage::setData(const uint8_t d0, const uint8_t d1,
                         const uint8_t d2, const uint8_t d3) {
    _dlc = 4;
    _u8[0] = d0; _u8[1] = d1; _u8[2] = d2; _u8[3] = d3;
}

void CanMessage::setData(const uint8_t d0, const uint8_t d1, const uint8_t d2,
                         const uint8_t d3, const uint8_t d4) {
    _dlc = 5;
    _u8[0] = d0; _u8[1] = d1; _u8[2] = d2; _u8[3] = d3; _u8[4] = d4;
}

void CanMessage::setData(const uint8_t d0, const uint8_t d1, const uint8_t d2,
                         const uint8_t d3, const uint8_t d4, const uint8_t d5) {
    _dlc = 6;
    _u8[0] = d0; _u8[1] = d1; _u8[2] = d2; _u8[3] = d3; _u8[4] = d4; _u8[5] = d5;
}

void CanMessage::setData(const uint8_t d0, const uint8_t d1, const uint8_t d2,
                         const uint8_t d3, const uint8_t d4, const uint8_t d5,
                         const uint8_t d6) {
    _dlc = 7;
    _u8[0] = d0; _u8[1] = d1; _u8[2] = d2; _u8[3] = d3;
    _u8[4] = d4; _u8[5] = d5; _u8[6] = d6;
}

void CanMessage::setData(const uint8_t d0, const uint8_t d1, const uint8_t d2,
                         const uint8_t d3, const uint8_t d4, const uint8_t d5,
                         const uint8_t d6, const uint8_t d7) {
    _dlc = 8;
    _u8[0] = d0; _u8[1] = d1; _u8[2] = d2; _u8[3] = d3;
    _u8[4] = d4; _u8[5] = d5; _u8[6] = d6; _u8[7] = d7;
}

/* --- Timestamp (Qt-based) -------------------------------------------------- */

quint64 CanMessage::getTimestampUsec() const {
    return _timestamp_usec;
}

void CanMessage::setTimestampUsec(quint64 usec) {
    _timestamp_usec = usec;
}

void CanMessage::setTimestamp(quint64 seconds, uint32_t micro_seconds)
{
    _timestamp_usec = seconds * 1000000ULL + micro_seconds;
}

double CanMessage::getFloatTimestamp() const
{
    return static_cast<double>(_timestamp_usec) / 1e6;
}

QDateTime CanMessage::getDateTime() const
{
    qint64 ms = static_cast<qint64>(_timestamp_usec / 1000);
    int us_rem = static_cast<int>(_timestamp_usec % 1000);

    // Qt does not support microseconds in QDateTime directly,
    // but this keeps millisecond precision intact.
    QDateTime dt = QDateTime::fromMSecsSinceEpoch(ms, Qt::UTC);

    // If you want: dt = dt.addMSecs(us_rem / 1000.0);
    // but that would change full precision due to rounding.

    return dt;
}

/* --- String output --------------------------------------------------------- */

QString CanMessage::getIdString() const
{
    if (isExtended())
        return QString().sprintf("0x%08X", getId());
    else
        return QString().sprintf("0x%03X", getId());
}

QString CanMessage::getDataHexString() const
{
    if (getLength() == 0)
        return "";

    QString outstr;
    for (int i = 0; i < getLength(); i++) {
        outstr += QString().sprintf("%02X ", getByte(i));
    }
    return outstr;
}
