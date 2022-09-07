#include <QtCore/QtCore>
#include "ScenarioInfo.h"


ScenarioInfo::ScenarioInfo(QObject *parent)
    : QObject{parent}
{
    m_qstrFileName = QCoreApplication::applicationDirPath() + "/Data/Project/Config.ini";
    //"Config.ini"配置文件，文件存在则打开，不存在则创建
    m_psetting = new QSettings(m_qstrFileName,QSettings::IniFormat);

}

/// 获取单例指针
ScenarioInfo* ScenarioInfo::GetInstance()
{
    static ScenarioInfo  sceDataManger;
    return(&sceDataManger);
}
/// 设置名称
void ScenarioInfo::setSceName(const QString &sName)
{
    if(sName != m_sSceName)
    {
        m_sSceName = sName;
        emit(sceNameChanged(m_sSceName));
    }
}

///设置设备编号
void ScenarioInfo::setID(const int& nID)
{
    if(nID != m_nID)
    {
        m_nID = nID;
        emit(IDChanged(m_nID));
    }
}

///设置人员名称
void ScenarioInfo::setName(const QString& sName)
{
    if(sName != m_sName)
    {
        m_sName = sName;
        emit(nameChanged(m_sName));
    }
}

///设置人员职务
void ScenarioInfo::setPosition(const QString& sPosition)
{
    if(sPosition != m_sPosition)
    {
        m_sPosition = sPosition;
        emit(positionChanged(m_sPosition));
    }
}

///设置人质
void ScenarioInfo::setHostage(const bool& bHostage)
{
    if(bHostage != m_bHostage)
    {
        m_sPosition = bHostage;
        emit(hostageChanged(m_bHostage));
    }
}



///解析文件
void ScenarioInfo::praseIni()
{
    m_psetting->setIniCodec("UTF8");     //可读取中文
//    m_sSceName=m_psetting->value("/Scenario/sceName").toString();

    //读取结构体
    QVariant v = m_psetting->value("/Scenario/SceConfigStruct");
    //转换
    SceConfigStruct str = v.value<SceConfigStruct>();
    //
    m_sSceName=str.SceName;
    m_nID=str.PersonConfigStruct->ID;
    m_sName=str.PersonConfigStruct->Name;
    m_sPosition=str.PersonConfigStruct->Position;
    m_sGroupType=str.PersonConfigStruct->GroupType;
    m_bHostage=str.PersonConfigStruct->Hostage;


    /*qDebug() << str.RxBaud << str.RxBitLength << str.RxParity
             << str.RxMode << str.RxFrameHeader << str.RxFramLength
             << str.RxLocalInterruptEn << str.RxDepth << str.TxBaud
             << str.TxBitLength << str.TxParity << str.TxStopBit;*/
}


///保存文件
//int ScenarioInfo::saveIni(ScenarioInfo *memberInfo)
void ScenarioInfo::saveIni()
{
    m_psetting->setValue("/Scenario/sceName",m_sSceName);
    m_psetting->setValue("/Scenario/id",m_nID);
    m_psetting->setValue("/Scenario/Name",m_sName);
    m_psetting->setValue("/Scenario/position",m_sPosition);
    m_psetting->setValue("/Scenario/groupType",m_sGroupType);
    m_psetting->setValue("/Scenario/hostage",m_bHostage);

    qDebug()<<"测试方案管理================";
//    QVariantMap SetMap;
//    SetMap.insert("sceName", m_sSceName);
//    SetMap.insert("ID", m_nID);
//    SetMap.insert("Name", m_sName);
//    SetMap.insert("Position", m_sPosition);
//    SetMap.insert("GroupType",m_sGroupType);
//    SetMap.insert("Hostage",m_bHostage);

//    //结构体
//     //1、转换
//    QVariant v = QVariant::fromValue(m_SceConfigStruct[PERSON_MAX]);
//    //2、写入结构体
//    m_psetting->setValue("/Scenario/SceConfigStruct", v);
}


/// 析构数据数据
ScenarioInfo::~ScenarioInfo()
{
    saveIni();
    delete m_psetting;
}
