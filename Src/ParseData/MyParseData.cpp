#include <QtEndian>
#include "../API-CRCheck.h"
#include "MyParseData.h"
#include "MyParse/MyParsetype.h"
#include "MyParse/MyEventInfo.h"
#include "MyParse/MySetQuipment.h"
#include "MyParse/MyQueryEquipment.h"

#include "../DataManager/DataManager.h"
#include "../DataManager/TypeDefine.pb.h"
#include "../DataManager/PersonInfo.pb.h"
#include "../ConfigInfo.h"
#include "DealDataManager.h"

Q_DECLARE_FLAGS(Guntypes,GunType)
static const uchar CS_BEGIN(0xAA);
static const uchar CS_CONNECTION(0x1E);

extern bool replayFlags;

CMyParseData::CMyParseData()
{
    m_pData = m_pBuffer + 10;
    m_pEvent = new CMyEventInfo;
    m_pSet = new CMySetQuipment;
    m_pQuery = new CMyQueryEquipment;
}

CMyParseData::~CMyParseData()
{
    delete m_pEvent;
    delete m_pSet;
    delete m_pQuery;
}

/// 解析数据
bool CMyParseData::ParseData(const QByteArray &rArray)
{
    /// 临时变量
    static int nCount,nIndex;
    static uchar ucTemp;

    /// 开始解析数据
    for(nIndex=0,nCount = rArray.size();
        nIndex<nCount;
        ++nIndex,++m_nNowLength)
    {
        ucTemp = static_cast<uchar>(rArray[nIndex]);

        /// 如果没有开始，则查找开始位置
        if(!m_bBegin)
        {
            if(ucTemp == CS_BEGIN)
            {
                InitState();
                m_pBuffer[0] = ucTemp;
            }
        }/// end if
        else
        {
            switch(m_nNowLength)
            {
            case 0:/// 命令类型
                m_ucType = ucTemp;
                m_pBuffer[1] = ucTemp;
                break;
            case 1:/// 目标地址的高位(接收端暂时作为要发送的地址)
                m_pBuffer[2] = ucTemp;
                m_stAddr.cHigh = ucTemp;
                break;
            case 2:/// 目标地址的低位(接收端暂时作为要发送的地址)
                m_pBuffer[3] = ucTemp;
                m_stAddr.cLow = ucTemp;
                m_unID = m_stAddr;
                break;
            case 3:/// 传输方式(接收端暂时不需要)
                m_pBuffer[4] = ucTemp;
                break;
            case 4:/// 未使用数据
                m_pBuffer[5] = ucTemp;
                break;
            case 5:/// 获取数据长度
                m_pBuffer[6] = ucTemp;
                m_nDataLength = ucTemp;
                break;
            case 6:/// 获取校验值
                m_pBuffer[7] = ucTemp;
                break;
            case 7:/// 获取校验值
                m_pBuffer[8] = ucTemp;
                m_usCRC16 = qFromBigEndian<quint16>(m_pBuffer+7);
                m_pBuffer[7] = m_pBuffer[8] = 0;
                break;
            default:
                m_pBuffer[m_nNowLength+1] = ucTemp;
                ++m_nDataGet;
                break;
            }

            /// 如果数据和接收到的数据相等，需要进行校验
            if(m_nDataGet == m_nDataLength)
            {
                /// 获取校验值
                quint16 unCRC = CRC16RTU(m_pBuffer,m_nNowLength+2);


                /// 如果校验通过
                if(m_usCRC16 == unCRC && !replayFlags)
                {
                    m_pPerson = CDataManager::GetInstance()->GetOrCreatePersonInfo(m_unID);
                    ParseData();
                    CDataManager::GetInstance()->Update(m_unID);
                }

                /// 不管结果怎样 重新接收数据
                m_bBegin = false;
            }
        }
    }

    return(true);
}

/// 更新时间
void CMyParseData::UpdateSeconds(const quint16 &nSeconds)
{
    m_pSet->UpdateSeconds(nSeconds);
    CParseData::UpdateSeconds(nSeconds);
}

/// 解析数据
void CMyParseData::ParseData()
{
    static uchar* pTempBuffer = m_pBuffer + 9;
    if(CS_CONNECTION == m_ucType)
    {
        /// 获取命令类型
        m_ucType = *pTempBuffer;
        --m_nDataGet;

        /// 根据事件类型进行处理
        switch (m_ucType)
        {
        case QUERY:
            m_pQuery->SetPerson(m_pPerson);
            m_pQuery->Update(m_pData,m_nDataGet);
            break;
        case SET_2:
            m_pSet->SetPerson(m_pPerson);
            m_pSet->Update(m_pData,m_nDataGet);
            break;
        case EVENT:
        {
            m_pEvent->SetPerson(m_pPerson);
            m_pEvent->Update(m_pData,m_nDataGet);

            /// 只有演习开始才校验仿真时间
            if(CConfigInfo::GetInstance()->GetStart())
            {
                static int nTimes;
                nTimes = m_pPerson->curtpos().ntime();

                nTimes -= m_unSeconds;
                if(nTimes < 0)
                {
                    nTimes *= -1;
                }

                /// 如果秒数大于同步时间则下发同步时间
                if(nTimes > CConfigInfo::GetInstance()->GetSynTimes())
                {
                    CDealDataManager::GetInstance()->PersonalSimTime(m_pPerson->id(),m_unSeconds);
                }
            }
        }
            break;
        default:
            break;
        }
    }
}

/// 清空事件状态
void CMyParseData::Clear()
{
    m_pEvent->ClearEventStatus();
}

/// 开始
void CMyParseData::SetStart(quint16 unID)
{
    m_vaInfo.setValue(m_unSeconds);
    m_pSet->SendCommand(unID,DRILL_START,m_vaInfo);
}

/// 演习开始，发送五遍
void CMyParseData::AllStart()
{
    m_vaInfo.setValue(0);
    for(auto i=0;i<5;++i)
    {
        m_pSet->SendCommand(g_unBroadCost,DRILL_START,m_vaInfo);
    }

    /// 调用父类的方法，处理消息
    CParseData::AllStart();
}

/// 演习结束
void CMyParseData::SetStop(quint16 unID)
{
    m_pSet->SendCommand(unID,DRILL_END,m_vaInfo);
}

void CMyParseData::AllStop()
{
    for(auto i=0;i<5;++i)
    {
        SetStop(g_unBroadCost);
    }
}

/// 闭锁
void CMyParseData::AllBiSuo()
{
    PersonalBiSuo(g_unBroadCost);
}

/// 闭锁指定类型的枪
void CMyParseData::AllBiSuo(const QVariant &gunInfo)
{
    PersonalBiSuo(g_unBroadCost,gunInfo);
}

void CMyParseData::PersonalBiSuo(quint16 unID)
{
    m_vaInfo.setValue(0xFF);
    m_pSet->SendCommand(unID,LOCK_GUN,m_vaInfo);
}

void CMyParseData::PersonalBiSuo(quint16 unID, const QVariant &gunInfo)
{
    Guntypes type;
    auto list = gunInfo.toList();
    for(auto one : list)
    {
        auto intAuto = one.toInt();
        if(GunType_IsValid(intAuto))
        {
            type.setFlag(static_cast<GunType>(intAuto));
        }
    }
    m_vaInfo.setValue(type.operator int());
    m_pSet->SendCommand(unID,LOCK_GUN,m_vaInfo);
}

/// 解锁所有的武器
void CMyParseData::AllJieSuo()
{
    PersonalJieSuo(g_unBroadCost);
}

void CMyParseData::AllJieSuo(const QVariant &gunInfo)
{
    PersonalJieSuo(g_unBroadCost,gunInfo);
}

void CMyParseData::PersonalJieSuo(quint16 unID)
{
    m_vaInfo.setValue(0);
    m_pSet->SendCommand(unID,LOCK_GUN,m_vaInfo);
}

void CMyParseData::PersonalJieSuo(quint16 unID, const QVariant &gunInfo)
{
    Guntypes type(0xff);
    auto list = gunInfo.toList();
    for(auto one : list)
    {
        auto intAuto = one.toInt();
        if(GunType_IsValid(intAuto))
        {
            type.setFlag(static_cast<GunType>(intAuto),false);
        }
    }
    m_vaInfo.setValue(type.operator int());
    m_pSet->SendCommand(unID,LOCK_GUN,m_vaInfo);
}

/// 命中提示
void CMyParseData::HitNotice(quint16 unID, const QVariant &hitInfo)
{
    m_vaInfo.setValue(hitInfo);
    m_pSet->SendCommand(unID,HIT_NOTICE,m_vaInfo);
}

/// 解除旁白
void CMyParseData::AllPangBai()
{
    m_pSet->SendCommand(g_unBroadCost,REALSE,m_vaInfo);
}

/// 判死
void CMyParseData::PersonalPanSi(quint16 unID)
{
    m_pSet->SendCommand(unID,SET_DEATH,m_vaInfo);
}

/// 复活
void CMyParseData::PersonalFuHuo(quint16 unID)
{
    m_pSet->SendCommand(unID,SET_REVIVE,m_vaInfo);
}

/// 充弹
void CMyParseData::AllChongDan(const QVariant &rInfo)
{
    m_pSet->SendCommand(g_unBroadCost,ADD_BULLET,rInfo);
}

void CMyParseData::PersonalChongDan(quint16 unID, const QVariant &rInfo)
{
    m_pSet->SendCommand(unID,ADD_BULLET,rInfo);
}

/// 配枪
void CMyParseData::AllPeiQiang(const QVariant &rInfo)
{
    m_pSet->SendCommand(g_unBroadCost,ADD_GUN,rInfo);
}

/// 损伤比例值
void CMyParseData::Damage(const QVariant &rInfo)
{
    m_pSet->SendCommand(g_unBroadCost,HURT_VALUE,rInfo);
}

/// 查询所有的状态
void CMyParseData::QueryAll()
{
    m_pQuery->QueryAll();
}

void CMyParseData::PersonalPeiQiang(quint16 unID, const QVariant &rInfo)
{
    m_pSet->SendCommand(unID,ADD_GUN,rInfo);
}

/// 同步时间
void CMyParseData::AllSycTime(quint16 unTime)
{
    PersonalSycTime(g_unBroadCost,unTime);
}

void CMyParseData::PersonalSycTime(quint16 unID, quint16 unTime)
{
    m_vaInfo.setValue(unTime);
    m_pSet->SendCommand(unID,HEART_TIME,m_vaInfo);
}

/// 仿真时间
void CMyParseData::AllSetSimTime(quint16 unTimes)
{
    PersonSimTime(g_unBroadCost,unTimes);
}

void CMyParseData::PersonSimTime(quint16 unID, quint16 unSimTime)
{
    m_vaInfo.setValue(unSimTime);
    m_pSet->SendCommand(unID,GIVE_TIME,m_vaInfo);
}

/// 校准电压
void CMyParseData::CalibrationCharge(quint16 unID)
{
    m_vaInfo.setValue(84);
    m_pSet->SendCommand(unID,CALIBRAION,m_vaInfo);
}

/// 开启第三者模式
void CMyParseData::Open3rd()
{
    m_pSet->SendCommand(g_unBroadCost,START_3RD,m_vaInfo);
}

void CMyParseData::Close3rd()
{
    m_pSet->SendCommand(g_unBroadCost,STOP_3RD,m_vaInfo);
}
