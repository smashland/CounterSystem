#ifndef JUDGELICENSE_H
#define JUDGELICENSE_H

#include <QQuickItem>

class QJudgeLicense : public QQuickItem
{
    Q_OBJECT
public:
    QJudgeLicense(QQuickItem *parent=nullptr);
    ~QJudgeLicense();

    Q_INVOKABLE void checkLicense();
    Q_INVOKABLE void saveLicense(const QByteArray &sLicInfo);
    Q_INVOKABLE QString getMD5MachineInfo();
    Q_INVOKABLE QString read();
    Q_INVOKABLE bool checkLicense(const QByteArray &sLicInfo);
    Q_INVOKABLE bool isFileExist();
    Q_INVOKABLE void deleteFile();


signals:
    void checked();
    void showError(const QString& sErrorInfo);
private:
    void getMachineInfo();
//    bool checkLicense(const QByteArray &sLicInfo);

private:
    QByteArray m_sLicInfo;
    std::string m_sMachineInfo;
    QString    m_sErrorInfo;
    bool       m_bGet;
};

#endif // JUDGELICENSE_H
