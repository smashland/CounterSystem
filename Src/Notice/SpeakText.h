#ifndef SPEAKTEXT_H
#define SPEAKTEXT_H

#include <QTextToSpeech>

class CSpeakText
{
public:
    CSpeakText();
    ~CSpeakText();

    /**
     * @brief ��ʼ��
     */
    bool Init();

    /**
     * @brief ��������
     * @param sInfo
     * @return
     */
    bool SpeakText(const QString& sInfo);

    /**
     * @brief ����������С
     * @param dVolume
     */
    void SetVolume(double dVolume);
private:
    QTextToSpeech *m_pSpeech; /// ��������
    bool m_bInit;            /// �Ƿ��ʼ��
    double m_dVolume;         /// ������С
};

#endif // SPEAKTEXT_H
