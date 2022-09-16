#ifndef SCEINFO_H
#define SCEINFO_H

#include <QObject>
#include <QMainWindow>
#include <QJsonObject>
#include <QVector>
#include "ScesPerson.h"

//class SceInfo : public QObject
//{
//    Q_OBJECT
//public:
//    enum SaveFormat {
//        Json, Binary
//    };

//    explicit SceInfo(QObject *parent = nullptr);

//    QString name() const;

//    QVector<ScesPerson> sces() const;
//    void setSces(const QVector<ScesPerson> &sces);

//    void newGame();
//    bool loadGame(SaveFormat saveFormat);
//    bool saveGame(SaveFormat saveFormat) const;

//    void read(const QJsonObject &json);
//    void write(QJsonObject &json) const;

//    void print(int indentation = 0) const;

//signals:

//private:
//    QString m_Name;
//    QVector<ScesPerson> m_Sces/*m_ScePersonInfos*/;


//};

class SceInfo
{
public:
    SceInfo()=default;
    SceInfo(const QString &name);

    QString name() const;
//    void setname(QString name);

    QVector<ScesPerson> sces() const;
    void setSces(const QVector<ScesPerson> &sces);

    void read(const QJsonObject &json);
    void write(QJsonObject &json) const;

    void print(int indentation = 0) const;
private:
    QString m_Name;
    QVector<ScesPerson> m_Sces;

};

#endif // SCEINFO_H
