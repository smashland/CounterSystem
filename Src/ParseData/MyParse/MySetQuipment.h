#ifndef MYSETQUIPMENT_H
#define MYSETQUIPMENT_H

#include <QStringList>
#include <QVariant>
#include "MyParsetype.h"

class PersonInfo;
/**
 * @brief ���豸��������
 */
class CMySetQuipment
{
public:
    CMySetQuipment();

    /**
     * @brief ����ID
     * @param crAddr
     */
    void SetPerson(PersonInfo* pPerson);

    /**
     * @brief ��������
     */
    void SendCommand(quint16 unID, SET_CMD typeCommand, const QVariant &allInfo);

    /**
     * @brief ����״̬��Ϣ
     * @param pData
     * @param nLength
     */
    void Update(const uchar *pData, int nLength);

    /**
     * @brief ����
     * @param nSeconds
     */
    void UpdateSeconds(const quint16 &nSeconds);

protected:
    /**
     * @brief ������Ϣ
     * @param unID
     * @param typeCommand
     * @param allInfo
     */
    void DealInfo(SET_CMD typeCommand, const QVariant &allInfo);

private:
    struct CMD_INFO
    {
        SET_CMD  cmdType;/// ��������
        QVariant info;   /// �����������
        qint16   nTime=0;  /// �����·���ʱ��
    };

    typedef QMap<quint16,CMD_INFO> ID2CMD;
    ID2CMD  m_mapSendInfo;
    PersonInfo* m_pCurrentPerson;/// �û���ID
};

#endif // MYSETQUIPMENT_H
