#ifndef CDATAMANAGER_H
#define CDATAMANAGER_H

#include <QMap>
#include <QSet>
#include <fstream>
#include "../TimeServer/ITimeObserver.h"
class IDataManagerObserver;

class PersonInfo;
class QFile;
struct PersonHeartInfo;
struct PersonEventInfo;

class CDataManager:public ITimeObserver
{
public:
    static CDataManager* GetInstance();

    /**
     * @brief 订阅数据管理者数据
     * @param pObserver
     */
    void SubObserver(IDataManagerObserver* pObserver);

    /**
     * @brief 取消订阅
     * @param pObserver
     */
    void UnSubObserver(IDataManagerObserver* pObserver);


    /**
     * @brief 发送命中信息
     * @param unID
     */
    void UpdateManEvent(quint16 unID);

    /**
     * @brief 重置人员状态
     */
    void ResetPersonInfo();

    /**
     * @brief 创造或者查询人员信息
     * @param uID
     * @return
     */
    PersonInfo* GetOrCreatePersonInfo(quint16 uID);

    /**
     * @brief 查找人员信息
     * @param uID
     * @return
     */
    PersonInfo* FindPersonInfo(quint16 uID);

    /**
     * @brief 更新信息
     */
    void Update(quint16 uID);

    /**
     * @brief 读取文件
     * @param sFileName
     */
    void ReadFile(const std::string &sFileName);

    /**
     * @brief 更新秒数
     * @param unSeconds
     */
    void UpdateSeconds(const quint16& unSeconds);
    void UpdateSimulationTime(const quint16 &);

    /**
     * @brief 不保存则删除数据
     */
    void RemoveData();

    /**
     * @brief 获取文件名称
     * @return
     */
    const QString& GetFileName(const QString& sDataString);

private:
    explicit CDataManager();
    ~CDataManager();

    /**
     * @brief 初始化人员状态
     * @param pPerson
     */
    void InitPerson(PersonInfo* pPerson);

    /**
     * @brief 初始化武器状态
     * @param pPerson
     */
    void InitWeapon(PersonInfo* pPerson);

    /**
     * @brief 清空记录信息
     */
    void ClearRecordInfo();

private:
    QSet<IDataManagerObserver*> m_setObserver;   /// 订阅消息
    typedef QMap<quint16,PersonInfo*> AllPersonInfo;
    AllPersonInfo               m_allPersonInfo; /// 所有的人员信息

    std::ofstream               m_outFile;       /// 输出的文件
    char*                       m_pDataBuffer;   /// 数据缓存区
    int                         m_nBufferLength; /// 数据大小
    int                         m_unTimes;       /// 同步时间

    QString                     m_sDataPath;      /// 存放回放数据的路径
    QString                     m_sCurrentFileName;             /// 打开文件
    std::vector<quint16>        m_vRecordTimes;                 /// 之前的演习时间
    std::vector<std::vector<PersonInfo*> > m_vRecordPersonInfo; /// 读取之前的演习数据
};

#endif // CDATAMANAGER_H
