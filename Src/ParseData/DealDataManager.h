#ifndef DEALDATAMANAGER_H
#define DEALDATAMANAGER_H

/**********************
 * @brief 处理数据的管理者
 **********************/

#include <QMap>
#include "../CommonTypeDefine.h"
#include "../TimeServer/ITimeObserver.h"

class CParseData;
class QVariant;

class CDealDataManager:public ITimeObserver
{
public:
    static CDealDataManager* GetInstance();

    /**
     * @brief 订阅更新时间
     * @param nSeconds
     */
    void UpdateSeconds(const quint16 &nSeconds);

    /**
     * @brief 订阅更新时间
     */
    void UpdateTime(const QDateTime&);

    /**
     * @brief 是否已经初始化
     * @return
     */
    bool IsInit();

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
    void AllBiSuo(const QVariant& gunInfo);
    void PersonalBiSuo(quint16 unID);
    void PersonalBiSuo(quint16 unID, const QVariant& gunInfo);

    /**
     * @brief 解锁
     */
    void AllJieSuo();
    void AllJieSuo(const QVariant& gunInfo);
    void PersonalJieSuo(quint16 unID);
    void PersonalJieSuo(quint16 unID,const QVariant& gunInfo);

    /**
     * @brief 解除旁白
     */
    void PangBai();

    /**
     * @brief 判死复活
     * @param unID
     */
    void PersonalPanSi(quint16 unID);
    void PersonalFuHuo(quint16 unID);

    /**
     * @brief 发送命中提示
     * @param unID
     */
    void HitNotice(quint16 unID,const QVariant& hitInfo);

    /**
     * @brief 充弹
     */
    void AllChongDan(const QVariant& gunInfo);
    void PersonalChongDan(quint16 unID,const QVariant& gunInfo);
//    void SetBulletSum(quint16 unID,const QStringList& bulletInfo);
    void SetBulletSum(quint16 unID,QList<int> bulletInfo);
    QStringList GetBulletSum(quint16 unID);
    void clearBulletSum();

    /**
     * @brief 配枪
     */
    void AllPeiQiang(const QVariant& gunInfo);
    void PersonalPeiQiang(quint16 unID,const QVariant& gunInfo);

    /**
     * @brief 同步时间
     */
    void AllSycTime(quint16 unTimes);
    void PersonalSycTime(quint16 unID,quint16 unTimes);

    /**
     * @brief 设置仿真时间
     */
    void AllSimTime(quint16 unTime);
    void PersonalSimTime(quint16 unID,quint16 unTimes);

    /**
     * @brief 开启第三者模式
     */
    void Open3rd();
    void Close3rd();

    /**
     * @brief 损伤比例值
     * @param damegeInfo
     */
    void Damege(const QVariant& damegeInfo);

    /**
     * @brief 校准电量
     */
    void CalibrationCharge(quint16 unID);

    /**
     * @brief 清空消息
     */
    void Clear();

    /**
     * @brief 查询所有信息
     */
    void QueryAll();

private:
    CDealDataManager();
    ~CDealDataManager();

private:
    CParseData*   m_pParse;    /// 默认的解析文件
    QMap<int,QStringList> m_mapId2BulletSum; ///编号和设置的子弹总数
};

#endif // DEALDATAMANAGER_H
