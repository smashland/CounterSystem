#ifndef PARSEDATA_H
#define PARSEDATA_H

#include "../CommonTypeDefine.h"
/**
 * @brief 解析数据基类
 */

#include <QByteArray>
#include <QVariant>

class CParseData
{
public:
    CParseData();
    virtual ~CParseData();

    /**
     * @brief 解析数据
     * @param rArray
     * @return
     */
    virtual bool ParseData(const QByteArray&);

    /**
     * @brief 更新时间
     */
    virtual void UpdateSeconds(const quint16& unSeconds);

    /**
     * @brief 清空暂存状态
     */
    virtual void Clear(){}

    /**
     * @brief 同步时间
     */
    virtual void AllSycTime(quint16){}
    virtual void PersonalSycTime(quint16,quint16){}

    /**
     * @brief 演习开始
     */
    virtual void AllStart();
    virtual void SetStart(quint16){}

    /**
     * @brief 演习结束
     */
    virtual void AllStop();
    virtual void SetStop(quint16){}

    /**
     * @brief 判死
     * @param unID
     */
    virtual void PersonalPanSi(quint16){}

    /**
     * @brief 复活
     * @param unID
     */
    virtual void PersonalFuHuo(quint16){}

    /**
     * @brief 损伤比例值
     */
    virtual void Damage(const QVariant&){}

    /**
     * @brief 闭锁所有人的所有枪
     * @brief 闭锁所有人的某类枪
     */
    virtual void AllBiSuo(){}
    virtual void AllBiSuo(const QVariant&){}

    /**
     * @brief 闭锁某个人的所有枪
     * @brief 闭锁某个人的某些枪
     * @param unID
     */
    virtual void PersonalBiSuo(quint16){}
    virtual void PersonalBiSuo(quint16 ,const QVariant&){}

    /**
     * @brief 解锁所有人的所有枪
     * @brief 解锁所有人的某些枪
     */
    virtual void AllJieSuo(){}
    virtual void AllJieSuo(const QVariant&){}

    /**
     * @brief 解锁某个人的所有枪
     * @brief 解锁某个人的某些枪
     * @param unID
     */
    virtual void PersonalJieSuo(quint16 ){}
    virtual void PersonalJieSuo(quint16 ,const QVariant& ){}

    /**
     * @brief 给所有的人充弹
     */
    virtual void AllChongDan(const QVariant&){}
    virtual void PersonalChongDan(quint16,const QVariant&){}

    /**
     * @brief 命中提示
     * @param unID
     * @param hitInfo
     */
    virtual void HitNotice(quint16,const QVariant&){}

    /**
     * @brief 解除旁白
     */
    virtual void AllPangBai(){}

    /**
     * @brief 仿真时间
     */
    virtual void AllSetSimTime(quint16){}
    virtual void PersonSimTime(quint16,quint16){}

    /**
     * @brief 配枪
     */
    virtual void AllPeiQiang(const QVariant&){}
    virtual void PersonalPeiQiang(quint16,const QVariant&){}

    /**
     * @brief 时间校准
     */
    virtual void CalibrationCharge(quint16){}

    /**
     * @brief 开启第三者模式
     */
    virtual void Open3rd(){}
    virtual void Close3rd(){}

    /**
     * @brief 查询所有的状态
     */
    virtual void QueryAll(){}

protected:
    /**
     * @brief 初始化状态
     */
    void InitState();

protected:
    static uint C_BUFFER_LENGTH;  /// 默认缓存大小
    bool    m_bBegin;       /// 是否已经开始
    quint16 m_unSeconds;   /// 当前的秒数
    quint16 m_unID;        /// 当前位置

    uchar* m_pBuffer;      /// 缓存数据长度
    int   m_nDataLength;  /// 数据长度
    int   m_nDataGet;     /// 当前获取到的数据
    int   m_nNowLength;   /// 读取数据长度

    uchar m_ucType;  /// 命令类型
    stAddr m_stAddr; /// 设备地址
    QVariant m_vaInfo; /// 需要设置的信息
};

#endif // PARSEDATA_H
