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
     * @brief 解析数据
     * @param rArray
     * @return
     */
    bool ParseData(const QByteArray &rArray);

    /**
     * @brief 更新
     * @param nSeconds
     */
    void UpdateSeconds(const quint16 &nSeconds);

    /**
     * @brief 根据命令解析数据
     */
    void ParseData();

    /**
     * @brief 清空信息
     */
    void Clear();

    /**
     * @brief 演习开始
     */
    void SetStart(quint16 unID);
    void AllStart();

    /**
     * @brief 演习结束
     */
    void SetStop(quint16 unID);
    void AllStop();

    /**
     * @brief 闭锁
     */
    void AllBiSuo();
    void AllBiSuo(const QVariant &gunInfo);
    void PersonalBiSuo(quint16 unID);
    void PersonalBiSuo(quint16 unID, const QVariant &gunInfo);

    /**
     * @brief 解锁
     */
    void AllJieSuo();
    void AllJieSuo(const QVariant &gunInfo);
    void PersonalJieSuo(quint16 unID);
    void PersonalJieSuo(quint16 unID, const QVariant &gunInfo);


    /**
     * @brief 命中提示
     * @param unID
     * @param hitInfo
     */
    void HitNotice(quint16 unID,const QVariant& hitInfo);

    /**
     * @brief 解除旁白
     */
    void AllPangBai();

    /**
     * @brief 判死复活
     * @param unID
     */
    void PersonalPanSi(quint16 unID);
    void PersonalFuHuo(quint16 unID);

    void AllChongDan(const QVariant& rInfo);
    void PersonalChongDan(quint16 unID,const QVariant& rInfo);

    /**
     * @brief 配枪
     * @param rInfo
     */
    void AllPeiQiang(const QVariant & rInfo);
    void PersonalPeiQiang(quint16 unID, const QVariant& rInfo);

    /**
     * @brief 同步时间
     */
    void AllSycTime(quint16);
    void PersonalSycTime(quint16 unID, quint16 unTime);

    /**
     * @brief 设置仿真时间
     */
    void AllSetSimTime(quint16);
    void PersonSimTime(quint16, quint16);

    /**
     * @brief 校准电量
     */
    void CalibrationCharge(quint16 unID);

    /**
     * @brief 开启/关闭第三者模式
     */
    void Open3rd();
    void Close3rd();

    /**
     * @brief 损伤比例值
     * @param rInfo
     */
    void Damage(const QVariant& rInfo);

    /**
     * @brief 查询所有的状态
     */
    void QueryAll();

private:
    quint16 m_usCRC16;          /// CRC数值
    uchar* m_pData;             /// 真实数据指针
    PersonInfo*        m_pPerson;/// 人员信息
    CMyQueryEquipment* m_pQuery;/// 查询数据
    CMySetQuipment*    m_pSet;  /// 设置数据
    CMyEventInfo*      m_pEvent;/// 事件数据
};

#endif // MYPARSEDATA_H
