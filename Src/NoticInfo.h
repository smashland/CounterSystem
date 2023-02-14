#ifndef NOTICINFO_H
#define NOTICINFO_H

#include <QObject>
#include <QJsonObject>
#include <QColor>

class NoticInfo : public QObject
{
    Q_OBJECT
public:
    explicit NoticInfo(QObject *parent = nullptr);
    Q_PROPERTY(QString noiceText READ getNoiceText WRITE setNoiceText NOTIFY noticTextChanged)
    Q_PROPERTY(QColor colorNotic READ getColorNotic WRITE setColorNotic NOTIFY colorNoticChanged)

    void setNoticNum(int sNoiceNum);
    int getNoticNum(){return m_nNoticNum;}
    void setNoiceText(const QString& sNoice);
    QString getNoiceText(){return m_sNoticText;}
    void setColorNotic(const QColor& rColor);
    QColor getColorNotic(){return m_colorNotic;}

    /**
     * @brief 将信息保存到Json对象中
     * @param rObj
     */
    void writeNoiceText(QJsonObject& rObj);

    /**
     * @brief 从json中读取
     * @param rObj
     */
    void readNoiceText(const QJsonObject& rObj);


signals:
    void noticTextChanged();
    void colorNoticChanged();

private:
    int     m_nNoticNum;
    QString m_sNoticText;
    QColor  m_colorNotic;

};

#endif // NOTICINFO_H
