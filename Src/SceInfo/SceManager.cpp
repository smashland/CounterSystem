#include "SceManager.h"
#include <QJsonDocument>
#include <QFile>
#include <QApplication>
#include <QJsonArray>

SceManager::SceManager(QObject *parent)
    : QObject{parent}
{
    //    loadData("");
}

SceManager::~SceManager()
{
    ClearPersonInfo();
}

QList<ScePersonInfo*> SceManager::sces() const
{
    return(m_mapId2Person.values());
}

void SceManager::read()
{
    //打开文件
    QString filePath = QApplication::applicationDirPath() + "/Data/Project/scesInfo5.json";
    QFile loadFile(filePath);
    if(!loadFile.open(QIODevice::ReadOnly))
    {
        qDebug() << "could't open projects json";
        return;
    }
    //读取文件内容
    QByteArray allData = loadFile.readAll();
    loadFile.close();

    //以json格式读取内容到JsonDoc
    QJsonParseError jsonError;
    QJsonDocument jsonDoc(QJsonDocument::fromJson(allData, &jsonError));

    if(jsonError.error != QJsonParseError::NoError)
    {
        qDebug() << "json error!" << jsonError.errorString();
        return;
    }

    //创建jsonObject
    QJsonObject rootObj = jsonDoc.object();

    QStringList keys = rootObj.keys();
    for(int i = 0; i < keys.size(); i++)
    {
        qDebug() << "key" << i << " is:" << keys.at(i);
    }

    //因为是预先定义好的JSON数据格式，所以这里可以这样读取
    if(rootObj.contains("Person"))
    {
        QJsonObject subObj = rootObj.value("Person").toObject();
        qDebug() << "id is:" << subObj["ID"].toInt();
        qDebug() << "name is:" << subObj["Name"].toString();
        qDebug() << "type is:" << subObj["Grouptype"].toInt();
        qDebug() << "position is:" << subObj["Position"].toInt();
        qDebug() << "host is:" << subObj["Host"].toBool();
    }
}

void SceManager::write() const
{
    QJsonArray personArray;

    QJsonObject jsonSce;
    jsonSce.insert("Scename",m_sSceName);

    foreach(auto one,m_mapId2Person)
    {
        QJsonObject personObject;      
        personObject.insert("ID", one->getID());
        personObject.insert("Name", one->getName());
        personObject.insert("Grouptype", one->getGroupType());
        personObject.insert("Position", one->getPosition());
        personObject.insert("Host", one->getHostage());
        personArray.append(personObject);
    }
    jsonSce.insert("PersonArray",personArray);

    QString filePath = QApplication::applicationDirPath() + QString("/Data/Project/%1.json").arg(m_sSceName);
    QFile saveFile(filePath);
    if (!saveFile.open(QIODevice::WriteOnly))
    {
        qWarning("Couldn't open save file.");
    }

    /// 构建 Json 文档
    QJsonDocument document;
//    document.setArray(personArray);
//    saveFile.write(document.toJson());

    document.setObject(jsonSce);
    saveFile.write(document.toJson());
}

void SceManager::setSceName(const QString& sName)
{
    if(m_sSceName != sName)
    {
      m_sSceName = sName;
      emit sceNameChanged(m_sSceName);
    }
}
///添加方案
void SceManager::addScenario(const QString &sName)
{
    setSceName(sName);
    if(m_mapId2Person.size() > 0)
    {
        write();
        ClearPersonInfo();
    }
}
///添加人员
void SceManager::addPerson(int nID,const QString& sName, int nLevel, int nGroup, bool bHostage)
{
    ScePersonInfo *scePersonInfo=new ScePersonInfo(this);
    scePersonInfo->setID(nID);
    scePersonInfo->setName(sName);
    scePersonInfo->setPosition(nLevel);
    scePersonInfo->setGroupType(nGroup);
    scePersonInfo->setHostage(bHostage);
    m_mapId2Person.insert(nID,scePersonInfo);

//    for(auto one=m_mapId2Person.begin();
//        one != m_mapId2Person.end(); ++one)
//    {
//        ScePersonInfo* pPersonStatus=one.value();
//        qDebug()<<"1___________"<<pPersonStatus->getID();
//        qDebug()<<"2___________"<<pPersonStatus->getName();
//        qDebug()<<"3___________"<<pPersonStatus->getGroupType();
//        qDebug()<<"4___________"<<pPersonStatus->getPosition();
//        qDebug()<<"5___________"<<pPersonStatus->getHostage();
//    }

}

bool SceManager::HavePerson(int nID)
{
    return(m_mapId2Person.contains(nID));
}

void SceManager::ClearPersonInfo()
{
    foreach (auto one, m_mapId2Person)
    {
        delete one;
    }
    m_mapId2Person.clear();
}


