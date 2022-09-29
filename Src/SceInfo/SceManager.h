#ifndef SCEMANAGER_H
#define SCEMANAGER_H

#include <QObject>
#include "SceInfo.h"

class SceManager : public QObject
{
    Q_OBJECT
public:
    explicit SceManager(QObject *parent = nullptr);
    ~SceManager();
    SceManager(const QString &name);

    Q_PROPERTY(QString sceName READ getSceName WRITE setSceName NOTIFY sceNameChanged)
    Q_PROPERTY(QVariantList listPerson MEMBER m_listPerson NOTIFY listPersonChanged)
//    Q_PROPERTY(QString m_text READ  WRITE setSceName NOTIFY sceNameChanged)


    /**
      * @brief 添加方案
      * @param sceName
      */
    Q_INVOKABLE CSceInfo* addScenari(const QString &sceName);

    /**
     * @brief 删除方案
     * @param sceName
     * @return
     */
    Q_INVOKABLE bool deleteScenario(const QString &sceName);

    /**
     * @brief 修改方案
     * @param sceName
     * @return
     */
     CSceInfo* modifyScenario(const QString &sceName);

    /**
     * @brief 查找方案
     * @param sceName
     * @return
     */
   Q_INVOKABLE  CSceInfo* findScenario(const QString &sceName);

    /**
     * @brief 获取所有的方案信息
     * @return
     */
    Q_INVOKABLE QList<CSceInfo*> getSceAll();




    ///读写文件保存方案信息
    Q_INVOKABLE void read();
    Q_INVOKABLE void write();
    Q_INVOKABLE void modify();
    Q_INVOKABLE QString text();

    void loadImagePath(const QString &strImagePath);

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

signals:
    void sceNameChanged(QString);
    void listPersonChanged(const QVariantList&);
protected:
    /**
     * @brief 读取单个文件
     * @param sname
     */
    void read(const QString &sname);
private:
    void ClearSceInfo();

private:
    QString m_sSceName;
    QMap<QString,CSceInfo*> m_mapName2SceInfo; /// 名称和方案信息的配对
    QVariantList       m_listPerson;          /// 添加人员的简要信息
    QStringList m_listSceFileName;
    QString m_text;


};

#endif // SCEMANAGER_H
