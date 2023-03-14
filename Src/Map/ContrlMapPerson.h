#ifndef CCONTRLMAPPERSON_H
#define CCONTRLMAPPERSON_H

#include <QtCore>
#include <QObject>
#include <Tool/ITool.h>
#include "../TimeServer/ITimeObserver.h"
class IMap;
class IMapLayer;
class CPlaceNodeInfo;
class ISceneGraph;
class IMapLine;
class CGlobalData;

struct HitLine
{
    quint16 times=0;
    IMapLine*  pLine=nullptr;
};

class CContrlMapPerson:public QObject,public ITimeObserver, public PickMessage
{
    Q_OBJECT
public:
    CContrlMapPerson(ISceneGraph* pSceneGraph,CGlobalData* pData);

    /**
     * @brief 定位
     */
    void Locate(quint16);

    /**
     * @brief 更新位置
     */
    void UpdatePos(quint16,double,double);

    /**
     * @brief 更新复活次数
     */
    void UpdateRelive(quint16,const QString&);

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

    /**
     * @brief 更新图片
     */
    void UpdateImage(/*const ScenePos &rLeftUp, const ScenePos &rRightDown, const std::string &sImagePath*/);

    /**
     * @brief 得到各方的id
     * @return
     */
    QList<int> getRedId(){return m_listRedPerId;}
    QList<int> getBuleId(){return m_listBulePerId;}
    QList<int> getUnknowId(){return m_listUnknowPerId;}

    /**
     * @brief 清除类型id
     */
    void clearAllTypeId();

    //    /**
    //     * @brief 重写点中事件
    //     * @param nPickID
    //     */
    //    void PickID(unsigned int nPickID, unsigned int);

signals:
    void mapPersonInfo(int id,QString name,int relive,double dLon, double dLat,bool bTk);
protected:
    /**
     * @brief 获取或者创建地图显示的人员信息
     * @return
     */
    CPlaceNodeInfo*   GetOrCreateMapPersonInfo(quint16);
private:
    quint16         m_unTimes=1000;
    ISceneGraph*    m_pSceneGraph;            /// 场景图
    IMap*           m_pMap;                   /// 地图
    IMapLayer*     m_pLayer;                 ///标绘图层
    QMap<quint16,CPlaceNodeInfo*> m_mapShowInfo; /// 更新显示
    QList<HitLine>  m_hitLine;
    CGlobalData*    m_pGloablData;
    QList<int>      m_listRedPerId;          ///红方人员ID
    QList<int>      m_listBulePerId;         ///蓝方人员ID
    QList<int>      m_listUnknowPerId;       ///未知人员ID
};

#endif // CCONTRLMAPPERSON_H
