#ifndef WIFICONNECTION_H
#define WIFICONNECTION_H

#include "Connection.h"

class QTcpSocket;

/**
 * @brief 实现链接的相关方法
 */
class CWifiConnection:public CConnection
{
public:
    CWifiConnection(QObject* parent=nullptr);
    ~CWifiConnection();

    /**
     * @brief 连接
     * @return
     */
    void Connect();

    /**
     * @brief 断开连接
     * @return
     */
    void DisConnect();

    /**
     * @brief 发送命令
     * @param rByteArray
     * @return
     */
    bool SendCommand(const QByteArray& rByteArray);

private slots:
    /**
     * @brief 接收到数据
     */
    void ReciveData();

private:
    QTcpSocket* m_pTcp;  /// wifi通过tcp连接
};

#endif // WIFICONNECTION_H
