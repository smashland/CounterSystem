#include <QTcpSocket>

#include "../ConfigInfo.h"
#include "WifiConnection.h"

CWifiConnection::CWifiConnection(QObject *parent)
    :CConnection (parent)
    ,m_pTcp(new QTcpSocket(this))
{
    /// 绑定信号和槽
    connect(m_pTcp,&QTcpSocket::readyRead,this,&CWifiConnection::ReciveData);
    connect(m_pTcp,&QTcpSocket::disconnected,this,&CConnection::disConnected);
    connect(m_pTcp,&QTcpSocket::connected,this,&CConnection::connected);
}

CWifiConnection::~CWifiConnection()
{
    m_pTcp->deleteLater();
}

/// 连接
void CWifiConnection::Connect()
{
    m_pTcp->connectToHost(CConfigInfo::GetInstance()->GetIP().c_str(),CConfigInfo::GetInstance()->GetPort());
}

/// 断开连接
void CWifiConnection::DisConnect()
{
    m_pTcp->abort();
    CConnection::DisConnect();
}

/// 发送数据
bool CWifiConnection::SendCommand(const QByteArray &rByteArray)
{
    static qint64 nSendSize;

    /// 只有连接到串口时，才发送数据
    if(m_bConnected)
    {
        nSendSize = m_pTcp->write(rByteArray);
        m_pTcp->flush();
        return(nSendSize == rByteArray.size());
    }

    return(false);
}

/// 接收数据
void CWifiConnection::ReciveData()
{
    if(m_pTcp->bytesAvailable() < 1)
    {
        return;
    }

    QByteArray temp = m_pTcp->readAll();
    InsertData(temp);
}
