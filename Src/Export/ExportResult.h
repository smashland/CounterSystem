 #ifndef CEXPORTRESULT_H
#define CEXPORTRESULT_H

#include <QString>

class CMyListModel;
class CGlobalSetting;

class CExportResult
{
public:
    /**
     * @brief 获取单例
     * @return
     */
    static CExportResult* GetInstance();

    /**
     * @brief 创建文档
     */
    void CreateDocx(const QString& sFileName, const QString &sTile, const QMap<QString,CMyListModel*>& rInfo);

    /**
     * @brief 返回导出的表格路径
     * @return
     */
    const QString& GetPath();

protected:
    CExportResult();
    ~CExportResult();
private:
    QString               m_sReportPath;  /// 导出的目录
    static CExportResult* S_PInstance;    /// 单例指针
};

#endif // CEXPORTRESULT_H
