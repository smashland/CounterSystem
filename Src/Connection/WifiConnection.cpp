#include <QTcpSocket>

#include "../ConfigInfo.h"
#include "WifiConnection.h"

CWifiConnection::CWifiConnection(QObject *parent)
    :CConnection (parent)
    ,m_pTcp(new QTcpSocket(this))
{
    /// ���źźͲ�
    connect(m_pTcp,&QTcpSocket::readyRead,this,&CWifiConnection::ReciveData);
    connect(m_pTcp,&QTcpSocket::disconnected,this,&CConnection::disConnected);
    connect(m_pTcp,&QTcpSocket::connected,this,&CConnection::connected);
}

CWifiConnection::~CWifiConnection()
{
    m_pTcp->deleteLater();
}

/// ����
void CWifiConnection::Connect()
{
    m_pTcp->connectToHost(CConfigInfo::GetInstance()->GetIP().c_str(),CConfigInfo::GetInstance()->GetPort());
}

/// �Ͽ�����
void CWifiConnection::DisConnect()
{
    m_pTcp->abort();
    CConnection::DisConnect();
}

/// ��������
bool CWifiConnection::SendCommand(const QByteArray &rByteArray)
{
    static qint64 nSendSize;

    /// ֻ�����ӵ�����ʱ���ŷ�������
    if(m_bConnected)
    {
        nSendSize = m_pTcp->write(rByteArray);
        m_pTcp->flush();
        return(nSendSize == rByteArray.size());
    }

    return(false);
}

/// ��������
void CWifiConnection::ReciveData()
{
    if(m_pTcp->bytesAvailable() < 1)
    {
        return;
    }

    QByteArray temp = m_pTcp->readAll();
    InsertData(temp);
}
