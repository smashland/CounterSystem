#include <QSerialPortInfo>
#include "SerialConnection.h"
#include "../ConfigInfo.h"

/// 构造函数
CControlSerial::CControlSerial(QObject *parent)
    :CConnection(parent)
    ,m_pSerialPort(new QSerialPort(this))
{
    connect(m_pSerialPort,SIGNAL(readyRead()),this,SLOT(ReadComData()));
    connect(m_pSerialPort,&QSerialPort::errorOccurred,this,&CControlSerial::ConnectError);
}

/// 析构函数
CControlSerial::~CControlSerial()
{
    m_pSerialPort->deleteLater();
}

/// 重新配置串口数据
bool CControlSerial::ReConfigSerialInfo()
{
    CConfigInfo* pConfigInfo = CConfigInfo::GetInstance();

    /// 如果串口开着，则关闭
    if(m_pSerialPort->isOpen())
    {
        m_pSerialPort->close();
    }

    /// 根据配置文件配置串口
    if(pConfigInfo)
    {
        /// 设置串口名称
        m_pSerialPort->setPortName(pConfigInfo->GetComName());

        /// 设置波特率
        m_pSerialPort->setBaudRate(QSerialPort::Baud115200);

        /// 设置数据位
        m_pSerialPort->setDataBits(QSerialPort::Data8);

        /// 设置校验位
        m_pSerialPort->setParity(QSerialPort::NoParity);


        /// 停止位
        m_pSerialPort->setStopBits(QSerialPort::OneStop);

        /// 设置通用数据
        m_pSerialPort->setFlowControl(QSerialPort::NoFlowControl);

        /// 打开串口
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

/// 获取串口数据
void CControlSerial::ReadComData()
{
    if(m_pSerialPort->bytesAvailable() < 1)
    {
        return;
    }

    QByteArray temp = m_pSerialPort->readAll();
    InsertData(temp);
}

void CControlSerial::ConnectError(QSerialPort::SerialPortError errorInof)
{
    switch(errorInof)
    {
    case QSerialPort::OpenError:
    case QSerialPort::PermissionError:
    case QSerialPort::DeviceNotFoundError:
        if(true == m_bConnected)
        {
            disConnected();
        }
        break;
    default:
        break;
    }
}


/// 发送命令
bool CControlSerial::SendCommand(const QByteArray& rByteArray)
{
    static qint64 nSendSize;

    /// 只有连接到串口时，才发送数据
    if(m_bConnected)
    {
        nSendSize = m_pSerialPort->write(rByteArray);
        m_pSerialPort->flush();
        return(nSendSize == rByteArray.size());
    }

    return(false);
}

/// 连接
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

/// 断开连接
void CControlSerial::DisConnect()
{
    m_pSerialPort->close();

    CConnection::DisConnect();
}


