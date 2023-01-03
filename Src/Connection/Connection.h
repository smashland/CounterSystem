#ifndef _YTY_CONNECTION_H__
#define _YTY_CONNECTION_H__

#include <QObject>
#include <QList>
#include <QByteArray>

/**
 * @brief 与外部连接的通信基类
 */
class CConnection:public QObject
{
    Q_OBJECT
public:
    CConnection(QObject* parent=nullptr);
    virtual ~CConnection();

    /**
     * @brief 发送信息
     * @param rByteArray 信息字符串
     * @return 命令发送成功则 返回 true 失败 则返回 false
     */
    virtual bool SendCommand(const QByteArray&){return(false);}

    /**
     * @brief 获取一条数据
     * @return
     */
     const QByteArray& GetData();

     /**
      * @brief 当前是否处于连接状态
      * @return
      */
     bool IsConnect(){return(m_bConnected);}

     /**
      * @brief 连接
      * @return
      */
     virtual void Connect()=0;

     /**
      * @brief 断开连接
      * @return
      */
     virtual void DisConnect();

     /**
      * @brief 清空数据
      */
     void ClearData();


signals:
     void connected2Center();
     void lostConnected2Center();

public slots:
     void connected();
     void disConnected();

protected:
    /**
     * @brief 添加信息
     * @param rData
     */
    void InsertData(const QByteArray& rData);

protected:
    QList<QByteArray> m_listReciveInfo; /// 保存所有的信息
    bool              m_bConnected;   /// 当前是否处于连接状态
};

#endif /// _YTY_CONNECTION_H__
