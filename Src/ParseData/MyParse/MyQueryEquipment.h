#ifndef MYQUERYEQUIPMENT_H
#define MYQUERYEQUIPMENT_H

class PersonInfo;

class CMyQueryEquipment
{
public:
    CMyQueryEquipment();

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
     * @brief ��ѯ���е�״̬
     */
    void QueryAll();
private:
    PersonInfo*         m_pPerson;
};

#endif // MYQUERYEQUIPMENT_H
