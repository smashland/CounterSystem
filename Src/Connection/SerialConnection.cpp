#include <QSerialPort>
#include <QSerialPortInfo>
#include "SerialConnection.h"
#include "../ConfigInfo.h"

/// ���캯��
CControlSerial::CControlSerial(QObject *parent)
    :CConnection(parent)
    ,m_pSerialPort(new QSerialPort(this))
{
    connect(m_pSerialPort,SIGNAL(readyRead()),this,SLOT(ReadComData()));
}

/// ��������
CControlSerial::~CControlSerial()
{
    m_pSerialPort->deleteLater();
}

/// �������ô�������
bool CControlSerial::ReConfigSerialInfo()
{
    CConfigInfo* pConfigInfo = CConfigInfo::GetInstance();

    /// ������ڿ��ţ���ر�
    if(m_pSerialPort->isOpen())
    {
        m_pSerialPort->close();
    }

    /// ���������ļ����ô���
    if(pConfigInfo)
    {
        /// ���ô�������
        m_pSerialPort->setPortName(pConfigInfo->GetComName());

        /// ���ò�����
        m_pSerialPort->setBaudRate(QSerialPort::Baud115200);

        /// ��������λ
        m_pSerialPort->setDataBits(QSerialPort::Data8);

        /// ����У��λ
        m_pSerialPort->setParity(QSerialPort::NoParity);


        /// ֹͣλ
        m_pSerialPort->setStopBits(QSerialPort::OneStop);

        /// ����ͨ������
        m_pSerialPort->setFlowControl(QSerialPort::NoFlowControl);

        /// �򿪴���
        if(m_pSerialPort->open(QIODevice::ReadWrite))
        {
            return(true);
        }
        else
        {
            return(false);
        }
    }

    return(false);

}

/// ��ȡ��������
void CControlSerial::ReadComData()
{
    if(m_pSerialPort->bytesAvailable() < 1)
    {
        return;
    }

    QByteArray temp = m_pSerialPort->readAll();
    InsertData(temp);
}


/// ��������
bool CControlSerial::SendCommand(const QByteArray& rByteArray)
{
    static qint64 nSendSize;

    /// ֻ�����ӵ�����ʱ���ŷ�������
    if(m_bConnected)
    {
        nSendSize = m_pSerialPort->write(rByteArray);
        m_pSerialPort->flush();
        return(nSendSize == rByteArray.size());
    }

    return(false);
}

/// ����
void CControlSerial::Connect()
{
    m_bConnected = ReConfigSerialInfo();

    if(m_bConnected)
    {
        connected();
    }
    else
    {
        disConnected();
    }
}

/// �Ͽ�����
void CControlSerial::DisConnect()
{
    m_pSerialPort->close();

    CConnection::DisConnect();
}
