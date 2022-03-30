#ifndef CCOMMON_BASE_H
#define CCOMMON_BASE_H

#include <QMap>
#include <QByteArray>
#include <QVector>

/// 装备地址结构体
struct stAddr
{
    stAddr():cHigh(0),cLow(0)
    {
    }

    stAddr(const stAddr& rOther)
    {
        if(this->operator !=(rOther))
        {
            this->cHigh = rOther.cHigh;
            this->cLow  = rOther.cLow;
        }
    }

    bool operator ==(const stAddr& crAddr) const
    {
        return(cHigh == crAddr.cHigh && cLow == crAddr.cLow);
    }

    bool operator !=(const stAddr& crAddr) const
    {
        return !(this->operator ==(crAddr));
    }

    /// 获取字节数组
    operator QByteArray() const
    {
        static QByteArray  tmpBytArry;

        tmpBytArry.resize(2);

        tmpBytArry[0] = static_cast<char>(cHigh);
        tmpBytArry[1] = static_cast<char>(cLow);

        return(tmpBytArry);
    }

    operator quint16() const
    {
        return(cHigh * 256 + cLow);
    }

    uchar cHigh;
    uchar cLow;
};
#endif // CCOMMON_BASE_H
