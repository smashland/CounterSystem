#ifndef NOTICMANGER_H
#define NOTICMANGER_H

#include <QObject>
#include "NoticInfo.h"

class NoticManger : public QObject
{
    Q_OBJECT
public:
    explicit NoticManger(QObject *parent = nullptr);

    void saveNoticeFile(const QString &noticPath);
    void praseNoticInfo(const QString& fileName);
    void addNoticInfo(const QString &noticText);
    Q_INVOKABLE bool deleteNoticInfo(const QString& fileName);

    QStringList listNoticInfo(); //播报语音

    void clearNoticInfo();
    void deleteNoticInfo();

signals:

private:
    QList<QObject*> m_listNotic;
    QMap<int,QString> m_mapNum2NoticInfo;

    QStringList m_slistNotic;
signals:

};

#endif // NOTICMANGER_H
