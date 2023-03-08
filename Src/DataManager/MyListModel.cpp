#include "PersonStatus.h"
#include "MyListModel.h"
#include "GroupStatus.h"
#include "DataManager.h"
#include "PersonInfo.pb.h"
#include "../ConfigInfo.h"
#include "../ParseData/DealDataManager.h"
enum
{
    ObjectModelRole = Qt::UserRole + 1
};


CMyListModel::CMyListModel(QObject *parent):
    QAbstractListModel(parent)
{
    m_mapRolesNames[ObjectModelRole] = "objectModelRole";
    m_pGroupStatus = new CGroupStatus(this);
    Clear();
}

CMyListModel::CMyListModel(const CMyListModel &other)
{
    m_allData = other.m_allData;
}

CMyListModel::~CMyListModel()
{
    delete m_pGroupStatus;
}

int CMyListModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_allData.count();
}

QVariant CMyListModel::data(const QModelIndex &index, int role) const
{
    Q_UNUSED(role)

    int row = index.row();
    if(row < 0 || row >= m_allData.count())
    {
        return QVariant();
    }

    QObject *data = m_allData[row];

    return QVariant::fromValue(data);
}

QHash<int, QByteArray> CMyListModel::roleNames() const
{
    return(m_mapRolesNames);
}

int CMyListModel::count() const
{
    return(m_allData.count());
}

CPersonStatus *CMyListModel::at(int nIndex)
{
    if(nIndex<0 || nIndex >= m_allData.count())
    {
        return(nullptr);
    }
    else
    {
        return(m_allData[nIndex]);
    }
}

/// 只有演习开始之前才允许进行操作
/// 此处进行操作不需要更新伤亡比率
void CMyListModel::remove(int nIndex)
{
    if(nIndex<0 || nIndex >= m_allData.count())
    {
        return;
    }

    beginRemoveRows(QModelIndex(), nIndex, nIndex);

    m_allData.removeAt(nIndex);

    /// 总人数更改,通知修改
    {
        --m_nCount;
        emit(countChanged(m_nCount));
    }

    endRemoveRows();
}

/// 只有演习开始之前才允许进行操作
/// 此处进行操作不需要更新伤亡比率
void CMyListModel::append(CPersonStatus *pPerson)
{
    int nInsertPos=0;
    for(int index=m_allData.size()-1;index>-1;--index)
    {
        if(m_allData.at(index)->getId() < pPerson->getId())
        {
            nInsertPos = index+1;
            break;
        }
    }

    beginInsertRows(QModelIndex(), nInsertPos, nInsertPos);

    /// 更新指定位置的
    m_allData.insert(nInsertPos,pPerson);

    m_allPerson.insert(pPerson->getId());
    m_setLive.insert(pPerson->getId());

    {
        ++m_nCount;
        emit(countChanged(m_nCount));
    }

    endInsertRows();
}

void CMyListModel::deathDefault()
{
    m_nDeathNum=0;
    emit(deathNumChanged(m_nDeathNum));
}

int CMyListModel::hurtNum()
{
    return(m_setHurt.size());
}

int CMyListModel::deathNum()
{
    return(m_nDeathNum);
}

int CMyListModel::totalNum()
{
    return(m_allData.size());
}

/// 获取活着的人数
int CMyListModel::liveNum()
{
    return(m_setLive.size());
}

/// 获取总分
int CMyListModel::getScore()
{
    int nTotalScore(0);

    for(auto one : m_allData)
    {
        auto pPerson = CDataManager::GetInstance()->FindPersonInfo(one->getId());
        qDebug()<<"测试人员id11111:"<<one->getId()<<one->getType()<<m_allData.size();
        if(nullptr != pPerson)
        {
            int nHitSize = pPerson->hitinfo_size();
            for(int i=0; i<nHitSize; ++i)
            {
                //                 auto pPersonHurt = CDataManager::GetInstance()->FindPersonInfo(pPerson->hitinfo(i).id());
                bool hurtFlag=false;
                int hurtId=pPerson->hitinfo(i).id();
                for(auto one : m_allData)
                {

                    qDebug()<<"属方ceshi ----："<<one->getType()<<one->getId()<<hurtId<<m_allData.size();
                    if(one->getId()==hurtId)
                    {
                        qDebug()<<"属方："<<one->getType()<<CConfigInfo::GetInstance()->CalHurtMark(pPerson->hitinfo(i).hurtpart());
                        int temp=CConfigInfo::GetInstance()->CalHurtMark(pPerson->hitinfo(i).hurtpart());
                        nTotalScore=nTotalScore-temp;//CConfigInfo::GetInstance()->CalHurtMark(pPerson->hitinfo(i).hurtpart());
                        hurtFlag=true;
                        break;
                    }

                }
                if(hurtFlag)
                {
                    continue;
                }
                nTotalScore +=CConfigInfo::GetInstance()->CalHurtMark(pPerson->hitinfo(i).hurtpart());
            }

        }
    }
    gethitRate();
//    getDepleteBullets();
//    getAllRemindBullets();
//    getAllHit();
    return(nTotalScore);
}

///*getAllBullets*/
int CMyListModel::getDepleteBullets()
{
    bool bLink1(false);
    int nNum(0),nNumBullets(0);
    int nHitSize(0),depleteBullets(0);
    for(auto one : m_allData)
    {
        auto pPersonInfo = CDataManager::GetInstance()->FindPersonInfo(one->getId());

        if(nullptr != pPersonInfo)
        {
            nHitSize+= pPersonInfo->hitinfo_size();
        }
        /// 判断剩余子弹数
        const ConnectStatus& conStatus = pPersonInfo->curtstatus();
        int nBaty = pPersonInfo->curtstatus().weapons_size();

        for(int nIndex=0; nIndex < nBaty; ++nIndex)
        {
            switch(conStatus.weapons(nIndex).weapontype())
            {
            case RIFLE:
                bLink1 = UNLINK != conStatus.weapons(nIndex).contype();
                if(bLink1)
                {
                    nNumBullets+=CDealDataManager::GetInstance()->GetBulletSum(pPersonInfo->id()).at(0).toInt();
                    nNumBullets+=CConfigInfo::GetInstance()->GetChargeBullets(1);
                    nNum += conStatus.weapons(nIndex).bulletnum();
                    qDebug()<<one->getType()<<"测试RIFLE子弹数："<<nNumBullets<<nNum;
                }
                break;
            case GRENAD:
                bLink1 = UNLINK != conStatus.weapons(nIndex).contype();
                if(bLink1)
                {
                    nNumBullets+=CDealDataManager::GetInstance()->GetBulletSum(pPersonInfo->id()).at(2).toInt();
                    nNumBullets+=CConfigInfo::GetInstance()->GetChargeBullets(2);
                    nNum += conStatus.weapons(nIndex).bulletnum();
                    qDebug()<<one->getType()<<"测试GRENAD子弹数："<<nNumBullets<<nNum;
                }
                break;
            case SUBMACHINE:
                bLink1 = UNLINK != conStatus.weapons(nIndex).contype();
                if(bLink1)
                {
                    nNumBullets+=CDealDataManager::GetInstance()->GetBulletSum(pPersonInfo->id()).at(4).toInt();
                    nNumBullets+=CConfigInfo::GetInstance()->GetChargeBullets(7);
                    nNum += conStatus.weapons(nIndex).bulletnum();
                    qDebug()<<one->getType()<<"测试SUBMACHINE子弹数："<<nNumBullets<<nNum;
                }
                break;
            }
        }
//        if(depleteBullets==0)
//        {
//            return 1;
//        }
//        else
//        {
//            qDebug()<<"命中率"<<nHitSize/depleteBullets;
//        }
        qDebug()<<one->getType()<<"消耗的子弹数："<<nNumBullets-nNum;
        return nNumBullets-nNum;
    }
    return nNumBullets-nNum;
}

int CMyListModel::getAllRemindBullets()
{
    bool bLink1(false),bLink(false);
    int nNum(0);
    for(auto one : m_allData)
    {
        auto pPersonInfo = CDataManager::GetInstance()->FindPersonInfo(one->getId());
        /// 判断剩余子弹数
        const ConnectStatus& conStatus = pPersonInfo->curtstatus();
        int nBaty = pPersonInfo->curtstatus().weapons_size();


        for(int nIndex=0; nIndex < nBaty; ++nIndex)
        {
            switch(conStatus.weapons(nIndex).weapontype())
            {
            case RIFLE:
                bLink1 = UNLINK != conStatus.weapons(nIndex).contype();
                if(bLink1)
                {
                    nNum += conStatus.weapons(nIndex).bulletnum();
                }
                break;
            case GRENAD:
                bLink1 = UNLINK != conStatus.weapons(nIndex).contype();
                if(bLink1)
                {
                    nNum+= conStatus.weapons(nIndex).bulletnum();
                }
                break;
            case SUBMACHINE:
                bLink1 = UNLINK != conStatus.weapons(nIndex).contype();
                if(bLink1)
                {
                    nNum+= conStatus.weapons(nIndex).bulletnum();
                }
                break;
            }
        }
        return nNum;
    }
}

int CMyListModel::getAllHit()
{
    int nHitSize=0;
    for(auto one : m_allData)
    {
        auto pPersonInfo = CDataManager::GetInstance()->FindPersonInfo(one->getId());
        if(nullptr != pPersonInfo)
        {
            nHitSize+= pPersonInfo->hitinfo_size();
        }
        return nHitSize;
    }
    return nHitSize;
}

float CMyListModel::gethitRate()
{
    bool bLink1(false);
    int nNum(0),nNumBullets(0);
    int nHitSize(0),depleteBullets(0);
    for(auto one : m_allData)
    {
        auto pPersonInfo = CDataManager::GetInstance()->FindPersonInfo(one->getId());
        /// 判断剩余子弹数
        const ConnectStatus& conStatus = pPersonInfo->curtstatus();
        int nBaty = pPersonInfo->curtstatus().weapons_size();

        for(int nIndex=0; nIndex < nBaty; ++nIndex)
        {
            switch(conStatus.weapons(nIndex).weapontype())
            {
            case RIFLE:
                bLink1 = UNLINK != conStatus.weapons(nIndex).contype();
                if(bLink1)
                {
                    nNumBullets+=CDealDataManager::GetInstance()->GetBulletSum(pPersonInfo->id()).at(0).toInt();
                    nNumBullets+=CConfigInfo::GetInstance()->GetChargeBullets(1);
                    nNum += conStatus.weapons(nIndex).bulletnum();
                    qDebug()<<one->getType()<<"测试RIFLE子弹数："<<nNumBullets<<nNum;
                }
                break;
            case GRENAD:
                bLink1 = UNLINK != conStatus.weapons(nIndex).contype();
                if(bLink1)
                {
                    nNumBullets+=CDealDataManager::GetInstance()->GetBulletSum(pPersonInfo->id()).at(2).toInt();
                    nNumBullets+=CConfigInfo::GetInstance()->GetChargeBullets(2);
                    nNum += conStatus.weapons(nIndex).bulletnum();
                    qDebug()<<one->getType()<<"测试GRENAD子弹数："<<nNumBullets<<nNum;
                }
                break;
            case SUBMACHINE:
                bLink1 = UNLINK != conStatus.weapons(nIndex).contype();
                if(bLink1)
                {
                    nNumBullets+=CDealDataManager::GetInstance()->GetBulletSum(pPersonInfo->id()).at(4).toInt();
                    nNumBullets+=CConfigInfo::GetInstance()->GetChargeBullets(7);
                    nNum += conStatus.weapons(nIndex).bulletnum();
                    qDebug()<<one->getType()<<"测试SUBMACHINE子弹数："<<nNumBullets<<nNum;
                }
                break;
            }
        }
        if(nullptr != pPersonInfo)
        {
            nHitSize+= pPersonInfo->hitinfo_size();
        }
        depleteBullets=nNumBullets-nNum;
         qDebug()<<" ----------------"<<depleteBullets<<nHitSize;
        if(depleteBullets==0)
        {
            return 1;
        }
        else
        {
            qDebug()<<"命中率"<<(float)nHitSize/(float)depleteBullets;
            return (float)nHitSize/(float)depleteBullets;
        }
    }
}

/// 更新信息
bool CMyListModel::UpdatePerson(quint16 nID, CPersonStatus *pPerson)
{
    auto findOne = m_allPerson.find(nID);
    if(m_allPerson.end() != findOne)
    {
        if(0 >= pPerson->getHealth())
        {
            m_setLive.remove(nID);
            m_setHurt.remove(nID);
            m_pGroupStatus->SetHurtRatio(static_cast<double>(hurtNum())/totalNum());
            m_pGroupStatus->SetLiveRatio(static_cast<double>(liveNum())/totalNum());
        }
        else if(0 < pPerson->getHealth() && pPerson->getHealth() < 100)
        {
            m_setHurt.insert(nID);
            m_pGroupStatus->SetHurtRatio(static_cast<double>(hurtNum())/totalNum());
        }
        else
        {
            m_setLive.insert(nID);
            m_pGroupStatus->SetLiveRatio(static_cast<double>(liveNum())/totalNum());
        }

        /// 战损人数更改,通知修改
        int nDeathNum =totalNum() - liveNum();
        if(m_nDeathNum != nDeathNum)
        {
            m_nDeathNum = nDeathNum;
            emit(deathNumChanged(m_nDeathNum));
        }

        return(true);
    }
    else
    {
        return(false);
    }
}

/// 获取组的状态
CGroupStatus *CMyListModel::GetGroupStatus()
{
    return(m_pGroupStatus);
}

/// 判断两个模型列表是否相等
bool CMyListModel::operator !=(const CMyListModel &rOther)
{
    if(this == &rOther)
    {
        return(false);
    }

    return(m_allData != rOther.m_allData);
}

/// 赋值操作符
CMyListModel &CMyListModel::operator=(const CMyListModel &rOther)
{
    if(this != &rOther)
    {
        m_allData = rOther.m_allData;
    }
    return(*this);
}

/// 清空
void CMyListModel::Clear()
{
    m_pGroupStatus->SetLiveRatio(1.0);
    m_pGroupStatus->SetHurtRatio(0.);
    m_setHurt.clear();
    m_setLive.clear();
    m_allPerson.clear();
    deathDefault();
    for(auto one = m_allData.begin();
        one != m_allData.end(); ++one)
    {
        m_setLive.insert((*one)->getId());
        m_allPerson.insert((*one)->getId());
    }
}
