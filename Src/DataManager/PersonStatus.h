#ifndef PERSONSTATUS_H
#define PERSONSTATUS_H

/**
 * @brief ��ʾ��Ա�ļ�Ҫ��Ϣ
 *   ��Ҫ��������װ�ߵ�����״̬����Ա����״̬�����飬���ơ����
 *   ��ص���
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

    /**
     * @brief ������Ϣ
     */
    void Update(quint16 uTimes);

    int  getId(){return(m_nID);}
    void setName(const QString& sName);
    int getHealth(){return(m_nHealth);}
    const QString& getName(){return(m_sName);}
    void updateTime(quint16 unTimes);
    bool IsOnLine(){return(m_bOnLine);}
    Q_INVOKABLE void setType(const QString& sType);
    Q_INVOKABLE const QString& getType(){return(m_sType);}

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

protected:
    /**
     * @brief ��������״̬
     */
    void UpdateStatus(const ConnectStatus&);

private:
    int  m_nID;
    bool m_bGPS=false;   /// GPS�Ƿ�����
    bool m_bTK=false;    /// ͷ���Ƿ�����
    bool m_bOnLine=false;/// �Ƿ�����
    bool m_bPistol=false;///��ǹ����״̬
    bool m_bRifle=false; ///��ǹ����״̬

    int  m_nBaty=100;     /// ��ص���
    int  m_nHealth=100;   /// ����״��
    int  m_unTimes=0;   /// ���һ�ε�time
    QString m_sName;    /// ����
    QString m_sType;    /// ����
};
#endif // PERSONSTATUS_H
