#include "ScePersonInfo.h"
#include <QDebug>

ScePersonInfo::ScePersonInfo(QObject *parent)
    : QObject{parent}
{

}
////设置士兵信息
void ScePersonInfo::setID(int nID)
{
//    if(m_ID!=nID)
//    {
//        m_ID=nID;
//        emit(IDChanged(m_ID));
//    }
     m_ID=nID;
    qDebug()<<"id99999999"<<m_ID;
}

int ScePersonInfo::getID() const
{
    return m_ID;
}

void ScePersonInfo::setName(QString sName)
{
    if(m_Name!=sName)
    {
        m_Name=sName;
        emit(nameChanged(m_Name));
    }
}

QString ScePersonInfo::getName()
{
    return m_Name;
}

void ScePersonInfo::setPosition(QString sPosition)
{
    m_Positon=sPosition;
}

QString ScePersonInfo::getPosition()
{
    return m_Positon;
}

void ScePersonInfo::setGroupType(QString groupType)
{
    m_Group=groupType;
}

QString ScePersonInfo::getGroupType()
{
    return m_Group;
}

void ScePersonInfo::setHostage(int bHostage)
{
    m_host=bHostage;
}

bool ScePersonInfo::getHostage()
{
    return m_host;
}
