#include <QCoreApplication>
#include <QDateTime>
#include "ErrorReport.h"
CErrorReport* CErrorReport::s_pErrorReport(nullptr);

CErrorReport *CErrorReport::GetInstance()
{
    if(nullptr == s_pErrorReport)
    {
        s_pErrorReport = new CErrorReport;
    }
    return(s_pErrorReport);
}

void CErrorReport::writeError(const QString &sErrorInfo)
{
    if(m_bOpend)
    {
        m_pLog->write(QTime::currentTime().toString("hh:mm:ss:").toUtf8());
        m_pLog->write(sErrorInfo.toUtf8());
        m_pLog->write("\n");
        m_pLog->flush();
    }
}

CErrorReport::CErrorReport():m_pLog(new QFile)
{
    m_pLog->setFileName(QCoreApplication::applicationDirPath()+QDate::currentDate().toString("/yyyyMMdd.log"));
    m_bOpend = m_pLog->open(QIODevice::Append|QIODevice::Text);
}

CErrorReport::~CErrorReport()
{
    m_pLog->close();
    delete m_pLog;
}
