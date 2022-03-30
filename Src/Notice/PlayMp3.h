#ifndef CPLAYMP3_H
#define CPLAYMP3_H

class QMediaPlayer;

class CPlayMp3
{
public:
    CPlayMp3();
    ~CPlayMp3();

    /**
     * @brief 设置声音大小
     * @param nVolume
     */
    void SetVolume(int nVolume);

    /**
     * @brief 播放第几个声音
     */
    void Play(int nIndex);

private:
    QMediaPlayer* m_pPlayer{};
};

#endif // CPLAYMP3_H
