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
}

CSceInfo *SceManager::createSceneri()
{
    return(new CSceInfo);
}

SceManager::~SceManager()
{
    ClearSceInfo();
}

//QList<ScePersonInfo*> SceManager::sces() const
//{
//    return(m_mapName2SceInfo.values());
//}

///添加方案
CSceInfo *SceManager::addScenari(const QString &sceName,CSceInfo* pSceInfo)
{
    auto findOne = m_mapName2SceInfo.find(sceName);
    qDebug()<<"测试添加方案函数："<<sceName;
    if(m_mapName2SceInfo.end() == findOne)
    {
        if(nullptr == pSceInfo)
        {
            CSceInfo* pNewOne = new CSceInfo;
            m_mapName2SceInfo.insert(sceName,pNewOne);
            return(pNewOne);
        }
        else
        {
            m_mapName2SceInfo.insert(sceName,pSceInfo);
            return(pSceInfo);
        }
    }
    else
    {
        return(nullptr);
    }
}

///删除方案
bool SceManager::deleteScenario(const QString &sceName)
{
    auto findOne = m_mapName2SceInfo.find(sceName);
    if(m_mapName2SceInfo.end() != findOne)
    {
        delete findOne.value();
        m_mapName2SceInfo.erase(findOne);
        return(true);
    }
    else
    {
        return(false);
    }
}
///查找方案信息
CSceInfo *SceManager::findScenario(const QString &sceName)
{
    qDebug()<<("查看方案");
    auto findOne = m_mapName2SceInfo.find(sceName);
    return m_mapName2SceInfo.end() == findOne ? nullptr : findOne.value();
}

/////得到所有的方案信息
//QList<CSceInfo *> SceManager::getSceAll()
//{
//    qDebug()<<"测试所有的方案信息";
//    return(m_mapName2SceInfo.values());
//}

QList<QObject *> SceManager::getSceAll()
{
    QList<QObject*> listObjct;
    foreach(auto one , m_mapName2SceInfo){
        listObjct.append(one);
        qDebug()<<"测试";
    }
    return(listObjct);
}

void SceManager::read()
{
    qDebug()<<"测试读取所有文件";
    showSceList();

    foreach(const QString& one,m_listSceFileName)
    {
        read(one);
    }
}


void SceManager::read(const QString &sname)
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
    CSceInfo* pSceInfo = new CSceInfo;
    pSceInfo->Prase(rootObj["PersonArray"].toArray());
    if (rootObj.contains("Scename") && rootObj["Scename"].isString())
    {
        pSceInfo->setSceName(rootObj["Scename"].toString());
    }
    m_mapName2SceInfo.insert(rootObj["Scename"].toString()/*rootObj["Scename"].toObject()["Scename"].toString()*/,pSceInfo);

}

void SceManager::write()
{    
    for(auto one=m_mapName2SceInfo.begin();one != m_mapName2SceInfo.end();++one)
    {
        QJsonObject jsonSce;
        QJsonArray personArray;
        jsonSce.insert("Scename",one.key());

        one.value()->Save(personArray);
        jsonSce.insert("PersonArray",personArray);
        QString filePath = QApplication::applicationDirPath() + QString("/Data/Project/%1.json").arg(one.key());
        QFile saveFile(filePath);
        if (!saveFile.open(QIODevice::WriteOnly))
        {
            qWarning("Couldn't open save file.");
        }

        /// 构建 Json 文档
        QJsonDocument document;
        document.setObject(jsonSce);
        saveFile.write(document.toJson());
    }
}
QString SceManager::text()
{
    qDebug() << "Going to read the text";
    read();
    return m_text;
}


void SceManager::modify()
{/*
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

//    ///修改方案名称
//    QJsonObject sceNameObj;
//    if(rootobj.contains("Scename"))
//    {
//        sceNameObj=rootobj.value("Scename").toObject();
//        sceNameObj["Scename"]=m_sSceName;
//    }


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
        //        file1.seek(0);
        file1.write(jsonDoc.toJson());
        //        file1.flush();
        file1.close();
    }*/
}
///加载图片信息
void SceManager::loadImagePath(const QString &strImagePath)
{
    qDebug()<<"66666666666"<<GetDataPath().c_str();
    qDebug()<<"测试路径-------"<<strImagePath;
    QDesktopServices::openUrl(QUrl::fromLocalFile(strImagePath));
}


///显示选中方案
void SceManager::SceManager::showScenfo(QString sSceName)
{
//    read(sSceName);

//    m_listPerson.clear();
//    QVariantMap tmpMap;
//    for(auto findOne = m_mapId2Person.begin(); m_mapId2Person.end() != findOne; ++findOne)
//    {
//        auto itorSecond = findOne.value();
//        tmpMap.insert("id",itorSecond->getID());
//        tmpMap.insert("name",itorSecond->getName());
//        tmpMap.insert("group",itorSecond->getGroupType());
//        tmpMap.insert("position",itorSecond->getPosition());
//        tmpMap.insert("host",itorSecond->getHostage());
//        m_listPerson.push_back(tmpMap);

//        qDebug()<<"id"<<itorSecond->getID();
//        qDebug()<<"name"<<itorSecond->getName();
//        qDebug()<<"group"<<itorSecond->getGroupType();
//        qDebug()<<"position"<<itorSecond->getPosition();
//        qDebug()<<"host"<<itorSecond->getHostage();
//    }
//    /// 更新模型列表
    emit listPersonChanged(m_listPerson);
}

///显示所有方案
QStringList SceManager::showSceList()
{
    qDebug()<<"555555555555555555555";
    if(m_listSceFileName.size() < 1)
    {
        QDir *dir=new QDir(QString("%1/%2").arg(GetDataPath().c_str()).arg("Project")); //文件夹
        QStringList filter; //过滤
        filter<<"*.json";
        dir->setNameFilters(filter);
        QFileInfoList fileInfoList = dir->entryInfoList(filter);
        delete dir;

        for(int i=0; i < fileInfoList.count(); i++)
        {
            m_listSceFileName.append(fileInfoList.at(i).baseName());
        }
    }
    return(m_listSceFileName);
}

/////设置方案名称
//void SceManager::setSceName(const QString& sName)
//{
//    if(m_sSceName != sName)
//    {
//        m_sSceName = sName;
//        emit sceNameChanged(m_sSceName);
//    }
//}
/////添加方案
void SceManager::addScenario(const QString &sName)
{
    if(m_mapName2SceInfo.size() > 0)
    {
        write();
        ClearSceInfo();
    }
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
//    ScePersonInfo *scePersonInfo=new ScePersonInfo(this);
//    scePersonInfo->setID(nID);
//    scePersonInfo->setName(sName);
//    scePersonInfo->setPosition(nLevel);
//    scePersonInfo->setGroupType(nGroup);
//    scePersonInfo->setHostage(bHostage);
//    scePersonInfo->setImagePath(sImagePath);
}

///清空方案信息
void SceManager::ClearSceInfo()
{
    foreach (auto one, m_mapName2SceInfo)
    {
        delete one;
    }
    m_mapName2SceInfo.clear();
}


