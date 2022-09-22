#include "SceManager.h"
#include <QJsonDocument>
#include <QFile>
#include <QApplication>
#include <QJsonArray>
#include <QDir>
#include <ISceneCore.h>
#include <QDesktopServices>

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
    QString filePath = QApplication::applicationDirPath() + QString("/Data/Project/%1").arg("222.json"/*sSceName*/);
    qDebug()<<"9999999999999"<<filePath;
    QFile loadFile(filePath);
    if(!loadFile.open(QIODevice::ReadOnly))
    {
        qDebug() << "could't open projects json";
        return;
    }
    //读取文件内容
    QByteArray allData = loadFile.readAll();
    //    loadFile.close();

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

    //    //因为是预先定义好的JSON数据格式，所以这里可以这样读取
    //    if(rootObj.contains("PersonArray"))
    //    {
    //        QJsonObject subObj = rootObj.value("PersonArray").toObject();
    //        qDebug() << "id is:" << subObj["ID"].toInt();
    //        qDebug() << "name is:" << subObj["Name"].toString();
    //        qDebug() << "type is:" << subObj["Grouptype"].toInt();
    //        qDebug() << "position is:" << subObj["Position"].toInt();
    //        qDebug() << "host is:" << subObj["Host"].toBool();
    //        qDebug() << "image is:" << subObj["ImagePath"].toString();
    //    }

    //因为是预先定义好的JSON数据格式，所以这里可以这样读取
    if(rootObj.contains("PersonArray"))
    {
        QJsonArray subArray = rootObj.value("PersonArray").toArray();
        for (int i = 0; i < subArray.size(); ++i)
        {
            //            ScePersonInfo *scePersonInfo=new ScePersonInfo(this);
            //            scePersonInfo->setID(subArray.at(i).toObject().value("ID").toInt());
            //            scePersonInfo->setName(subArray.at(i).toObject().value("Name").toString());
            //            scePersonInfo->setPosition(subArray.at(i).toObject().value("Position").toInt());
            //            scePersonInfo->setGroupType(subArray.at(i).toObject().value("Grouptype").toInt());
            //            scePersonInfo->setHostage(subArray.at(i).toObject().value("Host").toBool());
            //            scePersonInfo->setImagePath(subArray.at(i).toObject().value("ImagePath").toString());
            //            m_mapId2Person.insert(subArray.at(i).toObject().value("ID").toInt(),scePersonInfo);

            qDebug() << subArray.at(i).toObject().value("ID").toInt();
            qDebug() << subArray.at(i).toObject().value("Name").toString();
            qDebug() << subArray.at(i).toObject().value("Grouptype").toInt();
            qDebug() << subArray.at(i).toObject().value("Position").toInt();
            qDebug() << subArray.at(i).toObject().value("Host").toBool();
            qDebug() << subArray.at(i).toObject().value("ImagePath").toString();
        }
    }
    loadFile.close();
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
        personObject.insert("ImagePath",one->getImagePath());
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

void SceManager::showPersonInfo(int nID)
{
    //打开文件
    QString filePath = QApplication::applicationDirPath() + QString("/Data/Project/%1").arg(m_sSceName);
    qDebug()<<"9999999999999"<<filePath;
    QFile loadFile(filePath);
    if(!loadFile.open(QIODevice::ReadOnly))
    {
        qDebug() << "could't open projects json";
        return;
    }
    //读取文件内容
    QByteArray allData = loadFile.readAll();
    //    loadFile.close();

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


    //因为是预先定义好的JSON数据格式，所以这里可以这样读取
    if(rootObj.contains("PersonArray"))
    {
        QJsonArray subArray = rootObj.value("PersonArray").toArray();
        for (int i = 0; i < subArray.size(); ++i)
        {
            if(subArray.at(i).toObject().value("ID").toInt()==nID)
            {
//                ScePersonInfo *scePersonInfo=new ScePersonInfo(this);
//                scePersonInfo->setID(subArray.at(i).toObject().value("ID").toInt());
//                scePersonInfo->setName(subArray.at(i).toObject().value("Name").toString());
//                scePersonInfo->setPosition(subArray.at(i).toObject().value("Position").toInt());
//                scePersonInfo->setGroupType(subArray.at(i).toObject().value("Grouptype").toInt());
//                scePersonInfo->setHostage(subArray.at(i).toObject().value("Host").toBool());
//                scePersonInfo->setImagePath(subArray.at(i).toObject().value("ImagePath").toString());
//                m_mapId2Person.insert(subArray.at(i).toObject().value("ID").toInt(),scePersonInfo);

                qDebug() << subArray.at(i).toObject().value("ID").toInt();
                qDebug() << subArray.at(i).toObject().value("Name").toString();
                qDebug() << subArray.at(i).toObject().value("Grouptype").toInt();
                qDebug() << subArray.at(i).toObject().value("Position").toInt();
                qDebug() << subArray.at(i).toObject().value("Host").toBool();
                qDebug() << subArray.at(i).toObject().value("ImagePath").toString();

            }

        }
    }
    loadFile.close();
}

///显示选中方案
void SceManager::SceManager::showScenfo(QString &sSceName)
{
    QString filePath = QApplication::applicationDirPath() + QString("/Data/Project/").arg(sSceName);
    QFile sceFile(filePath);
    if (!sceFile.open(QIODevice::WriteOnly))
    {
        qWarning("Couldn't open save file.");
    }

    //读取文件内容
    QByteArray allData = sceFile.readAll();
    //    loadFile.close();

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
    if(rootObj.contains("PersonArray"))
    {
        QJsonArray subArray = rootObj.value("PersonArray").toArray();
        for (int i = 0; i < subArray.size(); ++i)
        {
            //            ScePersonInfo *scePersonInfo=new ScePersonInfo(this);
            //            scePersonInfo->setID(subArray.at(i).toObject().value("ID").toInt());
            //            scePersonInfo->setName(subArray.at(i).toObject().value("Name").toString());
            //            scePersonInfo->setPosition(subArray.at(i).toObject().value("Position").toInt());
            //            scePersonInfo->setGroupType(subArray.at(i).toObject().value("Grouptype").toInt());
            //            scePersonInfo->setHostage(subArray.at(i).toObject().value("Host").toBool());
            //            scePersonInfo->setImagePath(subArray.at(i).toObject().value("ImagePath").toString());
            //            m_mapId2Person.insert(subArray.at(i).toObject().value("ID").toInt(),scePersonInfo);

            qDebug() << subArray.at(i).toObject().value("ID").toInt();
            qDebug() << subArray.at(i).toObject().value("Name").toString();
            qDebug() << subArray.at(i).toObject().value("Grouptype").toInt();
            qDebug() << subArray.at(i).toObject().value("Position").toInt();
            qDebug() << subArray.at(i).toObject().value("Host").toBool();
            qDebug() << subArray.at(i).toObject().value("ImagePath").toString();
        }
    }
    sceFile.close();
}

///显示所有方案
QStringList SceManager::showSceList()
{
    QDir *dir=new QDir(QString("%1/%2").arg(GetDataPath().c_str()).arg("Project")); //文件夹
    QStringList filter; //过滤
    filter<<"*.json";
    dir->setNameFilters(filter);
    QFileInfoList fileInfoList = dir->entryInfoList(filter);
    delete dir;
    QStringList string_list;

    for(int i=0; i < fileInfoList.count(); i++)
    {
        string_list.append(fileInfoList.at(i).baseName());
    }
    return(string_list);
}

///设置方案名称
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
void SceManager::addPerson(int nID,const QString& sName, int nLevel, int nGroup, bool bHostage,const QString& sImagePath)
{
    ScePersonInfo *scePersonInfo=new ScePersonInfo(this);
    scePersonInfo->setID(nID);
    scePersonInfo->setName(sName);
    scePersonInfo->setPosition(nLevel);
    scePersonInfo->setGroupType(nGroup);
    scePersonInfo->setHostage(bHostage);
    scePersonInfo->setImagePath(sImagePath);
    m_mapId2Person.insert(nID,scePersonInfo);

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


