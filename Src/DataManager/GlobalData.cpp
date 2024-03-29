﻿#include <QUrl>
#include <QApplication>
#include "../ParseData/DealDataManager.h"
#include "GlobalData.h"
#include "MyListModel.h"
#include "PersonStatus.h"
#include "DataManager.h"
#include "TypeDefine.pb.h"
#include "PersonInfo.pb.h"
#include "GroupStatus.h"
#include "../Export/ExportResult.h"
#include "../ConfigInfo.h"
#include "../TimeServer/TimeServer.h"
#include "PersonAllInfo.h"
#include "../Map/ContrlMapPerson.h"
#include "../Notice/NoticeManager.h"
#include "../SceInfo/SceManager.h"
#include "../SceInfo/ScePersonInfo.h"
#include "../SceInfo/SceInfo.h"
#include "../Connection/ConnectionManager.h"
#include "Src/NoticManger.h"

CGlobalData::CGlobalData(QObject *parent) : QObject(parent),
    m_sCurrentFileName(QDir::homePath())
{
    qRegisterMetaType<CMyListModel*>("CMyListModel*");
    qRegisterMetaType<CPersonStatus*>("CPersonStatus*");
    qRegisterMetaType<CGroupStatus*>("CGroupStatus*");
    qRegisterMetaType<CPersonAllInfo*>("CPersonAllInfo*");
    qRegisterMetaType<SceManager*>("SceManager");
    m_listStatusModel = new CMyListModel;
    m_pPersonAllInfo = new CPersonAllInfo;
}

CGlobalData::~CGlobalData()
{
    delete m_listStatusModel;
    delete m_pPersonAllInfo;
    delete m_pCtrMapPerson;
}

/// 更新指定ID的人员信息
void CGlobalData::UpdateID(quint16 unID)
{
    CPersonStatus* pPersonStatus=GetOrCreatePersonStatus(unID);
    pPersonStatus->Update(m_unTimes);
    UpdateMap(unID);
}


/// 更新事件
void CGlobalData::UpdateEvent(quint16 unID)
{
    CPersonStatus* pPersonStatus=GetOrCreatePersonStatus(unID);
    pPersonStatus->Update(m_unTimes);

    /// 遍历所有的类型信息
    for(auto findOne = m_mapTypeInfo.begin();
        findOne != m_mapTypeInfo.end(); ++findOne)
    {
        if(findOne.value()->UpdatePerson(unID,pPersonStatus))
        {
            emit(updateGroup(findOne.value()->GetGroupStatus()));
            break;
        }
    }

    /// 交火线
    auto pPerson = CDataManager::GetInstance()->GetOrCreatePersonInfo(unID);
    if(0 < pPerson->hurtinfo_size())
    {
        m_pCtrMapPerson->UpdateHitLine(pPerson->hurtinfo(pPerson->hurtinfo_size()-1).id(),pPerson->id());
    }

    /// 将事件ID存放到list
    m_listEvent.push_back(unID);

    UpdateMap(unID);

    if(CConfigInfo::GetInstance()->GetStart())
    {
        UpdateLiveNum();
    }
}

/// 更新时间
void CGlobalData::UpdateSeconds(const quint16& unSconds)
{
    static int nSize;
    nSize =0;
    m_unTimes = unSconds;
    if(CConfigInfo::GetInstance()->GetStart())
    {
        emit unTimesChanged(m_unTimes);
    }
    for(auto one=m_mapStatusModel.begin();
        one != m_mapStatusModel.end(); ++one)
    {
        CPersonStatus* pPersonStatus=one.value();
        pPersonStatus->updateTime(m_unTimes);
        if(pPersonStatus->IsOnLine())
        {
            ++nSize;
        }
    }

    if(m_nOnLine != nSize)
    {
        m_nOnLine = nSize;
        emit lineSizeChanged(m_nOnLine);
    }

    if(m_bUpdate)
    {
        m_pPersonAllInfo->Update();
    }

    ///  如果文件打开则写入
    if(m_outFile.is_open())
    {
        m_outFile.write(reinterpret_cast<char*>(&m_unTimes),sizeof(m_unTimes));

        nSize = m_listEvent.size();
        m_outFile.write(reinterpret_cast<char*>(&nSize),sizeof(nSize));
        for(auto one : m_listEvent)
        {
            m_outFile.write(reinterpret_cast<char*>(&one),sizeof(one));
        }

        m_listEvent.clear();
    }
}

/// 更新仿真时间
int tempSimTime=0;
void CGlobalData::UpdateSimulationTime(const quint16 &uSimTimes)
{
    int eventTime=0;
    if(abs(uSimTimes-tempSimTime)>1)
    {
        CNoticeManager::GetInstance()->SetClearNoticInfo();
        emit clearShowText();
        UpdateSimulationTimeInfo(uSimTimes);
        tempSimTime=uSimTimes;
    }
    else
    {
        tempSimTime=uSimTimes;
    }
    emit simTimeChanged(uSimTimes);

    for(auto one:m_allReplayStatus)
    {
        one->updateTime(uSimTimes);
        one->Update(uSimTimes);
        UpdateMap(one->getId());
    }
    const QVector<int>& events = m_allReplayEvent[uSimTimes];
    if(!events.isEmpty())
    {
        for(int i=0;i<m_listEventTime.size();i++)
        {
            if(m_listEventTime.at(i)==uSimTimes)
            {
                if(m_listNoticText.size()>i)
                {
                    qDebug()<<"m_listEventTime.size():"<<m_listEventTime.size()<<eventTime;
                    eventTime=i;
                }

            }
        }
    }
    for(auto one : events)
    {
        bool evevtFlag=true;
        /// 交火线
        auto pPerson = CDataManager::GetInstance()->GetOrCreatePersonInfo(one);
        int b = 0;
        int nHurtIndex=pPerson->hurtinfo_size()-1;
        //        for(int nHurtIndex = pPerson->hurtinfo_size()-1; -1 < nHurtIndex;--nHurtIndex)
        if(evevtFlag==true&&-1<nHurtIndex)
        {

            evevtFlag=false;
            //            nHurtIndex = pPerson->hurtinfo_size()-1;
            qDebug()<<"nHurtIndex=="<<nHurtIndex<<"hurtinfo_size"<<pPerson->hurtinfo_size()<<pPerson->hurtinfo(nHurtIndex).type();
            m_pCtrMapPerson->UpdateHitLine(pPerson->hurtinfo(nHurtIndex).id(),one);
            /// 增加命中状态

            QString type;
            QString oper;
            int nGunType=pPerson->hurtinfo(nHurtIndex).type();
            switch (nGunType)
            {
            case 1:
                type = QString::fromUtf8("步枪");
                break;
            case 2:
                type = QString::fromUtf8("手枪");
                break;
            case 4:
                type = QString::fromUtf8("手雷");
                break;
            case 8:
                type = QString::fromUtf8("手雷2");
                break;
            case 16:
                type = QString::fromUtf8("手枪2");
                break;
            case 32:
                type = QString::fromUtf8("爆炸物");
                break;
            case 64:
                type = QString::fromUtf8("狙击枪");
                break;
            case 128:
                type = QString::fromUtf8("狙击枪11");
                break;
            }

            auto pPerson1 = CDataManager::GetInstance()->GetOrCreatePersonInfo(pPerson->hurtinfo(nHurtIndex).id());
            QString listInfo=QString::fromUtf8("%1%2使用%3击中%4%5").arg(pPerson->hurtinfo(nHurtIndex).id()).arg(pPerson1->name().c_str())
                    .arg(type).arg(pPerson->id()).arg(pPerson->name().c_str());
            if(nGunType==1||nGunType==2||nGunType==64)
            {
                listInfo +="的"+ CConfigInfo::GetInstance()->GetBodyName(pPerson->hurtinfo(nHurtIndex).hurtpart());
            }
            ///阵营颜色
            QString group=m_mapIdType.value(pPerson->hurtinfo(nHurtIndex).id());
            CNoticeManager::GetInstance()->SetColor(pPerson->hurtinfo(nHurtIndex).id(),group);//SetGroupId(pPerson->hurtinfo(nHurtIndex).id());
            /// 发送消息
            //            CNoticeManager::GetInstance()->SetNoticInfo(listInfo);
            CNoticeManager::GetInstance()->SetReplayNoticInfo(m_listNoticText.at(eventTime));
            --nHurtIndex;
        }
    }

    if(m_bUpdate)
    {
        m_pPersonAllInfo->Update();
    }
}

void CGlobalData::UpdateSimulationTimeInfo(const quint16 &uSimTimes)
{
    for(int i=0;i<m_listEventTime.size();i++)
    {
        if(m_listEventTime.at(i)<uSimTimes)
        {
            for(auto one:m_allReplayStatus)
            {
                one->updateTime(m_listEventTime.at(i));
                one->Update(m_listEventTime.at(i));
                UpdateMap(one->getId());
            }
            const QVector<int>& events = m_allReplayEvent[m_listEventTime.at(i)];
            for(auto one : events)
            {
                bool evevtFlag=true;
                /// 交火线
                auto pPerson = CDataManager::GetInstance()->GetOrCreatePersonInfo(one);
                int nHurtIndex=pPerson->hurtinfo_size()-1;

                if(evevtFlag==true&&nHurtIndex>-1)
                {
                    evevtFlag=false;
                    {
                        ///阵营颜色
                        QString group=m_mapIdType.value(pPerson->hurtinfo(nHurtIndex).id());
                        CNoticeManager::GetInstance()->SetColor(pPerson->hurtinfo(nHurtIndex).id(),group);
                        /// 发送消息
                    }
                }
            }
            if(i<m_listNoticText.size())
            {
                CNoticeManager::GetInstance()->SetHitInfo(m_listNoticText.at(i));
            }
        }
    }
}

/// 更新
void CGlobalData::UpdateTime(const QDateTime &dateTime)
{
    /// 演习开始
    if(!m_outFile.is_open() && CConfigInfo::GetInstance()->GetStart())
    {
        QString sTempLocal = dateTime.toString("/yyyyMMdd_HHmmss");
        QString sDataFile = CDataManager::GetInstance()->GetFileName(sTempLocal);
        m_sCurrentFileName = QDir::homePath() + sTempLocal;
        m_outFile.open(m_sCurrentFileName.toStdString(),std::ios::binary|std::ios::out);

        if(m_outFile.is_open())
        {
            /// 写入真正的演习数据的文件，路径长度，路径地址
            int nSize=sDataFile.toLocal8Bit().size();
            m_outFile.write(reinterpret_cast<char*>(&nSize),sizeof(nSize));
            m_outFile.write(sDataFile.toLocal8Bit().data(),nSize);

            int nId(0);
            /// 写入分组数量
            nSize = m_mapTypeInfo.size();
            m_outFile.write(reinterpret_cast<char*>(&nSize),sizeof(nSize));

            /// 写入每组的人员ID
            for(auto pOne = m_mapTypeInfo.begin(); pOne != m_mapTypeInfo.end();++pOne)
            {
                /// 写入每组的组名长度和组名
                nSize=pOne.key().toLocal8Bit().size();
                m_outFile.write(reinterpret_cast<char*>(&nSize),sizeof(nSize));
                m_outFile.write(pOne.key().toLocal8Bit().data(),nSize);

                /// 写入每组的人员数量和人员ID
                nSize = pOne.value()->count();
                m_outFile.write(reinterpret_cast<char*>(&nSize),sizeof(nSize));
                for(int nIndex=0; nIndex < nSize; ++nIndex)
                {
                    nId = pOne.value()->at(nIndex)->getId();
                    m_outFile.write(reinterpret_cast<char*>(&nId),sizeof(nId));
                }
            }
        }
    }

    /// 演习结束，关闭文件
    if(m_outFile.is_open() && !CConfigInfo::GetInstance()->GetStart())
    {
        m_outFile.close();
    }
}

/// 更新所有的数据
void CGlobalData::updateAllDataSize(int nData)
{
    if(nData != m_nAllData)
    {
        m_nAllData = nData;
        emit(allDataChanged(m_nAllData));
    }
}

/// 获取人员的所有信息
CPersonAllInfo *CGlobalData::getPersonAllInfo(quint16 unID)
{
    auto pPersonStatus = GetOrCreatePersonStatus(unID);
    m_pPersonAllInfo->UpdateTypeAndName(pPersonStatus->getName(),pPersonStatus->getType());
    m_pPersonAllInfo->Update(unID);
    return(m_pPersonAllInfo);
}

/// 设置用户名称
void CGlobalData::setUserName(quint16 unID, const QString &sName)
{
    QString IdVsName;
    auto pPersonStatus = GetOrCreatePersonStatus(unID);
    pPersonStatus->setName(sName);
    IdVsName=QString::number(unID)+" "+sName;
    m_pCtrMapPerson->UpdateName(unID,IdVsName/*unID + sName*/);

    auto pPersonInfo = CDataManager::GetInstance()->GetOrCreatePersonInfo(unID);
    pPersonInfo->set_name(sName.toStdString());
}

/// 清空状态
void CGlobalData::clearInfo()
{
    /// 清空事件信息
    CDealDataManager::GetInstance()->Clear();

    /// 清空人员信息
    CDataManager::GetInstance()->ResetPersonInfo();

    for(auto findOne = m_mapTypeInfo.begin();
        findOne != m_mapTypeInfo.end(); ++findOne)
    {
        findOne.value()->Clear();
    }

    UpdateLiveNum();
}

void CGlobalData::clearNameInfo()
{
    CDataManager::GetInstance()->ResetPersonName();
}

/// 创建类型
CMyListModel *CGlobalData::ceateType(const QString &sType)
{
    if(sType.isEmpty())
    {
        return(m_listStatusModel);
    }

    auto findOne = m_mapTypeInfo.find(sType);
    if(m_mapTypeInfo.end() != findOne)
    {
        return(findOne.value());
    }
    else
    {
        auto one = new CMyListModel(this);
        m_mapTypeInfo.insert(sType,one);
        one->GetGroupStatus()->SetTypeName(sType);
        return one;
    }
}

/// 获取所有的类型
QList<QString> CGlobalData::getAllType()
{
    QList<QString> vTempList;
    for(auto findOne = m_mapTypeInfo.begin(); m_mapTypeInfo.end() != findOne; ++findOne)
    {
        vTempList.push_back(findOne.key());
    }
    return(vTempList);
}

/// 统计结果
void CGlobalData::calResult()
{
    m_listResult.clear();
    m_listAllResult.clear();
    m_listHitRateResult.clear();


    QVariantMap tmpMap;
    QList<int>  listTemp;
    for(auto findOne = m_mapTypeInfo.begin(); m_mapTypeInfo.end() != findOne; ++findOne)
    {
        tmpMap.insert("belong",findOne.key());
        auto itorSecond = findOne.value();
        tmpMap.insert("all",itorSecond->totalNum());
        tmpMap.insert("hurt",itorSecond->hurtNum());
        tmpMap.insert("dealth",itorSecond->deathNum());
        tmpMap.insert("score",itorSecond->getScore());
        m_listResult.push_back(tmpMap);

        tmpMap.insert("hurt",itorSecond->GetGroupStatus()->GetHurtRatio());
        tmpMap.insert("dealth",1.0f-itorSecond->GetGroupStatus()->GetLiveRatio());
        tmpMap.insert("ok",itorSecond->GetGroupStatus()->GetLiveRatio()-itorSecond->GetGroupStatus()->GetHurtRatio());
        m_listAllResult.push_back(tmpMap);

//        tmpMap.insert("allBullets",itorSecond->getAllBullets());
//        tmpMap.insert("depleteBullets",itorSecond->getDepleteBullets());
//        tmpMap.insert("hitRate",itorSecond->gethitRate());

//        m_listAllResult.push_back(tmpMap);

//        listTemp=itorSecond->getBulletsList();

////        m_listHitRateResult = listTemp;
//        foreach(auto e, listTemp)
//        {
//            m_listHitRateResult.push_back(e);
//        }
    }



    /// 更新模型列表
    emit(resultChanged(m_listResult));
    emit(allResultChanged(m_listAllResult));

//    emit(hitRateChanged(m_listHitRateResult));
}

/// 定位人员
void CGlobalData::dingWei(quint16 unID)
{
    m_pCtrMapPerson->Locate(unID);
}

/// 设置地图信息
void CGlobalData::SetSeceneGraph(ISceneGraph *pSceneGraph)
{
    if(nullptr == m_pCtrMapPerson)
    {
        m_pCtrMapPerson = new CContrlMapPerson(pSceneGraph,this);
        //        connect(m_pCtrMapPerson,&CContrlMapPerson::mapPersonInfo,this,&CGlobalData::mapPersonInfo);
        CTimeServer::GetInstance()->SubTime(m_pCtrMapPerson);
    }
}

int CGlobalData::openReplayFile(const QUrl &rReplayFile)
{
    m_pCtrMapPerson->ClearMap();
    m_listEventTime.clear();
    std::string sFileName =rReplayFile.toLocalFile().toLocal8Bit().data();
    std::ifstream inFile;
    inFile.open(sFileName,std::ios::binary|std::ios::in);
    char buffer[256]="";
    int nSize,nID;
    int nIndex(0),nGroupIndex(0),nGroupSize(0);

    quint16 unTimes(0);
    if(inFile.is_open())
    {
        PushBackStatus();
        m_allReplayEvent.clear();
        m_mapIdType.clear();
        /// 获取路径大小
        inFile.read(reinterpret_cast<char*>(&nSize),sizeof(nSize));
        inFile.read(buffer,nSize);
        /// 读取真实的人员状态信息
        CDataManager::GetInstance()->ReadFile(buffer);

        /// 获取分组个数
        inFile.read(reinterpret_cast<char*>(&nGroupSize),sizeof(nGroupSize));
        while(nGroupIndex < nGroupSize)
        {
            /// 获取每组的人员数量，组名，各个人的状态
            nIndex = 0;
            inFile.read(reinterpret_cast<char*>(&nSize),sizeof(nSize));
            inFile.read(buffer,nSize);
            QString type = QString::fromLocal8Bit(buffer,nSize);

            auto findType = m_mapTypeInfo.find(type);
            /// 获取人员ID
            inFile.read(reinterpret_cast<char*>(&nSize),sizeof(nSize));
            while(nIndex++ < nSize)
            {
                inFile.read(reinterpret_cast<char*>(&nID),sizeof(nID));
                auto pPersonStatus = new CPersonStatus(nID,this);
                pPersonStatus->setType(type);
                qDebug()<<"openReplayFile:-------------"<<nID<<type;
                m_pCtrMapPerson->UpdateGroup(nID,type);
                //m_pCtrMapPerson->UpdateName(nID,);
                m_mapIdType.insert(nID,type);
                m_allReplayStatus.push_back(pPersonStatus);
                findType.value()->append(pPersonStatus);
            }

            ++nGroupIndex;
        }

        QVector<int> vEventID;
        /// 读取仿真时间
        while(!inFile.eof())
        {
            inFile.read(reinterpret_cast<char*>(&unTimes),sizeof(unTimes));
            inFile.read(reinterpret_cast<char*>(&nSize),sizeof(nSize));
            vEventID.resize(nSize);
            for(nIndex=0;nIndex<nSize;++nIndex)
            {
                inFile.read(reinterpret_cast<char*>(&nGroupIndex),sizeof(nGroupIndex));
                vEventID[nIndex] = nGroupIndex;
            }

            m_allReplayEvent[unTimes]=vEventID;
            if(!vEventID.isEmpty())
            {
                m_listEventTime.append(unTimes);
            }
        }

        CTimeServer::GetInstance()->SetSimuEndTime(unTimes);
        inFile.close();
        qDebug()<<"m_listEventTime"<<m_listEventTime;
    }

    return(unTimes);
}
bool replayFlags=false;
/// 回放演习开始
void CGlobalData::beginReplay()
{
    if(!replayFlags)
    {
        CTimeServer::GetInstance()->SimuStart();
        replayFlags = true;
    }
}
///设置回放标志
void CGlobalData::setReplayFlags(bool flag)
{
    replayFlags=flag;
}

void CGlobalData::readNoticText(const QString& fileName)
{
    NoticManger* noticManger = new NoticManger;
    noticManger->praseNoticInfo(fileName);
    m_listNoticText=noticManger->listNoticInfo();
}

int CGlobalData::getStartTime()
{
    return m_unTimes;
}

void CGlobalData::setStopTime()
{
    m_unTimes=0;
}

void CGlobalData::pauseReplay()
{
    CTimeServer::GetInstance()->SimuPause();
}

void CGlobalData::setSimuTime(quint16 uTimes)
{
    CTimeServer::GetInstance()->SetSimuTime(uTimes);
}

/// 演习结束 恢复分组,删除临时变量
void CGlobalData::endReplay()
{
    replayFlags = false;
    CTimeServer::GetInstance()->SimuEnd();
    PopUpStatus();

    for(auto one : m_allReplayStatus)
    {
        delete one;
    }

    m_allReplayStatus.clear();
}

///回放演习结果初始化
void CGlobalData::initReplay()
{
    m_listNoticText.clear();
    emit simTimeChanged(0);
}

void CGlobalData::endNoInitRePlay()
{
    CTimeServer::GetInstance()->SimuEnd();

    //    for(auto one : m_allReplayStatus)
    //    {
    //        delete one;
    //    }

    //    m_allReplayStatus.clear();
}

bool CGlobalData::deleteReplayFile(const QString &sReplayame)
{
    QString filePath = QApplication::applicationDirPath() + QString("/Data/Szy/%1.szy").arg(sReplayame);

    if (filePath.isEmpty() || !QDir().exists(filePath))//是否传入了空的路径||路径是否存在
        return false;

    QFileInfo FileInfo(filePath);

    if (FileInfo.isFile())//如果是文件
        QFile::remove(filePath);
    return true;
}

/// 保存数据文件
void CGlobalData::saveData(const QUrl &sDataFileName)
{
    QDateTime current_date_time =QDateTime::currentDateTime();
    QString current_date =current_date_time.toString("(yyyyMMdd_hhmmss)");
    QString sFilepath=sDataFileName.toLocalFile().chopped(4)+current_date+".szy";
    /// 移动文件到指定位置
    QFile::rename(m_sCurrentFileName,sFilepath/*sDataFileName.toLocalFile()*/);
    m_bRemoveFile = false;
}

/// 创建导出文档
void CGlobalData::createReport(const QUrl &sReportFileName)
{
    StatisticResult();
    CExportResult::GetInstance()->CreateDocx(sReportFileName.toLocalFile(),sReportFileName.fileName().split(".")[0],m_mapTypeInfo);
}

///得到方案名称和平均位置
void CGlobalData::getSceVsLoc(const QString &sceName,const QString &aveLocation)
{
    CExportResult::GetInstance()->setCurrentSceName(sceName);
    CExportResult::GetInstance()->setAveLocation(aveLocation);
}

///保存方案信息
void CGlobalData::saveSceInfo(const QString &strScePath)
{
    QFileInfo fileInfo(strScePath);
    QString sceName = fileInfo.fileName().chopped(4);

    SceManager* sceManager=new SceManager();
    auto sceNewPerson=sceManager->createSceneri();
    for(auto one=m_mapTypeInfo.begin();one!=m_mapTypeInfo.end();++one)
    {

        int nPersonNum=one.value()->count();
        for(int i=0;i<nPersonNum;++i)
        {
            CPersonStatus * pStutus = one.value()->at(i);
            ScePersonInfo* cePersonInfo=new ScePersonInfo();
            cePersonInfo->setID(pStutus->getId());
            cePersonInfo->setName(pStutus->getName());
            cePersonInfo->setPosition(0);
            cePersonInfo->setGroupType(pStutus->getType()=="蓝方"?0:1);
            cePersonInfo->setHostage(false);
            sceNewPerson->addPerson(pStutus->getId(),cePersonInfo);

        }
    }
    sceManager->addScenari(sceName,sceNewPerson);
    sceManager->write();
}

void CGlobalData::loadSceInfo(const QString &sceName)
{
    clearAllInfo();
    SceManager* sceManager=new SceManager();
    auto sceInfo = qobject_cast<CSceInfo*>(sceManager->findScenario(sceName));

    QList<int> listId=sceInfo->getAll();
    for(int i=0;i<listId.size();i++)
    {
        auto cePersonInfo = qobject_cast<ScePersonInfo*>(sceInfo->findPerson(listId.at(i)));
        CPersonStatus* personStatus=new CPersonStatus();
        personStatus->setId(cePersonInfo->getID());
        personStatus->setName(cePersonInfo->getName());
        personStatus->setRenzhi(cePersonInfo->getHostage());
        QString typeTemp;
        if(cePersonInfo->getGroupType()==0)
        {
            typeTemp="蓝方";
        }
        else if(cePersonInfo->getGroupType()==1)
        {
            typeTemp=tr("红方");
        }
        personStatus->setType(typeTemp);
        m_mapStatusModel.insert(cePersonInfo->getID(),personStatus);

        CMyListModel* m_listTypeModel=ceateType(typeTemp);
        m_listTypeModel->append(personStatus);

        /// 更新所有的状态信息
        setUserName(cePersonInfo->getID(),cePersonInfo->getName());
        updateAllDataSize(m_mapStatusModel.count());
        if(cePersonInfo->getHostage())
        {
            m_pCtrMapPerson->UpdateGroup(cePersonInfo->getID(),"人质");;
        }
        else{
            m_pCtrMapPerson->UpdateGroup(cePersonInfo->getID(),typeTemp);
        }

        //        ///地图上人员信息
        QString UIdVName=QString::number(cePersonInfo->getID())+cePersonInfo->getName();
        m_pCtrMapPerson->UpdateName(cePersonInfo->getID(),UIdVName);

    }

}

void CGlobalData::setUpdateAllInfo(bool bUpdate)
{
    m_bUpdate = bUpdate;
}

/// 清空所有数据
void CGlobalData::clearAllInfo()
{
    for(auto itor = m_mapTypeInfo.begin();
        itor != m_mapTypeInfo.end();++itor)
    {
        for(int nSize = itor.value()->count()-1; nSize > -1; --nSize)
        {
            itor.value()->remove(nSize);
        }
    }

    for(int nSize = m_listStatusModel->count()-1; nSize > -1; --nSize)
    {
        m_listStatusModel->remove(nSize);
    }

    for(auto one = m_mapStatusModel.begin();one != m_mapStatusModel.end();++one)
    {
        delete one.value();
    }
    m_mapStatusModel.clear();

    m_pCtrMapPerson->ClearMap();
    clearInfo();
}

/// 清空数据，由qml调用
void CGlobalData::removeSavedFile()
{
    if(m_bRemoveFile)
    {
        QDir::home().remove(m_sCurrentFileName);
        CDataManager::GetInstance()->RemoveData();
    }

    m_bRemoveFile = true;
}

/// 更改分组
void CGlobalData::changeGroup(quint16 unID, QString sType)
{
    m_pCtrMapPerson->UpdateGroup(unID,sType);
}
void CGlobalData::setAllMune(const QString &type,int index,const QStringList &allInfo)
{
    QList<int> typeId,nTempInfo;
    if(type=="蓝方")
    {
        typeId=m_pCtrMapPerson->getBuleId();
    }
    else if(type=="红方")
    {
        typeId=m_pCtrMapPerson->getRedId();
    }
    else
    {
        typeId=m_pCtrMapPerson->getUnknowId();
    }
    switch(index)
    {
    case 0:
        for(int i=0;i<typeId.size();i++)
        {
            ChongdanAll(typeId.at(i),allInfo);
        }
        break;
    case 1:
        for(int i=0;i<typeId.size();i++)
        {
            CDealDataManager::GetInstance()->PersonalBiSuo(typeId.at(i));
        }
        break;
    case 2:
        for(int i=0;i<typeId.size();i++)
        {
            CDealDataManager::GetInstance()->PersonalJieSuo(typeId.at(i));
        }
        break;
    case 3:
        for(int i=0;i<typeId.size();i++)
        {
            CDealDataManager::GetInstance()->PersonalPanSi(typeId.at(i));
        }
        break;
    case 4:
        for(int i=0;i<typeId.size();i++)
        {
            CDealDataManager::GetInstance()->PersonalFuHuo(typeId.at(i));
        }
        break;
    }

}


/// 初始化
void CGlobalData::InitGlobalData()
{
    /// 订阅时间
    CTimeServer::GetInstance()->SubTime(this);
    CDataManager::GetInstance()->SubObserver(this);
}

/// 统计成绩
void CGlobalData::StatisticResult()
{
}

/// 获取qml显示的简要信息
CPersonStatus *CGlobalData::GetOrCreatePersonStatus(quint16 unID)
{
    /// 查找关联的显示
    auto findOne =m_mapStatusModel.find(unID);
    CPersonStatus* pPersonStatus=nullptr;
    if(m_mapStatusModel.end() != findOne)
    {
        pPersonStatus = findOne.value();
    }
    else
    {
        pPersonStatus = new CPersonStatus(unID,this);
        m_mapStatusModel[unID] = pPersonStatus;

        /// 添加到默认的分组中
        m_listStatusModel->append(pPersonStatus);

        /// 更新所有的状态信息
        updateAllDataSize(m_mapStatusModel.count());
    }

    return(pPersonStatus);
}

/// 将演习状态压栈
void CGlobalData::PushBackStatus()
{
    m_mapFenZu.clear();

    QVector<quint16> vAllID;
    for(auto itor = m_mapTypeInfo.begin();
        itor != m_mapTypeInfo.end();++itor)
    {
        for(int nSize = itor.value()->count()-1; nSize > -1; --nSize)
        {
            vAllID.push_back(itor.value()->at(nSize)->getId());
            itor.value()->remove(nSize);
        }

        m_mapFenZu[itor.key()]=vAllID;
        vAllID.clear();
    }
}

/// 将演习状态出栈
void CGlobalData::PopUpStatus()
{
    m_pCtrMapPerson->ClearMap();

    /// 清空当前状态栏
    for(auto itor = m_mapTypeInfo.begin();
        itor != m_mapTypeInfo.end();++itor)
    {
        for(int nSize = itor.value()->count()-1; nSize > -1; --nSize)
        {
            itor.value()->remove(nSize);
        }
    }

    /// 恢复状态栏
    for(auto itor = m_mapFenZu.begin();
        itor != m_mapFenZu.end();++itor)
    {
        auto itorFindOne = m_mapTypeInfo.find(itor.key());
        if(itorFindOne != m_mapTypeInfo.end())
        {
            for(auto one : itor.value())
            {
                auto findOnePerson = m_mapStatusModel.find(one);
                if(findOnePerson != m_mapStatusModel.end())
                {
                    m_pCtrMapPerson->UpdateGroup(findOnePerson.value()->getId(),itorFindOne.key());
                    itorFindOne.value()->append(findOnePerson.value());
                }
            }
        }
    }

    /// 清空人员信息
    CDataManager::GetInstance()->ResetPersonInfo();
}

/// 更新地图绘制的人员信息
void CGlobalData::UpdateMap(quint16 unID)
{
    auto pPerson = CDataManager::GetInstance()->GetOrCreatePersonInfo(unID);
    m_pCtrMapPerson->UpdatePos(unID,
                               pPerson->curtpos().dlon(),
                               pPerson->curtpos().dlat());

    m_pCtrMapPerson->UpdateStatus(unID,pPerson->hearth());
}

/// 更新活着的人数
void CGlobalData::UpdateLiveNum()
{
    static int nLiveNum=0;

    nLiveNum = 0;
    for(auto findOne=m_mapTypeInfo.begin(); findOne != m_mapTypeInfo.end();++findOne)
    {
        nLiveNum += findOne.value()->liveNum();
    }

    if(m_nLiveNum != nLiveNum)
    {
        m_nLiveNum = nLiveNum;
        emit(liveNumChanged(m_nLiveNum));
    }
}

void CGlobalData::ChongdanAll(quint16 nID, const QStringList &allInfo)
{
    QStringList tempInfo=allInfo;
    QList<int>  nTempInfo;
    auto pPerson = CDataManager::GetInstance()->GetOrCreatePersonInfo(nID);
    /// 判断剩余子弹数
    const ConnectStatus& conStatus = pPerson->curtstatus();
    int nBaty = pPerson->curtstatus().weapons_size();

    bool bLink1(false),bLink(false);
    int nNum(0);
    int temp=0;
    for(int nIndex=0; nIndex < nBaty; ++nIndex)
    {
        switch(conStatus.weapons(nIndex).weapontype())
        {
        case RIFLE:
            bLink1 = UNLINK != conStatus.weapons(nIndex).contype();
            if(bLink1)
                nNum = conStatus.weapons(nIndex).bulletnum();
            break;
        case PISTOL:
            bLink = UNLINK != conStatus.weapons(nIndex).contype();
            if(bLink)
                nNum += conStatus.weapons(nIndex).bulletnum();
            temp=allInfo.at(0).toInt();
            temp=temp+nNum;
            //            tempInfo.append(QString::number(temp));
            tempInfo.replace(0,QString::number(temp));
            qDebug()<<"步枪枪数："<<nNum<<temp<<allInfo;
            break;
        case GRENAD:
            bLink1 = UNLINK != conStatus.weapons(nIndex).contype();
            if(bLink1)
                nNum = conStatus.weapons(nIndex).bulletnum();
            break;
        case MORTAR:
            bLink = UNLINK != conStatus.weapons(nIndex).contype();
            if(bLink)
                nNum += conStatus.weapons(nIndex).bulletnum();
            temp=allInfo.at(2).toInt();
            temp=temp+nNum;
            tempInfo.replace(2,QString::number(temp));
            qDebug()<<"shou枪枪数："<<nNum<<temp;
            break;
        case SUBMACHINE:
            bLink = UNLINK != conStatus.weapons(nIndex).contype();
            if(bLink)
                nNum += conStatus.weapons(nIndex).bulletnum();
            temp=allInfo.at(7).toInt();
            temp=temp+nNum;
            tempInfo.replace(7,QString::number(temp));
            qDebug()<<"狙击枪枪数："<<nNum<<temp;
            break;
        }
    }
    CDealDataManager::GetInstance()->PersonalChongDan(nID,tempInfo);

    for(int i=0;i<allInfo.size();i++)
    {
        nTempInfo.append(allInfo.at(i).toInt());
    }
    CDealDataManager::GetInstance()->SetBulletSum(nID,nTempInfo);
}
