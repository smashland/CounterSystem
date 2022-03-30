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
    CMyListModel(const CMyListModel& other);
    ~CMyListModel();

    /// ��дQAbstractListModel����
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    QHash<int, QByteArray> roleNames() const;
    int count()const;
    /// end ��дQAbstractListModel����

    CPersonStatus *at(int nIndex);
    Q_INVOKABLE void remove(int nIndex);
    Q_INVOKABLE void append(CPersonStatus* pPerson);
    int  hurtNum();
    int  deathNum();
    int  totalNum();
    int  liveNum();
    int  getScore();

    /**
     * @brief ���¸�����Ϣ
     * @param nIndex
     * @return
     */
    bool UpdatePerson(quint16 nID,CPersonStatus* pPerson);

    /**
     * @brief ��ȡ������Ϣ
     * @return
     */
    CGroupStatus* GetGroupStatus();

    /**
     * @brief ��д���Ȳ�����
     * @param rOther
     * @return
     */
    bool operator !=(const CMyListModel& rOther);

    /**
     * @brief ��д��ֵ������
     * @param rOther
     * @return
     */
    CMyListModel& operator=(const CMyListModel& rOther);

    /**
     * @brief ���
     */
    void Clear();

protected:
    CGroupStatus*                m_pGroupStatus;         /// ��״̬
    QSet<quint16>                m_setLive;              /// ���ŵ���
    QSet<quint16>                m_setHurt;              /// ����
    QSet<quint16>                m_allPerson;            /// ���е���
    QList<CPersonStatus*>        m_allData;              /// ���е���Ա״̬
    QHash<int, QByteArray>       m_mapRolesNames;        /// �������͵Ķ�Ӧ����
};


#endif // CMYLISTMODEL_H
