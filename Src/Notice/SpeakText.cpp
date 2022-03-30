#include <QVector>
#include "SpeakText.h"

CSpeakText::CSpeakText()
    : m_pSpeech(new QTextToSpeech)
    , m_bInit(false)
    , m_dVolume(70)
{
}

CSpeakText::~CSpeakText()
{
    delete m_pSpeech;
}

/// ��ʼ������
bool CSpeakText::Init()
{
    if(m_bInit)
    {
        return(m_bInit);
    }

    QVector<QLocale> vLocales = m_pSpeech->availableLocales();
    foreach(QLocale locale,vLocales)
    {
        if(locale.language() == QLocale::Chinese)
        {
            m_pSpeech->setLocale(locale);

            QVector<QVoice> vVoice = m_pSpeech->availableVoices();
            if(vVoice.size() > 0)
            {
                m_pSpeech->setVoice(vVoice[0]);

                m_pSpeech->setPitch(0.);
                m_pSpeech->setRate(0.);
                m_pSpeech->setVolume(m_dVolume);

                m_bInit = true;
            }
            break;
        }
    }

    return(m_bInit);
}

/// ��������
bool CSpeakText::SpeakText(const QString &sInfo)
{
    if(m_bInit)
    {
        /// ȥ��������Ϣ
        m_pSpeech->say(sInfo.right(sInfo.size() - 9));
    }

    return(m_bInit);
}

/// ����������С
void CSpeakText::SetVolume(double dVolume)
{
    if(fabs(m_dVolume - dVolume) > 1e-8)
    {
        m_dVolume = dVolume < 0.0 ? 0.0 : dVolume;

        /// ����Ѿ���ʼ��
        if(m_bInit)
        {
            m_pSpeech->setVolume(m_dVolume);
        }
    }
}
