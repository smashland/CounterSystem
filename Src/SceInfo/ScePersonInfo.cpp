#include "ScePersonInfo.h"
#include <QDebug>
#include <QFileInfo>
#include <QFile>
#include <ISceneCore.h>

ScePersonInfo::ScePersonInfo(QObject *parent)
    : QObject{parent}
{

}

void ScePersonInfo::readPerson(const QJsonObject &json)
{
    if (json.contains("ID") && json["ID"].isDouble())
        m_ID = json["ID"].toInt();

    if (json.contains("Name") && json["Name"].isString())
        m_Name = json["Name"].toString();

    if (json.contains("Grouptype") && json["Grouptype"].isDouble())
        m_Group = json["Grouptype"].toInt();

    if (json.contains("Position") && json["Position"].isDouble())
        m_Positon = json["Position"].toInt();

    if (json.contains("Host") && json["Host"].isDouble())
        m_host = json["Host"].toInt();

    if (json.contains("ImagePath") && json["ImagePath"].isString())
        m_sImagePath = json["ImagePath"].toString();

    qDebug()<<"id"<<m_ID<<"name"<<m_Name<<"type"<<m_Group<<"position"<<m_Positon<<"host"<<m_host;
}

void ScePersonInfo::writePerson(QJsonObject &json) const
{
    json["ID"]         = m_ID;
    json["Name"]       = m_Name;
    json["Grouptype"]  = m_Group;
    json["Position"]   = m_Positon;
    json["Host"]       = m_host;
    json["ImagePath"]  = m_sImagePath;
}
////设置士兵信息
void ScePersonInfo::setID(int nID)
{
    if(m_ID!=nID)
    {
        m_ID=nID;
        emit IDChanged(m_ID);
        qDebug()<<"编号————"<<m_ID;
    }
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

void ScePersonInfo::setImagePath(QString sImagePath)
{
    m_sImagePath=copyFile(sImagePath);
    qDebug()<<"000000000000000path"<<m_sImagePath;
}

QString ScePersonInfo::getImagePath()
{
    return m_sImagePath;
}

QString ScePersonInfo::copyFile(const QString &strImagePath, const QString &folderName)
{
    QFileInfo fileInfo(strImagePath);
    QString fileName = folderName + "\\" + fileInfo.fileName();
    qDebug()<<"源地址————"<<strImagePath;
    qDebug()<<"目标地址————"<<GetDataPath().c_str() + fileName;
    QFile::copy(strImagePath, GetDataPath().c_str() + fileName);
    QString imagePath=GetDataPath().c_str() + fileName;

    return imagePath;
}
