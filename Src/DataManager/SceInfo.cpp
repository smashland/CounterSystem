#include "SceInfo.h"
#include <QCborMap>
#include <QCborValue>
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QRandomGenerator>
#include <QTextStream>

//SceInfo::SceInfo(QObject *parent)
//    : QObject{parent}
//{

//}

SceInfo::SceInfo(const QString &name) : m_Name(name)
{

}

//void SceInfo::setname(QString name) const
//{
//    m_Name=name;
//}

QString SceInfo::name() const
{
    return m_Name;
}

QVector<ScesPerson> SceInfo::sces() const
{
    return m_Sces;
}

void SceInfo::setSces(const QVector<ScesPerson> &sces)
{
    m_Sces = sces;
}

//! [0]
void SceInfo::read(const QJsonObject &json)
{
    if (json.contains("name") && json["name"].isString())
        m_Name = json["name"].toString();

    if (json.contains("secs") && json["secs"].isArray()) {
        QJsonArray secsArray = json["secs"].toArray();
        m_Sces.clear();
        m_Sces.reserve(secsArray.size());
        for (int scesIndex = 0; scesIndex < secsArray.size(); ++scesIndex) {
            QJsonObject secsObject = secsArray[scesIndex].toObject();
            ScesPerson sces;
            sces.read(secsObject);
            m_Sces.append(sces);
        }
    }
}
//! [0]

//! [1]
void SceInfo::write(QJsonObject &json) const
{
    json["name"] = m_Name;
    QJsonArray secsArray;
    for (const ScesPerson &secs : m_Sces) {
        QJsonObject secsObject;
        secs.write(secsObject);
        secsArray.append(secsObject);
    }
    json["secs"] = secsArray;
}
//! [1]

void SceInfo::print(int indentation) const
{
    const QString indent(indentation * 2, ' ');
    QTextStream(stdout) << indent << "Name:\t" << m_Name << "\n";

    QTextStream(stdout) << indent << "scesPerson:\n";
    for (const ScesPerson &scesPerson : m_Sces)
        scesPerson.print(2);
}
