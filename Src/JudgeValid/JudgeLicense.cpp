#include <QGuiApplication>
#include <QDate>
#include "GetMachineInfo.h"
#include "../md5.h"
#include "../API-CRCheck.h"

#include "JudgeLicense.h"
const static QString S_LIC_NONE = QString::fromUtf8("没有许可文件");
const static QString S_INVALID_MACHINE = QString::fromUtf8("不是本机的许可");
const static QString S_INVALID = QString::fromUtf8("不是有效的许可");
const static QString S_OUT_RANGE = QString::fromUtf8("超出时间范围");
const static QString S_CANT_WRITE = QString::fromUtf8("无法保存许可");

QJudgeLicense::QJudgeLicense(QQuickItem *parent)
    :QQuickItem (parent)
    ,m_bGet(false)
{
    QFile licFile(QGuiApplication::applicationDirPath() + "/lic");
    if(licFile.open(QIODevice::ReadOnly|QIODevice::Text))
    {
        m_sLicInfo = licFile.readAll();
    }
}

/// 析构
QJudgeLicense::~QJudgeLicense()
{
    int n=0;
    ++n;
}

/// 检查是否有许可
void QJudgeLicense::checkLicense()
{
    if(!m_bGet)
    {
        getMachineInfo();
    }

    if(m_sLicInfo.size() < 1)
    {
        m_sErrorInfo = S_LIC_NONE;
        emit(showError(m_sErrorInfo));
    }
    else
    {
        if(!checkLicense(m_sLicInfo))
        {
           emit(showError(m_sErrorInfo));
        }
        else
        {
            emit(checked());
        }
    }

}

void QJudgeLicense::saveLicense(const QByteArray &sLicInfo)
{
    if(!m_bGet)
    {
        getMachineInfo();
    }

    if(!checkLicense(sLicInfo))
    {
        emit(showError(m_sErrorInfo));
    }
    else
    {
        QFile licFile(QGuiApplication::applicationDirPath() + "/lic");
        if(licFile.open(QIODevice::WriteOnly|QIODevice::Text))
        {
            licFile.write(sLicInfo);
            m_sLicInfo = sLicInfo;
            emit(checked());
        }
        else
        {
            m_sErrorInfo = S_CANT_WRITE;
            emit(showError(m_sErrorInfo));
        }
    }
}

/// 获取md5加密后的文件
QString QJudgeLicense::getMD5MachineInfo()
{
    if(!m_bGet)
    {
        getMachineInfo();
    }

    return(m_sMachineInfo.c_str());
}

/// 获取机器信息
void QJudgeLicense::getMachineInfo()
{
    if(!CGetMachineInfo::GetInstance()->IsInit())
    {
        CGetMachineInfo::GetInstance()->Init();
    }

    QString sMachineInfo=CGetMachineInfo::GetInstance()->GetCpuID();

    sMachineInfo += CGetMachineInfo::GetInstance()->GetHDSN();

    foreach(QString sTemp,CGetMachineInfo::GetInstance()->GetMacInfo())
    {
        sMachineInfo += sTemp;
    }



    MD5 tmpMD5(sMachineInfo.toStdString());

    m_sMachineInfo = tmpMD5.toString();
    m_bGet = true;
}

/// 检查许可是否有效
bool QJudgeLicense::checkLicense(const QByteArray& sLicInfo)
{
    QByteArray array = QByteArray::fromHex(sLicInfo);

    if(14 != array.length())
    {
        m_sErrorInfo = S_INVALID_MACHINE;
        return(false);
    }

    quint16 unCRC = CRC16RTU(reinterpret_cast<const uchar*>(m_sMachineInfo.c_str()),m_sMachineInfo.length());

    const char* pBuffer = array.data();
    quint16 unCheck = *(reinterpret_cast<const quint16*>(pBuffer));
    pBuffer += sizeof(unCheck);

    if(unCRC != unCheck)
    {
        m_sErrorInfo = S_INVALID_MACHINE;
        return(false);
    }
    else
    {
        qint64 nDays = QDate::fromJulianDay(*reinterpret_cast<const qint64*>(pBuffer)).daysTo(QDate::currentDate());

        qint64 nLicDays=-1;
        pBuffer += sizeof(nDays);
        switch (*pBuffer++)
        {
        case 0:   /// 长期有效
            nLicDays = _I64_MAX;
            break;
        case 1:   /// 年
            nLicDays = static_cast<int>(*reinterpret_cast<const uchar*>(pBuffer) * 365.25);
            break;
        case 2:   /// 月
            nLicDays = *reinterpret_cast<const uchar*>(pBuffer) * 30;
            break;
        case 3:   /// 日
            nLicDays = *reinterpret_cast<const uchar*>(pBuffer);
            break;
        default:
            m_sErrorInfo = S_INVALID;
            return(false);
        }

        if(nDays < 0 || nLicDays < 0 || nDays > nLicDays)
        {
            m_sErrorInfo = S_OUT_RANGE;
            return(false);
        }
        ++pBuffer;

        unCheck = *reinterpret_cast<const quint16*>(pBuffer);
        unCRC = CRC16RTU(reinterpret_cast<const uchar*>(array.data()),12);
        if(unCRC == unCheck)
        {
            return(true);
        }
        else
        {
            m_sErrorInfo = S_INVALID;
            return(false);
        }

    }
}
