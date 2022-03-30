#ifndef GETMACHINEINFO_H
#define GETMACHINEINFO_H
#include <QStringList>

class CGetMachineInfo
{
public:
    static CGetMachineInfo* GetInstance();

    /**
     * @brief ��ȡ������Ϣ
     * @return
     */
    const QStringList& GetMacInfo(){return(m_listMacInfo);}

    /**
     * @brief ��ȡcpuID
     * @return
     */
    const QString&       GetCpuID(){return(m_sCupID);}

    /**
     * @brief ��ȡ�������к�
     * @return
     */
    const QString&       GetHDSN(){return(m_sHardSN);}

    /**
     * @brief CPU�Ƿ��Ǵ��
     * @return
     */
    bool   IsBigEnd(){return(m_bIsBigEnd);}

    /**
     * @brief �Ƿ��ʼ��
     * @return
     */
    bool   IsInit(){return(m_bInit);}

    /**
     * @brief ��ʼ����Ϣ
     */
    void Init();

private:
    CGetMachineInfo();

private:
    QStringList m_listMacInfo;   /// ������Ϣ
    QString       m_sCupID;        /// CPU ��Ϣ
    QString       m_sHardSN;     /// ����sn

    bool             m_bInit;              /// �Ƿ��ʼ��
    bool             m_bIsBigEnd;   /// �Ƿ��Ǵ��
};

#endif // GETMACHINEINFO_H
