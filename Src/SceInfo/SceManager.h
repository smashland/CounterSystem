#ifndef SCEMANAGER_H
#define SCEMANAGER_H

#include <QObject>
#include "ScesPerson.h"
#include "ScePersonInfo.h"

class SceManager : public QObject
{
    Q_OBJECT
public:
    explicit SceManager(QObject *parent = nullptr);
    ~SceManager();
    SceManager(const QString &name);
    Q_PROPERTY(QString sceName READ getSceName WRITE setSceName NOTIFY sceNameChanged)


    QList<ScePersonInfo *> sces() const;
    void setSces(const QVector<ScePersonInfo> &sces);

    Q_INVOKABLE void read();
    void write() const;
    void writeSce() const;


    /**
      * @brief 设置方案名称
      * @param sName
      */
    Q_INVOKABLE void setSceName(const QString &sName);
    Q_INVOKABLE QString getSceName(){ return(m_sSceName);}

    /**
      * @brief 添加方案
      */
    Q_INVOKABLE void addScenario(const QString &sName);

    /**
      * @brief 添加人员
      */
    Q_INVOKABLE void addPerson(int nID, const QString &sName, int nLevel, int nGroup, bool bHostage);
    Q_INVOKABLE bool HavePerson(int nID);
signals:
    void sceNameChanged(QString);
private:
    void ClearPersonInfo();
private:
    QString m_sSceName;
    QMap<int,ScePersonInfo*> m_mapId2Person;


};

#endif // SCEMANAGER_H
