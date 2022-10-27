#include <ISceneCore.h>
#include <Plot/Map/IMapLocation.h>
#include <Plot/SceneShape/ILabel.h>
#include <Plot/SceneShape/IImage.h>
#include <Plot/Common/ISceneScreenGroup.h>
#include <Plot/Common/ISceneLodGroup.h>
#include <Plot/Common/ISceneScaleGroup.h>
#include "PlaceNodeInfo.h"


CPlaceNodeInfo::CPlaceNodeInfo(ISceneGraph *pSceneGraph):m_pSceneGraph(pSceneGraph)
{
    InitNode();
}

void CPlaceNodeInfo::SetPos(float fLon, float fLat)
{
    ScenePos pos;
    pos.dX = fLon;
    pos.dY = fLat;
    pos.dZ = 1000;
    m_pLocation->SetGeoPos(pos);
}

const ScenePos CPlaceNodeInfo::GetPos()
{
    return(m_pLocation->GeoPos());
}

void CPlaceNodeInfo::SetText(const std::string &sTextInfo)
{
    m_pLabel->SetText(sTextInfo);
    m_pLabel->SetFontSize(18);
    ScenePixelOffset spOffset;
    int nCout = sTextInfo.size();
    double dWordCount=0;
    const char* pChar = sTextInfo.c_str();
    for(int i=0;i<nCout;)
    {
        if(!((*pChar) & 0x80))
        {
            ++pChar;
            ++i;
            dWordCount += 0.5;
        }
        else if((*pChar) & 0x40)
        {
            if((*pChar) & 0x20)
            {
                if((*pChar) & 0x10)
                {
                    pChar += 4;
                    i+=4;
                }
                else
                {
                    pChar += 3;
                    i+=3;
                }
            }
            else
            {
                pChar += 2;
                i+=2;
            }
            dWordCount += 1;
        }
    }
    spOffset.sHeight=-26;
    spOffset.sWidth=-(9*dWordCount);
    m_pLabel->SetPixelOffset(spOffset);
}

/// 设置类型
void CPlaceNodeInfo::SetGroupType(GroupType emGroupType)
{
    if(emGroupType != m_emGroupType)
    {
        m_emGroupType = emGroupType;
        TypeChanged();
    }
}

void CPlaceNodeInfo::SetHurtType(HurtType emHurtType)
{
    if(m_emHurtType != emHurtType)
    {
        m_emHurtType = emHurtType;
        TypeChanged();
    }
}

void CPlaceNodeInfo::SetColor(const SceneColor &rColor)
{
    m_pImage->SetColor(rColor);
}

void CPlaceNodeInfo::InitNode()
{
    auto pScreenGroup = m_pSceneGraph->GetPlot()->CreateSceneGroup(SCREEN_GROUP)->AsSceneScreenGroup();
    m_pLabel = dynamic_cast<ILabel*>(m_pSceneGraph->GetPlot()->CreateSceneNode("ILabel"));
    m_pLocation = dynamic_cast<IMapLocation*>(m_pSceneGraph->GetPlot()->CreateSceneNode("IMapLocation"));
    m_pImage=dynamic_cast<IImage*>(m_pSceneGraph->GetPlot()->CreateSceneNode("IImage"));
    m_pImage->OpenCull(false);
    m_pImage->AlwasOnTop(true);
    m_pLabel->AlwasOnTop(true);
    m_pLocation->SetCanPick(true);
    TypeChanged();

    pScreenGroup->AddSceneNode(m_pImage);
    pScreenGroup->AddSceneNode(m_pLabel);
    pScreenGroup->AlwasOnTop(true);
    m_pLocation->SetSceneNode(pScreenGroup);
    m_pLocation->SetTerrainType(m_pLocation->RELATIVE_TERRAIN);
    m_pLabel->SetFont("Fonts/msyh.ttf");

//    ScenePixelOffset spOffset;
//    spOffset.sHeight=-26;
//    spOffset.sWidth=0;
//    m_pLabel->SetPixelOffset(spOffset);
}

/// 样式更改
void CPlaceNodeInfo::TypeChanged()
{
    std::string sImagePath("Image/Person/");
    switch (m_emGroupType)
    {
    case BLUE_GROUP:
        sImagePath += "blue";
        break;
    case RED_GROUP:
        sImagePath += "red";
        break;
    case GREEN_GROUP:
        sImagePath += "green";
        break;
    default:
        sImagePath += "white";
        break;
    }

    switch (m_emHurtType)
    {
    case Hurt_hurt:
        sImagePath +="_hurt.png";
        break;
    case Hurt_Death:
        sImagePath +="_death.png";
        break;
    case Hurt_ShouLei:
        sImagePath +="_shoulei.png";
        break;
    case Hurt_UNLINE:
        sImagePath +="_unline.png";
        break;
    case Hurt_Fire:
        sImagePath +="_fire.png";
        break;
    default:
        sImagePath +=".png";
        break;
    }

    m_pImage->SetImagePath(sImagePath);
    SceneImageSize size;
    size.unHeight=32;
    size.unWidth=32;
    m_pImage->SetImageSize(size);
}
