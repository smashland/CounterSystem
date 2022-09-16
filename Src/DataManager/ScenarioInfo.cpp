#include <QtCore/QtCore>
#include "ScenarioInfo.h"


//ScenarioInfo::ScenarioInfo(QObject *parent)
//    : QObject{parent}
//{
//    m_qstrFileName = QCoreApplication::applicationDirPath() + "/Data/Project/Config.ini";
//    //"Config.ini"配置文件，文件存在则打开，不存在则创建
//    m_psetting = new QSettings(m_qstrFileName,QSettings::IniFormat);
//    m_psetting->setIniCodec("UTF8");

//}

///// 获取单例指针
//ScenarioInfo* ScenarioInfo::GetInstance()
//{
//    static ScenarioInfo  sceDataManger;
//    return(&sceDataManger);
//}
///// 设置名称
//void ScenarioInfo::setSceName(const QString &sName)
//{
//    if(sName != m_sSceName)
//    {
//        m_sSceName = sName;
//        emit(sceNameChanged(m_sSceName));
//    }
//}

/////设置设备编号
//void ScenarioInfo::setID(const int& nID)
//{
//    if(nID != m_nID)
//    {
//        m_nID = nID;
//        emit(IDChanged(m_nID));
//    }
//}

/////设置人员名称
//void ScenarioInfo::setName(const QString& sName)
//{
//    if(sName != m_sName)
//    {
//        m_sName = sName;
//        emit(nameChanged(m_sName));
//    }
//}

/////设置人员职务
//void ScenarioInfo::setPosition(const QString& sPosition)
//{
//    if(sPosition != m_sPosition)
//    {
//        m_sPosition = sPosition;
//        emit(positionChanged(m_sPosition));
//    }
//}

/////设置人质
//void ScenarioInfo::setHostage(const bool& bHostage)
//{
//    if(bHostage != m_bHostage)
//    {
//        m_sPosition = bHostage;
//        emit(hostageChanged(m_bHostage));
//    }
//}



/////解析文件
//void ScenarioInfo::praseIni()
//{
////    m_psetting->setIniCodec("UTF8");     //可读取中文
////    m_sSceName=m_psetting->value("/Scenario/sceName").toString();

//    //读取结构体
//    QVariant v = m_psetting->value("/Scenario/SceConfigStruct");
//    //转换
//    SceConfigStruct str = v.value<SceConfigStruct>();
//    //
//    m_sSceName=str.SceName;
//    m_nID=str.PersonConfigStruct->ID;
//    m_sName=str.PersonConfigStruct->Name;
//    m_sPosition=str.PersonConfigStruct->Position;
//    m_sGroupType=str.PersonConfigStruct->GroupType;
//    m_bHostage=str.PersonConfigStruct->Hostage;
//}


/////保存文件
////int ScenarioInfo::saveIni(ScenarioInfo *scenarioInfo)
//void ScenarioInfo::saveIni()
//{
////    //结构体
////     //1、转换
////    QVariant v = QVariant::fromValue(m_SceConfigStruct[PERSON_MAX]);
////    //2、写入结构体
////    m_psetting->setValue("/Scenario/SceConfigStruct", v);
////      delete m_psetting;

//      m_psetting->beginWriteArray("Scenario");
//      m_psetting->setArrayIndex(m_scenCounts);
//      m_psetting->setValue("sceName",m_sSceName);
//      m_psetting->endArray();
//      m_scenCounts++;
//      m_psetting->setValue("sceNameCount",m_scenCounts);
//      qDebug()<<"测试方案管理================"<<m_scenCounts;
////       m_psetting->setValue("password", m_scenarios.at(i).m_sSceName);

//}
//// 方案数量
//int ScenarioInfo::scenariosCount()
//{
//    return m_scenarios.size();
//}

///// 析构数据数据
//ScenarioInfo::~ScenarioInfo()
//{
////    saveIni();
////    delete m_psetting;
//}
