#include "CSetEarth.h"

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
        m_sEarthPath=sEarthPath;
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
    rObj["Lat"]  = m_nLat;
    rObj["Lon"]  = m_nLon;
}

void CSetEarth::readEarth(const QJsonObject &rObj)
{
    if (rObj.contains("Name") && rObj["Name"].isString())
        m_sEarthName = rObj["Name"].toString();

    if (rObj.contains("Path") && rObj["Path"].isString())
        m_sEarthPath = rObj["Path"].toString();

    if (rObj.contains("Lat") && rObj["Lat"].isDouble())
        m_nLat = rObj["Lat"].toInt();

    if (rObj.contains("Lon") && rObj["Lon"].isDouble())
        m_nLon = rObj["Lon"].toInt();
}
