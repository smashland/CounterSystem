#ifndef NOTICEMANAGER_H
#define NOTICEMANAGER_H
/************************
 * 事件管理类
 ************************/
#include <QColor>

class CSpeakText;
class QString;
class QAppGlobal;
class CPlayMp3;

class CNoticeManager
{
public:
    static CNoticeManager* GetInstance();

    /**
     * @brief 设置阵营颜色id
     * @param typeId
     */
    void SetGroupId(int typeId);
    void SetColor(int typeId,QString color);

    /**
     * @brief 设置通知信息
     * @param sNoticeInfo
     */
    void SetNoticInfo(const QString& sNoticeInfo);

    /**
     * @brief 打开语音播报
     * @return 返回语音播报开启状态
     */
    bool OpenSpeak(bool bOpen);

    /**
     * @brief 语音播报是否开启
     * @return
     */
    bool IsSpeakOpen(){return(m_bOpenSpeak);}

    /**
     * @brief 设置声音大小
     */
    void SetVolume(double dVolume);

    /**
     * @brief 显示布告板
     */
    void ShowNoticeBoard(bool bShow);

    /**
     * @brief 布告板是否开启
     * @return
     */
    bool IsNoticeBoardShow(){return(m_bShowBoard);}

    /**
     * @brief 移动显示位置
     * @param nX
     * @param nY
     */
    void MoveBoardPos(int nX, int nY);

    /**
     * @brief 设置全局的
     * @param pGlobal
     */
    void SetGlobal(QAppGlobal* pGlobal);

    /**
     * @brief 播放声音
     * @param nIndex 声音索引
     */
    void PlaySound(int nIndex);
private:
    CNoticeManager();
    ~CNoticeManager();

private:
    bool  m_bOpenSpeak=true;  /// 是否开启语音播报
    bool  m_bShowBoard=true;   /// 是否显示布告板
    CSpeakText* m_pSpeak{}; /// 语音播报控制
    CPlayMp3*   m_pPlay{};
    QAppGlobal* m_pGLobal{};
    QColor m_stColor;
};

#endif // NOTICEMANAGER_H
