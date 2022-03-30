#include "ParseData.h"
uint CParseData::C_BUFFER_LENGTH(256);

CParseData::CParseData():
    m_bBegin(false)
{
    m_pBuffer = new uchar[C_BUFFER_LENGTH]();
}

/// 释放空间
CParseData::~CParseData()
{
    delete []m_pBuffer;
}

/// 默认实现
bool CParseData::ParseData(const QByteArray &)
{
    return(false);
}

/// 更新秒
void CParseData::UpdateSeconds(const quint16 &unSeconds)
{
    m_unSeconds = unSeconds;
}

/// 演习开始
void CParseData::AllStart()
{
    Clear();
}

void CParseData::AllStop()
{
}

/// 初始化状态
void CParseData::InitState()
{
    m_bBegin = true;
    m_nDataLength = -1;
    m_nNowLength = -1;
    m_nDataGet = 0;

    memset(m_pBuffer,0,C_BUFFER_LENGTH);
}
