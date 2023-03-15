#include "EarthManager.h"
#include <QApplication>
#include <QFile>
#include <QDir>
#include <QJsonParseError>
#include <QJsonArray>
#include <QMessageBox>
#include<QDomDocument>

static const QString cs_FileName("earth.map");
static const QString cs_JsonKey("earth");

EarthManager::EarthManager(QObject *parent)
    : QObject{parent}
{
    ReadFile();
    praseCurrentEarth();
}

EarthManager::~EarthManager()
{
    saveFile();
}

CSetEarth *EarthManager::createMap()
{
    return (new CSetEarth);
}

/// 增加成员
CSetEarth *EarthManager::addMaps(const QString &earthName,const QString &earthPath)
{
    QFileInfo earthPathInfo(earthPath);
    auto findOne = m_mapName2EarthInfo.find(earthName);
    if(m_mapName2EarthInfo.end() == findOne)
    {
        if(!m_mapName2EarthInfo.contains(earthName))
        {
            CSetEarth* pNewOne = new CSetEarth(this);
            m_mapName2EarthInfo.insert(earthName,pNewOne);
            pNewOne->setEarthNum(m_listEarth.size());
            m_listEarth.append(pNewOne);
            emit earthChanged();
//            if(earthPathInfo.suffix()=="jpg"||earthPathInfo.suffix()=="png")
//            {
//                //开始鼠标
//                //开始的确定区域
//                emit beginEdit();
//                qDebug()<<"lujing"<<earthPath;
//            }

            return(pNewOne);
        }
        else
        {
            return nullptr;
        }
    }
    else
    {
        return nullptr;
    }
    return nullptr;
}

bool EarthManager::deleteEarth(const QString &earthName,const QString &earthInfo)
{
    if(m_sCurrentName!=earthName) ///正在使用的地图不能删除
    {
    auto findOne = m_mapName2EarthInfo.find(earthName);
    if(m_mapName2EarthInfo.end() != findOne)
    {
        m_listEarth.removeOne(findOne.value());
        emit earthChanged();
        delete findOne.value();
        m_mapName2EarthInfo.erase(findOne);
        removeEarthFile(earthInfo);
        return(true);
    }
    else
    {
        return(false);
    }
    }
    else{
        return(false);
    }
}
bool EarthManager::removeEarthFile(const QString &earthInfo)
{
    if (earthInfo.isEmpty() || !QDir().exists(earthInfo))//是否传入了空的路径||路径是否存在
        return false;

    QFileInfo earthFileInfo(earthInfo);

    if(earthFileInfo.suffix()=="tif"||earthFileInfo.suffix()=="jpg"||earthFileInfo.suffix()=="png")
    {
        if (earthFileInfo.isFile())//如果是文件
            QFile::remove(earthInfo);
    }
    else if(earthFileInfo.suffix()=="xml")
    {
        QDir dir;
        dir.setPath(earthFileInfo.path());
        dir.removeRecursively();
    }

    return true;
}
void EarthManager::ReadFile()
{
    ClearEarthInfo();
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
        for (int i = 0; i < array.size(); ++i)
        {
            CSetEarth* pNote = new CSetEarth(this);
             pNote->readEarth(array[i].toObject());
             m_mapName2EarthInfo.insert(array[i].toObject().value("Name").toString(),pNote);
             m_listEarth.append(pNote);

        }
    }
}

void EarthManager::saveFile()
{
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

///解析地图文件
void EarthManager::praseEarthXml(QString sEarthPath)
{
    QFileInfo fileInfo(sEarthPath);

    /// 获取文件地址
    QString filePath = QApplication::applicationDirPath() + "/Data/Earth/Geocentric.earth";
    QFile file(filePath);
    if(!file.open(QIODevice::ReadOnly))
    {
        QMessageBox::information(NULL, "提示", "文件打开失败！");
        return;
    }

    QDomDocument doc;
    if (!doc.setContent(&file)) {
        QMessageBox::information(NULL, "提示", "操作的文件不是XML文件！");
        file.close();
        return;
    }
    file.close();
    // 获得根节点
    QDomElement root = doc.documentElement();
    QString tagName,itemName;
    QString tagNameM,itemNameM;
    if(fileInfo.suffix()=="tif")
    {
        tagName="GDALIMAGE";
        itemName="tifMap";
        tagNameM="tmsimage";
        itemNameM="xmlMap";
    }
    else if(fileInfo.suffix()=="xml")
    {
        tagName="tmsimage";
        itemName="xmlMap";
        tagNameM="GDALIMAGE";
        itemNameM="tifMap";
    }
    else if(fileInfo.suffix()=="jpg"||fileInfo.suffix()=="png")
    {
        sEarthPath="NULL";
        modifyEarthXml(root,"tmsimage","xmlMap","NULL");
        modifyEarthXml(root,"GDALIMAGE","tifMap","NULL");

        if (!file.open(QFileDevice::WriteOnly | QFileDevice::Truncate)) {
            QMessageBox::information(NULL, "提示", "文件打开失败！");
            return;
        }

        // 输出到文件
        QTextStream stream(&file);
        doc.save(stream, 4);	// 缩进4格
        file.close();
        return;
    }

    modifyEarthXml(root,tagNameM,itemNameM,"NULL");
    modifyEarthXml(root,tagName,itemName,sEarthPath);

    if (!file.open(QFileDevice::WriteOnly | QFileDevice::Truncate)) {
        QMessageBox::information(NULL, "提示", "文件打开失败！");
        return;
    }

    // 输出到文件
    QTextStream stream(&file);
    doc.save(stream, 4);	// 缩进4格
    file.close();
}

void EarthManager::modifyEarthXml(QDomElement root,QString tagName,QString itemName,QString sEarthPath)
{
    // 获取所有GDALIMAGE节点
    QDomNodeList list = root.elementsByTagName(tagName);
    /* 修改尖括号之间的值 */
    for (int i = 0; i < list.size(); i++) {
        QDomElement element = list.at(i).toElement();
        // 找到等于的节点
        if (element.attribute("name") == itemName) {
            // 获得子节点
            QDomNode node = element.namedItem("url");

            // 尖括号之间的内容作为子节点出现(修改前)
            QDomNode oldNode = node.firstChild();

            // 修改尖括号之间的值
            node.firstChild().setNodeValue(sEarthPath);

            // 尖括号之间的内容作为子节点出现(修改后)
            QDomNode newNode = node.firstChild();

            // 将新旧内容子节点进行替换
            node.replaceChild(newNode, oldNode);
            break;
        }
    }
}

void EarthManager::saveCurrentEarth(const QString &earthName,const QString &earthPath, float lat, float lon,float rdlat, float rdlon)
{
    QString sFilePath = QApplication::applicationDirPath() + QString("/Data/Earth/currentEarth.info");
    QFile openFile(sFilePath);
    if(openFile.open(QFile::WriteOnly|QFile::Truncate))
    {
        QJsonDocument jsonDoc;
        QJsonObject rootObj;
        rootObj.insert("earthName",earthName);
        rootObj.insert("earthPath",earthPath);
        rootObj.insert("earthLat",lat);
        rootObj.insert("earthLon",lon);
        rootObj.insert("earthRDLat",rdlat);
        rootObj.insert("earthRDLon",rdlon);
        jsonDoc.setObject(rootObj);
        openFile.write(jsonDoc.toJson());
    }
}

void EarthManager::praseCurrentEarth()
{
    QString sFilePath = QApplication::applicationDirPath() + QString("/Data/Earth/currentEarth.info");
    QFile openFile(sFilePath);
    if (!openFile.open(QFile::ReadOnly))
    {
        return;
        qWarning("Couldn't open save file.");
    }

    //读取文件内容
    QByteArray allData = openFile.readAll();
    openFile.close();

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
    if (rootObj.contains("earthName") && rootObj["earthName"].isString())
    {
        m_sCurrentName=rootObj["earthName"].toString();
        emit currentNameChanged();
    }
    if (rootObj.contains("earthPath") && rootObj["earthPath"].isString())
    {
        m_sCurrentPath=rootObj["earthPath"].toString();
        emit currentPathChanged();
    }
    if (rootObj.contains("earthLat") && rootObj["earthLat"].isDouble())
    {
        m_nCurrentLat=rootObj["earthLat"].toDouble();
        emit currentLatChanged();
    }
    if (rootObj.contains("earthLon") && rootObj["earthLon"].isDouble())
    {
        m_nCurrentLon=rootObj["earthLon"].toDouble();
        emit currentLonChanged();
    }
    if (rootObj.contains("earthRDLat") && rootObj["earthRDLat"].isDouble())
    {
        m_nCurrentRDLat=rootObj["earthRDLat"].toDouble();
        emit currentRDLatChanged();
    }
    if (rootObj.contains("earthRDLon") && rootObj["earthRDLon"].isDouble())
    {
        m_nCurrentRDLon=rootObj["earthRDLon"].toDouble();
        emit currentRDLonChanged();
    }

}

QString EarthManager::getCurrentEarthLoction()
{
    QString location=QString("{%1,%2}").arg(m_nCurrentLat).arg(m_nCurrentLon);
    return location;
}

int EarthManager::earthNum()
{
    return m_listEarth.size();
}

void EarthManager::ClearEarthInfo()
{
    foreach (auto one, m_mapName2EarthInfo)
    {
        delete one;
    }
    m_mapName2EarthInfo.clear();
}



