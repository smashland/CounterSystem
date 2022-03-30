#include <QNetworkInterface>
#include <QMap>
#include "GetMachineInfo.h"
#include "HardDriveSerialNumber.h"

/// ��ȡ������ַ
QStringList GetMac()
{
    QStringList strMac;

    QMap<QString,QString> allMacInfo;

    QString sHardwareAddress;
    /// ��ȡ����������Ϣ
    QList<QNetworkInterface> ifaces = QNetworkInterface::allInterfaces();

    foreach(QNetworkInterface iface, ifaces)
    {
        if(iface.name().contains("ethernet",Qt::CaseInsensitive) && !iface.humanReadableName().contains("vmware",Qt::CaseInsensitive))
        {
            sHardwareAddress = iface.hardwareAddress();
            if(!sHardwareAddress.isEmpty())
            {
                allMacInfo.insert(sHardwareAddress,sHardwareAddress);
            }
        }
    }

    if(allMacInfo.size() < 1)
    {
        foreach(QNetworkInterface iface, ifaces)
        {
            if(iface.name().contains("wireless",Qt::CaseInsensitive)&&iface.flags().testFlag(QNetworkInterface::IsUp))
            {
                sHardwareAddress = iface.hardwareAddress();
                if(!sHardwareAddress.isEmpty())
                {
                    allMacInfo.insert(sHardwareAddress,sHardwareAddress);
                }
            }
        }
    }
    strMac = allMacInfo.values();

    return(strMac);
}

/// ����
union ForTest
{
    uchar m_addr[2];
    quint16 m_short;
};

/// ��ȡ����
CGetMachineInfo *CGetMachineInfo::GetInstance()
{
    static CGetMachineInfo s_getMachineInfo;
    return(&s_getMachineInfo);
}

CGetMachineInfo::CGetMachineInfo():
    m_bInit(false),
    m_bIsBigEnd(false)
{
}

/// ��ʼ����Ϣ
void CGetMachineInfo::Init()
{
    if(m_bInit)
    {
        return;
    }

    m_listMacInfo = GetMac();

    CHardDriveSerialNumber tmpHardDrive;
    m_sCupID = tmpHardDrive.GetCPUID();
    m_sHardSN = tmpHardDrive.GetSerialNo();

    /// �жϴ�С��
    ForTest unionTest;
    unionTest.m_addr[1] = 0x01;
    if(0x01 == unionTest.m_short)
    {
        m_bIsBigEnd = true;
    }

    m_bInit = true;
}
