#include "SceManager.h"
#include <QJsonDocument>
#include <QFile>
#include <QApplication>

SceManager::SceManager(QObject *parent)
    : QObject{parent}
{
    //    loadData("");
}

QList<ScePersonInfo*> SceManager::sces() const
{
    return(m_mapId2Person.values());
}

void SceManager::read()
{
    QJsonObject json;


}

void SceManager::write() const
{

    QJsonObject json;
    json.insert("Scename",m_sSceName);

    foreach(auto one,m_mapId2Person)
    {
        QJsonObject personObject;
        personObject.insert("ID", one->getID());
        personObject.insert("Name", one->getName());
        personObject.insert("Grouptype", one->getGroupType());
        personObject.insert("Position", one->getPosition());
        personObject.insert("Host", one->getHostage());
        json.insert("Person", QJsonValue(personObject));
    }

    QString filePath = QApplication::applicationDirPath() + "/Data/Project/scesInfo5.json";
    QFile saveFile(filePath);
    if (!saveFile.open(QIODevice::WriteOnly))
    {
        qWarning("Couldn't open save file.");
    }

    /// 构建 Json 文档
    QJsonDocument document;
    document.setObject(json);
    saveFile.write(document.toJson());
}

void SceManager::setSceName(const QString& sName)
{
    m_sSceName = sName;
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

    write();
}

bool SceManager::HavePerson(int nID)
{
    return(m_mapId2Person.contains(nID));
}


void SceManager::addPerson()
{
    qDebug()<<"添加人员99999999999999";


//    // 构建 Json 对象 - Page
//    QJsonObject personObject;
//    ScePersonInfo *scePersonInfo=new ScePersonInfo(this);
//    personObject.insert("id", scePersonInfo->getID());
//    personObject.insert("Name", scePersonInfo->getName());
//    personObject.insert("Grouptype", scePersonInfo->getGroupType());
//    personObject.insert("Position", scePersonInfo->getPosition());
//    personObject.insert("Host", scePersonInfo->getHostage());

//    // 构建 Json 对象
//    QJsonObject json;
//    json.insert("Person", QJsonValue(personObject));

//    QFile saveFile(QStringLiteral("scesInfo5.json"));
//    if (!saveFile.open(QIODevice::WriteOnly)) {
//        qWarning("Couldn't open save file.");
//    }

//    // 构建 Json 文档
//    QJsonDocument document;
//    document.setObject(json);

//    saveFile.write(document.toJson());


//    return nullptr;


}


