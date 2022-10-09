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

    Q_PROPERTY(QList<QObject*> listSces MEMBER m_listSces NOTIFY listScesChanged)


    /**
     * @brief 创建一个方案
     * @return
     */
    Q_INVOKABLE CSceInfo* createSceneri();
    /**
      * @brief 添加方案
      * @param sceName
      */
    Q_INVOKABLE CSceInfo* addScenari(const QString &sceName,CSceInfo* pSceInfo);

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
//    Q_INVOKABLE QList<CSceInfo*> getSceAll();
      Q_INVOKABLE QList<QObject*> getSceAll();




    ///读写文件保存方案信息
    Q_INVOKABLE void read();
    Q_INVOKABLE void write();
    void modify();

    void loadImagePath(const QString &strImagePath);

    /**
      * @brief 显示选中方案的信息
      */
    void showScenfo(QString sSceName);

    /**
      * @brief 显示所有方案
      */
    Q_INVOKABLE QStringList showSceList();

//    /**
//      * @brief 设置方案名称
//      * @param sName
//      */
//    Q_INVOKABLE void setSceName(const QString &sName);
//    Q_INVOKABLE QString getSceName(){ return(m_sSceName);}

    /**
      * @brief 添加方案
      * @param sName
      */
     void addScenario(const QString &sName);

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
     void addPerson(int nID, const QString &sName, int nLevel, int nGroup, bool bHostage,const QString& sImagePath);

signals:
    void listScesChanged();
protected:
    /**
     * @brief 读取单个文件
     * @param sname
     */
    void read(const QString &sname);
private:
    void ClearSceInfo();

private:
//    QString m_sSceName;
    QMap<QString,CSceInfo*> m_mapName2SceInfo; /// 名称和方案信息的配对
    QStringList m_listSceFileName;
    QList<QObject*> m_listSces;


};

#endif // SCEMANAGER_H
