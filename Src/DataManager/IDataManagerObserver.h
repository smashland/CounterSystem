#ifndef _INTERFACE_DATA_MANAGER_OBSERVER_H_
#define _INTERFACE_DATA_MANAGER_OBSERVER_H_
/*****************************************************
 *  数据管理类观察者
 *****************************************************/
#include "../CommonTypeDefine.h"

class IDataManagerObserver
{
public:
    virtual ~IDataManagerObserver(){}

    /**
     * @brief 通知用户信息更改
     * @param unID
     */
    virtual void UpdateID(quint16){}

    /**
     * @brief 更新命中事件
     */
    virtual void UpdateEvent(quint16){}
};
#endif ///_INTERFACE_DATA_MANAGER_OBSERVER_H_
