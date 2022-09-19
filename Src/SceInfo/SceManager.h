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
    SceManager(const QString &name);
    //加载数据（从文件中读取文件）
    void loadData();
    void saveData();

    QList<ScePersonInfo *> sces() const;
    void setSces(const QVector<ScePersonInfo> &sces);

    void read();
    void write() const;


    /**
         * @brief 设置方案名称
         * @param sName
         */
    Q_INVOKABLE void setSceName(const QString &sName);
    Q_INVOKABLE QString getSceName(){ return(m_sSceName);}

    /**
      * @brief 添加人员
      */
    Q_INVOKABLE void addPerson(int nID, const QString &sName, int nLevel, int nGroup, bool bHostage);

    Q_INVOKABLE bool HavePerson(int nID);

    void addPerson();
signals:
private:
    QString m_sSceName;
    QMap<int,ScePersonInfo*> m_mapId2Person;

};

#endif // SCEMANAGER_H
