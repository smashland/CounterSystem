#include "PersonStatus.h"
#include "../ConfigInfo.h"
#include "PersonInfo.pb.h"
#include "DataManager.h"

/// 将浮点数的电池电压转换成电池电量
int flot2int(float fBaty)
{
    if(fBaty > 8.4f)
    {
        return(100);
    }
    else if(fBaty > 8.12f)
    {
        return((fBaty - 8.12f)/0.28f * 10 + 90);
    }
    else if(fBaty > 7.96f)
    {
        return((fBaty - 7.96f)/0.16f * 10 + 80);
    }
    else if(fBaty > 7.84f)
    {
        return((fBaty - 7.84f)/0.12f * 10 + 70);
    }
    else if(fBaty > 7.74f)
    {
        return((fBaty - 7.74f)/0.1f * 10 + 60);
    }
    else if(fBaty > 7.64f)
    {
        return((fBaty - 7.64f)/0.1f * 10 + 50);
    }
    else if(fBaty > 7.58f)
    {
        return((fBaty - 7.58f)/0.06f * 10 + 40);
    }
    else if(fBaty > 7.54f)
    {
        return((fBaty - 7.54f)/0.04f * 10 + 30);
    }
    else if(fBaty > 7.48f)
    {
        return((fBaty - 7.48f)/0.06f * 10 + 20);
    }
    else if(fBaty > 7.36f)
    {
        return((fBaty - 7.36f)/0.12f * 10 + 10);
    }
    else if(fBaty > 6.9f)
    {
        return((fBaty - 6.9f)/0.46f * 5 + 5);
    }
    else if(fBaty > 6.f)
    {
        return((fBaty - 6.f)/0.9f * 5);
    }
    else
    {
        return(0);
    }
}

CPersonStatus::CPersonStatus(int nID, QObject *parent)
    :QObject(parent)
    ,m_nID(nID)
    ,m_bGPS(false)
    ,m_bTK(false)
    ,m_bOnLine(true)
    ,m_nBaty(100)
    ,m_nHealth(100)
    ,m_unTimes(0)
    ,m_bRenZhi(false)
{
}


CPersonStatus::CPersonStatus(const CPersonStatus &rOther)
{
    m_bGPS = rOther.m_bGPS;
    m_bTK = rOther.m_bTK;
    m_nID = rOther.m_nID;
    m_nBaty = rOther.m_nBaty;
    m_nHealth = rOther.m_nHealth;
}


/// 更新状态信息
void CPersonStatus::Update(quint16 uTimes)
{
    m_unTimes = uTimes;
    if(!m_bOnLine)
    {
        m_bOnLine = true;
        emit(onLineChanged(m_bOnLine));
    }

    auto pPersonInfo = CDataManager::GetInstance()->GetOrCreatePersonInfo(m_nID);

    UpdateStatus(pPersonInfo->curtstatus());

    /// 更新健康状态
    if(m_nHealth != pPersonInfo->hearth())
    {
        m_nHealth = pPersonInfo->hearth();
        emit(healthChanged(m_nHealth));
    }

}

/// 设置名称
void CPersonStatus::setName(const QString &sName)
{
    if(sName != m_sName)
    {
        m_sName = sName;
        emit(nameChanged(m_sName));
    }
}

/// 是否人质
//bool CPersonStatus::setRenzhi()
//{

//}


/// 更新人员在线状态
void CPersonStatus::updateTime(quint16 unTimes)
{

    if(unTimes > m_unTimes)
    {
        if(unTimes - m_unTimes > CConfigInfo::GetInstance()->GetOfflineTime())
        {
            if(m_bOnLine)
            {
                m_bOnLine = false;
                emit(onLineChanged(m_bOnLine));
            }
        }
    }
}

/// 设置类型
void CPersonStatus::setType(const QString &sType)
{
    if(sType != m_sType)
    {
        m_sType = sType;
        emit(typeChanged(m_sType));
    }
}

/// 更新状态信息
void CPersonStatus::UpdateStatus(const ConnectStatus &conStatus)
{
    static int nBaty;
    static bool bLink,bLink1;
    /// 判断各个连接状态
    if(m_bGPS != conStatus.bgps())
    {
        m_bGPS = conStatus.bgps();
        emit(gpsChanged(m_bGPS));
    }

    if(m_bTK != conStatus.btk())
    {
        m_bTK = conStatus.btk();
        emit(tkChanged(m_bTK));
    }

    nBaty = flot2int(conStatus.fbatyvalue());

    if(m_nBaty != nBaty)
    {
        m_nBaty = nBaty;
        emit(batyChanged(m_nBaty));
    }

    /// 更新武器连接状态
    nBaty = conStatus.weapons_size();

    for(int nIndex=0; nIndex < nBaty; ++nIndex)
    {
        switch(conStatus.weapons(nIndex).weapontype())
        {
        case RIFLE:
            bLink1 = UNLINK != conStatus.weapons(nIndex).contype();
            break;
        case PISTOL:
            bLink = UNLINK != conStatus.weapons(nIndex).contype();
            if(m_bRifle != (bLink || bLink1))
            {
                m_bRifle = (bLink || bLink1);
                emit(rifleChanged(m_bRifle));
            }
            break;
        case GRENAD:
            bLink1 = UNLINK != conStatus.weapons(nIndex).contype();
            break;
        case MORTAR:
            bLink = UNLINK != conStatus.weapons(nIndex).contype();
            if(m_bPistol != (bLink || bLink1))
            {
                m_bPistol = (bLink || bLink1);
                emit(pistolChanged(m_bPistol));
            }
            break;
        }
    }
}
