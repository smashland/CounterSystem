#include "ScePersonInfo.h"
#include <QDebug>

ScePersonInfo::ScePersonInfo(QObject *parent)
    : QObject{parent}
{

}
////设置士兵信息
void ScePersonInfo::setID(int nID)
{
    if(m_ID!=nID)
    {
        m_ID=nID;
        emit IDChanged(m_ID);        
    }
}

int ScePersonInfo::getID() const
{
    qDebug()<<"编号————"<<m_ID;
    return m_ID;
}

void ScePersonInfo::setName(QString sName)
{
    if(m_Name!=sName)
    {
        m_Name=sName;
        emit nameChanged(m_Name);
        qDebug()<<"姓名————"<<m_Name;
    }
}

QString ScePersonInfo::getName()
{
    return m_Name;
}

void ScePersonInfo::setPosition(int sPosition)
{
    if(m_Positon!=sPosition)
    {
        m_Positon=sPosition;
        emit positionChanged(sPosition);
        qDebug()<<"职务————"<<m_Positon;
    }
}

int ScePersonInfo::getPosition()
{
    return m_Positon;
}

void ScePersonInfo::setGroupType(int groupType)
{
    if(m_Group!=groupType)
    {
        m_Group=groupType;
        emit groupTypeChanged(groupType);
        qDebug()<<"类型————"<<m_Group;
    }
}

int ScePersonInfo::getGroupType()
{
    return m_Group;
}


void ScePersonInfo::setHostage(bool bHostage)
{
    if(m_host!=bHostage)
    {
        m_host=bHostage;
        emit hostageChanged(bHostage);
        qDebug()<<"人质————"<<m_host;
    }
}

bool ScePersonInfo::getHostage()
{
    return m_host;
}

