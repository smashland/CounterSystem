#ifndef CEXPORTRESULT_H
#define CEXPORTRESULT_H

#include <QString>

class CMyListModel;
class CGlobalSetting;

class CExportResult
{
public:
    /**
     * @brief ��ȡ����
     * @return
     */
    static CExportResult* GetInstance();

    /**
     * @brief �����ĵ�
     */
    void CreateDocx(const QString& sFileName, const QString &sTile, const QMap<QString,CMyListModel*>& rInfo);

    /**
     * @brief ���ص����ı��·��
     * @return
     */
    const QString& GetPath();

protected:
    CExportResult();
    ~CExportResult();
private:
    QString               m_sReportPath;  /// ������Ŀ¼
    static CExportResult* S_PInstance;    /// ����ָ��
};

#endif // CEXPORTRESULT_H
