#ifndef CCONTROLSERIAL_H
#define CCONTROLSERIAL_H
///////////////////////////////////////////////////////
///  本类负责读取串口数据
///
///
///
///////////////////////////////////////////////////////
#include "Connection.h"

class QSerialPort;

class CControlSerial:public CConnection
{
    Q_OBJECT
public:
    CControlSerial(QObject* parent=nullptr);
    ~CControlSerial();

    /**
     * @brief 重新配置串口信息
     */
    bool ReConfigSerialInfo();


    /**
     * @brief 发送数据
     * @param pData  数据指针
     * @param nLength 数据长度
     * @return
     */
    bool SendCommand(const QByteArray& rByteArray);

    /**
     * @brief 连接串口
     */
    void Connect();

    /**
     * @brief 断开连接
     * @return
     */
    void DisConnect();

private slots:
    /**
     * @brief 从串口读取数据
     */
    void ReadComData();

private:
    QSerialPort* m_pSerialPort;  /// 串口通信
};

#endif // CCONTROLSERIAL_H
