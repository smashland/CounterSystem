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
    Q_PROPERTY(float nLat MEMBER m_nLat WRITE setEarthLat NOTIFY latChanged)
    Q_PROPERTY(float nLon MEMBER m_nLon WRITE setEarthLon NOTIFY lonChanged)
    Q_PROPERTY(float nRDLat MEMBER m_nRDLat WRITE setEarthRDLat NOTIFY latRDChanged)
    Q_PROPERTY(float nRDLon MEMBER m_nRDLon WRITE setEarthRDLon NOTIFY lonRDChanged)


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
    void setEarthLat(float nlat);
    const int getEarthlat(){return m_nLat;}

    /**
      * @brief 设置地图纬度
      * @param nlon
      */
    void setEarthLon(float nlon);
    const int getEarthlon(){return m_nLon;}

    /**
      * @brief 设置rd地图经度
      * @param nRDlat
      */
    void setEarthRDLat(float nRDlat);
    const int getEarthRDlat(){return m_nRDLat;}

    /**
      * @brief 设置rd地图纬度
      * @param nRDlon
      */
    void setEarthRDLon(float nRDlon);
    const int getEarthRDlon(){return m_nRDLon;}

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
    void latChanged(float);
    void lonChanged(float);
    void latRDChanged(float);
    void lonRDChanged(float);
private:

    QString m_sEarthName;///地图名称
    QString m_sEarthPath;///地球路径
    float     m_nLat;      ///地图经度
    float     m_nLon;      ///地图纬度
    float     m_nRDLat;      ///地图右下角经度
    float     m_nRDLon;      ///地图右下角纬度
    int     m_nEarthNum; ///地图编号
};

#endif // CSETEARTH_H
