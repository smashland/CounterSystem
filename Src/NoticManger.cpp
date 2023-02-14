#include "NoticManger.h"
#include "qjsonobject.h"
#include <QApplication>
#include <QFile>
#include <QDir>
#include <QJsonParseError>
#include <QJsonArray>
#include <QMessageBox>
#include<QDomDocument>

NoticManger::NoticManger(QObject *parent)
    : QObject{parent}
{

}


void NoticManger::saveNoticeFile(const QString &noticPath)
{
    qDebug()<<"ceshilujing:noticPath "<<noticPath;
    QJsonObject jsonNotic;
    QJsonArray arrayNotic;

    for(int i=0;i<m_slistNotic.size();i++)
    {
        jsonNotic.insert("NOTIC",m_slistNotic.at(i));
        arrayNotic.append(jsonNotic);
    }
    //    QString filePath = QApplication::applicationDirPath() + QString("/Data/Szy/test1.json")/*.arg(one.key())*/;
    QFile saveFile(noticPath);
    if (!saveFile.open(QIODevice::WriteOnly))
    {
        qWarning("Couldn't open save file.");
    }

    /// 构建 Json 文档
    QJsonDocument document;
    document.setArray(arrayNotic);
    saveFile.write(document.toJson());
}

//void NoticManger::addNoticInfo(int num, const QString &noticText)
void NoticManger::addNoticInfo(const QString &noticText)
{
    m_slistNotic.append(noticText);
}

bool NoticManger::deleteNoticInfo(const QString &fileName)
{
    QString sFilePath = QApplication::applicationDirPath() + QString("/Data/Szy/%1.notic").arg(fileName);

    if (sFilePath.isEmpty() || !QDir().exists(sFilePath))//是否传入了空的路径||路径是否存在
        return false;
    QFileInfo FileInfo(sFilePath);

    if (FileInfo.isFile())//如果是文件
        QFile::remove(sFilePath);
    return true;
}

QStringList NoticManger::listNoticInfo()
{
    return m_slistNotic;
}

void NoticManger::clearNoticInfo()
{
    m_slistNotic.clear();
}



void NoticManger::praseNoticInfo(const QString& fileName)
{
    QString sFilePath = QApplication::applicationDirPath() + QString("/Data/Szy/%1.notic").arg(fileName);
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
    QJsonObject rootObj;// = jsonDoc.object();
    QJsonArray rootArry=jsonDoc.array();
    for(int i=0;i<rootArry.count();i++)
    {
        rootObj=rootArry.at(i).toObject();

        if (rootObj.contains("NOTIC") && rootObj["NOTIC"].isString())
        {
            qDebug()<<"NOTIC:"<<rootObj["NOTIC"].toString();
            m_slistNotic.append(rootObj["NOTIC"].toString());
        }
    }
}
