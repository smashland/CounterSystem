#ifndef GLOBALSETTINGS_H
#define GLOBALSETTINGS_H

#include <QObject>
#include <QColor>
#include <QMap>
#include <QVariantMap>

class CGlobalData;
class CGlobalSettings : public QObject
{
    Q_OBJECT
public:
    explicit CGlobalSettings(QObject *parent = nullptr);
    Q_PROPERTY(QColor connectColor MEMBER m_qConnectColor NOTIFY connectColorChanged)
    Q_PROPERTY(QColor disConnColor MEMBER m_qDisConnectColor NOTIFY disConnColorChanged)
    Q_PROPERTY(int conType MEMBER m_nType)
    Q_PROPERTY(bool bIsStart MEMBER m_bIsStart NOTIFY startStatusChanged)
    Q_PROPERTY(bool bIsReplay MEMBER m_bIsReplay NOTIFY replayStatusChanged)
    Q_PROPERTY(QVariantList scoreSetting MEMBER m_scoreSetting NOTIFY scoreSettingChanged)
    Q_PROPERTY(QVariantList harmSetting MEMBER m_harmSetting NOTIFY harmSettingChanged)
    Q_PROPERTY(QVariantList systemSetting MEMBER m_sysSetting NOTIFY sysSettingChanged)
    Q_PROPERTY(int bIsStart MEMBER m_bIsStart NOTIFY startStatusChanged)

    //    Q_PROPERTY(int sIp MEMBER m_sIp NOTIFY sIpChanged)
    //    Q_PROPERTY(int sPort MEMBER m_sPort NOTIFY sPortChanged)

    Q_INVOKABLE QColor type2Color(const QString& sType);
    Q_INVOKABLE QColor type2BackColor(const QString& sType);
    Q_INVOKABLE QStringList types();
    Q_INVOKABLE int index(const QString& sType);
    Q_INVOKABLE QStringList comNameList();
    Q_INVOKABLE bool isExistcomName(const QString& sComName);

    Q_INVOKABLE void setComName(const QString& sComName);
    Q_INVOKABLE void setWifiInfo(const QString& sIP, ushort unPort);

    Q_INVOKABLE QString getSip();
    Q_INVOKABLE ushort getPort();

    Q_INVOKABLE void setStart();
    Q_INVOKABLE void setStop();
    Q_INVOKABLE void startReplay();
    Q_INVOKABLE void endReplay();

    Q_INVOKABLE QString getSysTime();


    Q_INVOKABLE void setBiSuo(quint16 nID); /// 闭锁
    Q_INVOKABLE void setJiesuoSuo(quint16 nID); /// 解锁
    Q_INVOKABLE void setJieChu(quint16 nID);    /// 解除旁白
    Q_INVOKABLE void setPanSi(quint16 nID);     /// 判死
    Q_INVOKABLE void setFuHuo(quint16 nID);     /// 复活
    Q_INVOKABLE void chongDan(quint16 nID,const QStringList& allInfo); /// 充弹
    Q_INVOKABLE void peiQiang(quint16 nID, int nGunID);  /// 配枪
    Q_INVOKABLE void sycTime(quint16 nID, quint16 nTime); /// 设置同步时间
    Q_INVOKABLE void changeSetting(const QString& sListType,const int& rIndex,const int& rInt);

//    Q_INVOKABLE void setAllLock();   ///所有武器闭锁
//    Q_INVOKABLE void setAllUnlock(); ///所有武器解锁
//    Q_INVOKABLE void setAllDeath();  ///所有人员判死
//    Q_INVOKABLE void setAllResurrection();///所有人员复活
//    Q_INVOKABLE void setAllCharge(); /// 所有武器充弹

    void setConnectColor(const QColor& qConColor);
    void setDisConnColor(const QColor& qDisConColor);

    void SetGlobalData(CGlobalData* pGlobalData);


signals:
    void connectColorChanged(const QColor& qConColor);
    void disConnColorChanged(const QColor& qDisColor);
    void startStatusChanged(bool bIsStart);
    void replayStatusChanged(bool bReplay);
    void scoreSettingChanged(const QVariantList&);
    void harmSettingChanged(const QVariantList&);
    void sysSettingChanged(const QVariantList&);

    //    int sIpChanged;
    //    int sPortChanged;
public slots:
    void updateConfig();
private:
    CGlobalData* m_pGlobalData=nullptr;      /// 全局数据
    int    m_nType;                          /// 通信类型
    bool   m_bIsStart=false;                 /// 是否演习开始
    bool   m_bIsReplay=false;                /// 是否处于回放状态
    QColor m_qConnectColor;                  /// 连接的时候颜色
    QColor m_qDisConnectColor;               /// 断开连接的时候的颜色
    QMap<QString,QColor> m_mapType2Color;    /// 类型与颜色的映射关系
    QMap<QString,QColor> m_mapType2BackColor;/// 类型与背景颜色的映射关系
    QVariantList         m_scoreSetting;     /// 得分设置
    QVariantList         m_harmSetting;      /// 损伤设置
    QVariantList         m_sysSetting;       /// 系统设置
    QString              sBeginTime;         ///开始时间
};

#endif // GLOBALSETTINGS_H
