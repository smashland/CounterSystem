#include <QGuiApplication>
#include <QFontDatabase>

#include <ISceneCore.h>
#include <SceneGraph/ISceneGraphManager.h>
#include <Plot/Map/IMap.h>
#include <QDesktopServices>
#include <QResource>
#include <QUrl>
#include <QDir>
#include <QList>
#include <QTextCodec>
#include <QDebug>
#include <QMap>

#include "AppGlobal.h"
#include "TimeServer/TimeServer.h"
#include "ParseData/DealDataManager.h"
#include "Connection/ConnectionManager.h"
#include "DataManager/DataManager.h"
#include "Notice/NoticeManager.h"
#include "ConfigInfo.h"


QAppGlobal::QAppGlobal(QObject *parent) : QObject(parent)
{
    setObjectName("AppGlobal");
    m_sAppPath = QGuiApplication::applicationDirPath();
    m_sLocalUrl = "file:///";

    /// 加载web字体
    int fontId = QFontDatabase::addApplicationFont(":/Font/onlinewebfonts.ttf");
    if (QFontDatabase::applicationFontFamilies(fontId).count() > 0)
    {
        m_sWebFontFamily = QFontDatabase::applicationFontFamilies(fontId).at(0);
    }

    m_pSettings = new CGlobalSettings(this);
    m_pData = new CGlobalData(this);
    m_pSettings->SetGlobalData(m_pData);
}

/// 退出程序
void QAppGlobal::exitApp()
{
    CTimeServer::GetInstance()->Stop();
    emit(exitSystem());
}

/// 初始化系统
void QAppGlobal::initSystem()
{
    CConnectionManager::GetInstance()->InitConnection(static_cast<CONN_TYPE>(CConfigInfo::GetInstance()->GetConnectionType()));
    CTimeServer::GetInstance()->SubTime(CDealDataManager::GetInstance());
    CTimeServer::GetInstance()->SubTime(CDataManager::GetInstance());
    m_pData->InitGlobalData();
    CTimeServer::GetInstance()->Start();

    /// 初始化声音
    CNoticeManager::GetInstance()->OpenSpeak(true);
    CNoticeManager::GetInstance()->SetVolume(100);
    CNoticeManager::GetInstance()->SetGlobal(this);

    connect(CConnectionManager::GetInstance(),&CConnectionManager::conected,this,&QAppGlobal::connected);
    connect(CConnectionManager::GetInstance(),&CConnectionManager::disConnected,this,&QAppGlobal::disConnected);
}

/// 开始连接
void QAppGlobal::startConnect()
{
    CConnectionManager::GetInstance()->Connect();
}

void QAppGlobal::changeEarth()
{
    auto pSeneGraph = GetSceneCore()->GetSceneGraphManager()->FindSceneGraph(m_pOsgItem);
    pSeneGraph->GetMap()->LoadUserMap(GetDataPath()+"/Earth/Geocentric.earth",false,true);
}

/// 更新信息
void QAppGlobal::updateNotic(const QString &rInfo)
{
//    QString sInfo;
//    sInfo = QTime::currentTime().toString("hh:mm:ss ") + rInfo;
    emit(notic(rInfo));
}

/// 设置程序路径
void QAppGlobal::setAppPath(QString sAppPath)
{
    if(sAppPath != m_sAppPath)
    {
        m_sAppPath = sAppPath;
        emit(appPathChanged(sAppPath));
    }
}

/// 设置本地路径
void QAppGlobal::setLocalUrl(QString sUrl)
{
    if(sUrl != m_sLocalUrl)
    {
        m_sLocalUrl = sUrl;
        emit(appPathChanged(sUrl));
    }
}

/// 设置字体
void QAppGlobal::setWebFont(QString sFamilyName)
{
    if(sFamilyName != m_sWebFontFamily)
    {
        m_sWebFontFamily = sFamilyName;
        emit(webFontChanged(sFamilyName));
    }
}

/// 配置设置
void QAppGlobal::setSettings(CGlobalSettings *pSettings)
{
    if(pSettings != m_pSettings)
    {
        m_pSettings->deleteLater();
        m_pSettings = pSettings;
        emit(settingsChanged(m_pSettings));
    }
}

void QAppGlobal::setData(CGlobalData *pData)
{
    if(pData != m_pData)
    {
        m_pData->deleteLater();
        m_pData = pData;
        emit(dataChanged(m_pData));
    }
}

QStringList QAppGlobal::openPath()
{
    QDir *dir=new QDir(QString("%1/%2").arg(GetDataPath().c_str()).arg("Szy")); //文件夹
    QStringList filter; //过滤
    filter<<"*.szy";
    dir->setNameFilters(filter);
    QFileInfoList fileInfoList = dir->entryInfoList(filter);
    delete dir;
    QStringList string_list;
    for(int i=0; i < fileInfoList.count(); i++)
    {
        string_list.append(fileInfoList.at(i).baseName());
    }
    return(string_list);
    //    QDir *dir=new QDir(QString("%1/%2").arg(GetDataPath().c_str()).arg("Szy")); //文件夹
    //    QStringList filter; //过滤
    //    filter<<"*.szy";
    //    dir->setNameFilters(filter);
    //    QFileInfoList fileInfoList = dir->entryInfoList(filter);
    //    delete dir;
    //    QStringList string_list;
    //     QMap<QString,QString> mapNameToTime;
    //    QString fileName,fileTime;
    //    for(int i=0; i < fileInfoList.count(); i++)
    //    {
    //        m_sReplayName=fileInfoList.at(i).baseName();
    //        m_sReplayTime=fileInfoList.at(i).created().toString("yyyy-MM-dd HH:mm:ss");
    //        string_list.append(m_sReplayName+m_sReplayTime);
    //    }
    //    return(string_list);
}

/// 设置osgItem
void QAppGlobal::setOsgItem(QQuickItem *pOsgItem)
{
    m_pOsgItem = pOsgItem;
    auto pSeneGraph = GetSceneCore()->GetSceneGraphManager()->FindSceneGraph(pOsgItem);

    m_pData->SetSeceneGraph(pSeneGraph);
}

QString QAppGlobal::copyFile(const QString &strImagePath, const QString &folderName)
{
    QFileInfo fileInfo(strImagePath);
    QString name = folderName + "/" + fileInfo.fileName();
    QFile::copy(strImagePath, GetDataPath().c_str() + name);
    return name;
}

QStringList QAppGlobal::openHelp()
{
    QDir *dir=new QDir(QString("%1/%2").arg(GetDataPath().c_str()).arg("Help")); //文件夹
    QStringList filter; //过滤
    filter<<"*.chm"<<"*.doc"<<"*.docx"<<"*.mp4"<<"*.mkv";
    dir->setNameFilters(filter);
    QFileInfoList fileInfoList = dir->entryInfoList(filter);
    delete dir;
    QStringList string_list;
    for(int i=0; i < fileInfoList.count(); i++)
    {
        string_list.append(fileInfoList.at(i).absoluteFilePath());
    }
    return(string_list);
}

void QAppGlobal::openFile(const QUrl &rReplayFile)
{
    //    QTextCodec *code = QTextCodec::codecForName("utf-8");
    QString str = rReplayFile.toLocalFile().toLocal8Bit().data();/*GetDataPath().c_str() + QString("Help/")*/;
    //    QString string = code->fromUnicode(str);
    QDesktopServices::openUrl(QUrl::fromLocalFile(str));
}
///
void QAppGlobal::setOpenSpeak(bool bOpenSpeak)
{
    CNoticeManager::GetInstance()->OpenSpeak(bOpenSpeak);
}

void QAppGlobal::setGroupId(int typeID)
{
    auto type=m_pData->GetOrCreatePersonStatus(typeID);
    if(type->getType()=="蓝方")
    {
        m_typeColor=Qt::blue;
    }
    else if(type->getType()=="红方")
    {
        m_typeColor=Qt::red;
    }
    else
    {
        m_typeColor=Qt::white;
    }
    emit typeColorChanged();
}
