#ifndef ITIMEOBSERVER_H
#define ITIMEOBSERVER_H
/********************************
 * 用于订阅时间
 ********************************/

#include <QDateTime>

class ITimeObserver
{
public:
    virtual ~ITimeObserver(){}

    /**
     * @brief 获取当前时间
     * @param rDateTime
     */
    virtual void UpdateTime(const QDateTime&){}

    /**
     * @brief 更新相对于开始时间的秒数
     * @param nSeconds
     */
    virtual void UpdateSeconds(const quint16&){}

    /**
     * @brief 更新仿真时间
     */
    virtual void UpdateSimulationTime(const quint16&){}
};
#endif // ITIMEOBSERVER_H
