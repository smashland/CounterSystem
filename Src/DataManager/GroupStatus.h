#ifndef CGROUPSTATUS_H
#define CGROUPSTATUS_H

#include <QObject>

class CGroupStatus : public QObject
{
    Q_OBJECT
public:
    explicit CGroupStatus(QObject *parent = nullptr);

    Q_PROPERTY(float liveRatio MEMBER m_fLiveRatio NOTIFY liveRatioChanged)
    Q_PROPERTY(float hurtRatio MEMBER m_fHurtRatio NOTIFY hurtRatioChanged)
    Q_PROPERTY(QString type MEMBER m_sType NOTIFY typeChanged)

    void SetTypeName(const QString& sType);
    const QString& GetTypeName(){return(m_sType);}

    void SetLiveRatio(float fLive);
    float GetLiveRatio(){return(m_fLiveRatio);}

    void SetHurtRatio(float fHurt);
    float GetHurtRatio(){return(m_fHurtRatio);}

signals:
    void typeChanged(const QString&);
    void liveRatioChanged(float);
    void hurtRatioChanged(float);

private:
    QString m_sType;
    float   m_fLiveRatio;
    float   m_fHurtRatio;
};

#endif // CGROUPSTATUS_H
