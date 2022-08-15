#ifndef TIMESERVER_H
#define TIMESERVER_H

#include <QObject>
#include <QSet>
#include "ITimeObserver.h"

class CTimeServer:public QObject
{
    Q_OBJECT
public:
    /**
     * @brief 获取时间服务的单例
     * @return
     */
    static CTimeServer* GetInstance();

    /**
     * @brief 设置定时器的时间间隔
     * @param nMiSceond
     */
    void SetInterval(int nMiSceond);
    int  GetInterval(){return(m_nInterval);}

    /**
     * @brief 订阅消息
     * @param pObserver
     */
    void SubTime(ITimeObserver* pObserver);

    /**
     * @brief 取消订阅
     * @param pObserver
     */
    void UnSubTime(ITimeObserver* pObserver);

    /**
     * @brief 开始发布时间
     */
    void Start();

    /**
     * @brief 停止发布时间
     */
    void Stop();

    /**
     * @brief 获取定时器是否开启
     * @return
     */
    bool IsStart();

    /**
     * @brief 重置仿真时间
     */
    void ResetSimTime();

    /**
     * @brief 演习开始
     */
    void SimuStart();
    void SimuPause();
    void SimuEnd();
    void SetSimuEndTime(quint16 uEndTime);
    void SetSimuTime(quint16 uSimuTime);

protected:
    void timerEvent(QTimerEvent* event);

private:
    CTimeServer();
    ~CTimeServer();

private:
    QSet<ITimeObserver*> m_setObserver; /// 订阅到时间的服务器

    int                  m_nTimerID;    /// 定时器ID
    int                  m_nInterval;   /// 定时器间隔
    quint16              m_unSimuSecond;/// 仿真时间
    quint16              m_unSimuEnd;   /// 仿真结束时间
    bool                 m_bSimStart;   /// 仿真开始时间
};

#endif // TIMESERVER_H
