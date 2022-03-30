#ifndef WIFICONNECTION_H
#define WIFICONNECTION_H

#include "Connection.h"

class QTcpSocket;

/**
 * @brief ʵ�����ӵ���ط���
 */
class CWifiConnection:public CConnection
{
public:
    CWifiConnection(QObject* parent=nullptr);
    ~CWifiConnection();

    /**
     * @brief ����
     * @return
     */
    void Connect();

    /**
     * @brief �Ͽ�����
     * @return
     */
    void DisConnect();

    /**
     * @brief ��������
     * @param rByteArray
     * @return
     */
    bool SendCommand(const QByteArray& rByteArray);

private slots:
    /**
     * @brief ���յ�����
     */
    void ReciveData();

private:
    QTcpSocket* m_pTcp;  /// wifiͨ��tcp����
};

#endif // WIFICONNECTION_H
