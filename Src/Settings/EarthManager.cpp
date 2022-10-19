#include "EarthManager.h"
#include <QApplication>
#include <QFile>
#include <QDir>
#include <QJsonParseError>
#include <QJsonArray>

static const QString cs_FileName("earth.map");
static const QString cs_JsonKey("earth");

EarthManager::EarthManager(QObject *parent)
    : QObject{parent}
{
    ReadFile();
}

CSetEarth *EarthManager::createEarth()
{
    return(new CSetEarth);
}

/// 增加成员
CSetEarth *EarthManager::addMaps(const QString &earthName)
{
     auto findOne = m_mapName2EarthInfo.find(earthName);
    if(m_mapName2EarthInfo.end() == findOne)
    {
        if(!m_mapName2EarthInfo.contains(earthName))
        {
             qDebug()<<"新增地图名称bu重复";
            CSetEarth* pNewOne = new CSetEarth(this);
            m_mapName2EarthInfo.insert(earthName,pNewOne);
            m_listEarth.append(pNewOne);
            emit earthChanged();
            return(pNewOne);
        }
        else
        {
            qDebug()<<"新增地图名称重复";
            return nullptr;
        }
    }
    else
    {
        qDebug()<<"新增地图名称重复";
        return nullptr;
    }
    return nullptr;
}

bool EarthManager::deleteEarth(QObject *pEarth)
{
    bool bRemove = m_listEarth.removeOne(pEarth);
    if(bRemove)
    {
        delete pEarth;
        emit earthChanged();
    }
    return(bRemove);
}

void EarthManager::ReadFile()
{
    QString sFilePath = QApplication::applicationDirPath() + QString("/Data/Earth/%1").arg(cs_FileName);
    QFile openFile(sFilePath);
    if(openFile.open(QFile::ReadOnly))
    {
        QByteArray allByte = openFile.readAll();
        QJsonParseError jsonError;
        QJsonDocument jsonDoc = QJsonDocument::fromJson(allByte, &jsonError);
        if(jsonError.error != QJsonParseError::NoError)
        {
            qDebug() << "json error!" << jsonError.errorString();
            return;
        }
        QJsonObject rootObj = jsonDoc.object();
        auto array = rootObj.value(cs_JsonKey).toArray();
        foreach(auto one, array){
            CSetEarth* pNote = new CSetEarth;
            pNote->readEarth(one.toObject());
            m_listEarth.append(pNote);
        }
    }
}

void EarthManager::saveFile()
{
    qDebug()<<"保存地图信息";
    QString sFilePath = QApplication::applicationDirPath() + QString("/Data/Earth/%1").arg(cs_FileName);
    QFile openFile(sFilePath);
    if(openFile.open(QFile::WriteOnly))
    {
        QJsonDocument jsonDoc;
        QJsonObject rootObj;

        QJsonArray array;
        QJsonObject noteJson;
        foreach(auto one , m_listEarth)
        {
            auto oneNote = qobject_cast<CSetEarth*>(one);
            if(nullptr != oneNote)
            {

                oneNote->writeEarth(noteJson);
                array.append(noteJson);
            }
        }

        rootObj.insert(cs_JsonKey,array);
        jsonDoc.setObject(rootObj);

        openFile.write(jsonDoc.toJson());
    }
}



