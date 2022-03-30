#ifndef MYPARSEDATA_H
#define MYPARSEDATA_H

#include "ParseData.h"

class CMyQueryEquipment;
class CMySetQuipment;
class CMyEventInfo;
class PersonInfo;

class CMyParseData : public CParseData
{
public:
    CMyParseData();
    ~CMyParseData();

    /**
     * @brief ��������
     * @param rArray
     * @return
     */
    bool ParseData(const QByteArray &rArray);

    /**
     * @brief ����
     * @param nSeconds
     */
    void UpdateSeconds(const quint16 &nSeconds);

    /**
     * @brief ���������������
     */
    void ParseData();

    /**
     * @brief �����Ϣ
     */
    void Clear();

    /**
     * @brief ��ϰ��ʼ
     */
    void SetStart(quint16 unID);
    void AllStart();

    /**
     * @brief ��ϰ����
     */
    void SetStop(quint16 unID);
    void AllStop();

    /**
     * @brief ����
     */
    void AllBiSuo();
    void AllBiSuo(const QVariant &gunInfo);
    void PersonalBiSuo(quint16 unID);
    void PersonalBiSuo(quint16 unID, const QVariant &gunInfo);

    /**
     * @brief ����
     */
    void AllJieSuo();
    void AllJieSuo(const QVariant &gunInfo);
    void PersonalJieSuo(quint16 unID);
    void PersonalJieSuo(quint16 unID, const QVariant &gunInfo);


    /**
     * @brief ������ʾ
     * @param unID
     * @param hitInfo
     */
    void HitNotice(quint16 unID,const QVariant& hitInfo);

    /**
     * @brief ����԰�
     */
    void AllPangBai();

    /**
     * @brief ��������
     * @param unID
     */
    void PersonalPanSi(quint16 unID);
    void PersonalFuHuo(quint16 unID);

    void AllChongDan(const QVariant& rInfo);
    void PersonalChongDan(quint16 unID,const QVariant& rInfo);

    /**
     * @brief ��ǹ
     * @param rInfo
     */
    void AllPeiQiang(const QVariant & rInfo);
    void PersonalPeiQiang(quint16 unID, const QVariant& rInfo);

    /**
     * @brief ͬ��ʱ��
     */
    void AllSycTime(quint16);
    void PersonalSycTime(quint16 unID, quint16 unTime);

    /**
     * @brief ���÷���ʱ��
     */
    void AllSetSimTime(quint16);
    void PersonSimTime(quint16, quint16);

    /**
     * @brief У׼����
     */
    void CalibrationCharge(quint16 unID);

    /**
     * @brief ����/�رյ�����ģʽ
     */
    void Open3rd();
    void Close3rd();

    /**
     * @brief ���˱���ֵ
     * @param rInfo
     */
    void Damage(const QVariant& rInfo);

    /**
     * @brief ��ѯ���е�״̬
     */
    void QueryAll();

private:
    quint16 m_usCRC16;          /// CRC��ֵ
    uchar* m_pData;             /// ��ʵ����ָ��
    PersonInfo*        m_pPerson;/// ��Ա��Ϣ
    CMyQueryEquipment* m_pQuery;/// ��ѯ����
    CMySetQuipment*    m_pSet;  /// ��������
    CMyEventInfo*      m_pEvent;/// �¼�����
};

#endif // MYPARSEDATA_H
