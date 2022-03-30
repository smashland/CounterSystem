#include <QList>
#include "ConnectionManager.h"
#include "WifiConnection.h"
#include "SerialConnection.h"
#include "../ErrorReport.h"
static QString S_SEND = QString::fromLocal8Bit("����:");
/// ���ӹ����൥��ָ��
CConnectionManager *CConnectionManager::GetInstance()
{
    static CConnectionManager s_connectionManager;
    return(&s_connectionManager);
}

/// ����
void CConnectionManager::Connect()
{
    if(nullptr != m_pConnection)
    {
        m_pConnection->Connect();
    }

}

/// �Ͽ�����
void CConnectionManager::DisConnect()
{
    if(nullptr != m_pConnection)
    {
       m_pConnection->DisConnect();
    }
}

/// ��������
bool CConnectionManager::InitConnection(CONN_TYPE emType)
{
    /// ��������Ѿ�����
    if(nullptr != m_pConnection)
    {
        delete m_pConnection;
        m_pConnection = nullptr;
    }

    switch (emType)
    {
    case WIFI:
        m_emType = WIFI;
        m_pConnection = new CWifiConnection(this);
        break;
    case SERIAL:
        m_emType = SERIAL;
        m_pConnection = new CControlSerial(this);
        break;
    default:
        m_emType = CONN_UNUSE;
        break;
    }

    if(nullptr != m_pConnection)
    {
        connect(m_pConnection,&CConnection::connected2Center,this,&CConnectionManager::conected);
        connect(m_pConnection,&CConnection::lostConnected2Center,this,&CConnectionManager::disConnected);
        return(true);
    }
    else
    {
        return(false);
    }
}

/// �Ƿ��ʼ��
bool CConnectionManager::IsInit()
{
    return(nullptr != m_pConnection);
}

/// ��ȡ���µ�������Ϣ
const QByteArray &CConnectionManager::GetData()
{
    static QByteArray s_ByteArray;
    if(nullptr != m_pConnection)
    {
        return(m_pConnection->GetData());
    }
    else
    {
        return(s_ByteArray);
    }
}

/// ��������
bool CConnectionManager::SendData(const QByteArray &rSendInfo)
{
    if(nullptr != m_pConnection)
    {
        CErrorReport::GetInstance()->writeError(S_SEND+rSendInfo.toHex().toUpper());
        return(m_pConnection->SendCommand(rSendInfo));
    }
    else
    {
        return(false);
    }
}

/// �Ƿ�������״̬
bool CConnectionManager::IsConnect()
{
    if(nullptr != m_pConnection)
    {
        return(m_pConnection->IsConnect());
    }
    else
    {
        return(false);
    }
}

void CConnectionManager::ClearData()
{
    m_pConnection->ClearData();
}


/// ���ӹ�����
CConnectionManager::CConnectionManager():
    m_pConnection(nullptr),
    m_emType(CONN_UNUSE)
{
}

/// ����
CConnectionManager::~CConnectionManager()
{
    if(nullptr != m_pConnection)
     {
        delete m_pConnection;
    }
}
