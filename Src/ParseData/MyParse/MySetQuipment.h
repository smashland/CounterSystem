#ifndef MYSETQUIPMENT_H
#define MYSETQUIPMENT_H

#include <QStringList>
#include <QVariant>
#include "MyParsetype.h"

class PersonInfo;
/**
 * @brief 对设备进行设置
 */
class CMySetQuipment
{
public:
    CMySetQuipment();

    /**
     * @brief 设置ID
     * @param crAddr
     */
    void SetPerson(PersonInfo* pPerson);

    /**
     * @brief 设置命令
     */
    void SendCommand(quint16 unID, SET_CMD typeCommand, const QVariant &allInfo);

    /**
     * @brief 更新状态信息
     * @param pData
     * @param nLength
     */
    void Update(const uchar *pData, int nLength);

    /**
     * @brief 更新
     * @param nSeconds
     */
    void UpdateSeconds(const quint16 &nSeconds);

protected:
    /**
     * @brief 处理信息
     * @param unID
     * @param typeCommand
     * @param allInfo
     */
    void DealInfo(SET_CMD typeCommand, const QVariant &allInfo);

private:
    struct CMD_INFO
    {
        SET_CMD  cmdType;/// 命令类型
        QVariant info;   /// 命令具体内容
        qint16   nTime=0;  /// 命令下发的时间
    };

    typedef QMap<quint16,CMD_INFO> ID2CMD;
    ID2CMD  m_mapSendInfo;
    PersonInfo* m_pCurrentPerson;/// 用户的ID
};

#endif // MYSETQUIPMENT_H
