#ifndef APPGLOBAL_H
#define APPGLOBAL_H

#include <QObject>
#include "Settings/GlobalSettings.h"
#include "DataManager/GlobalData.h"
#include <QTextCodec>
#include "NoticInfo.h"

class QQuickItem;

class QAppGlobal : public QObject
{
    Q_OBJECT
public:
    explicit QAppGlobal(QObject *parent = nullptr);
    Q_PROPERTY(QString appPath MEMBER m_sAppPath NOTIFY appPathChanged)
    Q_PROPERTY(QString localUrl MEMBER m_sLocalUrl NOTIFY urlChanged)
    Q_PROPERTY(QString webFont MEMBER m_sWebFontFamily NOTIFY webFontChanged)
    Q_PROPERTY(CGlobalSettings* settings MEMBER m_pSettings NOTIFY settingsChanged)
    Q_PROPERTY(CGlobalData* allData MEMBER m_pData NOTIFY dataChanged)

    Q_PROPERTY(QString replayName MEMBER m_sReplayName)
    Q_PROPERTY(QString replayTime MEMBER m_sReplayTime)
    Q_PROPERTY(QColor typeColor MEMBER m_typeColor NOTIFY typeColorChanged)
    Q_PROPERTY(bool openSpeak MEMBER m_bopenSpeak NOTIFY openSpeakChanged)

    Q_PROPERTY(bool openChonglian MEMBER m_bopenChonglian NOTIFY openChonglianChanged)
    Q_PROPERTY(QList<QObject*> noiceList MEMBER m_slistNoice NOTIFY noiceChanged)

    Q_PROPERTY(double  dAveLat MEMBER m_dAveLat NOTIFY aveLatChanged)
    Q_PROPERTY(double  dAveLon MEMBER m_dAveLon NOTIFY aveLonChanged)

    /**
     * @brief 退出app
     */
    Q_INVOKABLE void exitApp();
    Q_INVOKABLE void initSystem();
    Q_INVOKABLE void startConnect();
    Q_INVOKABLE void changeEarth();

    void updateNotic(const QString & rInfo);
    void setAppPath(QString sAppPath);
    void setLocalUrl(QString sUrl);
    void setWebFont(QString sFamilyName);
    void setSettings(CGlobalSettings* pSettings);
    void setData(CGlobalData* pData);
    Q_INVOKABLE void setOsgItem(QQuickItem* pOsgItem);

    ///帮助文档
    Q_INVOKABLE QString copyFile(const QString &strImagePath, const QString &folderName = "Help");
    Q_INVOKABLE QStringList openHelp();
    Q_INVOKABLE void openFile(const QString &strHelpFileName);
    Q_INVOKABLE bool removeHelpFile(const QString &strHelpFileName);

    ///回放文件
    Q_INVOKABLE QStringList openPath();
    /// 是否开启语音
    Q_INVOKABLE void setOpenSpeak(bool);
    Q_INVOKABLE bool getOpenSpeak();

    ///击杀情况清空
    Q_INVOKABLE void setClearNoticText();
    void setGroupId(int typeID);

    ///得到人员的平均位置
    Q_INVOKABLE void setAveLocation();

signals:
    /**
     * @brief 退出系统信号
     */
    void exitSystem();
    void appPathChanged(QString sAppPath);
    void urlChanged(QString sUrl);
    void webFontChanged(QString sWebFont);
    void settingsChanged(CGlobalSettings* pGlobalSetting);
    void dataChanged(CGlobalData* pGlobalData);
    void connected();
    void disConnected();
    void notic(QString sNoticInfo);
    void typeColorChanged();
    void replayChanged();
    void openSpeakChanged();
    void openChonglianChanged();
    void noiceChanged();
    void aveLatChanged(double);
    void aveLonChanged(double);

public slots:
private:
    QString m_sAppPath;       /// app所在路径
    QString m_sLocalUrl;      /// 本地文件所在的url
    QString m_sWebFontFamily; /// web字体名
    CGlobalSettings* m_pSettings; /// 设置对象
    CGlobalData*     m_pData;    /// 数据对象
    QQuickItem*      m_pOsgItem=nullptr; /// 设置绑定的osg显示

    QString         m_sReplayName;
    QString         m_sReplayTime;

    QColor          m_typeColor;       ///分组的颜色
    bool            m_bopenSpeak;      ///开启语音

    bool            m_bopenChonglian;      /// 打开自动重连

    QList<QObject*> m_slistNoice;          ///播报内容
    double          m_dAveLat=0.0;          ///平均纬度
    double          m_dAveLon=0.0;          ///平均经度
};

Q_DECLARE_METATYPE(CGlobalSettings*)
Q_DECLARE_METATYPE(CGlobalData*)

#endif // APPGLOBAL_H
