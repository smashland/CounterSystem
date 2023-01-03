#include <QDir>
#include <QCoreApplication>
#include "DataManager.h"
#include "IDataManagerObserver.h"

#include "../CommonTypeDefine.h"
#include "../Notice/NoticeManager.h"
#include "../ConfigInfo.h"
#include "PersonInfo.pb.h"
#include "../ErrorReport.h"
#include "../ParseData/DealDataManager.h"

/// 获取单例指针
CDataManager* CDataManager::GetInstance()
{
    static CDataManager tmpDataManger;
    return(&tmpDataManger);
}

/// 订阅消息
void CDataManager::SubObserver(IDataManagerObserver *pObserver)
{
    m_setObserver.insert(pObserver);
}

/// 取消订阅消息
void CDataManager::UnSubObserver(IDataManagerObserver *pObserver)
{
    m_setObserver.remove(pObserver);
}

CDataManager::CDataManager():
    m_unTimes(0),
    m_sDataPath(QCoreApplication::applicationDirPath()+"/Data")
{
    m_nBufferLength = 1024;
    m_pDataBuffer = new char[m_nBufferLength]();
}

/// 析构
CDataManager::~CDataManager()
{
    delete []m_pDataBuffer;
}

/// 初始化人员状态
void CDataManager::InitPerson(PersonInfo *pPerson)
{
    pPerson->set_hearth(100);
    pPerson->set_relive(0);
    pPerson->set_setdeath(0);
    pPerson->mutable_curtpos()->set_ntime(m_unTimes);
    pPerson->clear_hurtinfo();
    pPerson->clear_hitinfo();
    InitWeapon(pPerson);
}

/// 初始化武器状态
void CDataManager::InitWeapon(PersonInfo *pPerson)
{
    quint16 unGunType = 1;
    if(8 != pPerson->mutable_curtstatus()->weapons_size())
    {
        pPerson->mutable_curtstatus()->clear_weapons();

        for(int i=0;i<8;++i)
        {
            WeaponStatus* pWeaponStatus = pPerson->mutable_curtstatus()->add_weapons();
            pWeaponStatus->set_weapontype(static_cast<GunType>(unGunType<<i));
        }
    }
}

/// 清空记录
void CDataManager::ClearRecordInfo()
{
    for(auto one : m_vRecordPersonInfo)
    {
        for(auto pPerson : one)
        {
            pPerson->Clear();
            delete pPerson;
        }

        one.clear();
    }
    m_vRecordPersonInfo.clear();
}

///得到每个人的id
QList<int> CDataManager::AllPersonId()
{
    QList<int> int_list;
    for(QMap<quint16,PersonInfo*>::const_iterator it=m_allPersonInfo.constBegin();it!=m_allPersonInfo.constEnd();it++)
    {
        qDebug()<<it.key()<<m_allPersonInfo.size();
        int_list.append(it.key());
    }
    return int_list;
}

/// 发送命中信息
void CDataManager::UpdateManEvent(quint16 unID)
{
    for(auto tmpVar : m_setObserver)
    {
        tmpVar->UpdateEvent(unID);
    }
}

/// 获取或者创建一个人员信息
PersonInfo *CDataManager::GetOrCreatePersonInfo(quint16 uID)
{
    auto pPerson = FindPersonInfo(uID);
    if(nullptr == pPerson)
    {
        pPerson = PersonInfo::default_instance().New();
        InitPerson(pPerson);
        pPerson->set_id(uID);
        m_allPersonInfo.insert(uID,pPerson);

    }
    return(pPerson);
}

/// 查找是否已经存在人员信息
PersonInfo *CDataManager::FindPersonInfo(quint16 uID)
{
    auto itor = m_allPersonInfo.find(uID);
    if(m_allPersonInfo.end() == itor)
    {
        return(nullptr);
    }
    else
    {
        return(itor.value());
    }
}

/// 通知需要更新的人员ID
void CDataManager::Update(quint16 uID)
{
    for(auto tmpVar : m_setObserver)
    {
        tmpVar->UpdateID(uID);
    }
}

/// 读取所有的文件
void CDataManager::ReadFile(const std::string &sFileName)
{
    m_vRecordTimes.clear();
    ClearRecordInfo();

    std::ifstream in;
    in.open(sFileName,std::ios::binary|std::ios::in);
    if(in.is_open())
    {
        quint16 tmpTime;
        int     nSize;
        int     nBufferSize;

        std::vector<PersonInfo*> vTempPersonInfo;
        while(!in.eof())
        {
            in.read(reinterpret_cast<char*>(&tmpTime),sizeof(tmpTime));

            if(in.eof())
            {
                break;
            }

            in.read(reinterpret_cast<char*>(&nSize),sizeof(nSize));

            m_vRecordTimes.push_back(tmpTime);
            vTempPersonInfo.resize(nSize);

            for(int i=0; i<nSize;++i)
            {
                in.read(reinterpret_cast<char*>(&nBufferSize),sizeof(nBufferSize));
                in.read(m_pDataBuffer,nBufferSize);
                auto pPersoin = PersonInfo::default_instance().New();
                pPersoin->ParseFromArray(m_pDataBuffer,nBufferSize);
                vTempPersonInfo[i] = pPersoin;
            }

            m_vRecordPersonInfo.push_back(vTempPersonInfo);
        }
        in.close();
    }
}

/// 处理事件
void CDataManager::UpdateSeconds(const quint16 &unSeconds)
{
    /// 更新演习时间
    m_unTimes = unSeconds;

    /// 演习开始将数据保存
    if(CConfigInfo::GetInstance()->GetStart() && m_outFile.is_open())
    {
        static int nSize;
        nSize = m_allPersonInfo.size();
        m_outFile.write(reinterpret_cast<const char*>(&unSeconds),sizeof(unSeconds));
        m_outFile.write(reinterpret_cast<const char*>(&nSize),sizeof(nSize));

        for(auto one : m_allPersonInfo)
        {
            nSize = one->ByteSizeLong();
            m_outFile.write(reinterpret_cast<const char*>(&nSize),sizeof(nSize));
            one->SerializeToArray(m_pDataBuffer,nSize);
            m_outFile.write(m_pDataBuffer,nSize);
        }
    }

    /// 演习结束，关闭文件
    if(m_outFile.is_open() && !CConfigInfo::GetInstance()->GetStart())
    {
        m_outFile.close();
    }
}

/// 更新仿真时间
void CDataManager::UpdateSimulationTime(const quint16 & simTime)
{
    if(simTime < ((int)(m_vRecordPersonInfo.size()-1)))
    {
        auto replayInfo = m_vRecordPersonInfo[simTime];
        for(auto one:replayInfo)
        {
            auto findPerson = m_allPersonInfo.find(one->id());
            if(m_allPersonInfo.end() == findPerson)
            {
                m_allPersonInfo[one->id()] = one;
            }
            else
            {
                findPerson.value()->CopyFrom(*one);
            }
        }
    }
}

/// 移除数据
void CDataManager::RemoveData()
{
    if(m_outFile.is_open())
    {
        m_outFile.close();
    }
    QDir(m_sDataPath).remove(m_sCurrentFileName);
}

const QString &CDataManager::GetFileName(const QString &sDataString)
{
    m_sCurrentFileName = m_sDataPath + sDataString;
    m_outFile.open(m_sCurrentFileName.toStdString(),std::ios::binary|std::ios::out);
    return(m_sCurrentFileName);
}

/// 重置人员状态
void CDataManager::ResetPersonInfo()
{
    for(auto pPerson: m_allPersonInfo)
    {
        InitPerson(pPerson);
    }
}
