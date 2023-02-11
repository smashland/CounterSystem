#include <QtEndian>
#include <QVariant>
#include "MySetQuipment.h"
#include "../../Connection/ConnectionManager.h"
#include "../../DataManager/PersonInfo.pb.h"
#include "../../DataManager/DataManager.h"
#include "../../Notice/NoticeManager.h"
#include "../../ConfigInfo.h"

Q_DECLARE_FLAGS(Guntypes,GunType)

CMySetQuipment::CMySetQuipment()
{
}

/// 设置装备的地址
void CMySetQuipment::SetPerson(PersonInfo *pPerson)
{
    m_pCurrentPerson = pPerson;
}

/// 给设备设置命令
void CMySetQuipment::SendCommand(quint16 unID, SET_CMD typeCommand, const QVariant &allInfo)
{
    static int nHeadLenth=sizeof(CS_buffer);
    static QByteArray tmpByteArray(reinterpret_cast<const char*>(CS_buffer),nHeadLenth);
    static char tmpCRC[2]="";
    static quint16 uCrc(0);

    /// 将大于9的数据清掉
    tmpByteArray.resize(nHeadLenth);
    tmpByteArray[2]=static_cast<char>(unID/256);
    tmpByteArray[3]=static_cast<char>(unID%256);
    tmpByteArray[7]=tmpByteArray[8]=0;

    /// 是广播则
    if(g_unBroadCost == unID)
    {
        tmpByteArray.append(0x02);
    }
    else
    {
        tmpByteArray.append(0x03);
        CMD_INFO& rCmdInfo = m_mapSendInfo[unID];
        rCmdInfo.cmdType = typeCommand;
        rCmdInfo.info = allInfo;
    }

    tmpByteArray.append(static_cast<char>(typeCommand));

    switch (typeCommand)
    {
    case HEART_TIME:
    case LOCK_GUN:
        tmpByteArray.append(static_cast<char>(allInfo.toInt()));
        break;
    case DRILL_START:
    case GIVE_TIME:
    case ADD_GUN:
    case HIT_NOTICE:
        uCrc = static_cast<quint16>(allInfo.toInt());
        qToBigEndian<quint16>(uCrc,tmpCRC);
        tmpByteArray.append(tmpCRC[0]);
        tmpByteArray.append(tmpCRC[1]);
        break;
    case HURT_VALUE:
        tmpByteArray.append(allInfo.toByteArray());
        break;
    case CALIBRAION:
        tmpByteArray.append(static_cast<char>(allInfo.toInt()));
        break;
    case ADD_BULLET:
    {
        QList<QVariant> tmpList = allInfo.toList();
        int nSize = tmpList.size();
        qDebug()<<"ceshichangdu "<<nSize<<tmpList;
        Guntypes types;
        g_nGunType = 1;

        tmpByteArray.append(static_cast<char>(types.operator int()));
        for(int i=0;i<nSize;++i)
        {
            uCrc = static_cast<quint16>(tmpList.at(i).toUInt());
            if(0 != uCrc)
            {
                types.setFlag(static_cast<GunType>(g_nGunType<<i));

                qToBigEndian<quint16>(uCrc,tmpCRC);
                tmpByteArray.append(tmpCRC[0]);
                tmpByteArray.append(tmpCRC[1]);
            }
        }


        tmpByteArray[11] = static_cast<char>(types.operator int());
    }
        break;
    default:
        break;
    }

    tmpByteArray[6] = static_cast<char>(tmpByteArray.size() - nHeadLenth);

    /// 计算校验值
    uCrc = CRC16RTU(reinterpret_cast<const uchar*>(tmpByteArray.data()),tmpByteArray.size());
    qToBigEndian<quint16>(uCrc,tmpCRC);
    tmpByteArray[7] = tmpCRC[0];
    tmpByteArray[8] = tmpCRC[1];

    CConnectionManager::GetInstance()->SendData(tmpByteArray);
}

/// 设置状态
void CMySetQuipment::Update(const uchar *pData, int nLength)
{
    if(nLength < 1)
    {
        return;
    }

    /// 判断类型
    SET_CMD cmdType = static_cast<SET_CMD>(pData[0]);

    if(JUDGE_DEATH == cmdType)
    {
        if(0 == pData[1])
        {
            m_pCurrentPerson->set_hearth(0);
            m_pCurrentPerson->set_setdeath(m_pCurrentPerson->setdeath()+1);
            /// 发送消息
            CNoticeManager::GetInstance()->SetNoticInfo(QString::fromUtf8("%1被裁判枪判死").arg(m_pCurrentPerson->id()));
        }
        else if(1 == pData[1])
        {
            m_pCurrentPerson->set_hearth(100);
            m_pCurrentPerson->set_relive(m_pCurrentPerson->relive()+1);
            /// 发送消息
            CNoticeManager::GetInstance()->SetNoticInfo(QString::fromUtf8("%1被裁判枪复活").arg(m_pCurrentPerson->id()));
        }
    }
    else
    {
        ID2CMD::iterator itorMap = m_mapSendInfo.find(m_pCurrentPerson->id());
        if(m_mapSendInfo.end() != itorMap)
        {
            /// 如果发送了状态
            if(itorMap.value().cmdType == cmdType)
            {
                /// 处理信息
                DealInfo(itorMap.value().cmdType,itorMap.value().info);
                /// 移除相关信息
                m_mapSendInfo.erase(itorMap);
            }
        }
    }
}

/// 更新
void CMySetQuipment::UpdateSeconds(const quint16 &nSeconds)
{
    for(ID2CMD::iterator itor =m_mapSendInfo.begin();
        itor != m_mapSendInfo.end();)
    {
        if(0 == itor.value().nTime)
        {
            itor.value().nTime = nSeconds;
            ++itor;
        }
        else
        {
            /// 如果时间小于4秒则重复发送
            if(nSeconds - itor.value().nTime < 4)
            {
                SendCommand(itor.key(),itor.value().cmdType,itor.value().info);
                ++itor;
            }
            else
            {
                itor = m_mapSendInfo.erase(itor);
            }
        }
    }
}

/// 处理消息
void CMySetQuipment::DealInfo(SET_CMD typeCommand, const QVariant &allInfo)
{
    switch (typeCommand)
    {
    case SET_DEATH: /// 判死
        /// 演习开始之后 判死次数+1
        if(CConfigInfo::GetInstance()->GetStart())
        {
            m_pCurrentPerson->set_hearth(0);
            m_pCurrentPerson->set_setdeath(m_pCurrentPerson->setdeath()+1);
            CDataManager::GetInstance()->UpdateManEvent(m_pCurrentPerson->id());
        }
        break;
    case SET_REVIVE: /// 复活
        /// 演习开始之后 复活次数+1
        if(CConfigInfo::GetInstance()->GetStart())
        {
            m_pCurrentPerson->set_hearth(100);
            m_pCurrentPerson->set_relive(m_pCurrentPerson->relive()+1);
            CDataManager::GetInstance()->UpdateManEvent(m_pCurrentPerson->id());
        }
        break;
    case LOCK_GUN: /// 锁枪
    {
        Guntypes types(allInfo.toUInt());
        g_nGunType = 1;


        for(int i=0;i<8;++i)
        {
            /// 只有在线的武器才能更改武器闭锁状态
            if(UNLINK != m_pCurrentPerson->mutable_curtstatus()->mutable_weapons(i)->contype())
            {
                if(types.testFlag(static_cast<GunType>(g_nGunType<<i)))
                {
                    m_pCurrentPerson->mutable_curtstatus()->mutable_weapons(i)->set_contype(LOCK);
                }
                else
                {
                    m_pCurrentPerson->mutable_curtstatus()->mutable_weapons(i)->set_contype(OK);
                }
            }
        }
    }
        break;
    case ADD_GUN: /// 增加枪
        g_nGunType = allInfo.toUInt() / 1000;
        if(g_nGunType < 8)
        {
            m_pCurrentPerson->mutable_curtstatus()->mutable_weapons(g_nGunType)->set_contype(OK);
        }
        break;
    case ADD_BULLET: /// 充弹
    {       
        QList<QVariant> tmpList = allInfo.toList();
        if(8 == tmpList.size())
        {
            for(int i=0;i<8;++i)
            {
                g_nGunType = tmpList.at(i).toUInt();
                if(g_unBroadCost != g_nGunType)
                {
                    qDebug()<<"DealInfo-----------------------------------------"<<"充弹"<<i;
                    m_pCurrentPerson->mutable_curtstatus()->mutable_weapons(i)->set_bulletnum(g_nGunType);
                }
            }
        }
    }
        break;
    }
}
