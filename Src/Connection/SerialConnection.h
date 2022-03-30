#ifndef CCONTROLSERIAL_H
#define CCONTROLSERIAL_H
///////////////////////////////////////////////////////
///  ���ฺ���ȡ��������
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
     * @brief �������ô�����Ϣ
     */
    bool ReConfigSerialInfo();


    /**
     * @brief ��������
     * @param pData  ����ָ��
     * @param nLength ���ݳ���
     * @return
     */
    bool SendCommand(const QByteArray& rByteArray);

    /**
     * @brief ���Ӵ���
     */
    void Connect();

    /**
     * @brief �Ͽ�����
     * @return
     */
    void DisConnect();

private slots:
    /**
     * @brief �Ӵ��ڶ�ȡ����
     */
    void ReadComData();

private:
    QSerialPort* m_pSerialPort;  /// ����ͨ��
};

#endif // CCONTROLSERIAL_H
