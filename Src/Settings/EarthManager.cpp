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

///解析地图文件
void EarthManager::praseEarthXml(QString sEarthPath)
{
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

    // 获取所有GDALIMAGE节点
    QDomNodeList list = root.elementsByTagName("GDALIMAGE");
    qDebug()<<"获取所有GDALIMAGE节点"<<list.count();

    /* 修改尖括号之间的值 */
    for (int i = 0; i < list.size(); i++) {
        QDomElement element = list.at(i).toElement();
        // 找到等于的节点
        if (element.attribute("name") == "tif") {
            // 获得子节点
            QDomNode node = element.namedItem("url");
            qDebug()<<"测试节点信息"<<node.nodeValue();

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

    if (!file.open(QFileDevice::WriteOnly | QFileDevice::Truncate)) {
        QMessageBox::information(NULL, "提示", "文件打开失败！");
        return;
    }

    // 输出到文件
    QTextStream stream(&file);
    doc.save(stream, 4);	// 缩进4格
    file.close();
}



