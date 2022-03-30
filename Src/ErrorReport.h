#ifndef ERRORREPORT_H
#define ERRORREPORT_H
#include <QFile>

class CErrorReport
{
public:
    static CErrorReport* GetInstance();

    void writeError(const QString& sErrorInfo);
protected:
    CErrorReport();
    ~CErrorReport();
private:
    QFile*       m_pLog;
    bool         m_bOpend;
    static CErrorReport* s_pErrorReport;
};

#endif // ERRORREPORT_H
