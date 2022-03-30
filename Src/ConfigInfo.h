#ifndef CCONFIGINFO_H
#define CCONFIGINFO_H
#include <QString>
#include <QDateTime>
#include <QMap>
#include <QHostAddress>
#include "CommonTypeDefine.h"

class Config;
/**
 * @brief ���������������Ϣ
 */
class CConfigInfo
{
public:
    /**
     * @brief ��ȡΨһʵ��
     * @return ���ú���ָ��
     */
    static CConfigInfo* GetInstance();

    /**
     * @brief ��ȡ������Ϣ
     * @return
     */
    QString& GetComName(){return(m_stComName);}

    /**
     * @brief ��ȡ�жϵ��ߵĴ���
     * @return
     */
    int&  GetDroppedTimes(){return(m_nDroppedTimes);}

    /**
     * @brief ��ȡͬ��ʱ��
     * @return
     */
    int&  GetSynTimes(){return(m_nSynTimes);}

    /**
     * @brief �������ʱ��
     */
    void CalOfflineTime();

    /**
     * @brief ��ȡ����ʱ��
     * @return
     */
    int GetOfflineTime();

    /**
     * @brief ��ȡ�ط�����
     * @return
     */
    int&  GetResendTimes(){return(m_nResendTimes);}

    /**
     * @brief ��ȡĬ���ӵ���
     * @return
     */
    int&  GetDefaultBullets(){return(m_nDefaultBullets);}


    /**
     * @brief ��ȡ�Ƿ���ϰ��ʼ
     * @return
     */
    bool& GetStart(){return(m_bStart);}

    /**
     * @brief ��ȡ��ʼ����
     * @return
     */
    QDateTime& GetDateTime(){return(m_qStartDateTime);}

    /**
     * @brief ��ȡ����ߵ�ɾ��ʱ��
     * @return
     */
    int& GetDelHitLineSecs(){return (m_nHitLineDelSec);}

    /**
     * @brief ��ȡϵͳ�д��������б�
     * @return
     */
    QStringList GetComNameList();

    /**
     * @brief �Ƿ��������˺�
     * @return
     */
    bool&  IsAllowKillSelf(){return(m_bKillSelf);}

    /**
     * @brief ���������Ƿ���Ч
     * @return
     */
    bool&  CanHitDeath(){return(m_bCanHitDeath);}

    /**
     * @brief ��ȡIP��ַ
     * @return
     */
    void SetIP(const QString& sIP);
    const std::string& GetIP();

    /**
     * @brief ��ö˿ں�
     * @return
     */
    uint GetPort();
    void SetPort(uint nPort);

    /**
     * @brief ��ȡͨ������
     * @return
     */
    int  GetConnectionType();

    /**
     * @brief �������е÷����
     * @param nType
     * @return
     */
    int GetHurtMark(int nType);
    int CalHurtMark(int nHurtType);
    void SetHurtMark(int nIndex,int nValue);

    /**
     * @brief ������������ֵ�������
     * @param nType
     * @return
     */
    int GetHitDamage(int nType);
    int CalHitDamage(int nHurtType);
    void SetHitDamae(int nIndex,int nValue);
    void AllSetHitDamae();

    /**
     * @brief ��ȡ���Ͷ�Ӧ��������
     * @param nType
     * @return
     */
    const QString& GetBodyName(int nType);

    /**
     * @brief �ж��Ƿ��ڻط�״̬
     * @return
     */
    bool &GetIsReplay();
private:
    /**
     * @brief ����INI�ļ�
     */
    void PraseIni();

    /**
     * @brief ����ini�ļ�
     */
    void SaveIni();

    /// ���캯��
    CConfigInfo();
    ~CConfigInfo();

private:
    int     m_nDroppedTimes;   /// ������û�л��������Ϣ������Ϊ����
    int     m_nSynTimes;       /// ͬ��ʱ��
    int     m_nResendTimes;    /// �����ط�����
    int     m_nDefaultBullets; /// Ĭ���ӵ���
    int     m_nHitLineDelSec;  /// ɾ������ߵ�ʱ��
    int     m_nType;           /// ����
    int     m_nOfflineTime;    /// ����ʱ��
    bool    m_bStart;          /// �Ƿ�ʼ��ϰ
    bool    m_bKillSelf;       /// �Ƿ���������˺�
    bool    m_bCanHitDeath;    /// �����������Ƿ�÷�
    bool    m_bReplay;         /// �Ƿ������ݻط�״̬
    std::string m_sFileName;   /// �����ļ�����


    QString         m_stComName;      /// ������Ϣ
    QDateTime       m_qStartDateTime; /// �����ʼʱ��ʱ��

    QHostAddress            m_addrTcp;     /// IP ��ַ
    ushort                  m_unPort;      /// �󶨶˿ں�

    Config*          m_pConfig;       /// ������Ϣ
    QVector<int>     m_vHurtMark;          /// �÷����
    QVector<int>     m_vHitDamea;          /// �˺�ֵ
};

#endif // CCONFIGINFO_H
