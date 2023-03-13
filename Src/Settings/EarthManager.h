#ifndef EARTHMANAGER_H
#define EARTHMANAGER_H

#include <QObject>
#include "CSetEarth.h"
#include "qdom.h"

class EarthManager : public QObject
{
    Q_OBJECT
public:

    Q_PROPERTY(QList<QObject*> earthList MEMBER m_listEarth  NOTIFY earthChanged)
    Q_PROPERTY(QString currentName MEMBER m_sCurrentName NOTIFY currentNameChanged )
    Q_PROPERTY(int currentLat MEMBER m_nCurrentLat NOTIFY currentLatChanged)
    Q_PROPERTY(int currentLon MEMBER m_nCurrentLon NOTIFY currentLonChanged)

    explicit EarthManager(QObject *parent = nullptr);
    ~EarthManager();

    Q_INVOKABLE CSetEarth* createMap();
    /**
      * @brief 添加地图
      * @param earthName
      */
    Q_INVOKABLE CSetEarth* addMaps(const QString &earthName,const QString &earthPath);

    /**
     * @brief 删除地图
     * @param earthName
     * @return
     */

    Q_INVOKABLE bool deleteEarth(const QString &earthName,const QString &earthInfo);
    bool removeEarthFile(const QString &earthInfo);

    Q_INVOKABLE void saveFile();

    /**
     * @brief 解析地图XML文件
     */
    Q_INVOKABLE void praseEarthXml(QString sEarthPath);

    void modifyEarthXml(QDomElement root,QString tagName,QString itemName,QString sEarthPath);
    /**
     * @brief 保存现在点击的地图信息
     * @param earthName
     * @param lat
     * @param lon
     */
    Q_INVOKABLE void saveCurrentEarth(const QString &earthName,int lat,int lon);

    /**
     * @brief 解析当前的地图文件
     */
    Q_INVOKABLE void praseCurrentEarth();

    QString getCurrentEarthName(){return m_sCurrentName;}
    QString getCurrentEarthLoction();

    int earthNum();

private:
    void ClearEarthInfo();  ///清空
signals:
    void earthChanged();
    void currentNameChanged();
    void currentLatChanged();
    void currentLonChanged();
    void beginEdit();
    void endEdit();
protected:
    void ReadFile();
private:
    QList<QObject*> m_listEarth;
    QMap<QString,CSetEarth*> m_mapName2EarthInfo;   /// 名称和地图信息的配对

    QString m_sCurrentName;
    int     m_nCurrentLat;
    int     m_nCurrentLon;
};

#endif // EARTHMANAGER_H
