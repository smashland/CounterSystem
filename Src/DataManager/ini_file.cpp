#include "ini_file.h"

#include <QtCore/QtCore>
#include <QFile>
#include <QDebug>

INI_File::INI_File()
{
    m_qstrFileName = QCoreApplication::applicationDirPath() + "/Data/Config/Config.txt";

    qDebug()<<"m_qstrFileName: "<<m_qstrFileName;

    //"Config.ini"配置文件，文件存在则打开，不存在则创建
    m_psetting = new QSettings(m_qstrFileName,QSettings::IniFormat);
}

INI_File::~INI_File()
{
    delete m_psetting;
    m_psetting = NULL;
}

///设置开始时间
void INI_File::SetBeginTime(QString sBeginTime)
{
    m_psetting->setValue("/Times/begin",sBeginTime);
}
QString INI_File::GetBeginTime()
{
    return m_psetting->value("/Times/begin").toString();
}
///设置结束时间
void INI_File::SetEndTime(QString sEndTime)
{
    m_psetting->setValue("/Times/end",sEndTime);
}
QString INI_File::GetEndTime()
{
    return m_psetting->value("/Times/end").toString();
}
