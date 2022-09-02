#ifndef GLOBALSETTINGS_H
#define GLOBALSETTINGS_H

#include <QObject>
#include <QColor>
#include <QMap>
#include <QVariantMap>

class CGlobalData;
class CGlobalSettings : public QObject
{
    Q_OBJECT
public:
    explicit CGlobalSettings(QObject *parent = nullptr);
    Q_PROPERTY(QColor connectColor MEMBER m_qConnectColor NOTIFY connectColorChanged)
    Q_PROPERTY(QColor disConnColor MEMBER m_qDisConnectColor NOTIFY disConnColorChanged)
    Q_PROPERTY(int conType MEMBER m_nType)
    Q_PROPERTY(bool bIsStart MEMBER m_bIsStart NOTIFY startStatusChanged)
    Q_PROPERTY(bool bIsReplay MEMBER m_bIsReplay NOTIFY replayStatusChanged)
    Q_PROPERTY(QVariantList scoreSetting MEMBER m_scoreSetting NOTIFY scoreSettingChanged)
    Q_PROPERTY(QVariantList harmSetting MEMBER m_harmSetting NOTIFY harmSettingChanged)
    Q_PROPERTY(QVariantList systemSetting MEMBER m_sysSetting NOTIFY sysSettingChanged)

    Q_INVOKABLE QColor type2Color(const QString& sType);
    Q_INVOKABLE QColor type2BackColor(const QString& sType);
    Q_INVOKABLE QStringList types();
    Q_INVOKABLE int index(const QString& sType);
    Q_INVOKABLE QStringList comNameList();

    Q_INVOKABLE void setComName(const QString& sComName);
    Q_INVOKABLE void setWifiInfo(const QString& sIP, ushort unPort);

    Q_INVOKABLE void setStart();
    Q_INVOKABLE void setStop();
    Q_INVOKABLE void startReplay();
    Q_INVOKABLE void endReplay();

    Q_INVOKABLE QString getSysTime();


    Q_INVOKABLE void setBiSuo(quint16 nID); /// ����
    Q_INVOKABLE void setJiesuoSuo(quint16 nID); /// ����
    Q_INVOKABLE void setJieChu(quint16 nID);    /// ����԰�
    Q_INVOKABLE void setPanSi(quint16 nID);     /// ����
    Q_INVOKABLE void setFuHuo(quint16 nID);     /// ����
    Q_INVOKABLE void chongDan(quint16 nID,const QStringList& allInfo); /// �䵯
    Q_INVOKABLE void peiQiang(quint16 nID, int nGunID);  /// ��ǹ
    Q_INVOKABLE void sycTime(quint16 nID, quint16 nTime); /// ����ͬ��ʱ��
    Q_INVOKABLE void changeSetting(const QString& sListType,const int& rIndex,const int& rInt);

    void setConnectColor(const QColor& qConColor);
    void setDisConnColor(const QColor& qDisConColor);

    void SetGlobalData(CGlobalData* pGlobalData);


signals:
    void connectColorChanged(const QColor& qConColor);
    void disConnColorChanged(const QColor& qDisColor);
    void startStatusChanged(bool bIsStart);
    void replayStatusChanged(bool bReplay);
    void scoreSettingChanged(const QVariantList&);
    void harmSettingChanged(const QVariantList&);
    void sysSettingChanged(const QVariantList&);
public slots:
    void updateConfig();
private:
    CGlobalData* m_pGlobalData=nullptr;      /// ȫ������
    int    m_nType;                          /// ͨ������
    bool   m_bIsStart=false;                 /// �Ƿ���ϰ��ʼ
    bool   m_bIsReplay=false;                /// �Ƿ��ڻط�״̬
    QColor m_qConnectColor;                  /// ���ӵ�ʱ����ɫ
    QColor m_qDisConnectColor;               /// �Ͽ����ӵ�ʱ�����ɫ
    QMap<QString,QColor> m_mapType2Color;    /// ��������ɫ��ӳ���ϵ
    QMap<QString,QColor> m_mapType2BackColor;/// �����뱳����ɫ��ӳ���ϵ
    QVariantList         m_scoreSetting;     /// �÷�����
    QVariantList         m_harmSetting;      /// ��������
    QVariantList         m_sysSetting;       /// ϵͳ����
    QString              sBeginTime;
};

#endif // GLOBALSETTINGS_H
