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

void SceManager::read(QString &sname)
{
    QString filePath = QApplication::applicationDirPath() + QString("/Data/Project/%1.json").arg(sname);
    qDebug()<<"选中方案路径：------"<<filePath;
    QFile sceFile(filePath);
    if (!sceFile.open(QIODevice::ReadOnly))
    {
        qWarning("Couldn't open save file.");
    }

    //读取文件内容
    QByteArray allData = sceFile.readAll();
    sceFile.close();

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

    //    QStringList keys = rootObj.keys();
    //    for(int i = 0; i < keys.size(); i++)
    //    {
    //        qDebug() << "key" << i << " is:" << keys.at(i);
    //    }

    ///解析方案名称
    if(rootObj.contains("Scename"))
    {
        m_sSceName=rootObj["Scename"].toString();
        qDebug()<<"方案名称："<<rootObj["Scename"].toString();
    }

    //因为是预先定义好的JSON数据格式，所以这里可以这样读取
    if(rootObj.contains("PersonArray"))
    {
        QJsonArray subArray = rootObj.value("PersonArray").toArray();
        for (int i = 0; i < subArray.size(); ++i)
        {
            ScePersonInfo *scePersonInfo=new ScePersonInfo(this);
            scePersonInfo->setID(subArray.at(i).toObject().value("ID").toInt());
            scePersonInfo->setName(subArray.at(i).toObject().value("Name").toString());
            scePersonInfo->setPosition(subArray.at(i).toObject().value("Position").toInt());
            scePersonInfo->setGroupType(subArray.at(i).toObject().value("Grouptype").toInt());
            scePersonInfo->setHostage(subArray.at(i).toObject().value("Host").toBool());
            scePersonInfo->setImagePath(subArray.at(i).toObject().value("ImagePath").toString());
            m_mapId2Person.insert(subArray.at(i).toObject().value("ID").toInt(),scePersonInfo);

            //            qDebug() << subArray.at(i).toObject().value("ID").toInt();
            //            qDebug() << subArray.at(i).toObject().value("Name").toString();
            //            qDebug() << subArray.at(i).toObject().value("Grouptype").toInt();
            //            qDebug() << subArray.at(i).toObject().value("Position").toInt();
            //            qDebug() << subArray.at(i).toObject().value("Host").toBool();
            //            qDebug() << subArray.at(i).toObject().value("ImagePath").toString();
        }
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

void SceManager::modify()
{
    QByteArray byte;
    QString filePath = QApplication::applicationDirPath() + QString("/Data/Project/%1.json").arg("测试方案111");
    QFile file(filePath);
    if(file.exists()){
        file.open(QIODevice::ReadOnly|QIODevice::Text);
        byte=file.readAll();
        file.close();
    }
    else
    {
        qDebug()<<"openFileError";
        return;
    }

    QJsonParseError jsonError;
    QJsonDocument jsonDoc(QJsonDocument::fromJson(byte,&jsonError));
    if(jsonError.error!=QJsonParseError::NoError)
    {
        qDebug() << "json error!" << jsonError.errorString();
        return ;
    }
    QJsonObject rootobj=jsonDoc.object();

    ///修改方案名称
    QJsonObject sceNameObj;
    if(rootobj.contains("Scename"))
    {
        sceNameObj=rootobj.value("Scename").toObject();
        sceNameObj["Scename"]=m_sSceName;
    }


    QJsonArray personArray=rootobj.value("PersonArray").toArray();
    for (int i = 0; i < personArray.size(); ++i)
    {
        QJsonObject personObj;
        personObj=personArray[i].toObject();
        personObj["Name"]="MINGZI";
        personObj["Grouptype"]=10;
        personObj["Position"]=6;
        personObj["Host"]=false;
        personObj["ImagePath"]="路径2";
        personArray.replace(i,personObj);
    }

    rootobj["Scename"]=sceNameObj;
    rootobj["PersonArray"]=personArray;


    QFile file1(filePath);
    if(file1.exists()){
        file1.open(QIODevice::WriteOnly|QIODevice::Text);
        jsonDoc.setObject(rootobj);
        file1.seek(0);
        file1.write(jsonDoc.toJson());
        file1.flush();
        file1.close();
    }
}
///加载图片信息
void SceManager::loadImagePath(const QString &strImagePath)
{
    qDebug()<<"66666666666"<<GetDataPath().c_str();
    qDebug()<<"测试路径-------"<<strImagePath;
    QDesktopServices::openUrl(QUrl::fromLocalFile(strImagePath));
}

///查看个人信息 //未完成
void SceManager::showPersonInfo(int nID)
{
    foreach(auto one,m_mapId2Person)
    {
        if(one->getID()==nID)
        {
            qDebug()<<"选中的--------id"        <<one->getID();
            qDebug()<<"选中的--------name"      <<one->getName();
            qDebug()<<"选中的--------group"     <<one->getGroupType();
            qDebug()<<"选中的--------position"  <<one->getPosition();
            qDebug()<<"选中的--------host"      <<one->getHostage();
            qDebug()<<"选中的--------imagePath" <<one->getImagePath();
            //            loadImagePath(one->getImagePath());
        }
    }

}

///删除选中的某人信息 //未完成
void SceManager::removePersonInfo(int nID)
{
    foreach(auto one,m_mapId2Person)
    {
        if(one->getID()==nID)
        {
            qDebug()<<"选中的--------id"        <<one->getID();
            qDebug()<<"选中的--------name"      <<one->getName();
            qDebug()<<"选中的--------group"     <<one->getGroupType();
            qDebug()<<"选中的--------position"  <<one->getPosition();
            qDebug()<<"选中的--------host"      <<one->getHostage();
            qDebug()<<"选中的--------imagePath" <<one->getImagePath();
            //            loadImagePath(one->getImagePath());
        }
    }
}
///修改选中的人员信息
bool SceManager::modifyPersonInfo(const int nID)
{
    foreach(auto one,m_mapId2Person)
    {
        if(one->getID()==nID)
        {

            qDebug()<<"选中的--------id"        <<one->getID();
            qDebug()<<"选中的--------name"      <<one->getName();
            qDebug()<<"选中的--------group"     <<one->getGroupType();
            qDebug()<<"选中的--------position"  <<one->getPosition();
            qDebug()<<"选中的--------host"      <<one->getHostage();
            qDebug()<<"选中的--------imagePath" <<one->getImagePath();
            //            loadImagePath(one->getImagePath());
        }
    }


    //    ScePersonInfo *scePersonInfo=new ScePersonInfo(this);
    //    scePersonInfo->setID(nID);
    //    scePersonInfo->setName(sName);
    //    scePersonInfo->setPosition(nLevel);
    //    scePersonInfo->setGroupType(nGroup);
    //    scePersonInfo->setHostage(bHostage);
    //    scePersonInfo->setImagePath(sImagePath);
    //    m_mapId2Person.insert(nID,scePersonInfo);

    return true;
}

///显示选中方案
void SceManager::SceManager::showScenfo(QString sSceName)
{
    read(sSceName);

    m_listPerson.clear();
    QVariantMap tmpMap;
    for(auto findOne = m_mapId2Person.begin(); m_mapId2Person.end() != findOne; ++findOne)
    {
        auto itorSecond = findOne.value();
        tmpMap.insert("id",itorSecond->getID());
        tmpMap.insert("name",itorSecond->getName());
        tmpMap.insert("group",itorSecond->getGroupType());
        tmpMap.insert("position",itorSecond->getPosition());
        tmpMap.insert("host",itorSecond->getHostage());
        m_listPerson.push_back(tmpMap);

        qDebug()<<"id"<<itorSecond->getID();
        qDebug()<<"name"<<itorSecond->getName();
        qDebug()<<"group"<<itorSecond->getGroupType();
        qDebug()<<"position"<<itorSecond->getPosition();
        qDebug()<<"host"<<itorSecond->getHostage();
    }
    /// 更新模型列表
    emit listPersonChanged(m_listPerson);
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

///修改方案 :未完成
bool SceManager::modifyScenario(const QString &sName)
{
    return true;
}
///删除所选方案
bool SceManager::removeScenario(const QString &sName)
{
    QString filePath = QApplication::applicationDirPath() + QString("/Data/Project/%1.json").arg(sName);

    if (filePath.isEmpty() || !QDir().exists(filePath))//是否传入了空的路径||路径是否存在
        return false;

    QFileInfo FileInfo(filePath);

    if (FileInfo.isFile())//如果是文件
        QFile::remove(filePath);
    return true;
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


