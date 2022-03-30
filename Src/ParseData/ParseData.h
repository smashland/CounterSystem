#ifndef PARSEDATA_H
#define PARSEDATA_H

#include "../CommonTypeDefine.h"
/**
 * @brief �������ݻ���
 */

#include <QByteArray>
#include <QVariant>

class CParseData
{
public:
    CParseData();
    virtual ~CParseData();

    /**
     * @brief ��������
     * @param rArray
     * @return
     */
    virtual bool ParseData(const QByteArray&);

    /**
     * @brief ����ʱ��
     */
    virtual void UpdateSeconds(const quint16& unSeconds);

    /**
     * @brief ����ݴ�״̬
     */
    virtual void Clear(){}

    /**
     * @brief ͬ��ʱ��
     */
    virtual void AllSycTime(quint16){}
    virtual void PersonalSycTime(quint16,quint16){}

    /**
     * @brief ��ϰ��ʼ
     */
    virtual void AllStart();
    virtual void SetStart(quint16){}

    /**
     * @brief ��ϰ����
     */
    virtual void AllStop();
    virtual void SetStop(quint16){}

    /**
     * @brief ����
     * @param unID
     */
    virtual void PersonalPanSi(quint16){}

    /**
     * @brief ����
     * @param unID
     */
    virtual void PersonalFuHuo(quint16){}

    /**
     * @brief ���˱���ֵ
     */
    virtual void Damage(const QVariant&){}

    /**
     * @brief ���������˵�����ǹ
     * @brief ���������˵�ĳ��ǹ
     */
    virtual void AllBiSuo(){}
    virtual void AllBiSuo(const QVariant&){}

    /**
     * @brief ����ĳ���˵�����ǹ
     * @brief ����ĳ���˵�ĳЩǹ
     * @param unID
     */
    virtual void PersonalBiSuo(quint16){}
    virtual void PersonalBiSuo(quint16 ,const QVariant&){}

    /**
     * @brief ���������˵�����ǹ
     * @brief ���������˵�ĳЩǹ
     */
    virtual void AllJieSuo(){}
    virtual void AllJieSuo(const QVariant&){}

    /**
     * @brief ����ĳ���˵�����ǹ
     * @brief ����ĳ���˵�ĳЩǹ
     * @param unID
     */
    virtual void PersonalJieSuo(quint16 ){}
    virtual void PersonalJieSuo(quint16 ,const QVariant& ){}

    /**
     * @brief �����е��˳䵯
     */
    virtual void AllChongDan(const QVariant&){}
    virtual void PersonalChongDan(quint16,const QVariant&){}

    /**
     * @brief ������ʾ
     * @param unID
     * @param hitInfo
     */
    virtual void HitNotice(quint16,const QVariant&){}

    /**
     * @brief ����԰�
     */
    virtual void AllPangBai(){}

    /**
     * @brief ����ʱ��
     */
    virtual void AllSetSimTime(quint16){}
    virtual void PersonSimTime(quint16,quint16){}

    /**
     * @brief ��ǹ
     */
    virtual void AllPeiQiang(const QVariant&){}
    virtual void PersonalPeiQiang(quint16,const QVariant&){}

    /**
     * @brief ʱ��У׼
     */
    virtual void CalibrationCharge(quint16){}

    /**
     * @brief ����������ģʽ
     */
    virtual void Open3rd(){}
    virtual void Close3rd(){}

    /**
     * @brief ��ѯ���е�״̬
     */
    virtual void QueryAll(){}

protected:
    /**
     * @brief ��ʼ��״̬
     */
    void InitState();

protected:
    static uint C_BUFFER_LENGTH;  /// Ĭ�ϻ����С
    bool    m_bBegin;       /// �Ƿ��Ѿ���ʼ
    quint16 m_unSeconds;   /// ��ǰ������
    quint16 m_unID;        /// ��ǰλ��

    uchar* m_pBuffer;      /// �������ݳ���
    int   m_nDataLength;  /// ���ݳ���
    int   m_nDataGet;     /// ��ǰ��ȡ��������
    int   m_nNowLength;   /// ��ȡ���ݳ���

    uchar m_ucType;  /// ��������
    stAddr m_stAddr; /// �豸��ַ
    QVariant m_vaInfo; /// ��Ҫ���õ���Ϣ
};

#endif // PARSEDATA_H
