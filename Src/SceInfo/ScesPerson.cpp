#include "ScesPerson.h"
#include <QMetaEnum>
#include <QTextStream>

ScesPerson::ScesPerson()
{

}
//ScesPerson::ScesPerson(int id, const QString &name, const QString &position, GroupType groupType,bool host):
//m_ID(id),
//m_Name(name),
//m_Positon(position),
//m_Group(groupType),
//m_host(host)
//ScesPerson::ScesPerson(int id, const QString &name):
//m_ID(id),
//m_Name(name)
//{

//}

//////设置士兵信息
//void ScesPerson::setID(int nID)
//{
//    m_ID=nID;
//    qDebug()<<"id99999999"<<m_ID;
//}

//int ScesPerson::getID()
//{
//    return m_ID;
//}

//void ScesPerson::setName(QString sName)
//{
//    m_Name=sName;
//    qDebug()<<"Name99999999"<<m_Name;
//}

//QString ScesPerson::getName()
//{
//    return m_Name;
//}

//void ScesPerson::setPosition(QString sPosition)
//{
//    m_Positon=sPosition;
//}

//QString ScesPerson::getPosition()
//{
//    return m_Positon;
//}

//void ScesPerson::setGroupType(QString groupType)
//{
//    m_Group=groupType;
//}

//QString ScesPerson::getGroupType()
//{
//    return m_Group;
//}

//void ScesPerson::setHostage(int bHostage)
//{
//    m_host=bHostage;
//}

//bool ScesPerson::getHostage()
//{
//    return m_host;
//}



//int ScesPerson::id() const
//{
//    return m_ID;
//}
//void ScesPerson::setId(int id)
//{
//    m_ID = id;
//}

//QString ScesPerson::name() const
//{
//    return m_Name;
//}
//void ScesPerson::setName(const QString &name)
//{
//    m_Name = name;
//}

//QString ScesPerson::position() const
//{
//    return m_Positon;
//}
//void ScesPerson::setPosition(const QString &position)
//{
//    m_Positon = position;
//}

//int ScesPerson::groupType() const
//{
//    return m_Group;
//}
//void ScesPerson::setGroupType(int groupType)
//{
//    m_Group=groupType;
//}

////ScesPerson::GroupType ScesPerson::groupType() const
////{
////    return m_Group;
////}
////void ScesPerson::setGroupType(ScesPerson::GroupType groupType)
////{
////    m_Group=groupType;
////}

//bool ScesPerson::host() const
//{
//    return m_host;
//}
//void ScesPerson::setHost(bool host)
//{
//    m_host = host;
//}

////! [0]
//void ScesPerson::read(const QJsonObject &json)
//{
//    if (json.contains("id") && json["id"].isDouble())
//        m_ID = json["id"].toInt();

//    if (json.contains("name") && json["name"].isString())
//        m_Name = json["name"].toString();

////    if (json.contains("groupType") && json["groupType"].isDouble())
////        m_Group = GroupType(json["groupType"].toInt());
//}
////! [0]

////! [1]
//void ScesPerson::write(QJsonObject &json) const
//{
//    json["id"] = m_ID;
//    json["name"] = m_Name;
////    json["groupType"] = m_Group;
//}
////! [1]

//void ScesPerson::print(int indentation) const
//{
//    const QString indent(indentation * 2, ' ');
//    QTextStream(stdout) << indent << "ID:\t" << m_ID << "\n";
//    QTextStream(stdout) << indent << "Name:\t" << m_Name << "\n";
////    QTextStream(stdout) << indent << "Group:\t" << m_Group << "\n";

////    QString groupName = QMetaEnum::fromType<GroupType>().valueToKey(m_Group);
////    QTextStream(stdout) << indent << "Group:\t" << m_Group << "\n";
//}
