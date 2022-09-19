#ifndef SPEAKTEXT_H
#define SPEAKTEXT_H

#include <QTextToSpeech>

class CSpeakText
{
public:
    CSpeakText();
    ~CSpeakText();

    /**
     * @brief 初始化
     */
    bool Init();

    /**
     * @brief 语音播报
     * @param sInfo
     * @return
     */
    bool SpeakText(const QString& sInfo);

    /**
     * @brief 设置声音大小
     * @param dVolume
     */
    void SetVolume(double dVolume);
private:
    QTextToSpeech *m_pSpeech; /// 处理声音
    bool m_bInit;            /// 是否初始化
    double m_dVolume;         /// 声音大小
};

#endif // SPEAKTEXT_H
