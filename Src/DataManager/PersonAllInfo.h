﻿#ifndef CPERSONALLINFO_H
#define CPERSONALLINFO_H

#include <QObject>
#include <QStringList>

class PersonInfo;

class CPersonAllInfo : public QObject
{
    Q_OBJECT
public:
    explicit CPersonAllInfo(QObject *parent = nullptr);

    Q_PROPERTY(int id MEMBER m_nID NOTIFY idChanged)
    Q_PROPERTY(QString name MEMBER m_sName NOTIFY nameChanged)
    Q_PROPERTY(QString type MEMBER m_sType NOTIFY typeChanged)
    Q_PROPERTY(QStringList listHit MEMBER m_listHitInfo NOTIFY hitChanged)
    Q_PROPERTY(int nPistol MEMBER m_nPistol NOTIFY pistolNumChanged)
    Q_PROPERTY(int nRifle MEMBER m_nRifle NOTIFY rifleNumChanged)
    Q_PROPERTY(int nSniper MEMBER m_nSniper NOTIFY sniperNumChanged)
    Q_PROPERTY(bool bPistol MEMBER m_bPistol NOTIFY pistolChanged)
    Q_PROPERTY(bool bRifle MEMBER m_bRifle NOTIFY rifleChanged)
    Q_PROPERTY(bool bSniper MEMBER m_bSniper NOTIFY sniperChanged)
    Q_PROPERTY(bool bStand MEMBER m_bSatand NOTIFY standChanged)
    Q_PROPERTY(bool bHead MEMBER m_bHead NOTIFY headChanged)
    Q_PROPERTY(bool bCenter MEMBER m_bCenter NOTIFY centerChanged)
    Q_PROPERTY(bool bLeftArm MEMBER m_bLeftArm NOTIFY leftArmChanged)
    Q_PROPERTY(bool bLeftLeg MEMBER m_bLeftLeg NOTIFY leftLegChanged)
    Q_PROPERTY(bool bRightArm MEMBER m_bRightArm NOTIFY rightArmChanged)
    Q_PROPERTY(bool bRightLeg MEMBER m_bRightLeg NOTIFY rightLegChanged)
    Q_PROPERTY(bool bBreast MEMBER m_bBreast NOTIFY breastChanged)
    Q_PROPERTY(bool bAbdomen MEMBER m_bAbdomen NOTIFY abdomenChanged)
    Q_PROPERTY(double  dLat MEMBER m_dLat NOTIFY latChanged)
    Q_PROPERTY(double  dLon MEMBER m_dLon NOTIFY lonChanged)
    Q_PROPERTY(int uRelive MEMBER m_uRelive NOTIFY reliveChanged)

    Q_PROPERTY(int nPistolSum MEMBER m_nPistolSum NOTIFY pistolSumChanged)
    Q_PROPERTY(int nRifleSum MEMBER m_nRifleSum NOTIFY rifleSumChanged)
    Q_PROPERTY(int nSniperSum MEMBER m_nSniperSum NOTIFY sniperSumChanged)
    Q_PROPERTY(int nHitCount MEMBER m_nHitCount NOTIFY hitCountChanged)
    Q_PROPERTY(int nHurtCount MEMBER m_nHurtCount NOTIFY hurtCountChanged)

    int        getId()      {return m_nID;}
    QString    getName()    {return m_sName;}
    int        getRelive()  {return m_uRelive;}
    double     getLat()     {return m_dLat;}
    double     getLon()     {return m_dLon;}


    /**
     * @brief 更新显示信息
     */
    void Update(quint16);

    /**
     * @brief 定时更新显示
     */
    void Update();

    /**
     * @brief 更新名称和分组
     * @param sName
     * @param sType
     */
    void UpdateTypeAndName(const QString& sName, const QString& sType);
signals:
    void pistolNumChanged(int);
    void rifleNumChanged(int);
    void sniperNumChanged(int);
    void rifleChanged(bool);
    void pistolChanged(bool);
    void sniperChanged(bool);
    void standChanged(bool);
    void headChanged(bool);
    void centerChanged(bool);
    void leftArmChanged(bool);
    void leftLegChanged(bool);
    void rightArmChanged(bool);
    void rightLegChanged(bool);
    void breastChanged(bool);
    void abdomenChanged(bool);
    void idChanged(int);
    void nameChanged(QString);
    void typeChanged(QString);
    void hitChanged(QStringList);
    void latChanged(double);
    void lonChanged(double);
    void reliveChanged(int);
    void pistolSumChanged(int);
    void rifleSumChanged(int);
    void sniperSumChanged(int);
    void hitCountChanged(int);
    void hurtCountChanged(int);

protected:
    void UpdateBaseInfo(PersonInfo* pPersonInfo);

private:
    int m_nPistol=0; //手枪子弹
    int m_nRifle=0;  //步枪子弹
    int m_nSniper=0; //狙击枪子弹
    int m_nRifleSum=0; //步枪总数子弹
    int m_nPistolSum=0;//手枪总数子弹
    int m_nSniperSum=0;//狙击枪子弹

    int m_nHitCount=0; ///击中的次数
    int m_nHurtCount=0; ///被击中的次数

    bool m_bPistol=false;
    bool m_bRifle=false;
    bool m_bSniper=false;
    bool m_bSatand=false; /// 是否站立
    bool m_bHead=false;   ///头部是否受伤
    bool m_bCenter=false; ///背部是否受伤
    bool m_bLeftArm=false;///左臂是否受伤
    bool m_bLeftLeg=false;///左腿是否受伤
    bool m_bRightLeg=false;///右腿是否受伤
    bool m_bRightArm=false;///右臂是否受伤
    bool m_bBreast=false;  /// 胸部是否受伤
    bool m_bAbdomen=false; /// 腹部是否受伤
    int  m_nID=0;
    double m_dLon{};
    double m_dLat{};
    int  m_uRelive=0;   ///复活
    QString m_sName;  /// 名字
    QString m_sType;  /// 分类
    QStringList m_listHitInfo;
};

#endif // CPERSONALLINFO_H
