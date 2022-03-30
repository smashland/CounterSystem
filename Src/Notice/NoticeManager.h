#ifndef NOTICEMANAGER_H
#define NOTICEMANAGER_H
/************************
 * �¼�������
 ************************/

class CSpeakText;
class QString;
class QAppGlobal;
class CPlayMp3;

class CNoticeManager
{
public:
    static CNoticeManager* GetInstance();

    /**
     * @brief ����֪ͨ��Ϣ
     * @param sNoticeInfo
     */
    void SetNoticInfo(const QString& sNoticeInfo);

    /**
     * @brief ����������
     * @return ����������������״̬
     */
    bool OpenSpeak(bool bOpen);

    /**
     * @brief ���������Ƿ���
     * @return
     */
    bool IsSpeakOpen(){return(m_bOpenSpeak);}

    /**
     * @brief ����������С
     */
    void SetVolume(double dVolume);

    /**
     * @brief ��ʾ�����
     */
    void ShowNoticeBoard(bool bShow);

    /**
     * @brief ������Ƿ���
     * @return
     */
    bool IsNoticeBoardShow(){return(m_bShowBoard);}

    /**
     * @brief �ƶ���ʾλ��
     * @param nX
     * @param nY
     */
    void MoveBoardPos(int nX, int nY);

    /**
     * @brief ����ȫ�ֵ�
     * @param pGlobal
     */
    void SetGlobal(QAppGlobal* pGlobal);

    /**
     * @brief ��������
     * @param nIndex ��������
     */
    void PlaySound(int nIndex);
private:
    CNoticeManager();
    ~CNoticeManager();

private:
    bool  m_bOpenSpeak=true;  /// �Ƿ�����������
    bool  m_bShowBoard=true;   /// �Ƿ���ʾ�����
    CSpeakText* m_pSpeak{}; /// ������������
    CPlayMp3*   m_pPlay{};
    QAppGlobal* m_pGLobal{};
};

#endif // NOTICEMANAGER_H
