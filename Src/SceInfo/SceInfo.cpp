#include <QJsonArray>
#include "SceInfo.h"

CSceInfo::CSceInfo(QObject *parent)
    : QObject{parent}
{
    ClearMap();
}

///设置方案名称
void CSceInfo::setSceName(const QString &sName)
{
    qDebug()<<"测试方案名称"+sName;
    if(m_sSceName != sName)
    {
        m_sSceName = sName;
        emit sceNameChanged(m_sSceName);
    }
}

/// 增加成员
ScePersonInfo *CSceInfo::addPerson(int nID)
{
    auto findOne = m_mapId2Person.find(nID);    
    if(m_mapId2Person.end() == findOne)
    {
        ScePersonInfo* pNewOne = new ScePersonInfo(this);
        pNewOne->setID(nID);
        m_mapId2Person.insert(nID,pNewOne);
        m_listPerson.append(pNewOne);
        emit personChanged();
        return(pNewOne);
    }
    else
    {
        return(nullptr);
    }
}

ScePersonInfo *CSceInfo::modifyPerson(int nID)
{
    auto findOne = m_mapId2Person.find(nID);
    if(m_mapId2Person.end() != findOne)
    {
        m_mapId2Person.value(nID,findOne.value());
        return(findOne.value());
    }
    else
    {
        return(nullptr);
    }

}

/// 根据ID查找人员信息
ScePersonInfo *CSceInfo::findPerson(int nID)
{ 
    auto findOne = m_mapId2Person.find(nID);
    return m_mapId2Person.end() == findOne ? nullptr : findOne.value();
}

/// 获取所有的人员信息
QList<QObject *> CSceInfo::getAll()
{
    QList<QObject*> listObjct;
    foreach(auto one , m_mapId2Person){
        listObjct.append(one);
    }
    return(listObjct);
}

/// 删除指定ID的人员
bool CSceInfo::deletePerson(int nID)
{
    auto findOne = m_mapId2Person.find(nID);
    if(m_mapId2Person.end() != findOne)
    {
        delete findOne.value();
        m_mapId2Person.erase(findOne);
        return(true);
    }
    else
    {
        return(false);
    }
}

/// 从Json中解析出来数据
void CSceInfo::Prase(const QJsonArray &rObj)
{
    ClearMap();

    for (int i = 0; i < rObj.size(); ++i)
    {
        ScePersonInfo *scePersonInfo=new ScePersonInfo(this);
        scePersonInfo->readPerson(rObj.at(i).toObject());
        m_mapId2Person.insert(rObj.at(i).toObject().value("ID").toInt(),scePersonInfo);
        m_listPerson.append(scePersonInfo);
    }
}

/// 将信息保存到Json中
void CSceInfo::Save(QJsonArray &rArray)
{
    foreach(auto one,m_mapId2Person)
    {
        QJsonObject personObject;
        one->writePerson(personObject);
        rArray.append(personObject);
    }
    foreach(auto one , m_listPerson)
    {
        auto oneNote = qobject_cast<ScePersonInfo*>(one);
        if(nullptr != oneNote)
        {
            QJsonObject personObject;
            oneNote->writePerson(personObject);
            rArray.append(personObject);
        }
    }
}

/// 清空人员信息
void CSceInfo::ClearMap()
{
    foreach (auto one, m_mapId2Person)
    {
        delete one;
    }
    m_mapId2Person.clear();
    m_listPerson.clear();
}
