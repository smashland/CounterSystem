#include "PersonStatus.h"
#include "MyListModel.h"
#include "GroupStatus.h"
#include "DataManager.h"
#include "PersonInfo.pb.h"
#include "../ConfigInfo.h"

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

    endInsertRows();
}

int CMyListModel::hurtNum()
{
    return(m_setHurt.size());
}

int CMyListModel::deathNum()
{
    return(totalNum() - liveNum());
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
        if(nullptr != pPerson)
        {
            int nHitSize = pPerson->hitinfo_size();
            for(int i=0; i<nHitSize; ++i)
            {
                nTotalScore +=CConfigInfo::GetInstance()->CalHurtMark(pPerson->hitinfo(i).hurtpart());
            }
        }
    }
    return(nTotalScore);
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

    for(auto one = m_allData.begin();
        one != m_allData.end(); ++one)
    {
        m_setLive.insert((*one)->getId());
        m_allPerson.insert((*one)->getId());
    }
}
