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
    Q_PROPERTY(QString currentSceName MEMBER m_sCurrentSceName NOTIFY currentSceNameChanged(QString))


    ///读写文件保存方案信息
    Q_INVOKABLE void read();

    Q_INVOKABLE void write();

    /**
     * @brief 导入方案
     * @param strImagePath
     * @param folderName
     * @return
     */
    Q_INVOKABLE QString importSce(const QString &strImagePath);

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
    Q_INVOKABLE  QObject* findScenario(const QString &sceName);

    /**
     * @brief 获取所有的方案信息
     * @return
     */
    Q_INVOKABLE QList<QObject*> getSceAll();

    /**
      * @brief 显示所有方案
      */
    Q_INVOKABLE QStringList showSceList();

    /**
      * @brief 删除方案文件
      * @param sName
      */
    bool removeSceFile(const QString &sName);

    /**
     * @brief 得到加载时候的方案名称
     * @param sceName
     * @return
     */
    Q_INVOKABLE void setCurrentSceName(const QString &currentSceName);
    Q_INVOKABLE QString getCurrentSceName(){return m_sCurrentSceName;}

    Q_INVOKABLE void importSceInfo(const QString &strImagePath);
    void parseExcel(const QString &strImagePath);

signals:
    void listScesChanged();
    void currentSceNameChanged(QString);
protected:
    /**
     * @brief 读取单个文件
     * @param sname
     */
    void read(const QString &sname);
private:
    void ClearSceInfo();  ///清空

private:
    QMap<QString,CSceInfo*> m_mapName2SceInfo;   /// 名称和方案信息的配对
    QStringList m_listSceFileName;               ///存放文件
    QList<QObject*> m_listSces;                  ///方案信息
    QHash<QString,CSceInfo*> m_hashName2SceInfo; ///存放查看的方案信息
    QString m_sCurrentSceName; ///加载时的方案名称

    QList<QString> m_listTitle;      ///导入excel时存放每列的标头m_listTitle

};

#endif // SCEMANAGER_H
