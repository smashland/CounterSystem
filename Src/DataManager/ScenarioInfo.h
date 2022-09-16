#ifndef SCENARIOINFO_H
#define SCENARIOINFO_H

#include <QObject>
//#include <QSettings>

//#define PERSON_MAX 1000
//#define SCE_MAX 1000

//struct PersonConfigStruct
//{
//    int                  ID;          ///设备编号
//    QString              Name;        ///人员名称
//    QString              Position;    ///职务
//    QString              GroupType;   ///红蓝方
//    bool                 Hostage;     ///人质
//};
//Q_DECLARE_METATYPE(PersonConfigStruct)

//struct SceConfigStruct
//{
//    QString              SceName;     /// 方案名称
//    PersonConfigStruct   PersonConfigStruct[PERSON_MAX];
//};
//Q_DECLARE_METATYPE(SceConfigStruct)

class ScenarioInfo : public QObject
{
    Q_OBJECT
public:
    explicit ScenarioInfo(QObject *parent = nullptr);
    ~ScenarioInfo();
//    SceConfigStruct m_SceConfigStruct[SCE_MAX];
//    ///单例
//    static ScenarioInfo* GetInstance();

//    Q_PROPERTY(QString sceName MEMBER m_sSceName NOTIFY sceNameChanged)
//    Q_PROPERTY(int id MEMBER m_nID NOTIFY IDChanged)
//    Q_PROPERTY(QString name MEMBER m_sName NOTIFY nameChanged)
//    Q_PROPERTY(QString position MEMBER m_sPosition NOTIFY positionChanged)
//    Q_PROPERTY(QString type MEMBER m_sGroupType NOTIFY groupTypeChanged)
//    Q_PROPERTY(bool hostage MEMBER m_bHostage NOTIFY hostageChanged)

//    // 方案数量
//    Q_INVOKABLE int scenariosCount();

//    /**
//     * @brief 保存ini文件
//     */
//    Q_INVOKABLE void saveIni();

//    /**
//     * @brief 设置方案名称
//     * @param sName
//     */
//    Q_INVOKABLE void setSceName(const QString& sName);
//    QString getSceName(){return(m_sSceName);}

//    /**
//     * @brief 设置设备编号
//     * @param nID
//     */
//    void setID(const int& nID);
//    int  getID(){return(m_nID);}

//    /**
//     * @brief 设置人员名称
//     * @param sName
//     */
//    void setName(const QString& sName);
//    QString getName(){return(m_sName);}

//    /**
//     * @brief 设置人员职务
//     * @param sPosition
//     */
//    void setPosition(const QString& sPosition);
//    QString getPosition(){return(m_sPosition);}

//    /**
//     * @brief 设置人质
//     * @param sPosition
//     */
//    void setHostage(const bool& bHostage);
//    bool getHostage(){return(m_bHostage);}

////private:
//    /**
//     * @brief 解析INI文件
//     */
//    void praseIni();
//    int saveIni(ScenarioInfo *scenarioInfo);
////    Q_INVOKABLE void saveIni();

//signals:
//    void sceNameChanged(QString);
//    void IDChanged(int);
//    void nameChanged(QString);
//    void positionChanged(QString);
//    void groupTypeChanged(QString);
//    void hostageChanged(bool);

//private:
//    QString              m_qstrFileName;
//    QSettings           *m_psetting;

//    QString              m_sSceName;     /// 方案名称
//    int                  m_nID;          ///设备编号
//    QString              m_sName;        ///人员名称
//    QString              m_sPosition;    ///职务
//    QString              m_sGroupType;   ///红蓝方
//    bool                 m_bHostage;     ///人质
//    int                  m_scenCounts=0;

//    QList<QObject*>      m_scenarios;    ///方案信息


};

#endif // SCENARIOINFO_H




