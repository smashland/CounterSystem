#include "../Connection/ConnectionManager.h"
#include "DealDataManager.h"
#include "MyParseData.h"
#include "../ErrorReport.h"
#include "../ConfigInfo.h"

static QString S_RECIVE = QString::fromUtf8("接收到:");
CDealDataManager *CDealDataManager::GetInstance()
{
    static CDealDataManager s_DealDataManager;
    return(&s_DealDataManager);
}

/// 更新时间
void CDealDataManager::UpdateSeconds(const quint16 &nSeconds)
{
    m_pParse->UpdateSeconds(nSeconds);
}
#include <QDebug>
/// 处理数据
void CDealDataManager::UpdateTime(const QDateTime &)
{
    QByteArray rGetData = CConnectionManager::GetInstance()->GetData();
    while(!rGetData.isEmpty())
    {
        CErrorReport::GetInstance()->writeError(S_RECIVE+rGetData.toHex().toUpper());
        /// 解析数据
        m_pParse->ParseData(rGetData);
        rGetData = CConnectionManager::GetInstance()->GetData();
    }
}

/// 是否初始化
bool CDealDataManager::IsInit()
{
    return(nullptr != m_pParse);
}

/// 指定某人演习开始
void CDealDataManager::SetStart(quint16 unID)
{
    m_pParse->SetStart(unID);
}

/// 所有人演习开始
void CDealDataManager::AllStart()
{
    m_pParse->AllStart();
}

/// 演习结束
void CDealDataManager::SetStop(quint16 unID)
{
    m_pParse->SetStop(unID);
}

void CDealDataManager::AllStop()
{
    m_pParse->AllStop();
}

/// 闭锁
void CDealDataManager::AllBiSuo()
{
    m_pParse->AllBiSuo();
}

void CDealDataManager::AllBiSuo(const QVariant &gunInfo)
{
    m_pParse->AllBiSuo(gunInfo);
}

void CDealDataManager::PersonalBiSuo(quint16 unID)
{
    m_pParse->PersonalBiSuo(unID);
}

void CDealDataManager::PersonalBiSuo(quint16 unID, const QVariant &gunInfo)
{
    m_pParse->PersonalBiSuo(unID,gunInfo);
}

/// 解锁
void CDealDataManager::AllJieSuo()
{
    m_pParse->AllJieSuo();
}

void CDealDataManager::AllJieSuo(const QVariant &gunInfo)
{
    m_pParse->AllJieSuo(gunInfo);
}

void CDealDataManager::PersonalJieSuo(quint16 unID)
{
    m_pParse->PersonalJieSuo(unID);
}

void CDealDataManager::PersonalJieSuo(quint16 unID, const QVariant &gunInfo)
{
    m_pParse->PersonalJieSuo(unID,gunInfo);
}

/// 解除旁白
void CDealDataManager::PangBai()
{
    m_pParse->AllPangBai();
}

/// 判死
void CDealDataManager::PersonalPanSi(quint16 unID)
{
    m_pParse->PersonalPanSi(unID);
}

/// 复活
void CDealDataManager::PersonalFuHuo(quint16 unID)
{
    m_pParse->PersonalFuHuo(unID);
}

/// 命中提示
void CDealDataManager::HitNotice(quint16 unID, const QVariant &hitInfo)
{
    m_pParse->HitNotice(unID,hitInfo);
}

/// 充弹
void CDealDataManager::AllChongDan(const QVariant &gunInfo)
{
    m_pParse->AllChongDan(gunInfo);
}

void CDealDataManager::PersonalChongDan(quint16 unID, const QVariant &gunInfo)
{
    m_pParse->PersonalChongDan(unID,gunInfo);
}

void CDealDataManager::SetBulletSum(quint16 unID, const QStringList &bulletInfo)
{
//    m_mapId2BulletSum.insert(unID,bulletInfo);
}

QStringList CDealDataManager::GetBulletSum(quint16 unID)
{
//    if(m_mapId2BulletSum.contains(unID))
//    {
//        return m_mapId2BulletSum.value(unID);
//    }
//    else
    {
        QStringList listFaultBullets;
        QString strFaultBullets=QString::number(CConfigInfo::GetInstance()->GetDefaultBullets());
        for(int i=0;i<7;++i)
        {
            listFaultBullets.append(strFaultBullets);
        }
        m_mapId2BulletSum.insert(unID,listFaultBullets);
        return m_mapId2BulletSum.value(unID);
    }

}

void CDealDataManager::clearBulletSum()
{
    m_mapId2BulletSum.clear();
}

/// 配枪
void CDealDataManager::AllPeiQiang(const QVariant &gunInfo)
{
    m_pParse->AllPeiQiang(gunInfo);
}

void CDealDataManager::PersonalPeiQiang(quint16 unID, const QVariant &gunInfo)
{
    m_pParse->PersonalPeiQiang(unID,gunInfo);
}

/// 同步时间
void CDealDataManager::AllSycTime(quint16 unTimes)
{
    m_pParse->AllSycTime(unTimes);
}

void CDealDataManager::PersonalSycTime(quint16 unID, quint16 unTimes)
{
    m_pParse->PersonalSycTime(unID,unTimes);
}

/// 设置仿真时间
void CDealDataManager::AllSimTime(quint16 unTime)
{
    m_pParse->AllSycTime(unTime);
}

void CDealDataManager::PersonalSimTime(quint16 unID, quint16 unTimes)
{
    m_pParse->PersonSimTime(unID,unTimes);
}

/// 开启第三者模式
void CDealDataManager::Open3rd()
{
    m_pParse->Open3rd();
}

void CDealDataManager::Close3rd()
{
    m_pParse->Close3rd();
}

void CDealDataManager::Damege(const QVariant &damegeInfo)
{
    m_pParse->Damage(damegeInfo);
}

///校准电量
void CDealDataManager::CalibrationCharge(quint16 unID)
{
    m_pParse->CalibrationCharge(unID);
}

void CDealDataManager::Clear()
{
    CConnectionManager::GetInstance()->ClearData();
    m_pParse->Clear();
}

void CDealDataManager::QueryAll()
{
    m_pParse->QueryAll();
}

/// 处理数据管理类
CDealDataManager::CDealDataManager()
    : m_pParse(new CMyParseData)
{
}

/// 析构函数
CDealDataManager::~CDealDataManager()
{
    delete m_pParse;
    m_pParse = nullptr;
}
