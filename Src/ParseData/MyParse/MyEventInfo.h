#ifndef MYEVENTINFO_H
#define MYEVENTINFO_H

#include <QMap>
class PersonInfo;


class CMyEventInfo
{
public:
    CMyEventInfo();

    /**
     * @brief ����ID
     * @param crAddr
     */
    void SetPerson(PersonInfo* pPerson);

    /**
     * @brief ����״̬��Ϣ
     * @param pData
     * @param nLength
     */
    void Update(const unsigned char* pData, int nLength);

    /**
     * @brief ����¼�״̬
     */
    void ClearEventStatus();
protected:

    /**
     * @brief �����¼�ID��ִ
     * @param nEventID
     */
    void SendEventBack(quint16 unID, quint16 unEventID);

    /**
     * @brief �Ƿ��������λ��
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
