#ifndef C_PLACENODEINFO_H
#define C_PLACENODEINFO_H

#include <string>
class ISceneGraph;
class IMapLocation;
class ILabel;
class IImage;
struct ScenePos;
struct SceneColor;

enum GroupType
{
    BLUE_GROUP,
    RED_GROUP,
//    GREEN_GROUP,
    UN_KNOW
};

enum HurtType
{
    Hurt_OK,
    Hurt_hurt,
    Hurt_Death,
    Hurt_Fire,
    Hurt_UNLINE,
    Hurt_ShouLei
};

class CPlaceNodeInfo
{
public:
    CPlaceNodeInfo(ISceneGraph*  pSceneGraph);

    /**
     * @brief 设置地雷的位置
     * @param fLon
     * @param fLat
     */
    void SetPos(float fLon, float fLat);
    const ScenePos GetPos();

    /**
     * @brief 设置显示的文字
     * @param sTextInfo
     */
    void SetText(const std::string& sTextInfo);

    /**
     * @brief 设置武器类型
     */
    void SetGroupType(GroupType);

    /**
     * @brief 设置受伤状态
     */
    void SetHurtType(HurtType);

    /**
     * @brief 设置图标颜色
     */
    void SetColor(const SceneColor&);

    /**
     * @brief 获取位置节点
     * @return
     */
    IMapLocation* GetLocationNode(){return(m_pLocation);}
protected:
    /**
      * @brief 初始化节点
      */
    void InitNode();

    void TypeChanged();
protected:
    ISceneGraph*  m_pSceneGraph;
    IMapLocation* m_pLocation=nullptr;
    ILabel*       m_pLabel=nullptr;
    IImage*       m_pImage=nullptr;
    GroupType     m_emGroupType=UN_KNOW;
    HurtType      m_emHurtType=Hurt_OK;
};
#endif // C_PLACENODEINFO_H
