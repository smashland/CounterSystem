#include <QTimerEvent>
#include <QElapsedTimer>

#include "TimeServer.h"

static QElapsedTimer s_ElapsedTimer;

/// 获取单例
CTimeServer *CTimeServer::GetInstance()
{
    static CTimeServer s_TimeServer;
    return(&s_TimeServer);
}

/// 设置定时器
void CTimeServer::SetInterval(int nMiSceond)
{
    if(nMiSceond != m_nInterval)
    {
        m_nInterval = nMiSceond < 0 ? 0 : nMiSceond;

        if(IsStart())
        {
            Stop();
            Start();
        }
    }
}

/// 订阅时间
void CTimeServer::SubTime(ITimeObserver *pObserver)
{
    m_setObserver.insert(pObserver);
}

/// 移除时间
void CTimeServer::UnSubTime(ITimeObserver *pObserver)
{
    m_setObserver.remove(pObserver);
}

/// 开启定时器
void CTimeServer::Start()
{
    if(0 == m_nTimerID)
    {
        m_nTimerID = startTimer(m_nInterval);
        s_ElapsedTimer.start();
    }
}

/// 关闭定时器
void CTimeServer::Stop()
{
    if(0 != m_nTimerID)
    {
        killTimer(m_nTimerID);
        s_ElapsedTimer.invalidate();
        m_nTimerID = 0;
    }
}

/// 判断是否开启定时器
bool CTimeServer::IsStart()
{
    return(0 != m_nTimerID);
}

void CTimeServer::ResetSimTime()
{
    s_ElapsedTimer.restart();
}

/// 开始仿真
void CTimeServer::SimuStart()
{
    m_unSimuSecond = 0;
    m_bSimStart = true;
}

void CTimeServer::SimuPause()
{
    m_bSimStart = !m_bSimStart;
}

void CTimeServer::SimuEnd()
{
    m_bSimStart = false;
}

void CTimeServer::SetSimuEndTime(quint16 uEndTime)
{
    m_unSimuEnd = uEndTime;
}

/// 设置仿真时间
void CTimeServer::SetSimuTime(quint16 uSimuTime)
{
    if(uSimuTime < m_unSimuEnd)
    {
        m_unSimuSecond = uSimuTime;
    }
}

/// 响应定时器消息
void CTimeServer::timerEvent(QTimerEvent* event)
{
    /// 定时发布时间信息
    static QDateTime s_tmpDateTime;
    static quint16 s_tmpSeconds1(0),s_tmpSeconds2(0);

    s_tmpDateTime = QDateTime::currentDateTime();
    if(m_nTimerID == event->timerId())
    {
        killTimer(m_nTimerID);

        for(ITimeObserver* pObserver : m_setObserver)
        {
            s_tmpSeconds2 = static_cast<quint16>(s_ElapsedTimer.elapsed() / 1000);
            pObserver->UpdateTime(s_tmpDateTime);
            if(s_tmpSeconds1 != s_tmpSeconds2)
            {
                pObserver->UpdateSeconds(s_tmpSeconds2);
            }
        }

        if(m_bSimStart && m_unSimuSecond < m_unSimuEnd)
        {
            if(s_tmpSeconds1 != s_tmpSeconds2)
            {
                ++m_unSimuSecond;
                for(ITimeObserver* pObserver : m_setObserver)
                {
                    pObserver->UpdateSimulationTime(m_unSimuSecond);
                }

            }
        }

        s_tmpSeconds1 = s_tmpSeconds2;


        m_nTimerID = startTimer(m_nInterval);
    }
}

/// 初始化定时器消息
CTimeServer::CTimeServer()
    : m_nTimerID(0)
    , m_nInterval(10)
    , m_unSimuSecond(0)
    , m_unSimuEnd(0)
    , m_bSimStart(false)
{
}

CTimeServer::~CTimeServer()
{
    Stop();
}
