#ifndef SCESPERSON_H
#define SCESPERSON_H

#include <QJsonObject>
#include <QString>


enum GroupType {
    RED, BLUE, NON
};

class ScesPerson
{
//        Q_GADGET;
public:
//    enum GroupType {
//        RED, BLUE, NON
//    };
//   Q_ENUM(GroupType)


    ScesPerson();
    ScesPerson(int id, const QString &name);
//    personInfo(int id, const QString &name, const QString &position, GroupType groupType,bool host);

    int id() const;
    void setId(int id);

    QString name() const;
    void setName(const QString &name);

    QString position() const;
    void setPosition(const QString &positin);

//    GroupType groupType() const;
//    void setGroupType(GroupType groupType);
    int groupType() const;
    void setGroupType(/*GroupType*/int groupType);

    bool host() const;
    void setHost(bool host);

    void read(const QJsonObject &json);
    void write(QJsonObject &json) const;

    void print(int indentation = 0) const;

private:
    int        m_ID;
    QString    m_Name;
    QString    m_Positon;
//    GroupType  m_Group;
    int        m_Group;
    bool       m_host;
};
#endif // SCESPERSON_H
