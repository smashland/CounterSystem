#include <QtEndian>
#include "../../ConfigInfo.h"
#include "MyParsetype.h"
#include "MyEventInfo.h"
#include "../../Connection/ConnectionManager.h"
#include "../../DataManager/PersonInfo.pb.h"
#include "../../DataManager/DataManager.h"
#include "../DealDataManager.h"
#include "../../Notice/NoticeManager.h"
#include <GisMath/GisMath.h>
#include <VersionMathCommon.h>
Q_DECLARE_FLAGS(Guntypes,GunType)

CMyEventInfo::CMyEventInfo():m_pPerson(nullptr)
{
}

/// 设置地址
void CMyEventInfo::SetPerson(PersonInfo* pPerson)
{
    /// 获取人员信息
    m_pPerson = pPerson;
}

/// 解析数据
void CMyEventInfo::Update(const unsigned char *pData, int nLength)
{
    static quint8 s_ucStatus;
    static quint8 s_unIndex;

    s_unIndex = 0;

    while(nLength > 0)
    {
        switch(++s_unIndex)
        {
        case 1:   /// 获取状态信息
            s_ucStatus = pData[0];
            ++pData;
            --nLength;
            break;
        case 2:   /// 获取时间信息
            m_pPerson->mutable_curtpos()->set_ntime(qFromBigEndian<quint16>(pData));
            pData += 2;
            nLength -=2;
            break;
        case 3:   /// 获取位置信息
            m_dLon = qFromBigEndian<qint32>(pData)*CS_INT2DOUBLE;
            pData += 4;
            nLength -=4;
            break;
        case 4:
            m_dLat = qFromBigEndian<qint32>(pData)*CS_INT2DOUBLE;
            if(CanSetPos())
            {
                m_pPerson->mutable_curtstatus()->set_bgps(true);
                m_pPerson->mutable_curtpos()->set_dlon(m_dLon);
                m_pPerson->mutable_curtpos()->set_dlat(m_dLat);
            }
            pData += 4;
            nLength -=4;
            break;
        case 5: /// 头盔连接状态
            if(s_ucStatus & TouKui_Con)
            {
                m_pPerson->mutable_curtstatus()->set_btk(*pData);
                ++pData;
                --nLength;
            }
            break;
        case 6:/// GPS连接状态
            if(s_ucStatus & GPS_Connct)
            {
                if(0==*pData)
                {
                    m_pPerson->mutable_curtstatus()->set_bgps(false);
                }
                ++pData;
                --nLength;
            }
            break;
        case 7:/// 武器连接状态
            if(s_ucStatus & WEAPON_Con)
            {
                Guntypes types(*pData);

                g_nGunType = 1;


                for(int i=0;i<8;++i)
                {
                    if(types.testFlag(static_cast<GunType>(g_nGunType<<i)))
                    {
                        m_pPerson->mutable_curtstatus()->mutable_weapons(i)->set_contype(OK);
                    }
                    else
                    {
                        m_pPerson->mutable_curtstatus()->mutable_weapons(i)->set_contype(UNLINK);
                    }
                }

                ++pData;
                --nLength;
            }
            break;
        case 8:/// 电池电量
            if(s_ucStatus & Baty_Value)
            {
                m_pPerson->mutable_curtstatus()->set_fbatyvalue(static_cast<float>(*pData * CS_INT2FLOAT));
//                if(m_pPerson->mutable_curtstatus()->fbatyvalue() > 8.4f)
//                {
//                    CDealDataManager::GetInstance()->CalibrationCharge(m_pPerson->id());
//                }
                ++pData;
                --nLength;
            }
            break;
        case 9:/// 人员状态
            if(s_ucStatus & Person_Sta)
            {
                m_pPerson->mutable_curtstatus()->set_bstand(*pData);
                ++pData;
                --nLength;
            }
            break;
        case 10:/// 子弹数量变化
            if(s_ucStatus & Bullet_Val)
            {
                /// 获取枪的类型
                Guntypes types(*pData);

                ++pData;
                --nLength;

                if(CConfigInfo::GetInstance()->GetStart())
                {
                    g_nGunType = 1;
                    for(int i=0;i<8 && nLength > 1;++i)
                    {
                        if(types.testFlag(static_cast<GunType>(g_nGunType<<i)))
                        {
                            if(0 != m_pPerson->mutable_curtstatus()->mutable_weapons(i)->bulletnum() &&
                               qFromBigEndian<quint16>(pData) < m_pPerson->mutable_curtstatus()->mutable_weapons(i)->bulletnum())
                            {
                                CNoticeManager::GetInstance()->PlaySound(1);
                            }

                            m_pPerson->mutable_curtstatus()->mutable_weapons(i)->set_bulletnum(qFromBigEndian<quint16>(pData));
                            nLength -= 2;
                            pData += 2;
                        }
                    }
                }
            }
            break;
        case 11:/// 击中事件
            if(s_ucStatus & Hit_Happen)
            {
                /// 确保长度有效
                if(nLength > 4)
                {
                    CNoticeManager::GetInstance()->PlaySound(2);
                    quint16 nIndex=qFromBigEndian<quint16>(pData+2);
                    SendEventBack(m_pPerson->id(),nIndex);

                    /// 只有演习开始才保存，处理命中事件
                    if(CConfigInfo::GetInstance()->GetStart())
                    {
                        auto itor = m_mapEvent.find(m_pPerson->id());
                        if(itor == m_mapEvent.end() || itor.value()!=nIndex)
                        {
                            /// 更新事件ID
                            m_mapEvent[m_pPerson->id()]=nIndex;


                            auto hurtInfo = m_pPerson->add_hurtinfo();
                            g_nGunType = qFromBigEndian<quint16>(pData);
                            nIndex = g_nGunType%1000;
                            hurtInfo->set_id(nIndex);


                            /// 给射击的人计算成绩
                            auto pShotPerson = CDataManager::GetInstance()->GetOrCreatePersonInfo(nIndex);

                            auto hitInfo = pShotPerson->add_hitinfo();
                            hitInfo->set_id(m_pPerson->id());


                            nIndex = g_nGunType / 1000;
                            g_nGunType=1;
                            auto gunType = static_cast<GunType>(g_nGunType << (nIndex-1));


                            /// 设置枪的类型
                            hurtInfo->set_type(gunType);
                            hitInfo->set_type(gunType);

                            pData +=2;
                            pData +=2;

                            /// 设置击中部位
                            hurtInfo->set_hurtpart(static_cast<PERSON_PART>(*pData));
                            hitInfo->set_hurtpart(hurtInfo->hurtpart());

                            /// 更新人员健康状态
                            m_pPerson->set_hearth(m_pPerson->hearth() - CConfigInfo::GetInstance()->CalHitDamage(hurtInfo->hurtpart()));

                            if(4==nIndex || 3 == nIndex || 6 == nIndex)
                            {
                                QString type;
                                switch (nIndex)
                                {
                                case 4:
                                case 3:
                                    type = QString::fromUtf8("手雷");
                                    break;
                                case 6:
                                    type = QString::fromUtf8("爆炸物");
                                    break;
                                }
                                /// 增加命中状态
                                QString listInfo=QString::fromUtf8("%3 %1被%2的%4炸死").arg(m_pPerson->id())
                                        .arg(pShotPerson->id()).arg(QTime::currentTime().toString("hh:mm:ss"))
                                        .arg(type);

                                /// 发送消息
                                CNoticeManager::GetInstance()->SetNoticInfo(listInfo);
                            }
                            else
                            {
                                /// 增加命中状态
                                QString listInfo=QString::fromUtf8("%3 %1被%2的%4击中").arg(m_pPerson->id())
                                        .arg(pShotPerson->id()).arg(QTime::currentTime().toString("hh:mm:ss")).arg(gunType);
                                listInfo += CConfigInfo::GetInstance()->GetBodyName(hurtInfo->hurtpart());

                                /// 发送消息
                                CNoticeManager::GetInstance()->SetNoticInfo(listInfo);
                            }

                            /// 通知有命中消息过来
                            CDataManager::GetInstance()->UpdateManEvent(m_pPerson->id());
                            CDealDataManager::GetInstance()->HitNotice(pShotPerson->id(),m_pPerson->id());
                        }
                        nLength -= 5;
                    }
                }
            }
            break;
        default:
            ++pData;
            --nLength;
            break;
        }
    }                                                                   
}

/// 清除状态
void CMyEventInfo::ClearEventStatus()
{
    m_mapEvent.clear();
}

void CMyEventInfo::SendEventBack(quint16 unID, quint16 unEventID)
{
    static QByteArray tmpByteArray(reinterpret_cast<const char*>(CS_buffer),9);
    static char tmpCRC[2]="";
    static quint16 uCrc(0);

    tmpByteArray.resize(9);

    qToBigEndian<quint16>(unID,tmpCRC);
    tmpByteArray[2] = tmpCRC[0];
    tmpByteArray[3] = tmpCRC[1];

    tmpByteArray[6] = 3;
    tmpByteArray[7]=tmpByteArray[8]=0;
    tmpByteArray.append(0x04);

    /// 转成高字节
    qToBigEndian<quint16>(unEventID,tmpCRC);

    tmpByteArray.append(tmpCRC[0]);
    tmpByteArray.append(tmpCRC[1]);


    /// 发送事件回执
    uCrc = CRC16RTU(reinterpret_cast<const unsigned char*>(tmpByteArray.data()),tmpByteArray.size());
    qToBigEndian<quint16>(uCrc,tmpCRC);
    tmpByteArray[7] = tmpCRC[0];
    tmpByteArray[8] = tmpCRC[1];

    /// 发送数据
    CConnectionManager::GetInstance()->SendData(tmpByteArray);
}

bool CMyEventInfo::CanSetPos()
{
    /// 过滤掉没有位置信息的
    if(fabs(m_dLon)<1e-7 && fabs(m_dLat)<1e-7)
    {
        return(false);
    }

    /// 判断当前存放的数据数量
    if(m_nIndex < 10)
    {
        m_dAllLon[m_nIndex]=m_dLon;
        m_dAllLat[m_nIndex]=m_dLat;
        ++m_nIndex;
        return(true);
    }
    else
    {
        int nNear(0),nFar(0),nFindFar(-1);
        /// 判断是否跟
        for(int i=0; i<10;++i)
        {
            if(fabs(m_dAllLat[i]-m_dLat)<.5
            && fabs(m_dAllLon[i]-m_dLon)<.5)
            {
                ++nNear;
            }
            else
            {
                nFindFar = i;
                ++nFar;
            }
        }

        if(nNear > nFar)
        {
            if(-1 != nFindFar)
            {
                m_dAllLat[nFindFar] = m_dLat;
                m_dAllLon[nFindFar] = m_dLon;
            }
            return(true);
        }
    }
}
