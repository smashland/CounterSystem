#ifndef GETMACHINEINFO_H
#define GETMACHINEINFO_H
#include <QStringList>

class CGetMachineInfo
{
public:
    static CGetMachineInfo* GetInstance();

    /**
     * @brief 获取网卡信息
     * @return
     */
    const QStringList& GetMacInfo(){return(m_listMacInfo);}

    /**
     * @brief 获取cpuID
     * @return
     */
    const QString&       GetCpuID(){return(m_sCupID);}

    /**
     * @brief 获取磁盘序列号
     * @return
     */
    const QString&       GetHDSN(){return(m_sHardSN);}

    /**
     * @brief CPU是否是大端
     * @return
     */
    bool   IsBigEnd(){return(m_bIsBigEnd);}

    /**
     * @brief 是否初始化
     * @return
     */
    bool   IsInit(){return(m_bInit);}

    /**
     * @brief 初始化信息
     */
    void Init();

private:
    CGetMachineInfo();

private:
    QStringList m_listMacInfo;   /// 网卡信息
    QString       m_sCupID;        /// CPU 信息
    QString       m_sHardSN;     /// 磁盘sn

    bool             m_bInit;              /// 是否初始化
    bool             m_bIsBigEnd;   /// 是否是大端
};

#endif // GETMACHINEINFO_H
