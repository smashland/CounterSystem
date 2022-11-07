#ifndef PERSONSTATUS_H
#define PERSONSTATUS_H

/**
 * @brief 显示人员的简要信息
 *   主要包括各种装具的连接状态，人员健康状态，分组，名称、编号
 *   电池电量
 */

#include <QObject>

class ConnectStatus;

class CPersonStatus : public QObject
{
    friend class CGlobalData;
    Q_OBJECT
public:
    explicit CPersonStatus(int nID=0,QObject *parent = nullptr);
    CPersonStatus(const CPersonStatus& rOther);
    Q_PROPERTY(int id MEMBER m_nID NOTIFY idChanged)
    Q_PROPERTY(QString name MEMBER m_sName NOTIFY nameChanged)
    Q_PROPERTY(QString type MEMBER m_sType READ getType WRITE setType NOTIFY typeChanged)
    Q_PROPERTY(bool bGPS MEMBER m_bGPS NOTIFY gpsChanged)
    Q_PROPERTY(bool bTK MEMBER m_bTK NOTIFY tkChanged)
    Q_PROPERTY(bool bOnLine MEMBER m_bOnLine NOTIFY onLineChanged)
    Q_PROPERTY(bool bPistol MEMBER m_bPistol NOTIFY pistolChanged)
    Q_PROPERTY(bool bRifle MEMBER m_bRifle NOTIFY rifleChanged)
    Q_PROPERTY(int  nBaty MEMBER m_nBaty NOTIFY batyChanged)
    Q_PROPERTY(int  nHealth MEMBER m_nHealth NOTIFY healthChanged)
    Q_PROPERTY(bool bRenZhi MEMBER m_bRenZhi NOTIFY renZhiChanged)

    /**
     * @brief 更新信息
     */
    void Update(quint16 uTimes);

    void setId(int nId);
    int  getId(){return(m_nID);}
    void setName(const QString& sName);
    bool getBtk(){return m_bTK;}
    int getHealth(){return(m_nHealth);}
    const QString& getName(){return(m_sName);}
    void updateTime(quint16 unTimes);
    bool IsOnLine(){return(m_bOnLine);}
    Q_INVOKABLE void setType(const QString& sType);
    Q_INVOKABLE const QString& getType(){return(m_sType);}
    void setRenzhi(bool bHostage);

signals:
    void idChanged(int);
    void nameChanged(QString);
    void typeChanged(QString);
    void gpsChanged(bool);
    void tkChanged(bool);
    void onLineChanged(bool);
    void pistolChanged(bool);
    void rifleChanged(bool);
    void batyChanged(int);
    void healthChanged(int);
    void renZhiChanged(bool);


protected:
    /**
     * @brief 更新连接状态
     */
    void UpdateStatus(const ConnectStatus&);

private:
    int  m_nID{};
    bool m_bGPS=false;   /// GPS是否连接
    bool m_bTK=false;    /// 头盔是否连接
    bool m_bOnLine=false;/// 是否在线
    bool m_bPistol=false;///手枪连接状态
    bool m_bRifle=false; ///步枪连接状态

    int  m_nBaty{100};     /// 电池电量
    int  m_nHealth{100};   /// 健康状况
    int  m_unTimes{0};   /// 最后一次的time

    QString m_sName;    /// 名字
    QString m_sType;    /// 分组

    bool m_bRenZhi=false;///是否人质
};
#endif // PERSONSTATUS_H
