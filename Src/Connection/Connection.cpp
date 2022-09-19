#include <QList>
#include "Connection.h"

/// 发送命令
CConnection::CConnection(QObject *parent)
    :QObject(parent),m_bConnected(false)
{
}

/// 析构连接
CConnection::~CConnection()
{
    if(m_bConnected)
    {
        DisConnect();
    }
}

/// 获取数据
const QByteArray &CConnection::GetData()
{
    static QByteArray s_emptyArray;

    s_emptyArray.clear();

    /// 如果列表中不为空
    if(!m_listReciveInfo.isEmpty())
    {
         s_emptyArray = m_listReciveInfo.front();
         m_listReciveInfo.pop_front();
    }

    return(s_emptyArray);
}

void CConnection::DisConnect()
{
    disConnected();
}

/// 清空数据
void CConnection::ClearData()
{
    m_listReciveInfo.clear();
}

/// 连接
void CConnection::connected()
{
    m_bConnected = true;
    emit(connected2Center());
}

/// 断开连接
void CConnection::disConnected()
{
    m_bConnected = false;
    emit(lostConnected2Center());
}

/// 将数据插入到列表里
void CConnection::InsertData(const QByteArray &rData)
{
    m_listReciveInfo.push_back(rData);
}
