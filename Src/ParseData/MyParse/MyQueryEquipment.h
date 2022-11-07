#ifndef MYQUERYEQUIPMENT_H
#define MYQUERYEQUIPMENT_H

class PersonInfo;

class CMyQueryEquipment
{
public:
    CMyQueryEquipment();

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
     * @brief 查询所有的状态
     */
    void QueryAll();
private:
    PersonInfo*         m_pPerson;
};

#endif // MYQUERYEQUIPMENT_H
