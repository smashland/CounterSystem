#ifndef EARTHMANAGER_H
#define EARTHMANAGER_H

#include <QObject>
#include "CSetEarth.h"

class EarthManager : public QObject
{
    Q_OBJECT
public:

    Q_PROPERTY(QList<QObject*> earthList MEMBER m_listEarth  NOTIFY earthChanged)

    explicit EarthManager(QObject *parent = nullptr);

    Q_INVOKABLE CSetEarth* createEarth();

    /**
      * @brief 添加地图
      * @param earthName
      */
    Q_INVOKABLE CSetEarth* addMaps(const QString &earthName);

    /**
     * @brief 删除地图
     * @param earthName
     * @return
     */
    Q_INVOKABLE bool deleteEarth(QObject *pEarth);

    Q_INVOKABLE void saveFile();


signals:
    void earthChanged();
protected:
    void ReadFile();

private:
    QList<QObject*> m_listEarth;

    QMap<QString,CSetEarth*> m_mapName2EarthInfo;   /// 名称和地图信息的配对
};

#endif // EARTHMANAGER_H
