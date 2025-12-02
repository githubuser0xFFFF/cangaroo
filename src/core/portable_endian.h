#pragma once

#include <QtEndian>
#include <QtGlobal>
#include <QSysInfo>

// Helper macros matching the original API

#define htobe16(x)  qToBigEndian<quint16>(x)
#define htole16(x)  qToLittleEndian<quint16>(x)
#define be16toh(x)  qFromBigEndian<quint16>(x)
#define le16toh(x)  qFromLittleEndian<quint16>(x)

#define htobe32(x)  qToBigEndian<quint32>(x)
#define htole32(x)  qToLittleEndian<quint32>(x)
#define be32toh(x)  qFromBigEndian<quint32>(x)
#define le32toh(x)  qFromLittleEndian<quint32>(x)

#define htobe64(x)  qToBigEndian<quint64>(x)
#define htole64(x)  qToLittleEndian<quint64>(x)
#define be64toh(x)  qFromBigEndian<quint64>(x)
#define le64toh(x)  qFromLittleEndian<quint64>(x)

// Optional compatibility with the original defines:
#define __BYTE_ORDER    (QSysInfo::ByteOrder == QSysInfo::BigEndian ? __BIG_ENDIAN : __LITTLE_ENDIAN)
#define __BIG_ENDIAN    4321
#define __LITTLE_ENDIAN 1234
