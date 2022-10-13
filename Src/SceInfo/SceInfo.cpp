#include <QJsonArray>
#include "SceInfo.h"

CSceInfo::CSceInfo(QObject *parent)
    : QObject{parent}
{
    //    ClearMap();
}

///设置方案名称
void CSceInfo::setSceName(const QString &sName)
{
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
        qDebug()<<"新增人员"<<m_mapId2Person.isEmpty();//没有找到
        if(!m_mapId2Person.contains(nID))
        {
            QHash<int, ScePersonInfo*>::iterator i;
            for( i=m_hashId2Person.begin(); i!=m_hashId2Person.end(); ++i)
            {
                qDebug()<<"删除原有的人";
                m_listPerson.removeOne(i.value());
                m_mapId2Person.remove(i.key());
                emit personChanged();
            }
            ScePersonInfo* pNewOne = new ScePersonInfo(this);
            pNewOne->setID(nID);
            m_mapId2Person.insert(nID,pNewOne);
            m_listPerson.append(pNewOne);
            emit personChanged();
            return(pNewOne);
        }
        else
        {
            qDebug()<<"新增人员id重复";
            return nullptr;
        }
    }
    else
    {
        qDebug()<<"找到相同的数值"<<m_hashId2Person.isEmpty()<<"===="<<nID;//找到
        QHash<int, ScePersonInfo*>::iterator i;
        for( i=m_hashId2Person.begin(); i!=m_hashId2Person.end(); ++i)
        {
            qDebug()<<"删除原有的人";
            m_listPerson.removeOne(i.value());
            m_mapId2Person.remove(i.key());
            emit personChanged();
        }

        if(!m_mapId2Person.contains(nID))
        {
            qDebug()<<"修改原有的人";
            ScePersonInfo* pNewOne = new ScePersonInfo(this);
            pNewOne->setID(nID);
            m_mapId2Person.insert(nID,pNewOne);
            m_listPerson.append(pNewOne);
            emit personChanged();
            return(pNewOne);
        }
        else
        {
            qDebug()<<"存在原有的人";
            QHash<int, ScePersonInfo*>::iterator i;
            for( i=m_hashId2Person.begin(); i!=m_hashId2Person.end(); ++i)
            {
                m_mapId2Person.insert(i.key(),i.value());
                m_listPerson.append(i.value());
                emit personChanged();
            }
            return(nullptr);
        }
    }
}

ScePersonInfo *CSceInfo::addPerson(int nID, ScePersonInfo *pScePersonInfo)
{
    auto findOne = m_mapId2Person.find(nID);
    if(m_mapId2Person.end() == findOne)
    {
        if(!m_mapId2Person.contains(nID))
        {
            pScePersonInfo->setID(nID);
            m_mapId2Person.insert(nID, pScePersonInfo);
            m_listPerson.append(pScePersonInfo);
            emit personChanged();
            return(pScePersonInfo);
        }
        else
        {
            qDebug()<<"含有相同的编号"<<nID;

        }
    }
    return (nullptr);
}

/// 根据ID查找人员信息
QObject *CSceInfo::findPerson(int nID)
{
    m_hashId2Person.clear();
    auto findOne = m_mapId2Person.find(nID);
    if(m_mapId2Person.end() != findOne)
    {
        m_hashId2Person.insert(nID,findOne.value());
        return(findOne.value());
    }
    else
    {
        return nullptr;
    }
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
        m_listPerson.removeOne(findOne.value());
        emit personChanged();
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
        //        rArray.append(personObject);
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
    qDebug()<<"清空人员信息";
    foreach (auto one, m_mapId2Person)
    {
        delete one;
    }
    m_mapId2Person.clear();
    m_hashId2Person.clear();
    m_listPerson.clear();
}
