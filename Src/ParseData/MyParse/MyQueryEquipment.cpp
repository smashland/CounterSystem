#include <QtEndian>
#include "MyQueryEquipment.h"
#include "MyParsetype.h"
#include "../../DataManager/PersonInfo.pb.h"
#include "../../Connection/ConnectionManager.h"

Q_DECLARE_FLAGS(Guntypes,GunType)

CMyQueryEquipment::CMyQueryEquipment():m_pPerson(nullptr)
{
}

void CMyQueryEquipment::SetPerson(PersonInfo* pPerson)
{
    m_pPerson = pPerson;
}
#include<QDebug>
/// 解析数据
void CMyQueryEquipment::Update(const unsigned char *pData, int nLength)
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
        case 2: /// 头盔连接状态
            if(s_ucStatus & TouKui_Con)
            {
                m_pPerson->mutable_curtstatus()->set_btk(*pData);
                ++pData;
                --nLength;
            }
            break;
        case 3:/// GPS连接状态
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
        case 4:/// 武器连接状态
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
        case 5:/// 电池电量
            if(s_ucStatus & Baty_Value)
            {
                m_pPerson->mutable_curtstatus()->set_fbatyvalue(static_cast<float>(*pData * CS_INT2FLOAT));
                ++pData;
                --nLength;
            }
            break;
        case 6:/// 人员状态
            if(s_ucStatus & Person_Sta)
            {
                m_pPerson->mutable_curtstatus()->set_bstand(*pData);
                qDebug()<<"Person_Sta:"<<*pData;
                ++pData;
                --nLength;
            }
            break;
        case 7:/// 子弹数量变化
            if(s_ucStatus & Bullet_Val)
            {
                /// 获取枪的类型
                Guntypes types(*pData);

                ++pData;
                --nLength;

                g_nGunType = 1;
                for(int i=0;i<8 && nLength > 1;++i)
                {
                    if(types.testFlag(static_cast<GunType>(g_nGunType<<i)))
                    {
                        m_pPerson->mutable_curtstatus()->mutable_weapons(i)->set_contype(OK);
                        m_pPerson->mutable_curtstatus()->mutable_weapons(i)->set_bulletnum(qFromBigEndian<quint16>(pData));
                        nLength -= 2;
                        pData += 2;
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

/// 查询所有的状态
void CMyQueryEquipment::QueryAll()
{
    static int nHeadLenth=sizeof(CS_buffer);
    static QByteArray tmpByteArray(reinterpret_cast<const char*>(CS_buffer),nHeadLenth);
    static char tmpCRC[2]="";
    static quint16 uCrc(0);

    tmpByteArray.resize(9);

    tmpByteArray[6] = 2;
    tmpByteArray[7]=tmpByteArray[8]=0;
    tmpByteArray.append(0x01);
    tmpByteArray.append(0x1F);

    /// 计算校验值
    uCrc = CRC16RTU(reinterpret_cast<const uchar*>(tmpByteArray.data()),tmpByteArray.size());
    qToBigEndian<quint16>(uCrc,tmpCRC);
    tmpByteArray[7] = tmpCRC[0];
    tmpByteArray[8] = tmpCRC[1];

    CConnectionManager::GetInstance()->SendData(tmpByteArray);
}
