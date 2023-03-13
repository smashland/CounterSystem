#ifndef CMYLISTMODEL_H
#define CMYLISTMODEL_H
#include <QAbstractListModel>
#include <QSet>

class CPersonStatus;
class CGroupStatus;

class CMyListModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit CMyListModel(QObject *parent = nullptr);
    Q_PROPERTY(int count MEMBER m_nCount NOTIFY countChanged)
    Q_PROPERTY(int deathNum MEMBER m_nDeathNum NOTIFY deathNumChanged)
    CMyListModel(const CMyListModel& other);
    ~CMyListModel();

    /// 重写QAbstractListModel函数
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    QHash<int, QByteArray> roleNames() const;
    int count()const;
    /// end 重写QAbstractListModel函数

    CPersonStatus *at(int nIndex);
    Q_INVOKABLE void remove(int nIndex);
    Q_INVOKABLE void append(CPersonStatus* pPerson);

    ///默认战损人数
    void deathDefault();
    int  hurtNum();
    int  deathNum();
    int  totalNum();
    int  liveNum();
    int  getScore();

    int getDepleteBullets();   ///得到消耗的子弹数
    int getAllBullets();       ///得到总弹药数
    int getAllRemindBullets(); ///得到总的剩余弹药数
    int getAllHit();           ///得到总的击中次数
    float gethitRate();        ///得到总的命中率
    QList<int> getBulletsList();


    /**
     * @brief 更新个人信息
     * @param nIndex
     * @return
     */
    bool UpdatePerson(quint16 nID,CPersonStatus* pPerson);

    /**
     * @brief 获取分组信息
     * @return
     */
    CGroupStatus* GetGroupStatus();

    /**
     * @brief 重写不等操作符
     * @param rOther
     * @return
     */
    bool operator !=(const CMyListModel& rOther);

    /**
     * @brief 重写赋值操作符
     * @param rOther
     * @return
     */
    CMyListModel& operator=(const CMyListModel& rOther);

    /**
     * @brief 清空
     */
    void Clear();
signals:
    void countChanged(int);
    void deathNumChanged(int);
protected:
    CGroupStatus*                m_pGroupStatus;         /// 组状态
    QSet<quint16>                m_setLive;              /// 活着的人
    QSet<quint16>                m_setHurt;              /// 受伤
    QSet<quint16>                m_allPerson;            /// 所有的人
    QList<CPersonStatus*>        m_allData;              /// 所有的人员状态
    QHash<int, QByteArray>       m_mapRolesNames;        /// 返回类型的对应名字
    int                          m_nCount{};             /// 总人数
    int                          m_nDeathNum{};          /// 战损人数
    int                          m_nDepleteBullets;      ///消耗的子弹数
    int                          m_nhitRate;             ///命中率
};


#endif // CMYLISTMODEL_H
