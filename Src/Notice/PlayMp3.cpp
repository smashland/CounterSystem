#include <QMediaPlayer>
#include <ISceneCore.h>
#include "PlayMp3.h"

CPlayMp3::CPlayMp3()
{
    m_pPlayer = new QMediaPlayer;
    m_pPlayer->setVolume(30);
}

CPlayMp3::~CPlayMp3()
{
    m_pPlayer->deleteLater();
}

/// 设置声音大小
void CPlayMp3::SetVolume(int nVolume)
{
    if(nVolume != m_pPlayer->volume())
    {
        m_pPlayer->setVolume(nVolume);
    }
}

/// 播放第几个声音
void CPlayMp3::Play(int nIndex)
{
    if(nIndex < 1 || nIndex > 3) return;

    m_pPlayer->setMedia(QUrl::fromLocalFile(
                            QString::fromLocal8Bit("%1Sound\\%2.mp3")
                            .arg(GetDataPath().c_str())
                            .arg(nIndex)));
    m_pPlayer->play();
}
