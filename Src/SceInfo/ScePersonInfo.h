#ifndef SCEPERSONINFO_H
#define SCEPERSONINFO_H

#include <QObject>
class ScePersonInfo : public QObject
{
    Q_OBJECT
public:
    explicit ScePersonInfo(QObject *parent = nullptr);



    Q_PROPERTY(int id READ getID WRITE setID NOTIFY IDChanged/*int id MEMBER m_ID NOTIFY IDChanged*/)
    Q_PROPERTY(QString name READ getName WRITE setName NOTIFY nameChanged/*QString name MEMBER m_Name NOTIFY nameChanged*/)
    Q_PROPERTY(QString position READ getPosition WRITE setPosition NOTIFY positionChanged)
    Q_PROPERTY(QString groupType READ getGroupType WRITE setGroupType NOTIFY positionChanged)
    Q_PROPERTY(bool hostage READ getHostage WRITE setHostage NOTIFY hostageChanged)

    /**
      * @brief 设置设备编号
      * @param nID
      */
    void setID(int nID);
    int  getID() const;


    /**
      * @brief 设置人员名称
      * @param sName
      */
    void setName(QString sName);
    QString getName();

    /**
      * @brief 设置人员职务
      * @param sPosition
      */
    void setPosition(QString sPosition);
    QString getPosition();

    void setGroupType(QString groupType);
    QString getGroupType();

    /**
      * @brief 设置人质
      * @param sPosition
      */
    void setHostage(bool bHostage);
    bool getHostage();

signals:
    void IDChanged(int);
    void nameChanged(QString);
    void positionChanged(QString);
    void groupTypeChanged(QString);
    void hostageChanged(bool);

private:
    int        m_ID;
    QString    m_Name;
    QString    m_Positon;
    QString    m_Group;
    bool       m_host{true};

};

#endif // SCEPERSONINFO_H
