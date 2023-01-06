#ifndef CONNECTIONMANAGER_H
#define CONNECTIONMANAGER_H

#include "Connection.h"
#include "../DataManager/Config.pb.h"
/**
 * @brief 连接管理类
 */
class CConnectionManager:public QObject
{
    Q_OBJECT
public:
    /**
     * @brief 连接管理单例
     * @return
     */
    static CConnectionManager *GetInstance();

    /**
     * @brief 开始连接
     * @return
     */
    void Connect();

    /**
     * @brief 断开连接
     * @return
     */
    void DisConnect();

    /**
     * @brief 创建连接
     * @param emType
     * @return
     */
    bool InitConnection(CONN_TYPE emType);

    /**
     * @brief 是否初始化
     * @return
     */
    bool IsInit();

    /**
     * @brief 获取连接类型
     * @return
     */
    CONN_TYPE GetConnectionType(){return(m_emType);}

    /**
     * @brief 获取收到的数据
     * @return
     */
    const QByteArray& GetData();

    /**
     * @brief 发送数据
     * @param rSendInfo
     * @return
     */
    bool SendData(const QByteArray& rSendInfo);

    /**
     * @brief 当前是否连接
     * @return
     */
    bool IsConnect();

    /**
     * @brief 返回错误信息
     * @return
     */
    const QString& GetError(){return(m_sLastError);}

    void ClearData();
signals:
    void conected();
    void disConnected();

protected:
    void timerEvent(QTimerEvent *event);

private:
    CConnectionManager();
    ~CConnectionManager();
protected slots:
    void connectionLost();
private:

    QString            m_sLastError;     /// 最后一个错误信息
    CConnection*       m_pConnection;    /// 默认的连接
    CONN_TYPE          m_emType;        /// 当前连接的 类型
    int                m_nTimerID{-1};
};

#endif // CONNECTIONMANAGER_H
