#include "SceManager.h"
#include <QJsonDocument>
#include <QFile>
#include <QApplication>
#include <QJsonArray>
#include <QDir>
#include <ISceneCore.h>
#include <QDesktopServices>
#include <QAxObject>
#include <QXlsx/xlsxdocument.h>
#include <QXlsx/xlsxchartsheet.h>
#include <QXlsx/xlsxchart.h>

SceManager::SceManager(QObject *parent)
    : QObject{parent}
{
    read();
}

CSceInfo *SceManager::createSceneri()
{
    return(new CSceInfo);
}

SceManager::~SceManager()
{
    //    ClearSceInfo();
}

///添加方案
CSceInfo *SceManager::addScenari(const QString &sceName,CSceInfo* pSceInfo)
{
    auto findOne = m_mapName2SceInfo.find(sceName);
    if(m_mapName2SceInfo.end() == findOne)
    {
        if(!m_mapName2SceInfo.contains(sceName))
        {
            if(nullptr == pSceInfo)
            {
                CSceInfo* pNewOne = new CSceInfo;
                pNewOne->setSceName(sceName);
                m_mapName2SceInfo.insert(sceName,pNewOne);
                m_listSces.append(pNewOne);
                emit listScesChanged();
                return(pNewOne);
            }
            else
            {
                QHash<QString, CSceInfo*>::iterator i;
                for( i=m_hashName2SceInfo.begin(); i!=m_hashName2SceInfo.end(); ++i)
                {
                    removeSceFile(i.key());
                    m_mapName2SceInfo.remove(i.key());
                    m_listSces.removeOne(i.value());
                    emit listScesChanged();
                }
                pSceInfo->setSceName(sceName);
                m_mapName2SceInfo.insert(sceName, pSceInfo);
                m_listSces.append(pSceInfo);
                emit listScesChanged();
                return(pSceInfo);
            }
        }
        else
        {
            return (nullptr);
        }

    }
    else
    {
        if(!m_mapName2SceInfo.contains(sceName))
        {
            QHash<QString, CSceInfo*>::iterator i;
            for( i=m_hashName2SceInfo.begin(); i!=m_hashName2SceInfo.end(); ++i)
            {
                deleteScenario(i.key());
            }
            pSceInfo->setSceName(sceName);
            m_mapName2SceInfo.insert(sceName, pSceInfo);
            m_listSces.append(pSceInfo);
            emit listScesChanged();
            return(pSceInfo);
        }
        else
        {
            QHash<QString, CSceInfo*>::iterator i;
            for( i=m_hashName2SceInfo.begin(); i!=m_hashName2SceInfo.end(); ++i)
            {
                if(i.key()==sceName)
                {
                     removeSceFile(i.key());
                     m_mapName2SceInfo.remove(i.key());
                     m_listSces.removeOne(i.value());
                     emit listScesChanged();
                     pSceInfo->setSceName(sceName);
                     m_mapName2SceInfo.insert(sceName, pSceInfo);
                     m_listSces.append(pSceInfo);
                     emit listScesChanged();
                     return(pSceInfo);
                }
                else
                {
                    return nullptr;
                }

            }
            return nullptr;
        }
    }
    return nullptr;
}

///删除方案
bool SceManager::deleteScenario(const QString &sceName)
{
    auto findOne = m_mapName2SceInfo.find(sceName);
    if(m_mapName2SceInfo.end() != findOne)
    {
        m_listSces.removeOne(findOne.value());
        emit listScesChanged();
        delete findOne.value();
        m_mapName2SceInfo.erase(findOne);
        removeSceFile(sceName);
        return(true);
    }
    else
    {
        return(false);
    }
}
///查找方案信息
QObject *SceManager::findScenario(const QString &sceName)
{
    m_hashName2SceInfo.clear();
    auto findOne = m_mapName2SceInfo.find(sceName);
    if(m_mapName2SceInfo.end() != findOne)
    {
        m_hashName2SceInfo.insert(sceName,findOne.value());
        return (findOne.value());
    }
    else
    {
        return nullptr;
    }

}


QList<QObject *> SceManager::getSceAll()
{
    QList<QObject*> listObjct;
    foreach(auto one , m_mapName2SceInfo){
        listObjct.append(one);
    }
    return(listObjct);
}

void SceManager::  read()
{
    ClearSceInfo();
    showSceList();
    foreach(const QString& one,m_listSceFileName)
    {
        read(one);
    }
}


void SceManager::read(const QString &sname)
{
    QString filePath = QApplication::applicationDirPath() + QString("/Data/Project/%1.sce").arg(sname);
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
    m_mapName2SceInfo.insert(rootObj["Scename"].toString(),pSceInfo);
    m_listSces.append(pSceInfo);

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

        //        QString filePath = QApplication::applicationDirPath() + QString("/Data/Project/%1.sce").arg(one.key());
        //        QFile saveFile(filePath);
        //        if (!saveFile.open(QIODevice::WriteOnly))
        //        {
        //            qWarning("Couldn't open save file.");
        //        }

        //        /// 构建 Json 文档
        //        QJsonDocument document;
        //        document.setObject(jsonSce);
        //        saveFile.write(document.toJson());
    }


    foreach(auto one , m_listSces)
    {
        auto oneNote = qobject_cast<CSceInfo*>(one);
        QJsonObject jsonSce;
        QJsonArray personArray;

        if(nullptr != oneNote)
        {
            jsonSce.insert("Scename",oneNote->getSceName());
            oneNote->Save(personArray);
            jsonSce.insert("PersonArray",personArray);
        }
        QString filePath = QApplication::applicationDirPath() + QString("/Data/Project/%1.sce").arg(oneNote->getSceName());
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



///导入方案
QString SceManager::importSce(const QString &strImagePath)
{
    QFileInfo fileInfo(strImagePath);
    QString targetPath = QApplication::applicationDirPath() +QString("/Data/Project/%1").arg(fileInfo.fileName());
    if(QFile::copy(strImagePath,targetPath))
    {
        //        ClearSceInfo();
        read();
    }
    else
    {
        return(nullptr);
    }

    return (nullptr);
}

///显示所有方案
QStringList SceManager::showSceList()
{
    m_listSceFileName.clear();
    //    if(m_listSceFileName.size() < 1)
    {
        QDir *dir=new QDir(QString("%1/%2").arg(GetDataPath().c_str()).arg("Project")); //文件夹
        QStringList filter; //过滤
        filter<<"*.sce";
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

bool SceManager::removeSceFile(const QString &sName)
{
    QString filePath = QApplication::applicationDirPath() + QString("/Data/Project/%1.sce").arg(sName);

    if (filePath.isEmpty() || !QDir().exists(filePath))//是否传入了空的路径||路径是否存在
        return false;

    QFileInfo FileInfo(filePath);

    if (FileInfo.isFile())//如果是文件
        QFile::remove(filePath);
    return true;
}

void SceManager::setCurrentSceName(const QString &currentSceName)
{
    if(currentSceName!=m_sCurrentSceName)
    {
        m_sCurrentSceName=currentSceName;
        emit currentSceNameChanged(m_sCurrentSceName);
    }
}

void SceManager::importSceInfo(const QString &strImagePath)
{
    parseExcel(strImagePath);
    read();
}

void SceManager::parseExcel(const QString &strImagePath)
{
    QFileInfo fileInfo(strImagePath);
    QXlsx::Document xlsx2(strImagePath);
    QStringList sheetnames = xlsx2.sheetNames();
    qDebug()<<sheetnames<<" 00"<<fileInfo.baseName();
    for(int sheetCout=0;sheetCout<1/*sheetnames.size()*/;sheetCout++)
    {
        QXlsx::Worksheet* workSheet = dynamic_cast<QXlsx::Worksheet*>(xlsx2.sheet(sheetnames[sheetCout]));
       qDebug()<<workSheet->sheetName()<<','<<workSheet->sheetType()<<sheetnames.size();
        QStringList titles;
        int rowCount=workSheet->dimension().rowCount();
        int columnCount=workSheet->dimension().columnCount();


        for (int j = 1; j <= columnCount; j++)
        {
            QXlsx::Cell *cell = workSheet->cellAt(1, j);
            titles.append(cell->value().toString());
        }
        qDebug()<<titles[0]<<titles[1]<<titles[2]<<titles[3]<<titles[4];
        if(titles[0]=="设备ID"&&titles[1]=="姓名"&&titles[2]=="职务"&&titles[3]=="阵营"&&titles[4]=="人质")
        {
            qDebug()<<"表头正确";
            qDebug()<<"方案内容"<<workSheet->sheetName()<<rowCount;
            CSceInfo* pSceInfo = new CSceInfo;
            pSceInfo->PraseExcelInfo(workSheet,rowCount,columnCount);

            pSceInfo->setSceName(fileInfo.baseName());
            m_mapName2SceInfo.insert(fileInfo.baseName(),pSceInfo);
            m_listSces.append(pSceInfo);
            write();
        }
        else
        {
            return ;
        }
    }

}


///清空方案信息
void SceManager::ClearSceInfo()
{
    foreach (auto one, m_mapName2SceInfo)
    {
        delete one;
    }
    m_mapName2SceInfo.clear();
    m_hashName2SceInfo.clear();
    m_listSces.clear();
    m_listTitle.clear();
}


