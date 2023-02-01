#include "../AppGlobal.h"
#include "SpeakText.h"
#include "PlayMp3.h"
#include "NoticeManager.h"


CNoticeManager *CNoticeManager::GetInstance()
{
    static CNoticeManager s_NoticeManager;
    return(&s_NoticeManager);
}

void CNoticeManager::SetGroupId(int typeId)
{
    m_pGLobal->setGroupId(typeId);
}

void CNoticeManager::SetColor(int typeId, QString color)
{
    m_pGLobal->setGroupC(typeId,color);
}

/// 设置通信信息
void CNoticeManager::SetNoticInfo(const QString &sNoticeInfo)
{
    /// 开启播报则播放声音
    if(m_bOpenSpeak)
    {
        m_pSpeak->SpeakText(sNoticeInfo);
    }

    /// 开启面板显示
    if(m_bShowBoard)
    {
        m_pGLobal->updateNotic(sNoticeInfo);
    }
}

/// 设置语音播报
bool CNoticeManager::OpenSpeak(bool bOpen)
{
    if(m_bOpenSpeak != bOpen)
    {
        if(m_bOpenSpeak)
        {
            m_bOpenSpeak = bOpen;
        }
        else
        {
            m_bOpenSpeak = m_pSpeak->Init();
        }
    }

    /// 返回开启状态
    return(m_bOpenSpeak);
}

/// 设置声音大小
void CNoticeManager::SetVolume(double dVolume)
{
    m_pSpeak->SetVolume(dVolume);
    m_pPlay->SetVolume(dVolume);
}

/// 是否显示布告板
void CNoticeManager::ShowNoticeBoard(bool bShow)
{
    if(m_bShowBoard != bShow)
    {
        m_bShowBoard = bShow;
    }
}

/// 移动位置
void CNoticeManager::MoveBoardPos(int nX, int nY)
{
}

void CNoticeManager::SetGlobal(QAppGlobal *pGlobal)
{
    m_pGLobal = pGlobal;
}

/// 播放声音
void CNoticeManager::PlaySound(int nIndex)
{
    if(m_bOpenSpeak)
    {
        m_pPlay->Play(nIndex);
    }
}

/// 初始化
CNoticeManager::CNoticeManager()
{
    m_pSpeak = new CSpeakText;
    m_pPlay = new CPlayMp3;
    m_pSpeak->Init();
}

/// 析构
CNoticeManager::~CNoticeManager()
{
    delete m_pSpeak;
    delete m_pPlay;
}
