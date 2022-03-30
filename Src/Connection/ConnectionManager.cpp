#include <QList>
#include "ConnectionManager.h"
#include "WifiConnection.h"
#include "SerialConnection.h"
#include "../ErrorReport.h"
static QString S_SEND = QString::fromLocal8Bit("发送:");
/// 连接管理类单例指针
CConnectionManager *CConnectionManager::GetInstance()
{
    static CConnectionManager s_connectionManager;
    return(&s_connectionManager);
}

/// 连接
void CConnectionManager::Connect()
{
    if(nullptr != m_pConnection)
    {
        m_pConnection->Connect();
    }

}

/// 断开连接
void CConnectionManager::DisConnect()
{
    if(nullptr != m_pConnection)
    {
       m_pConnection->DisConnect();
    }
}

/// 创建链接
bool CConnectionManager::InitConnection(CONN_TYPE emType)
{
    /// 如果连接已经存在
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

/// 是否初始化
bool CConnectionManager::IsInit()
{
    return(nullptr != m_pConnection);
}

/// 获取最新的数据信息
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

/// 发送数据
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

/// 是否处于连接状态
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


/// 连接管理类
CConnectionManager::CConnectionManager():
    m_pConnection(nullptr),
    m_emType(CONN_UNUSE)
{
}

/// 析构
CConnectionManager::~CConnectionManager()
{
    if(nullptr != m_pConnection)
     {
        delete m_pConnection;
    }
}
