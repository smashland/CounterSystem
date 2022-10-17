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
