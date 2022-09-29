#include <QCoreApplication>
#include <QtXml>

class TestXml: public QObject
{
    Q_OBJECT

public:
    Q_INVOKABLE void writeXml(QString xmlPath);
};
