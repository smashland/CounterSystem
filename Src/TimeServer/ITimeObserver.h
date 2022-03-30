#ifndef ITIMEOBSERVER_H
#define ITIMEOBSERVER_H
/********************************
 * ���ڶ���ʱ��
 ********************************/

#include <QDateTime>

class ITimeObserver
{
public:
    virtual ~ITimeObserver(){}

    /**
     * @brief ��ȡ��ǰʱ��
     * @param rDateTime
     */
    virtual void UpdateTime(const QDateTime&){}

    /**
     * @brief ��������ڿ�ʼʱ�������
     * @param nSeconds
     */
    virtual void UpdateSeconds(const quint16&){}

    /**
     * @brief ���·���ʱ��
     */
    virtual void UpdateSimulationTime(const quint16&){}
};
#endif // ITIMEOBSERVER_H
