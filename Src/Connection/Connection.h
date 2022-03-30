#ifndef _YTY_CONNECTION_H__
#define _YTY_CONNECTION_H__

#include <QObject>
#include <QList>
#include <QByteArray>

/**
 * @brief ���ⲿ���ӵ�ͨ�Ż���
 */
class CConnection:public QObject
{
    Q_OBJECT
public:
    CConnection(QObject* parent=nullptr);
    virtual ~CConnection();

    /**
     * @brief ������Ϣ
     * @param rByteArray ��Ϣ�ַ���
     * @return ����ͳɹ��� ���� true ʧ�� �򷵻� false
     */
    virtual bool SendCommand(const QByteArray&){return(false);}

    /**
     * @brief ��ȡһ������
     * @return
     */
     const QByteArray& GetData();

     /**
      * @brief ��ǰ�Ƿ�������״̬
      * @return
      */
     bool IsConnect(){return(m_bConnected);}

     /**
      * @brief ����
      * @return
      */
     virtual void Connect()=0;

     /**
      * @brief �Ͽ�����
      * @return
      */
     virtual void DisConnect();

     /**
      * @brief �������
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
     * @brief �����Ϣ
     * @param rData
     */
    void InsertData(const QByteArray& rData);

protected:
    QList<QByteArray> m_listReciveInfo; /// �������е���Ϣ
    bool              m_bConnected;   /// ��ǰ�Ƿ�������״̬
};

#endif /// _YTY_CONNECTION_H__
