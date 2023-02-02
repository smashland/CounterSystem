#include "../ConfigInfo.h"
#include "../ParseData/DealDataManager.h"
#include "DataManager.h"
#include "PersonAllInfo.h"
#include "PersonInfo.pb.h"

static QString sHurt = QString::fromUtf8("被%1击中%2");
static QString sHurtDeath=QString::fromUtf8("被%1炸死");
static QString sHit = QString::fromUtf8("命中%1%2");
static QString sHitDeath=QString::fromUtf8("炸死%1");

CPersonAllInfo::CPersonAllInfo(QObject *parent) : QObject(parent)
{

}

///通过查找人员信息更新显示
void CPersonAllInfo::Update(quint16 unID)
{
    auto pPerson = CDataManager::GetInstance()->GetOrCreatePersonInfo(unID);
    UpdateBaseInfo(pPerson);
}

void CPersonAllInfo::Update()
{
    Update(m_nID);
}

/// 更新名称和分组
void CPersonAllInfo::UpdateTypeAndName(const QString &sName, const QString &sType)
{
    if(m_sName != sName)
    {
        m_sName = sName;
        emit(nameChanged(m_sName));
    }

    if(m_sType != sType)
    {
        m_sType = sType;
        emit(typeChanged(m_sType));
    }
}

/// 更新基本信息
void CPersonAllInfo::UpdateBaseInfo(PersonInfo *pPersonInfo)
{
    QStringList tmpList;
    if(m_nID != pPersonInfo->id())
    {
        if(m_bHead){m_bHead=false;emit(headChanged(m_bHead));}
        if(m_bBreast){m_bBreast=false;emit(breastChanged(m_bBreast));}
        if(m_bAbdomen){m_bAbdomen=false;emit(abdomenChanged(m_bAbdomen));}
        if(m_bCenter){m_bCenter=false;emit(centerChanged(m_bCenter));}
        if(m_bLeftArm){m_bLeftArm=false;emit(leftArmChanged(m_bLeftArm));}
        if(m_bLeftLeg){m_bLeftLeg=false;emit(leftLegChanged(m_bLeftLeg));}
        if(m_bRightLeg){m_bRightLeg=false;emit(rightLegChanged(m_bRightLeg));}
        if(m_bRightArm){m_bRightArm=false;emit(rightArmChanged(m_bRightArm));}

        m_listHitInfo.clear();
        emit(hitChanged(m_listHitInfo));

        m_nID = pPersonInfo->id();
        emit(idChanged(m_nID));
    }

    int nHurtSize = pPersonInfo->hurtinfo_size();
    if(m_nHurtCount!=nHurtSize)
    {
        m_nHurtCount=nHurtSize;
        emit(hurtCountChanged(m_nHurtCount));
    }
    if(0==nHurtSize)
    {
        if(m_bHead){m_bHead=false;emit(headChanged(m_bHead));}
        if(m_bBreast){m_bBreast=false;emit(breastChanged(m_bBreast));}
        if(m_bAbdomen){m_bAbdomen=false;emit(abdomenChanged(m_bAbdomen));}
        if(m_bCenter){m_bCenter=false;emit(centerChanged(m_bCenter));}
        if(m_bLeftArm){m_bLeftArm=false;emit(leftArmChanged(m_bLeftArm));}
        if(m_bLeftLeg){m_bLeftLeg=false;emit(leftLegChanged(m_bLeftLeg));}
        if(m_bRightLeg){m_bRightLeg=false;emit(rightLegChanged(m_bRightLeg));}
        if(m_bRightArm){m_bRightArm=false;emit(rightArmChanged(m_bRightArm));}
    }
    else
    {
        for(int nIndex=0; nIndex<nHurtSize; ++nIndex)
        {
            /// 增加被命中信息
            switch(pPersonInfo->hurtinfo(nIndex).type())
            {
            case GRENAD:
            case MORTAR:
            case SNIPER:
                tmpList += sHurtDeath.arg(pPersonInfo->hurtinfo(nIndex).id());
                break;
            default:
                tmpList += sHurt.arg(pPersonInfo->hurtinfo(nIndex).id())
                        .arg(CConfigInfo::GetInstance()->GetBodyName(pPersonInfo->hurtinfo(nIndex).hurtpart()));
                break;
            }

            switch(pPersonInfo->hurtinfo(nIndex).hurtpart())
            {
            case HEAD:if(!m_bHead){m_bHead=true;emit(headChanged(m_bHead));}
                break;
            case CHEST:if(!m_bBreast){m_bBreast=true;emit(breastChanged(m_bBreast));}
                break;
            case ABDOMEN:if(!m_bAbdomen){m_bAbdomen=true;emit(abdomenChanged(m_bAbdomen));}
                break;
            case BACK:if(!m_bCenter){m_bCenter=true;emit(centerChanged(m_bCenter));}
                break;
            case LEFT_ARM:if(!m_bLeftArm){m_bLeftArm=true;emit(leftArmChanged(m_bLeftArm));}
                break;
            case LEFT_LEG:if(!m_bLeftLeg){m_bLeftLeg=true;emit(leftLegChanged(m_bLeftLeg));}
                break;
            case RIGHT_LEG:if(!m_bRightLeg){m_bRightLeg=true;emit(rightLegChanged(m_bRightLeg));}
                break;
            case RIGHT_ARM:if(!m_bRightArm){m_bRightArm=true;emit(rightArmChanged(m_bRightArm));}
                break;
            }
        }
    }

    nHurtSize = pPersonInfo->hitinfo_size();
    if(m_nHitCount!=nHurtSize)
    {
        m_nHitCount=nHurtSize;
        emit(hitCountChanged(m_nHitCount));
    }
    for(int nIndex=0; nIndex<nHurtSize; ++nIndex)
    {
        /// 增加命中信息
        switch(pPersonInfo->hitinfo(nIndex).type())
        {
        case GRENAD:
        case MORTAR:
        case SNIPER:
            tmpList += sHitDeath.arg(pPersonInfo->hitinfo(nIndex).id());
            break;
        default:
            tmpList += sHit.arg(pPersonInfo->hitinfo(nIndex).id())
                    .arg(CConfigInfo::GetInstance()->GetBodyName(pPersonInfo->hitinfo(nIndex).hurtpart()));
            break;
        }

    }

    if(0 != pPersonInfo->relive())
    {
        tmpList += QString::fromUtf8("复活次数 %1").arg(pPersonInfo->relive());
    }

    if(0 != pPersonInfo->setdeath())
    {
        tmpList += QString::fromUtf8("判死次数 %1").arg(pPersonInfo->setdeath());
    }

    /// 判断剩余子弹数
    const ConnectStatus& conStatus = pPersonInfo->curtstatus();
    int nBaty = pPersonInfo->curtstatus().weapons_size();

    bool bLink1(false),bLink(false);
    int nNum(0);
    for(int nIndex=0; nIndex < nBaty; ++nIndex)
    {
        switch(conStatus.weapons(nIndex).weapontype())
        {
        case RIFLE:
            bLink1 = UNLINK != conStatus.weapons(nIndex).contype();
            if(bLink1) nNum = conStatus.weapons(nIndex).bulletnum();
            break;
        case PISTOL:
            bLink = UNLINK != conStatus.weapons(nIndex).contype();
            if(bLink) nNum += conStatus.weapons(nIndex).bulletnum();
            if(m_bRifle != (bLink || bLink1))
            {
                m_bRifle = (bLink || bLink1);
                emit(rifleChanged(m_bRifle));
            }

            if(m_nRifle != nNum)
            {
                m_nRifle = nNum;
                emit(rifleNumChanged(m_nRifle));
                qDebug()<<"步枪gengxin1："<<nNum;
            }
            break;
        case GRENAD:
            bLink1 = UNLINK != conStatus.weapons(nIndex).contype();
            if(bLink1) nNum = conStatus.weapons(nIndex).bulletnum();
            else       nNum = 0;
            break;
        case MORTAR:
            bLink = UNLINK != conStatus.weapons(nIndex).contype();
            if(bLink) nNum += conStatus.weapons(nIndex).bulletnum();
            if(m_bPistol != (bLink || bLink1))
            {
                m_bPistol = (bLink || bLink1);
                emit(pistolChanged(m_bPistol));
            }

            if(m_nPistol != nNum)
            {
                m_nPistol = nNum;
                emit(pistolNumChanged(m_nPistol));
                qDebug()<<"手枪gengxin1："<<nNum;
            }
            break;
        }
    }
    //    countDanFlag=false;

    /// 如果命中信息更新则返回
    if(m_listHitInfo != tmpList)
    {
        m_listHitInfo = tmpList;
        emit(hitChanged(m_listHitInfo));
    }

    emit(hitChanged(m_listHitInfo));

    if(m_bSatand != pPersonInfo->curtstatus().bstand())
    {
        m_bSatand = pPersonInfo->curtstatus().bstand();
        emit(standChanged(m_bSatand));
    }

    auto &pos = pPersonInfo->curtpos();
    if(fabs(m_dLat-pos.dlat())>DBL_EPSILON)
    {
        m_dLat = pos.dlat();
        emit(latChanged(m_dLat));
    }

    if(fabs(m_dLon - pos.dlon())>DBL_EPSILON)
    {
        m_dLon = pos.dlon();
        emit(lonChanged(m_dLon));
    }

    auto repos= pPersonInfo->relive();
    if(0!=repos)
    {
        m_uRelive = repos;
        emit(reliveChanged(m_uRelive));
    }
    QStringList listBulletSum =CDealDataManager::GetInstance()->GetBulletSum(pPersonInfo->id());
    for(int i = 0; i< listBulletSum.size();++i)
    {
        if(listBulletSum.at(i)==NULL)
        {
            listBulletSum[i]="0";
        }
    }
    if(m_nRifleSum!=listBulletSum.at(0).toInt())
    {
        m_nRifleSum=listBulletSum.at(0).toInt();
        emit(rifleSumChanged(m_nRifleSum));
    }
    if(m_nPistolSum!=listBulletSum.at(2).toInt())
    {
        m_nPistolSum=listBulletSum.at(2).toInt();
        emit(pistolSumChanged(m_nPistolSum));
    }

}
