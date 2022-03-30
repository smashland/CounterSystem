#ifndef CPERSONALLINFO_H
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
    Q_PROPERTY(bool bPistol MEMBER m_bPistol NOTIFY pistolChanged)
    Q_PROPERTY(bool bRifle MEMBER m_bRifle NOTIFY rifleChanged)
    Q_PROPERTY(bool bStand MEMBER m_bSatand NOTIFY standChanged)
    Q_PROPERTY(bool bHead MEMBER m_bHead NOTIFY headChanged)
    Q_PROPERTY(bool bCenter MEMBER m_bCenter NOTIFY centerChanged)
    Q_PROPERTY(bool bLeftArm MEMBER m_bLeftArm NOTIFY leftArmChanged)
    Q_PROPERTY(bool bLeftLeg MEMBER m_bLeftLeg NOTIFY leftLegChanged)
    Q_PROPERTY(bool bRightArm MEMBER m_bRightArm NOTIFY rightArmChanged)
    Q_PROPERTY(bool bRightLeg MEMBER m_bRightLeg NOTIFY rightLegChanged)
    Q_PROPERTY(bool bBreast MEMBER m_bBreast NOTIFY breastChanged)
    Q_PROPERTY(bool bAbdomen MEMBER m_bAbdomen NOTIFY abdomenChanged)

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
    void rifleChanged(bool);
    void pistolChanged(bool);
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

protected:
    void UpdateBaseInfo(PersonInfo* pPersonInfo);

private:
    int m_nPistol=0;
    int m_nRifle=0;

    bool m_bPistol=false;
    bool m_bRifle=false;
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
    QString m_sName;  /// 名字
    QString m_sType;  /// 分类
    QStringList m_listHitInfo;
};

#endif // CPERSONALLINFO_H
