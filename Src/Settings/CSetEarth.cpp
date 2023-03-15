#include "CSetEarth.h"
#include <QFileInfo>
#include <QFile>
#include <QApplication>


CSetEarth::CSetEarth(QObject *parent)
    : QObject{parent}
{

}

void CSetEarth::setEarthName(const QString &sEarthName)
{
    if(sEarthName!=m_sEarthName)
    {
        m_sEarthName=sEarthName;
        emit earthNameChanged(m_sEarthName);
    }
}

void CSetEarth::setEarthPath(const QString &sEarthPath)
{
    if(sEarthPath!=m_sEarthPath)
    {
        //        m_sEarthPath=sEarthPath;
        m_sEarthPath=copyEarthFile(m_sEarthName,sEarthPath);
        emit earthPathChanged(m_sEarthPath);
    }
}

void CSetEarth::setEarthLat(float nlat)
{
    if(nlat!=m_nLat)
    {
        m_nLat=nlat;
        emit latChanged(m_nLat);
    }
}

void CSetEarth::setEarthLon(float nlon)
{
    if(nlon!=m_nLon)
    {
        m_nLon=nlon;
        emit lonChanged(m_nLon);
    }
}

void CSetEarth::setEarthRDLat(float nRDlat)
{
    if(nRDlat!=m_nRDLat)
    {
        m_nRDLat=nRDlat;
        emit latRDChanged(m_nRDLat);
    }
}

void CSetEarth::setEarthRDLon(float nRDlon)
{
    if(nRDlon!=m_nRDLon)
    {
        m_nRDLon=nRDlon;
        emit lonChanged(m_nRDLon);
    }
}

void CSetEarth::writeEarth(QJsonObject &rObj)
{
    rObj["Name"] = m_sEarthName;
    rObj["Path"] = m_sEarthPath;
    rObj["Lat"]  = m_nLat;
    rObj["Lon"]  = m_nLon;
    rObj["RDLat"]  = m_nRDLat;
    rObj["RDLon"]  = m_nRDLon;
}

void CSetEarth::readEarth(const QJsonObject &rObj)
{
    if (rObj.contains("Name") && rObj["Name"].isString())
        m_sEarthName = rObj["Name"].toString();

    if (rObj.contains("Path") && rObj["Path"].isString())
        m_sEarthPath = rObj["Path"].toString();

    if (rObj.contains("Lat") && rObj["Lat"].isDouble())
        m_nLat = rObj["Lat"].toDouble();

    if (rObj.contains("Lon") && rObj["Lon"].isDouble())
        m_nLon = rObj["Lon"].toDouble();

    if (rObj.contains("RDLat") && rObj["RDLat"].isDouble())
        m_nRDLat = rObj["RDLat"].toDouble();

    if (rObj.contains("RDLon") && rObj["RDLon"].isDouble())
        m_nRDLon = rObj["RDLon"].toDouble();
}

void CSetEarth::setEarthNum(int EarthNum)
{
    m_nEarthNum=EarthNum;
}



QString CSetEarth::copyEarthFile(const QString &sEarthName,const QString &strImagePath)
{
    QFileInfo fileInfo(strImagePath);

    qDebug()<<"测试地图数量："<<m_nEarthNum;
    QString newFilePath = QString("%1/Data/Earth/Map/%2").arg(QApplication::applicationDirPath()).arg(m_nEarthNum);
    ///tiff
    if(fileInfo.suffix()=="tif"||fileInfo.suffix()=="jpg"||fileInfo.suffix()=="png")
    {
        newFilePath = QString("%1.%2").arg(newFilePath).arg(fileInfo.suffix());
        QFile file(newFilePath);
        if (file.exists())
        {
            file.remove();
        }
        QFile::copy(strImagePath,newFilePath);

    }
    else if(fileInfo.suffix()=="xml")
    {
        QDir  fromDir(fileInfo.path());
        QDir  toDir(newFilePath);
        qCopyDirectory(fromDir,toDir,true);
        newFilePath=QString("%1/%2").arg(newFilePath).arg(fileInfo.fileName());
    }
    return newFilePath;
}

bool CSetEarth::qCopyDirectory(const QDir& fromDir, const QDir& toDir, bool bCoverIfFileExists)
{
    QDir formDir_ = fromDir;
    QDir toDir_ = toDir;

    if(!toDir_.exists())
    {
        if(!toDir_.mkdir(toDir.absolutePath()))
            return false;
    }

    QFileInfoList fileInfoList = formDir_.entryInfoList();
    foreach(QFileInfo fileInfo, fileInfoList)
    {
        if(fileInfo.fileName() == "." || fileInfo.fileName() == "..")
            continue;

        //拷贝子目录
        if(fileInfo.isDir())
        {
            //递归调用拷贝
            if(!qCopyDirectory(fileInfo.filePath(), toDir_.filePath(fileInfo.fileName()),true))
                return false;
        }
        //拷贝子文件
        else
        {
            if(bCoverIfFileExists && toDir_.exists(fileInfo.fileName()))
            {
                toDir_.remove(fileInfo.fileName());
            }
            if(!QFile::copy(fileInfo.filePath(), toDir_.filePath(fileInfo.fileName())))
            {
                return false;
            }
        }
    }
    return true;
}
