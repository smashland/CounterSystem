#ifndef CCONFIGINFO_H
#define CCONFIGINFO_H
#include <QString>
#include <QDateTime>
#include <QMap>
#include <QHostAddress>
#include "CommonTypeDefine.h"

class Config;
/**
 * @brief 整个软件的配置信息
 */
class CConfigInfo
{
public:
    /**
     * @brief 获取唯一实例
     * @return 配置函数指针
     */
    static CConfigInfo* GetInstance();

    /**
     * @brief 获取串口信息
     * @return
     */
    QString& GetComName(){return(m_stComName);}

    /**
     * @brief 获取判断掉线的次数
     * @return
     */
    int&  GetDroppedTimes(){return(m_nDroppedTimes);}

    /**
     * @brief 获取同步时间
     * @return
     */
    int&  GetSynTimes(){return(m_nSynTimes);}

    /**
     * @brief 计算掉线时间
     */
    void CalOfflineTime();

    /**
     * @brief 获取掉线时间
     * @return
     */
    int GetOfflineTime();

    /**
     * @brief 获取重发次数
     * @return
     */
    int&  GetResendTimes(){return(m_nResendTimes);}

    /**
     * @brief 获取默认子弹数
     * @return
     */
    int&  GetDefaultBullets(){return(m_nDefaultBullets);}


    /**
     * @brief 获取是否演习开始
     * @return
     */
    bool& GetStart(){return(m_bStart);}

    /**
     * @brief 获取开始日期
     * @return
     */
    QDateTime& GetDateTime(){return(m_qStartDateTime);}

    /**
     * @brief 获取打击线的删除时间
     * @return
     */
    int& GetDelHitLineSecs(){return (m_nHitLineDelSec);}

    /**
     * @brief 获取系统中串口名字列表
     * @return
     */
    QStringList GetComNameList();

    /**
     * @brief 是否开启队友伤害
     * @return
     */
    bool&  IsAllowKillSelf(){return(m_bKillSelf);}

    /**
     * @brief 命中死亡是否有效
     * @return
     */
    bool&  CanHitDeath(){return(m_bCanHitDeath);}

    /**
     * @brief 获取IP地址
     * @return
     */
    void SetIP(const QString& sIP);
    const std::string& GetIP();

    /**
     * @brief 获得端口号
     * @return
     */
    uint GetPort();
    void SetPort(uint nPort);

    /**
     * @brief 获取通信类型
     * @return
     */
    int  GetConnectionType();

    /**
     * @brief 设置命中得分情况
     * @param nType
     * @return
     */
    int GetHurtMark(int nType);
    int CalHurtMark(int nHurtType);
    void SetHurtMark(int nIndex,int nValue);

    /**
     * @brief 设置命中生命值损伤情况
     * @param nType
     * @return
     */
    int GetHitDamage(int nType);
    int CalHitDamage(int nHurtType);
    void SetHitDamae(int nIndex,int nValue);
    void AllSetHitDamae();

    /**
     * @brief 获取类型对应的中文名
     * @param nType
     * @return
     */
    const QString& GetBodyName(int nType);

    /**
     * @brief 判断是否处于回放状态
     * @return
     */
    bool &GetIsReplay();

    /**
     * @brief 获取IP地址
     * @return
     */
    void SetSpeack(bool IsSpeack);
    int GetSpeack();

private:
    /**
     * @brief 解析INI文件
     */
    void PraseIni();
    void PraseXml();

    /**
     * @brief 保存ini文件
     */
    void SaveIni();

    /// 构造函数
    CConfigInfo();
    ~CConfigInfo();

private:
    int     m_nDroppedTimes;   /// 当几次没有获得心跳信息，则认为掉线
    int     m_nSynTimes;       /// 同步时间
    int     m_nResendTimes;    /// 设置重发次数
    int     m_nDefaultBullets; /// 默认子弹数
    int     m_nHitLineDelSec;  /// 删除打击线的时间
    int     m_nType;           /// 类型
    int     m_nOfflineTime;    /// 掉线时间
    bool    m_bStart;          /// 是否开始演习
    bool    m_bKillSelf;       /// 是否允许队友伤害
    bool    m_bCanHitDeath;    /// 命中死亡人是否得分
    bool    m_bReplay;         /// 是否处于数据回放状态
    int     m_nSpeak;          /// 是否开启语音
    QString     m_nIp;          /// 是否开启语音
    std::string m_sFileName;   /// 保存文件名称

    QMap<QString,QMap<quint16,QString>> m_mapAllInfo;


    QString         m_stComName;      /// 串口信息
    QDateTime       m_qStartDateTime; /// 点击开始时的时间

    QHostAddress            m_addrTcp;     /// IP 地址
    ushort                  m_unPort;      /// 绑定端口号

    Config*          m_pConfig;       /// 连接信息
    QVector<int>     m_vHurtMark;          /// 得分情况
    QVector<int>     m_vHitDamea;          /// 伤害值
};

#endif // CCONFIGINFO_H
