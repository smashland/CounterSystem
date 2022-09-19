#include <SceneGraph/ISceneGraph.h>
#include <Plot/Map/IMap.h>
#include <Plot/Map/IMapLayer.h>
#include <Plot/IPlot.h>
#include <Plot/Map/IMapLine.h>
#include <SceneGraph/IViewPort.h>
#include <Plot/SceneShape/ILabel.h>
#include <Plot/Map/IMapLocation.h>
#include <Plot/Map/SpaceEnv/ISpaceEnv.h>
#include <SceneGraph/IWindow.h>
#include "PlaceNodeInfo.h"
#include "ContrlMapPerson.h"
#include "../ErrorReport.h"

CContrlMapPerson::CContrlMapPerson(ISceneGraph *pSceneGraph):
    m_pSceneGraph(pSceneGraph)
{
    m_pMap = m_pSceneGraph->GetMap();
    m_pMap->GetSpaceEnv()->ShowSpaceBackGround(false);
    m_pMap->OpenLight(false);
    m_pLayer = m_pMap->CreateLayer("Test");
}

/// 定位
void CContrlMapPerson::Locate(quint16 unID)
{
    auto pMapPerson = GetOrCreateMapPersonInfo(unID);

    SceneViewPoint tmpViewPoint;
    ScenePos pos = pMapPerson->GetPos();

    tmpViewPoint.stPos.dX = pos.dX;
    tmpViewPoint.stPos.dY = pos.dY;
    tmpViewPoint.stPos.dZ = pos.dZ;
    tmpViewPoint.fElev = 90.f;
    tmpViewPoint.fDistance = 1000;

    m_pSceneGraph->GetMainWindow()->GetMainViewPoint()->SetViewPoint(tmpViewPoint,5);
}

/// 更新人员分组
void CContrlMapPerson::UpdateGroup(quint16 unID, const QString & sGroup)
{
    auto pMapPerson = GetOrCreateMapPersonInfo(unID);

    if(sGroup == QString::fromLocal8Bit("蓝方"))
    {
        pMapPerson->SetGroupType(BLUE_GROUP);
    }
    else if(sGroup == QString::fromLocal8Bit("红方"))
    {
        pMapPerson->SetGroupType(RED_GROUP);
    }
    else
    {
        pMapPerson->SetGroupType(UN_KNOW);
    }
}

/// 更新状态
void CContrlMapPerson::UpdateStatus(quint16 unID, int nHealth)
{
    auto pMapPerson = GetOrCreateMapPersonInfo(unID);

    HurtType status(Hurt_OK);
    if(nHealth < 100 && nHealth > 0)
    {
        status = Hurt_hurt;
    }
    else if(nHealth < 1)
    {
        status = Hurt_Death;
    }

    pMapPerson->SetHurtType(status);
}

/// 更新人员位置
void CContrlMapPerson::UpdatePos(quint16 unID, double dLon, double dLat)
{
    auto pMapPerson = GetOrCreateMapPersonInfo(unID);

    /// 更新位置
    static ScenePos pos;
    pos.dX = dLon;
    pos.dY = dLat;
    pos.dZ = 0;

    pMapPerson->GetLocationNode()->SetGeoPos(pos);
}
///更新复活次数
void CContrlMapPerson::UpdateRelive(quint16 unID,const QString & sRelive)
{
    auto pMapPerson = GetOrCreateMapPersonInfo(unID);
    pMapPerson->SetText(sRelive.toUtf8().data());
}

/// 更新人员名称
void CContrlMapPerson::UpdateName(quint16 unID, const QString & sName)
{
    auto pMapPerson = GetOrCreateMapPersonInfo(unID);
    pMapPerson->SetText(sName.toUtf8().data());
}


void CContrlMapPerson::ClearMap()
{
    m_mapShowInfo.clear();
    m_pLayer->Clear();
}

/// 更新射击线
void CContrlMapPerson::UpdateHitLine(quint16 id1, quint16 id2)
{
    auto pMapPerson1 = GetOrCreateMapPersonInfo(id1);

    auto pMapPerson2 = GetOrCreateMapPersonInfo(id2);

    const ScenePos& rPos1 = pMapPerson1->GetPos();
    const ScenePos& rPos2 = pMapPerson2->GetPos();

    auto pLine = (IMapLine*)m_pSceneGraph->GetPlot()->CreateSceneNode("IMapLine");
    pLine->GetDrawLine()->AddPoint(0,rPos1);
    pLine->GetDrawLine()->AddPoint(1,rPos2);
    SceneColor color;
    color.fR = 1.0f;
    pLine->GetDrawLine()->SetColor(color);
    pLine->GetDrawLine()->SetLineWidth(3.0);
    pLine->GetDrawLine()->SetLineType(ILine::SOLID_LINE);
    pLine->SetTerrainType(IMapLine::CLOSE_TERRAIN);
    m_pLayer->AddSceneNode(pLine);

    HitLine tmpHit;
    tmpHit.times = m_unTimes;
    tmpHit.pLine = pLine;
    m_hitLine.push_back(tmpHit);
}

/// 更新时间
void CContrlMapPerson::UpdateSeconds(const quint16 &seconds)
{
    m_unTimes = seconds;
    for(QList<HitLine>::iterator one = m_hitLine.begin();
        one != m_hitLine.end();)
    {
        if(m_unTimes-(*one).times > 1)
        {
            m_pLayer->RemoveSceneNode((*one).pLine);
            one = m_hitLine.erase(one);
        }
        else
        {
            ++one;
        }
    }
}

/// 查找显示信息
CPlaceNodeInfo *CContrlMapPerson::GetOrCreateMapPersonInfo(quint16 unID)
{
    CPlaceNodeInfo * pPersonInfo = nullptr;
    auto findPerson = m_mapShowInfo.find(unID);
    if(m_mapShowInfo.end() == findPerson)
    {
        pPersonInfo = new CPlaceNodeInfo(m_pSceneGraph);
        pPersonInfo->SetText(QString::number(unID).toUtf8().data());
        m_pLayer->AddSceneNode(pPersonInfo->GetLocationNode());
        m_mapShowInfo[unID] = pPersonInfo;
    }
    else
    {
        pPersonInfo = findPerson.value();
    }

    return(pPersonInfo);
}
