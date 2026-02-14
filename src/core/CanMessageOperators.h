#pragma once

#include "CanMessage.h"
#include <iostream>
#include <QDebug>
#include <QDateTime>

// Stream operator for std::cout and other std::ostream objects
inline std::ostream& operator<<(std::ostream& os, const CanMessage& msg)
{
    QDateTime dt = QDateTime::currentDateTime();
    QString timestamp = QString("[%1:%2.%3] ")
                           .arg(dt.time().minute(), 2, 10, QChar('0'))
                           .arg(dt.time().second(), 2, 10, QChar('0'))
                           .arg(dt.time().msec(), 3, 10, QChar('0'));
    
    os << timestamp.toStdString() << msg.toString().toStdString();
    return os;
}

// Stream operator for qDebug() and other QDebug objects
inline QDebug operator<<(QDebug debug, const CanMessage& msg)
{
    QDateTime dt = QDateTime::currentDateTime();
    QString timestamp = QString("[%1:%2.%3] ")
                           .arg(dt.time().minute(), 2, 10, QChar('0'))
                           .arg(dt.time().second(), 2, 10, QChar('0'))
                           .arg(dt.time().msec(), 3, 10, QChar('0'));
    
    debug.nospace() << timestamp << msg.toString();
    return debug.maybeSpace();
}