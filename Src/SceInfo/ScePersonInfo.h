#ifndef SCEPERSONINFO_H
#define SCEPERSONINFO_H

#include <QObject>
#include <QJsonObject>

class ScePersonInfo : public QObject
{
    Q_OBJECT
public:
    explicit ScePersonInfo(QObject *parent = nullptr);
    Q_PROPERTY(int id READ getID WRITE setID NOTIFY IDChanged/*int id MEMBER m_ID NOTIFY IDChanged*/)
    Q_PROPERTY(QString name READ getName WRITE setName NOTIFY nameChanged/*QString name MEMBER m_Name NOTIFY nameChanged*/)
    Q_PROPERTY(int position READ getPosition WRITE setPosition NOTIFY positionChanged)
    Q_PROPERTY(int groupType READ getGroupType WRITE setGroupType NOTIFY positionChanged)
    Q_PROPERTY(bool hostage READ getHostage WRITE setHostage NOTIFY hostageChanged)


    void readPerson(const QJsonObject &json);
    void writePerson(QJsonObject &json) const;

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
    void setPosition(int sPosition);
    int getPosition();

    void setGroupType(int groupType);
    int getGroupType();

    /**
      * @brief 设置人质
      * @param sPosition
      */
    void setHostage(bool bHostage);
    bool getHostage();

    /**
      * @brief 设置人员名称
      * @param sName
      */
    void setImagePath(QString sImagePath);
    QString getImagePath();

    /**
      * @brief 复制文件
      * @param strImagePath
      * @param folderName
      *
      */
    Q_INVOKABLE QString copyFile(const QString &strImagePath, const QString &folderName="Project\\Image");

signals:
    void IDChanged(int);
    void nameChanged(QString);
    void positionChanged(int);
    void groupTypeChanged(int);
    void hostageChanged(bool);

private:
    int        m_ID;
    QString    m_Name;
    int        m_Positon;
    int        m_Group;
    bool       m_host{true};
    QString    m_sImagePath;

};

#endif // SCEPERSONINFO_H
