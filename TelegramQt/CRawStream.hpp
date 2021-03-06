/*
   Copyright (C) 2014-2017 Alexandr Akulich <akulichalexander@gmail.com>

   This file is a part of TelegramQt library.

   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

 */

#ifndef CRAWSTREAM_HPP
#define CRAWSTREAM_HPP

#include <QByteArray>

QT_FORWARD_DECLARE_CLASS(QIODevice)

class CRawStream
{
public:
    explicit CRawStream(QByteArray *data, bool write);
    explicit CRawStream(const QByteArray &data);

    explicit CRawStream(QIODevice *d = nullptr);

    virtual ~CRawStream();

    QIODevice *device() const { return m_device; }
    void setDevice(QIODevice *newDevice);
    void unsetDevice();

    bool error() const { return m_error; }
    void resetError();

    bool atEnd() const;
    int bytesAvailable() const;

    QByteArray readBytes(int count);

    QByteArray readAll();

    CRawStream &operator>>(qint8 &i);
    CRawStream &operator>>(qint16 &i);
    CRawStream &operator>>(qint32 &i);
    CRawStream &operator>>(qint64 &i);
    CRawStream &operator>>(quint8 &i);
    CRawStream &operator>>(quint16 &i);
    CRawStream &operator>>(quint32 &i);
    CRawStream &operator>>(quint64 &i);

    CRawStream &operator>>(double &d);

    CRawStream &operator<<(qint8 i);
    CRawStream &operator<<(qint16 i);
    CRawStream &operator<<(qint32 i);
    CRawStream &operator<<(qint64 i);
    CRawStream &operator<<(quint8 i);
    CRawStream &operator<<(quint16 i);
    CRawStream &operator<<(quint32 i);
    CRawStream &operator<<(quint64 i);

    CRawStream &operator<<(const double &d);

    CRawStream &operator<<(const QByteArray &data);

protected:
    bool read(void *data, qint64 size);
    bool write(const void *data, qint64 size);

    template<typename Int>
    inline CRawStream &protectedWrite(Int i);

    template<typename Int>
    inline CRawStream &protectedRead(Int &i);

private:
    QIODevice *m_device;
    bool m_ownDevice;
    bool m_error;

};

class CRawStreamEx : public CRawStream
{
public:
    explicit CRawStreamEx(QByteArray *data, bool write) :
        CRawStream(data, write)
    {
    }
    explicit CRawStreamEx(const QByteArray &data) :
        CRawStream(data)
    {
    }

    explicit CRawStreamEx(QIODevice *d = nullptr) :
        CRawStream(d)
    {
    }

    using CRawStream::operator <<;
    using CRawStream::operator >>;

    CRawStreamEx &operator>>(QByteArray &data);
    CRawStreamEx &operator<<(const QByteArray &data);

};

inline void CRawStream::resetError()
{
    m_error = false;
}

inline QByteArray CRawStream::readAll()
{
    return readBytes(bytesAvailable());
}

inline CRawStream &CRawStream::operator>>(quint8 &i)
{
    return *this >> reinterpret_cast<qint8&>(i);
}

inline CRawStream &CRawStream::operator>>(quint16 &i)
{
    return *this >> reinterpret_cast<qint16&>(i);
}

inline CRawStream &CRawStream::operator>>(quint32 &i)
{
    return *this >> reinterpret_cast<qint32&>(i);
}

inline CRawStream &CRawStream::operator>>(quint64 &i)
{
    return *this >> reinterpret_cast<qint64&>(i);
}

inline CRawStream &CRawStream::operator<<(quint8 i)
{
    return *this << qint8(i);
}

inline CRawStream &CRawStream::operator<<(quint16 i)
{
    return *this << qint16(i);
}

inline CRawStream &CRawStream::operator<<(quint32 i)
{
    return *this << qint32(i);
}

inline CRawStream &CRawStream::operator<<(quint64 i)
{
    return *this << qint64(i);
}

#endif // CRAWSTREAM_HPP
