#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QLocale>
#include <QTranslator>
#include <QFontDatabase>
#include <GisMath/GisMath.h>
#include <ISceneCore.h>
#include <Qml/QtOsgItem.h>
#include "Src/JudgeValid/JudgeLicense.h"
#include "Src/JudgeValid/MyRectageItem.h"
#include "Src/JudgeValid/Blur.h"
#include "Src/AppGlobal.h"
#include "Src/SingleApplication/SingleApplication"
#include "Src/SceInfo/SceManager.h"
#include "Src/SceInfo/ScePersonInfo.h"
#include "Src/SceInfo/SceInfo.h"

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    SingleApplication app(argc, argv,true);
    QFontDatabase::addApplicationFont(":/font/iconfont.ttf");

    if(app.isSecondary() )
    {
        app.sendMessage( app.arguments().join(' ').toUtf8());
        app.exit(0);
        return(-2);
    }
    bool bChecked = CheckPC(argv);
    if(!bChecked)
    {
        return(-1);
    }

    GisMath::InitGis(GisMath::WGS_84);

    /// 注册C++类变成 qml类型
    qmlRegisterType<QJudgeLicense>("MyItem",1,0,"LicItem");
    qmlRegisterType<QMyRectageItem>("MyItem",1,0,"Rect");
    qmlRegisterType<QAppGlobal>("MyItem",1,0,"AppGlobal");
    qmlRegisterType<QmlBlur>("MyItem",1,0,"Blur");
    qmlRegisterType<QtOsgItem>("SceneGraphRendering", 1, 0, "QuickOSGViewer");
    qmlRegisterType<SceManager>("MyItem",1,0,"SceManager");
    qmlRegisterType<CSceInfo>("MyItem",1,0,"SceInfo");

    qRegisterMetaType<ScePersonInfo*>("ScePersonInfo*");
    qRegisterMetaType<CSceInfo*>("CSceInfo*");
    qRegisterMetaType<SceManager*>("SceManager*");

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages)
    {
        const QString baseName = "CounterSystem_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName))
        {
            app.installTranslator(&translator);
            break;
        }
    }

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("appDir",qApp->applicationDirPath());
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl)
    {
        if (!obj && url == objUrl)
        {
            QCoreApplication::exit(-1);
        }
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
