#ifndef MYEVENTINFO_H
#define MYEVENTINFO_H

#include <QMap>
class PersonInfo;


class CMyEventInfo
{
public:
    CMyEventInfo();

    /**
     * @brief 设置ID
     * @param crAddr
     */
    void SetPerson(PersonInfo* pPerson);

    /**
     * @brief 更新状态信息
     * @param pData
     * @param nLength
     */
    void Update(const unsigned char* pData, int nLength);

    /**
     * @brief 清空事件状态
     */
    void ClearEventStatus();
protected:

    /**
     * @brief 发送事件ID回执
     * @param nEventID
     */
    void SendEventBack(quint16 unID, quint16 unEventID);

    /**
     * @brief 是否可以设置位置
     * @return
     */
    bool CanSetPos();
private:
    PersonInfo* m_pPerson;
    QMap<quint16,quint16> m_mapEvent;
    int                   m_nIndex=0;
    double                m_dLon;
    double                m_dLat;
    double                m_dAllLon[10];
    double                m_dAllLat[10];
};

#endif // MYEVENTINFO_H
