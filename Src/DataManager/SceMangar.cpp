#include "SceMangar.h"

//SceMangar::SceMangar(QObject *parent)
//    : QObject{parent}
//{

//}
#include <QCborMap>
#include <QCborValue>
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QRandomGenerator>
#include <QTextStream>
int count=0;
SceMangar::SceMangar(QWidget *parent)
//    : QObject{parent}
{

}

SceMangar::~SceMangar()
{

}

//QVector<SceInfo> SceMangar::sceInfos() const
//{
//    return m_SceInfos;
//}
void SceMangar::setSceName(QString sName)
{
    if(m_sceName!=sName)
    {
        m_sceName=sName;
        emit(sceNameChanged(m_sceName));

    }
}
///设置设备编号
void SceMangar::setID(int nID)
{
    if(nID != m_nID)
    {
        m_nID = nID;
        emit(IDChanged(m_nID));
         qDebug()<<"m_nID                                    "<<m_nID;
    }
}

///设置人员名称
void SceMangar::setName(QString sName)
{
    if(sName != m_sName)
    {
        m_sName = sName;
        emit(nameChanged(m_sName));
        qDebug()<<"mingzi                                    "<<m_sName;
    }
}

///设置人员类型
void SceMangar::setGroupType(QString sType)
{
    if(sType != m_sGroupType)
    {
        m_sGroupType = sType;
        emit(nameChanged(m_sGroupType));
    }
}
///设置人员职务
void SceMangar::setPosition(QString sPosition)
{
    if(sPosition != m_sPosition)
    {
        m_sPosition = sPosition;
        emit(positionChanged(m_sPosition));
    }
}

///设置人质
void SceMangar::setHostage(bool bHostage)
{
    if(bHostage != m_bHostage)
    {
        m_sPosition = bHostage;
        emit(hostageChanged(m_bHostage));
    }
}

////! [0]
//void SceMangar::newGame()
//{
//    m_SceInfos.clear();
//    m_SceInfos.reserve(2);

//    SceInfo village(QStringLiteral("zhang"));
//    QVector<ScesPerson> villageSces;
//    villageSces.reserve(2);
//    villageSces.append(ScesPerson(0,
//                                 QStringLiteral("one")
//                                 /*ScesPerson::RED*/));
//    villageSces.append(ScesPerson(1,
//                                 QStringLiteral("two")
//                                 /*ScesPerson::NON*/));
//    villageSces.append(ScesPerson(2,
//                                 QStringLiteral("three")
//                                 /*ScesPerson::BLUE*/));
//    village.setSces(villageSces);
//    m_SceInfos.append(village);

//    SceInfo dungeon(QStringLiteral("li"));
//    QVector<ScesPerson> dungeonSces;
//    dungeonSces.reserve(3);
//    dungeonSces.append(ScesPerson(01,
//                                 QStringLiteral("one1")
//                                 /*ScesPerson::RED*/));
//    dungeonSces.append(ScesPerson(11,
//                                 QStringLiteral("two1")
//                                 /*ScesPerson::NON*/));
//    dungeonSces.append(ScesPerson(21,
//                                 QStringLiteral("three1")
//                                /* ScesPerson::BLUE*/));

//    dungeon.setSces(dungeonSces);
//    m_SceInfos.append(dungeon);
//}
//! [0]

//! [3]
bool SceMangar::loadInfo()
{
    QJsonParseError jsonError;
    QByteArray byteArray;
    QJsonDocument doucment = QJsonDocument::fromJson(byteArray, &jsonError);  // 转化为 JSON 文档
    if (!doucment.isNull() && (jsonError.error == QJsonParseError::NoError)) {  // 解析未发生错误
        if (doucment.isObject()) {  // JSON 文档为对象
            QJsonObject object = doucment.object();  // 转化为对象
            if (object.contains("Name")) {
                QJsonValue value = object.value("Name");
                if (value.isString()) {
                    QString strName = value.toString();
                    qDebug() << "Name : " << strName;
                }
            }
            if (object.contains("Company")) {
                QJsonValue value = object.value("Company");
                if (value.isString()) {
                    QString strCompany = value.toString();
                    qDebug() << "Company : " << strCompany;
                }
            }
            if (object.contains("From")) {
                QJsonValue value = object.value("From");
                if (value.isDouble()) {
                    int nFrom = value.toVariant().toInt();
                    qDebug() << "From : " << nFrom;
                }
            }
            if (object.contains("Version")) {
                QJsonValue value = object.value("Version");
                if (value.isArray()) {  // Version 的 value 是数组
                    QJsonArray array = value.toArray();
                    int nSize = array.size();
                    for (int i = 0; i < nSize; ++i) {
                        QJsonValue value = array.at(i);
                        if (value.isDouble()) {
                            double dVersion = value.toDouble();
                            qDebug() << "Version : " << dVersion;
                        }
                    }
                }
            }
            if (object.contains("Page")) {
                QJsonValue value = object.value("Page");
                if (value.isObject()) {  // Page 的 value 是对象
                    QJsonObject obj = value.toObject();
                    if (obj.contains("Home")) {
                        QJsonValue value = obj.value("Home");
                        if (value.isString()) {
                            QString strHome = value.toString();
                            qDebug() << "Home : " << strHome;
                        }
                    }
                    if (obj.contains("Download")) {
                        QJsonValue value = obj.value("Download");
                        if (value.isString()) {
                            QString strDownload = value.toString();
                            qDebug() << "Download : " << strDownload;
                        }
                    }
                    if (obj.contains("Developers")) {
                        QJsonValue value = obj.value("Developers");
                        if (value.isString()) {
                            QString strDevelopers = value.toString();
                            qDebug() << "Developers : " << strDevelopers;
                        }
                    }
                }
            }
        }
    }


//    QFile loadFile(QStringLiteral("scesInfo.json"));


//    if (!loadFile.open(QIODevice::ReadOnly)) {
//        qWarning("Couldn't open save file.");
//        return false;
//    }

//    QByteArray saveData = loadFile.readAll();

//    QJsonDocument loadDoc(QJsonDocument::fromJson(saveData));

//    read(loadDoc.object());

//    QTextStream(stdout) << "Loaded save for "
//                        << loadDoc["player"]["name"].toString();
    return true;
}
//! [3]


//添加人员
bool SceMangar::addPerson()
{
//    sce->personArry[sce->m_PersonSize].ID=m_nID;
//    //    sce->personArry[sce->m_PersonSize].Name=m_sName;
//    //    sce->personArry[sce->m_PersonSize].GroupType=m_sGroupType;
//    //    sce->personArry[sce->m_PersonSize].Position=m_sPosition;
//    //    sce->personArry[sce->m_PersonSize].Hostage=m_bHostage;
//    sce->m_PersonSize++;

    qDebug()<<"idcunchu"<<sce->personArry[sce->m_PersonSize].ID;
    qDebug()<<"m_PersonSize"<<sce->m_PersonSize;


    return true;


    // 构建 Json 对象 - Pag
}
//! [4]
bool SceMangar::saveInfo() /*const*/
{  
//    // 构建 Json 对象 - Page
//    QJsonObject personObject;
//    personObject.insert("id", m_nID);
//    personObject.insert("Name", m_sName);
//    personObject.insert("type", m_sGroupType);
//    personObject.insert("Position", m_sPosition);
//    personObject.insert("Host", m_bHostage);

//    // 构建 Json 对象
//    QJsonObject json;
//    json.insert("SceName", m_sceName/*"方案名称"*/);
//    json.insert("Person", QJsonValue(personObject));

//    qDebug() << "0000000000000000000"<<m_sceName;
//    // 构建 Json 文档
//    QJsonDocument document;
//    document.setObject(json);


//    QMap<QString, QVariant> mapData = QMap<QString, QVariant>();
//    mapData.insert("id", "3000101");
//    mapData.insert("number", "15289705326");
//    mapData.insert("name", "Job Bresh");
////    QJsonObject jscObject;
////    jscObject.fromVariantMap(mapData);
//    QJsonDocument doc = QJsonDocument::fromVariant(QVariant(mapData));
//    QByteArray jba = doc.toJson();
//    QString jsonString = QString(jba);
//    qDebug() << "QMap<QString, QVariant> to json: \n" << jsonString;

////    QByteArray njba = jsonString.toUtf8();
////    QJsonObject nobj = QJsonObject(QJsonDocument::fromJson(njba).object());
////    //字符串转换后的对象
////    qDebug() << "string conversion of object: \n"
////             << nobj.take("id").toString() << endl
////             << nobj.take("number").toString() << endl;

//    QFile saveFile(QStringLiteral("scesInfo2.json"));
//    if (!saveFile.open(QIODevice::WriteOnly)) {
//        qWarning("Couldn't open save file.");
//    }
//    doc.setObject(jscObject);
//    saveFile.write(doc.toJson());

    /* 遍历数据要使用迭代器，QT提供了两种方式的迭代 */
    /* 第一种是Java类型的迭代 */
//    QMapIterator<QString, QVariant> iterator(map);
//    while (iterator.hasNext()) {
//        iterator.next();
//        qDebug() << iterator.key() << ":" << iterator.value();
//    }

//    /* 第二种是STL类型的迭代 */
//    QMap<QString, QVariant>::const_iterator iterator_1 = map.constBegin();
//    while (iterator_1 != map.constEnd()) {
//        qDebug() << iterator_1.key() << ":" << iterator_1.value();
//        ++iterator_1;
//    }

    ////CESHI
    QJsonArray jsonArray;

    for(int i = 0; i<sce->m_PersonSize ; i++) {
        QJsonObject jsonObject;
        jsonObject.insert("id", sce->personArry[sce->m_PersonSize].ID);
        jsonArray.append(jsonObject);
    }
        //// 构建 Json 对象
//     QJsonObject json;
//    json.insert("SceName", m_sceName/*"方案名称"*/);
//    QJsonObject jsonObject;
//    jsonObject.insert("number", jsonArray.size());
//    jsonArray.append(jsonObject);
///DUXIEWENJAIN
    QFile saveFile(QStringLiteral("scesInfo1.json"));
    if (!saveFile.open(QIODevice::WriteOnly)) {
        qWarning("Couldn't open save file.");
    }
    QJsonDocument jsonDoc;
    jsonDoc.setArray(jsonArray);

    saveFile.write(jsonDoc.toJson());
    saveFile.close();
    qDebug() << "Write to file";
    return true;
}
//! [1]

//! [2]
void SceMangar::write(QJsonObject &json) const
{
//    QJsonObject playerObject;
//    m_Player.write(playerObject);
//    json["player"] = playerObject;

//    m_SceInfos.clear();
//    m_SceInfos.reserve(2);

//    QJsonArray sceslArray;
//    for (const SceInfo &sceInfos :m_SceInfos) {
//        QJsonObject scesObject;
//        sceInfos.write(scesObject);
//        sceslArray.append(scesObject);
//    }
//    json["sces"] = sceslArray;
}
//! [2]

void SceMangar::print(int indentation) const
{
    const QString indent(indentation * 2, ' ');
//    QTextStream(stdout) << indent << "Player\n";
//    m_Player.print(indentation + 1);

//    QTextStream(stdout) << indent << "sces\n";
//    for (SceInfo sceInfos : m_SceInfos)
//        sceInfos.print(indentation + 1);
}
