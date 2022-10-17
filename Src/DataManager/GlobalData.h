#ifndef GLOBALDATA_H
#define GLOBALDATA_H
#include <fstream>
#include <QObject>
#include <QList>
#include <QVariantMap>

#include "PersonStatus.h"
#include "../TimeServer/ITimeObserver.h"
#include "IDataManagerObserver.h"

class CMyListModel;
class CPersonAllInfo;
class CPersonStatus;
class CContrlMapPerson;
class CGroupStatus;
class ISceneGraph;

class CGlobalData : public QObject,public ITimeObserver,public IDataManagerObserver
{
    Q_OBJECT

    Q_PROPERTY(int atLineNumber MEMBER m_nOnLine NOTIFY lineSizeChanged)
    Q_PROPERTY(int allDataNumber MEMBER m_nAllData NOTIFY allDataChanged)
    Q_PROPERTY(int allLiveNumber MEMBER m_nLiveNum NOTIFY liveNumChanged)
    Q_PROPERTY(quint16 simuTime NOTIFY simTimeChanged)
    Q_PROPERTY(QVariantList listResult MEMBER m_listResult NOTIFY resultChanged)
    Q_PROPERTY(QVariantList allResult MEMBER m_listAllResult NOTIFY allResultChanged)
public:
    explicit CGlobalData(QObject *parent = nullptr);
    ~CGlobalData();

    /**
     * @brief 初始化GlobalData
     */
    void InitGlobalData();

    /**
     * @brief 人员信息更新
     * @param unID
     */
    void UpdateID(quint16 unID);

    /**
     * @brief UpdateEvent
     */
    void UpdateEvent(quint16 unID);

    /**
     * @brief 更新时间
     * @attention 定时更新在线状态
     * @param unSconds
     */
    void UpdateSeconds(const quint16&);

    /**
     * @brief 更新时间
     * @param dateTime
     */
    void UpdateTime(const QDateTime &dateTime);

    void UpdateSimulationTime(const quint16 &);

    /**
     * @brief 更新数据
     * @param nData
     */
    void updateAllDataSize(int nData);

    /**
     * @brief 根据ID查找人员的所有状态信息
     * @param unID
     * @return
     */
    Q_INVOKABLE CPersonAllInfo* getPersonAllInfo(quint16 unID);

    /**
     * @brief 设置用户名称
     */
    Q_INVOKABLE void setUserName(quint16,const QString&);

    /**
     * @brief 清空状态
     */
    Q_INVOKABLE void clearInfo();

    /**
     * @brief 根据类型创建模型列表
     * @param sType
     * @return
     */
    Q_INVOKABLE CMyListModel *ceateType(const QString& sType);

    /**
     * @brief 获取所有的类型
     * @return
     */
    Q_INVOKABLE QList<QString> getAllType();

    /**
     * @brief 获取结果
     * @return
     */
    Q_INVOKABLE void calResult();

    /**
     * @brief 定位
     * @param unID
     */
    Q_INVOKABLE void dingWei(quint16 unID);

    /**
     * @brief 设置地图场景
     * @param pSceneGraph
     */
    void SetSeceneGraph(ISceneGraph* pSceneGraph);

    /**
     * @brief 回放开始/结束
     */
    Q_INVOKABLE int openReplayFile(const QUrl &rReplayFile);
    Q_INVOKABLE void beginReplay();
    Q_INVOKABLE void pauseReplay();
    Q_INVOKABLE void setSimuTime(quint16 uTimes);
    Q_INVOKABLE void endReplay();

    /**
     * @brief 保存数据
     * @param sDataFileName
     */
    Q_INVOKABLE void saveData(const QUrl& sDataFileName);

    /**
     * @brief 创建报表
     * @param sReportFileName
     */
    Q_INVOKABLE void createReport(const QUrl& sReportFileName);

    /**
     * @brief 保存方案
     * @param strScePath
     */
    Q_INVOKABLE void saveSceInfo(const QString &strScePath);

    /**
     * @brief 加载方案
     * @param strScePath
     */
    Q_INVOKABLE void loadSceInfo(const QString &sceName);

    /**
     * @brief 是否更新人员状态
     */
    Q_INVOKABLE void setUpdateAllInfo(bool);

    /**
     * @brief 清空所有数据
     */
    Q_INVOKABLE void clearAllInfo();

    /**
     * @brief 移除文件
     */
    Q_INVOKABLE void removeSavedFile();

    /**
     * @brief 更改分组
     */
    Q_INVOKABLE void changeGroup(quint16,QString);

signals:
    void simTimeChanged(quint16 simTime);
    void lineSizeChanged(int);
    void allDataChanged(int);
    void liveNumChanged(int);
    void updateGroup(CGroupStatus* groupStatus);
    void resultChanged(const QVariantList&);
    void allResultChanged(const QVariantList&);
protected:
    /**
     * @brief 统计成绩
     */
    void StatisticResult();

    /**
     * @brief 获取或者创建qml显示的简要信息
     * @return
     */
    CPersonStatus* GetOrCreatePersonStatus(quint16);

    /**
     * @brief 将状态压栈
     */
    void PushBackStatus();

    /**
     * @brief 将状态出栈
     */
    void PopUpStatus();


    /**
     * @brief 更新地图绘制的人员信息
     */
    void UpdateMap(quint16);

    /**
     * @brief 更新在线人数
     */
    void UpdateLiveNum();

private:
    bool            m_bUpdate=false;          /// 是否更新人员状态
    bool            m_bRemoveFile=true;       /// 是否删除文件
    int             m_nOnLine=0;              /// 在线人数
    int             m_nAllData=0;             /// 所有的数据
    int             m_nLiveNum=0;             /// 演习中存活人数
    std::ofstream   m_outFile;                /// 要保存的数据流
    QString         m_sCurrentFileName;       /// 当前文件名称
    quint16         m_unTimes=0;              /// 当前时间
    CContrlMapPerson* m_pCtrMapPerson=nullptr;/// 地图人员操作器
    CMyListModel* m_listStatusModel=nullptr;  /// 上线的人默认的加载组
    CPersonAllInfo* m_pPersonAllInfo=nullptr; /// 人员的所有信息
    QMap<QString,CMyListModel*> m_mapTypeInfo;/// 各种类型
    QMap<QString,QVector<quint16> > m_mapFenZu;/// 保存之前的分组信息
    QMap<quint16,CPersonStatus*> m_mapStatusModel;/// 所有的人员的简要信息
    QMap<quint16,QVector<int> >  m_allReplayEvent;/// 所有的回放事件
    QVector<CPersonStatus*>      m_allReplayStatus;/// 所有的回放人员状态
    QList<int>         m_listEvent;           /// 将事件保存下来
    QVariantList       m_listResult;          /// 各组的简要信息
    QVariantList       m_listAllResult;       /// 分组的详情
};

#endif // GLOBALDATA_H
