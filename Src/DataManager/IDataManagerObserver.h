#ifndef _INTERFACE_DATA_MANAGER_OBSERVER_H_
#define _INTERFACE_DATA_MANAGER_OBSERVER_H_
/*****************************************************
 *  ���ݹ�����۲���
 *****************************************************/
#include "../CommonTypeDefine.h"

class IDataManagerObserver
{
public:
    virtual ~IDataManagerObserver(){}

    /**
     * @brief ֪ͨ�û���Ϣ����
     * @param unID
     */
    virtual void UpdateID(quint16){}

    /**
     * @brief ���������¼�
     */
    virtual void UpdateEvent(quint16){}
};
#endif ///_INTERFACE_DATA_MANAGER_OBSERVER_H_
