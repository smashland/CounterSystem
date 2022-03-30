#include "ParseData.h"
uint CParseData::C_BUFFER_LENGTH(256);

CParseData::CParseData():
    m_bBegin(false)
{
    m_pBuffer = new uchar[C_BUFFER_LENGTH]();
}

/// �ͷſռ�
CParseData::~CParseData()
{
    delete []m_pBuffer;
}

/// Ĭ��ʵ��
bool CParseData::ParseData(const QByteArray &)
{
    return(false);
}

/// ������
void CParseData::UpdateSeconds(const quint16 &unSeconds)
{
    m_unSeconds = unSeconds;
}

/// ��ϰ��ʼ
void CParseData::AllStart()
{
    Clear();
}

void CParseData::AllStop()
{
}

/// ��ʼ��״̬
void CParseData::InitState()
{
    m_bBegin = true;
    m_nDataLength = -1;
    m_nNowLength = -1;
    m_nDataGet = 0;

    memset(m_pBuffer,0,C_BUFFER_LENGTH);
}
