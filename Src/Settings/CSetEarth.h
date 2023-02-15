#ifndef CSETEARTH_H
#define CSETEARTH_H

#include <QObject>
#include <QJsonObject>
#include <QDir>

class CSetEarth : public QObject
{
    Q_OBJECT
public:
    explicit CSetEarth(QObject *parent = nullptr);


    Q_PROPERTY(QString earthName MEMBER m_sEarthName WRITE setEarthName NOTIFY earthNameChanged)
    Q_PROPERTY(QString earthPath MEMBER m_sEarthPath WRITE setEarthPath NOTIFY earthPathChanged)
    Q_PROPERTY(int nLat MEMBER m_nLat WRITE setEarthLat NOTIFY latChanged)
    Q_PROPERTY(int nLon MEMBER m_nLon WRITE setEarthLon NOTIFY lonChanged)


    /**
      * @brief 设置地图名称
      * @param sEarthName
      */
    void setEarthName(const QString &sEarthName);
    const QString getEarthName(){return m_sEarthName;}

    /**
      * @brief 设置地图路径
      * @param sEarthPath
      */
    void setEarthPath(const QString &sEarthPath);
    const QString getEarthPath(){return m_sEarthPath;}

    /**
      * @brief 设置地图经度
      * @param nlat
      */
    void setEarthLat(int nlat);
    const int getEarthlat(){return m_nLat;}

    /**
      * @brief 设置地图纬度
      * @param nlon
      */
    void setEarthLon(int nlon);
    const int getEarthlon(){return m_nLon;}

    /**
     * @brief 将信息保存到Json对象中
     * @param rObj
     */
    void writeEarth(QJsonObject& rObj);

    /**
     * @brief 从json中读取
     * @param rObj
     */
    void readEarth(const QJsonObject& rObj);

    /**
     * @brief 地图设置编号
     * @param num
     */
    void setEarthNum(int EarthNum);

    QString copyEarthFile(const QString &sEarthName,const QString &strImagePath);
    bool qCopyDirectory(const QDir& fromDir, const QDir& toDir, bool bCoverIfFileExists);
signals:
    void earthNameChanged(QString);
    void earthPathChanged(QString);
    void latChanged(int);
    void lonChanged(int);
private:

    QString m_sEarthName;///地图名称
    QString m_sEarthPath;///地球路径
    int     m_nLat;      ///地图经度
    int     m_nLon;      ///地图纬度
    int     m_nEarthNum; ///地图编号
};

#endif // CSETEARTH_H
