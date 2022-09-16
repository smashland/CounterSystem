#ifndef SCEMANGAR_H
#define SCEMANGAR_H
#include <QObject>
//#include "ScesPerson.h"
//#include "SceInfo.h"
#include <QByteArray>
#include <QJsonObject>

struct PersonConfigStruct
{
    int                  ID;          ///设备编号
    QString              Name;        ///人员名称
    QString              Position;    ///职务
    QString              GroupType;   ///红蓝方
    bool                 Hostage;     ///人质
};
Q_DECLARE_METATYPE(PersonConfigStruct)

struct SceConfigStruct
{
    struct PersonConfigStruct personArry[99];
    int m_PersonSize;
};
Q_DECLARE_METATYPE(SceConfigStruct)

class SceMangar : public QObject
{
    Q_OBJECT

public:

//    enum SaveFormat {
//        Json, Binary
//    };

    SceMangar(QWidget *parent = nullptr);
    ~SceMangar();


//        Q_PROPERTY(QString sceName READ m_sceName WRITE setSceName /*NOTIFY sceNameChanged*/)
    Q_PROPERTY(QString sceName MEMBER m_sceName NOTIFY sceNameChanged)
    Q_PROPERTY(int id MEMBER m_nID NOTIFY IDChanged)
    Q_PROPERTY(QString name MEMBER m_sName NOTIFY nameChanged)
    Q_PROPERTY(QString position MEMBER m_sPosition NOTIFY positionChanged)
    Q_PROPERTY(QString type MEMBER m_sGroupType NOTIFY groupTypeChanged)
    Q_PROPERTY(bool hostage MEMBER m_bHostage NOTIFY hostageChanged)



    /**
     * @brief 设置方案名称
     * @param sName
     */
     Q_INVOKABLE void setSceName(QString sName);
     Q_INVOKABLE QString getSceName(){ return(m_sceName);}

     /**
      * @brief 设置设备编号
      * @param nID
      */
     Q_INVOKABLE void setID(int nID);
     Q_INVOKABLE int  getID(){return(m_nID);}

     /**
      * @brief 设置人员名称
      * @param sName
      */
     Q_INVOKABLE void setName(QString sName);
     Q_INVOKABLE QString getName(){return(m_sName);}

     /**
      * @brief 设置人员职务
      * @param sPosition
      */
     Q_INVOKABLE void setPosition(QString sPosition);
     Q_INVOKABLE QString getPosition(){return(m_sPosition);}

    Q_INVOKABLE void setGroupType(QString groupType);
    Q_INVOKABLE QString getGroupType(){return(m_sGroupType);}

     /**
      * @brief 设置人质
      * @param sPosition
      */
     Q_INVOKABLE void setHostage(bool bHostage);
     Q_INVOKABLE bool getHostage(){return(m_bHostage);}

     Q_INVOKABLE bool addPerson();



//    ScesPerson player() const;
//    QVector<SceInfo> sceInfos() const;

     void newGame();
    Q_INVOKABLE bool loadInfo();
    Q_INVOKABLE bool saveInfo() ;

    void read(const QJsonObject &json);
    void write(QJsonObject &json) const;

    void print(int indentation = 0) const;

signals:
    void sceNameChanged(QString);
    void IDChanged(int);
    void nameChanged(QString);
    void positionChanged(QString);
    void groupTypeChanged(QString);
    void hostageChanged(bool);

private:
    QString              m_sceName;      /// 方案名称
    int                  m_nID;          ///设备编号
    QString              m_sName;        ///人员名称
    QString              m_sPosition;    ///职务
    QString              m_sGroupType;   ///红蓝方
    bool                 m_bHostage;     ///人质

    int                  m_sceCounts=0;
//    struct PersonConfigStruct personArry[1];

//    QVector<SceInfo>    m_SceInfos;
    SceConfigStruct* sce;

    QMap<QString,QVariant>  map;
    QByteArray          jsonArray;
};

#endif // SCEMANGAR_H
