#include "SceManager.h"
#include <QJsonDocument>
#include <QFile>
SceManager::SceManager(QObject *parent)
    : QObject{parent}
{
    //    loadData("");
}

void SceManager::addPerson()
{
    qDebug()<<"添加人员99999999999999";

    // 构建 Json 对象 - Page
    QJsonObject personObject;
    ScePersonInfo *scePersonInfo=new ScePersonInfo;
    personObject.insert("id", scePersonInfo->getID());
    personObject.insert("Name", scePersonInfo->getName());
    personObject.insert("Grouptype", scePersonInfo->getGroupType());
    personObject.insert("Position", scePersonInfo->getPosition());
    personObject.insert("Host", scePersonInfo->getHostage());

    // 构建 Json 对象
    QJsonObject json;
    json.insert("Person", QJsonValue(personObject));

    QFile saveFile(QStringLiteral("scesInfo5.json"));
    if (!saveFile.open(QIODevice::WriteOnly)) {
        qWarning("Couldn't open save file.");
    }

    // 构建 Json 文档
    QJsonDocument document;
    document.setObject(json);

    saveFile.write(document.toJson());


}

///添加人员
int SceManager::addPerson(ScePersonInfo *scePersonInfo)
{

    qDebug()<<"ID666666666666666666666666";//ScePersonInfo *scePersonInfo
    // 构建 Json 对象 - Page
    QJsonObject personObject;

    personObject.insert("id", scePersonInfo->getID());
    personObject.insert("Name", scePersonInfo->getName());
    personObject.insert("Grouptype", scePersonInfo->getGroupType());
    personObject.insert("Position", scePersonInfo->getPosition());
    personObject.insert("Host", scePersonInfo->getHostage());

    //         // 构建 Json 对象
    QJsonObject json;
    //         json.insert("SceName", m_sceName/*"方案名称"*/);
    json.insert("Person", QJsonValue(personObject));

    //         qDebug() << "0000000000000000000"<<m_sceName;


    QFile saveFile(QStringLiteral("scesInfo3.json"));
    if (!saveFile.open(QIODevice::WriteOnly)) {
        qWarning("Couldn't open save file.");
    }
    // 构建 Json 文档
    QJsonDocument document;
    document.setObject(json);

    saveFile.write(document.toJson());

    return true;

    //    qDebug()<<"ID"<< m_scesPerson[0]->m_ID<<"Name:"; m_scesPerson
}

//int SceManager::addMember(ScePersonInfo *scePersonInfo)
//{

//}
