#ifndef NOTICINFO_H
#define NOTICINFO_H

#include <QObject>
#include <QColor>

class NoticInfo : public QObject
{
    Q_OBJECT
public:
    explicit NoticInfo(QObject *parent = nullptr);
    Q_PROPERTY(QString noiceText READ getNoiceText WRITE setNoiceText NOTIFY noticTextChanged)
    Q_PROPERTY(QColor colorNotic READ getColorNotic WRITE setColorNotic NOTIFY colorNoticChanged)

    void setNoiceText(const QString& sNoice);
    QString getNoiceText(){return m_sNoticText;}
    void setColorNotic(const QColor& rColor);
    QColor getColorNotic(){return m_colorNotic;}


signals:
    void noticTextChanged();
    void colorNoticChanged();

private:
    QString m_sNoticText;
    QColor  m_colorNotic;

};

#endif // NOTICINFO_H
