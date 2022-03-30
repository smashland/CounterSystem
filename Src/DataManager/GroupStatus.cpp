#include "GroupStatus.h"

CGroupStatus::CGroupStatus(QObject *parent) : QObject(parent)
{
}

void CGroupStatus::SetTypeName(const QString &sType)
{
    if(sType != m_sType)
    {
        m_sType = sType;
        emit(typeChanged(m_sType));
    }
}

void CGroupStatus::SetLiveRatio(float fLive)
{
    if(fLive != m_fLiveRatio)
    {
        m_fLiveRatio = fLive;
        emit(liveRatioChanged(m_fLiveRatio));
    }
}

void CGroupStatus::SetHurtRatio(float fHurt)
{
    if(fHurt != m_fHurtRatio)
    {
        m_fHurtRatio = fHurt;
        emit(hurtRatioChanged(m_fHurtRatio));
    }
}
