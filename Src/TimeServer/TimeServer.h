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
     * @brief ��ȡʱ�����ĵ���
     * @return
     */
    static CTimeServer* GetInstance();

    /**
     * @brief ���ö�ʱ����ʱ����
     * @param nMiSceond
     */
    void SetInterval(int nMiSceond);
    int  GetInterval(){return(m_nInterval);}

    /**
     * @brief ������Ϣ
     * @param pObserver
     */
    void SubTime(ITimeObserver* pObserver);

    /**
     * @brief ȡ������
     * @param pObserver
     */
    void UnSubTime(ITimeObserver* pObserver);

    /**
     * @brief ��ʼ����ʱ��
     */
    void Start();

    /**
     * @brief ֹͣ����ʱ��
     */
    void Stop();

    /**
     * @brief ��ȡ��ʱ���Ƿ���
     * @return
     */
    bool IsStart();

    /**
     * @brief ���÷���ʱ��
     */
    void ResetSimTime();

    /**
     * @brief ��ϰ��ʼ
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
    QSet<ITimeObserver*> m_setObserver; /// ���ĵ�ʱ��ķ�����

    int                  m_nTimerID;    /// ��ʱ��ID
    int                  m_nInterval;   /// ��ʱ�����
    quint16              m_unSimuSecond;/// ����ʱ��
    quint16              m_unSimuEnd;   /// �������ʱ��
    bool                 m_bSimStart;   /// ���濪ʼʱ��
};

#endif // TIMESERVER_H
