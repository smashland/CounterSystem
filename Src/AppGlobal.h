#ifndef APPGLOBAL_H
#define APPGLOBAL_H

#include <QObject>
#include "Settings/GlobalSettings.h"
#include "DataManager/GlobalData.h"

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

    /**
     * @brief 退出app
     */
    Q_INVOKABLE void exitApp();
    Q_INVOKABLE void initSystem();
    Q_INVOKABLE void startConnect();

    void updateNotic(const QString & rInfo);
    void setAppPath(QString sAppPath);
    void setLocalUrl(QString sUrl);
    void setWebFont(QString sFamilyName);
    void setSettings(CGlobalSettings* pSettings);
    void setData(CGlobalData* pData);
    Q_INVOKABLE void setOsgItem(QQuickItem* pOsgItem);


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

public slots:
private:
    QString m_sAppPath;       /// app所在路径
    QString m_sLocalUrl;      /// 本地文件所在的url
    QString m_sWebFontFamily; /// web字体名
    CGlobalSettings* m_pSettings; /// 设置对象
    CGlobalData*     m_pData;    /// 数据对象
    QQuickItem*      m_pOsgItem=nullptr; /// 设置绑定的osg显示
};

Q_DECLARE_METATYPE(CGlobalSettings*)
Q_DECLARE_METATYPE(CGlobalData*)

#endif // APPGLOBAL_H
