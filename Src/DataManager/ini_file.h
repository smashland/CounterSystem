#ifndef INI_FILE_H
#define INI_FILE_H

#include <QString>
#include <QSettings>

class INI_File
{
public:
    INI_File();
    ~INI_File();
    void CreateFile(QString qstrFilePath, QString qstrFileName);

    /**
     * @brief 开始时间
     * @return
     */
    void SetBeginTime(QString sBeginTime);
    QString GetBeginTime();
    /**
     * @brief 结束时间
     * @return
     */
    void SetEndTime(QString sEndinTime);
    QString GetEndTime();

private:
    QString m_qstrFileName;
    QSettings *m_psetting;
};

#endif // INI_FILE_H
