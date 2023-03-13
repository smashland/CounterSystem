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

void CSetEarth::setEarthLat(int nlat)
{
    if(nlat!=m_nLat)
    {
        m_nLat=nlat;
        emit latChanged(m_nLat);
    }
}

void CSetEarth::setEarthLon(int nlon)
{
    if(nlon!=m_nLon)
    {
        m_nLon=nlon;
        emit lonChanged(m_nLon);
    }
}

void CSetEarth::writeEarth(QJsonObject &rObj)
{
    rObj["Name"] = m_sEarthName;
    rObj["Path"] = m_sEarthPath;
//    rObj["Lat"]  = m_nLat;
//    rObj["Lon"]  = m_nLon;
}

void CSetEarth::readEarth(const QJsonObject &rObj)
{
    if (rObj.contains("Name") && rObj["Name"].isString())
        m_sEarthName = rObj["Name"].toString();

    if (rObj.contains("Path") && rObj["Path"].isString())
        m_sEarthPath = rObj["Path"].toString();

//    if (rObj.contains("Lat") && rObj["Lat"].isDouble())
//        m_nLat = rObj["Lat"].toInt();

//    if (rObj.contains("Lon") && rObj["Lon"].isDouble())
//        m_nLon = rObj["Lon"].toInt();
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
    if(fileInfo.suffix()=="tif")
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
