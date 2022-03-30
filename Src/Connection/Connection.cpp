#include <QList>
#include "Connection.h"

/// ��������
CConnection::CConnection(QObject *parent)
    :QObject(parent),m_bConnected(false)
{
}

/// ��������
CConnection::~CConnection()
{
    if(m_bConnected)
    {
        DisConnect();
    }
}

/// ��ȡ����
const QByteArray &CConnection::GetData()
{
    static QByteArray s_emptyArray;

    s_emptyArray.clear();

    /// ����б��в�Ϊ��
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

/// �������
void CConnection::ClearData()
{
    m_listReciveInfo.clear();
}

/// ����
void CConnection::connected()
{
    m_bConnected = true;
    emit(connected2Center());
}

/// �Ͽ�����
void CConnection::disConnected()
{
    m_bConnected = false;
    emit(lostConnected2Center());
}

/// �����ݲ��뵽�б���
void CConnection::InsertData(const QByteArray &rData)
{
    m_listReciveInfo.push_back(rData);
}
