#ifndef SCEMANAGER_H
#define SCEMANAGER_H

#include <QObject>
#include "ScePersonInfo.h"

class SceManager : public QObject
{
    Q_OBJECT
public:
    explicit SceManager(QObject *parent = nullptr);
    ~SceManager();
    SceManager(const QString &name);

    Q_PROPERTY(QString sceName READ getSceName WRITE setSceName NOTIFY sceNameChanged)
    Q_PROPERTY(QVariantList listPerson MEMBER m_listPerson NOTIFY listPersonChanged)


    QList<ScePersonInfo *> sces() const;
    void setSces(const QVector<ScePersonInfo> &sces);


    ///读写文件保存方案信息
    void read(QString &sname);
    void write() const;
    Q_INVOKABLE void modify();
    void loadImagePath(const QString &strImagePath);

    /**
      * @brief 查看选中人员的信息（未完成）
      */
    Q_INVOKABLE void showPersonInfo(int nID);

    /**
      * @brief 删除选中人员的信息(未完成)
      */
    Q_INVOKABLE void removePersonInfo(int nID);

    /**
      * @brief 修改选中人员信息（未完成）
      * @param nID
      */
    Q_INVOKABLE bool modifyPersonInfo(const int nID);

    /**
      * @brief 显示选中方案的信息
      */
    Q_INVOKABLE void showScenfo(QString sSceName);

    /**
      * @brief 显示所有方案
      */
    Q_INVOKABLE QStringList showSceList();

    /**
      * @brief 设置方案名称
      * @param sName
      */
    Q_INVOKABLE void setSceName(const QString &sName);
    Q_INVOKABLE QString getSceName(){ return(m_sSceName);}

    /**
      * @brief 添加方案
      * @param sName
      */
    Q_INVOKABLE void addScenario(const QString &sName);

    /**
      * @brief 修改方案（未完成）
      * @param sName
      */
    Q_INVOKABLE bool modifyScenario(const QString &sName);

    /**
      * @brief 删除方案
      * @param sName
      */
    Q_INVOKABLE bool removeScenario(const QString &sName);

    /**
      * @brief 添加人员
      * @param nID
      * @param sName
      * @param nLevel
      * @param nGroup
      * @param bHostage
      * @param sImagePath
      */
    Q_INVOKABLE void addPerson(int nID, const QString &sName, int nLevel, int nGroup, bool bHostage,const QString& sImagePath);
    Q_INVOKABLE bool HavePerson(int nID);

signals:
    void sceNameChanged(QString);
    void listPersonChanged(const QVariantList&);

private:
    void ClearPersonInfo();

private:
    QString m_sSceName;
    QMap<int,ScePersonInfo*> m_mapId2Person;
    QVariantList       m_listPerson;          /// 添加人员的简要信息


};

#endif // SCEMANAGER_H
