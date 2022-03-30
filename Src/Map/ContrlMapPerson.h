#ifndef CCONTRLMAPPERSON_H
#define CCONTRLMAPPERSON_H

#include <QtCore>
#include "../TimeServer/ITimeObserver.h"
class IMap;
class IMapLayer;
class CPlaceNodeInfo;
class ISceneGraph;
class IMapLine;

struct HitLine
{
    quint16 times=0;
    IMapLine*  pLine=nullptr;
};

class CContrlMapPerson:public ITimeObserver
{
public:
    CContrlMapPerson(ISceneGraph* pSceneGraph);

    /**
     * @brief 定位
     */
    void Locate(quint16);

    /**
     * @brief 更新位置
     */
    void UpdatePos(quint16,double,double);

    /**
     * @brief 更新名称
     */
    void UpdateName(quint16,const QString&);

    /**
     * @brief 更新分组
     */
    void UpdateGroup(quint16,const QString&);

    /**
     * @brief 更新人员状态
     */
    void UpdateStatus(quint16,int);

    /**
     * @brief 清空地图数据
     */
    void ClearMap();

    /**
     * @brief 更新射击线
     */
    void UpdateHitLine(quint16,quint16);

    /**
     * @brief 更新时间
     */
    void UpdateSeconds(const quint16&);

protected:
    /**
     * @brief 获取或者创建地图显示的人员信息
     * @return
     */
    CPlaceNodeInfo*   GetOrCreateMapPersonInfo(quint16);
private:
    quint16         m_unTimes=0;
    ISceneGraph*    m_pSceneGraph;            /// 场景图
    IMap*           m_pMap;                   /// 地图
    IMapLayer*     m_pLayer;                 ///标绘图层
    QMap<quint16,CPlaceNodeInfo*> m_mapShowInfo; /// 更新显示
    QList<HitLine>  m_hitLine;
};

#endif // CCONTRLMAPPERSON_H
