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
    //加载数据（从文件中读取文件）
    void loadData();
    void saveData();


    //    /**
    //     * @brief 设置方案名称
    //     * @param sName
    //     */
    //     Q_INVOKABLE void setSceName(QString sName);
    ////     Q_INVOKABLE QString getSceName(){ return(m_sceName);}

    /**
      * @brief 添加人员
      */
    Q_INVOKABLE void addPerson();
//    Q_INVOKABLE int addMember(ScePersonInfo *scePersonInfo);

signals:
private:
    QStringList m_fileds; //表头字段

//    QList<ScesPerson*> m_scesPerson;
//    ScesPerson *scesPerson;

};

#endif // SCEMANAGER_H
