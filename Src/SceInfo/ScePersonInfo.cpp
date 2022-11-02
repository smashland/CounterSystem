#include "ScePersonInfo.h"
#include <QDebug>
#include <QFileInfo>
#include <QFile>
#include <ISceneCore.h>
#include <QApplication>

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

    if (json.contains("Host") && json["Host"].isBool())
        m_host = json["Host"].toBool();

    if (json.contains("ImagePath") && json["ImagePath"].isString())
        m_sImagePath = json["ImagePath"].toString();
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

void ScePersonInfo::praseExcelPerson(QXlsx::Worksheet *workSheet,int rowCount, int columnCount)
{
    for (int col = 1; col <= columnCount; col++)
    {
        QXlsx::Cell *cell = workSheet->cellAt(rowCount, col);
        switch (col) {
        case 1:
            m_ID=cell->value().toInt();
            break;
        case 2:
            m_Name=cell->value().toString();
            break;
        case 3:
            if(cell->value().toString()=="士兵")
            {
                m_Positon=1;
            }else if(cell->value().toString()=="军官")
            {
                m_Positon=2;
            }
            else if(cell->value().toString()=="")
            {
                m_Positon=0;
            }
            break;
        case 4:
            if(cell->value().toString()=="蓝")
            {
                m_Group=0;
            }
            else if(cell->value().toString()=="红")
            {
                m_Group=1;
            }
            break;
        case 5:
            if(cell->value().toString()=="是")
            {
                m_host=1;
            }
            else if(cell->value().toString()=="否")
            {
                m_host=0;
            }
            break;
        default:
            break;
        }

    }
//    qDebug()<<m_ID<<m_Name<<m_Positon<<m_Group<<m_host;
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
    return m_ID;
}

void ScePersonInfo::setName(QString sName)
{
    if(m_Name!=sName)
    {
        m_Name=sName;
        emit nameChanged(m_Name);
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
    }
}

bool ScePersonInfo::getHostage()
{
    return m_host;
}

void ScePersonInfo::setImagePath(QString sImagePath)
{
    m_sImagePath=copyFile(m_ID,sImagePath);
    emit imageChanged(m_sImagePath);
}

QString ScePersonInfo::getImagePath()
{
    return m_sImagePath;
}

QString ScePersonInfo::copyFile(int nID, const QString &strImagePath)
{
    QFileInfo fileInfo(strImagePath);
    QString newFilePath = QString("%1/Data/Project/Image/%2.%3").arg(QApplication::applicationDirPath()).arg(QString::number(nID)).arg(fileInfo.suffix());
    QFile file(newFilePath);
    if (file.exists())
    {
        file.remove();
    }
    QFile::copy(strImagePath,newFilePath);
//    QFileInfo pathInfo(newFilePath);
    return newFilePath;
}
