#include <QDate>
#include <QString>
#include <QApplication>
#include <QDir>
#include "../ConfigInfo.h"
#include "WordProcessingMerger.h"
#include "ExportResult.h"
#include "../ErrorReport.h"
#include "../DataManager/MyListModel.h"
#include "../DataManager/PersonStatus.h"
#include "../DataManager/DataManager.h"
#include "../DataManager/PersonInfo.pb.h"
#include "../DataManager/ini_file.h"
#include "../Settings/EarthManager.h"

static QString sHurt = QString::fromUtf8("被%1击中%2");
static QString sHit = QString::fromUtf8("命中%1%2");

using namespace DocxFactory;

CExportResult* CExportResult::S_PInstance = nullptr;

CExportResult::CExportResult()
{
    m_sReportPath = QApplication::applicationDirPath()+ "/Data/Report/";
}

CExportResult::~CExportResult()
{
}

CExportResult *CExportResult::GetInstance()
{
    if(nullptr == S_PInstance)
    {
        S_PInstance = new CExportResult;
    }
    return(S_PInstance);
}

/// 创建导出文档
void CExportResult::CreateDocx(const QString &sFileName, const QString& sTile,const QMap<QString, CMyListModel *> &rInfo)
{
    try
    {
        QString sFilePath = m_sReportPath + "out.dfw";
        WordProcessingMerger& l_merger = WordProcessingMerger::getInstance();
        l_merger.load(sFilePath.toUtf8().data());

        l_merger.setClipboardValue("_header", "headTitle",sTile.toUtf8().data());
        l_merger.setClipboardValue("_header", "PrintDate",QDate::currentDate().toString("yyyy/MM/dd").toStdString());
        l_merger.setClipboardValue("AllInfo","worldTitle",sTile.toUtf8().data());


        l_merger.setClipboardValue("Result","nName",m_currentSceName.toStdString()/*currentSceName.toStdString()*/);
        l_merger.setClipboardValue("Result","nBeginTime",INI_File().GetBeginTime().toStdString());
        l_merger.setClipboardValue("Result","nFinishTime",INI_File().GetEndTime().toStdString());
        l_merger.setClipboardValue("Result","nMapName",EarthManager().getCurrentEarthName().toStdString());
        l_merger.setClipboardValue("Result","nLocation",m_aveLocation.toStdString());
        l_merger.paste("Result");

        for(auto one=rInfo.begin();one!=rInfo.end();++one)
        {

            /// 总结各个组的综合情况
            l_merger.setClipboardValue("Total","nTotal",one.value()->count());
            l_merger.setClipboardValue("Total","nHurt",one.value()->hurtNum());
            l_merger.setClipboardValue("Total","nDeath",one.value()->deathNum());
            l_merger.setClipboardValue("Total","belong",one.key().toUtf8().data());
            if(0 == one.value()->count())
            {
                l_merger.setClipboardValue("Total","nRate","0%");
            }
            else
            {
                l_merger.setClipboardValue("Total","nRate",
                                           QString("%1%").arg(
                                               double(one.value()->hurtNum()+one.value()->deathNum())/one.value()->count()*100
                                               ).toUtf8().data());
            }
            l_merger.setClipboardValue("Total","CustomerPic","G:/F/model/DocxFactoryWin32/DocxFactory/exercises/images/customer0.png");
            l_merger.paste("Total");


            /// 填写各个组的信息表格
            l_merger.setClipboardValue("PersonStatuTable","nTotal",one.value()->count());
            l_merger.setClipboardValue("PersonStatuTable","nHurt",one.value()->hurtNum());
            l_merger.setClipboardValue("PersonStatuTable","nDeath",one.value()->deathNum());
            l_merger.setClipboardValue("PersonStatuTable","belong",one.key().toUtf8().data());

            if(0 == one.value()->count())
            {
                l_merger.setClipboardValue("PersonStatuTable","nRate","0%");
            }
            else
            {
                l_merger.setClipboardValue("PersonStatuTable","nRate",
                                           QString("%1%").arg(
                                               double(one.value()->hurtNum()+one.value()->deathNum())/one.value()->count()*100
                                               ).toUtf8().data());
            }

            l_merger.paste("PersonStatuTable");

            int nPersonNum=one.value()->count();
            for(int i=0;i<nPersonNum;++i)
            {
                CPersonStatus * pStutus = one.value()->at(i);
                l_merger.setClipboardValue("PersonInfo","belong",pStutus->getType().toUtf8().data());
                l_merger.setClipboardValue("PersonInfo","name",pStutus->getName().toUtf8().data());
                l_merger.setClipboardValue("PersonInfo","id",pStutus->getId());
                PersonInfo * pAllInto = CDataManager::GetInstance()->GetOrCreatePersonInfo(pStutus->getId());

                /// 梳理个人信息
                {
                    /// 判断剩余子弹数
                    const ConnectStatus& conStatus = pAllInto->curtstatus();
                    int nBaty = pAllInto->curtstatus().weapons_size();

                    bool bLink1(false),bLink(false);
                    QString sGunInfo,sGunNumInfo;
                    int nNumRifle(0),nNumPistol(0);
                    /// 获取默认子弹数
                    int nNumBullets(0);

                    for(int nIndex=0; nIndex < nBaty; ++nIndex)
                    {
                        switch(conStatus.weapons(nIndex).weapontype())
                        {
                        case RIFLE:
                            bLink1 = UNLINK != conStatus.weapons(nIndex).contype();
                            if(bLink1) nNumRifle += conStatus.weapons(nIndex).bulletnum();
                            break;
                        case PISTOL:
                            bLink = UNLINK != conStatus.weapons(nIndex).contype();
                            if(bLink) nNumRifle += conStatus.weapons(nIndex).bulletnum();
                            if(bLink || bLink1)
                            {
                                sGunInfo += QString::fromUtf8("步枪");
                                sGunNumInfo += QString::fromUtf8("步枪剩余子弹数:%1").arg(nNumRifle);
                                nNumBullets += CConfigInfo::GetInstance()->GetDefaultBullets();
                            }
                            break;
                        case GRENAD:
                            bLink1 = UNLINK != conStatus.weapons(nIndex).contype();
                            if(bLink1) nNumPistol += conStatus.weapons(nIndex).bulletnum();
                            break;
                        case MORTAR:
                            bLink = UNLINK != conStatus.weapons(nIndex).contype();
                            if(bLink) nNumPistol += conStatus.weapons(nIndex).bulletnum();

                            if(bLink || bLink1)
                            {
                                if(!sGunInfo.isEmpty())
                                {
                                    sGunInfo+="\n";
                                    sGunNumInfo+="\n";
                                }
                                nNumBullets += CConfigInfo::GetInstance()->GetDefaultBullets();
                                sGunInfo += QString::fromUtf8("手枪");
                                sGunNumInfo += QString::fromUtf8("手枪剩余子弹数:%1").arg(nNumPistol);
                            }
                            break;
                        }
                    }
                    l_merger.setClipboardValue("PersonInfo","weapontype",sGunInfo.toUtf8().data());

                    int nHitSize = pAllInto->hitinfo_size(),nScore(0);
                    QString sHitInfo,sHurtInfo;
                    for(int nIndex=0; nIndex<nHitSize; ++nIndex)
                    {
                        /// 增加命中信息

                        switch(pAllInto->hitinfo(nIndex).type())
                        {
                        case GRENAD:
                        case MORTAR:
                        case SNIPER:
                            sHitInfo += QString::fromUtf8("炸死%1").arg(pAllInto->hitinfo(nIndex).id());
                            break;
                        default:
                            sHitInfo += sHit.arg(pAllInto->hitinfo(nIndex).id())
                                    .arg(CConfigInfo::GetInstance()->GetBodyName(pAllInto->hitinfo(nIndex).hurtpart()));
                            break;
                        }

                        nScore += CConfigInfo::GetInstance()->CalHurtMark(pAllInto->hitinfo(nIndex).hurtpart());
                    }

                    int nHurtSize = pAllInto->hurtinfo_size();
                    for(int nIndex=0; nIndex<nHurtSize; ++nIndex)
                    {
                        /// 增加被命中信息
                        switch(pAllInto->hurtinfo(nIndex).type())
                        {
                        case GRENAD:
                        case MORTAR:
                        case SNIPER:
                            sHurtInfo += QString::fromUtf8("被%1炸死").arg(pAllInto->hurtinfo(nIndex).id());
                            break;
                        default:
                            sHurtInfo += sHurt.arg(pAllInto->hurtinfo(nIndex).id())
                                    .arg(CConfigInfo::GetInstance()->GetBodyName(pAllInto->hurtinfo(nIndex).hurtpart()));
                            break;
                        }
                    }

                    /// 射出的子弹数
                    nNumBullets -= nNumPistol + nNumRifle;
                    double dHitRate(0);
                    if(0 < nNumBullets)
                    {
                        dHitRate = static_cast<double>(nHitSize)/ nNumBullets;
                    }

                    nHitSize = dHitRate*100;
                    QString sHitRate = QString("%1%").arg(nHitSize);
                    l_merger.setClipboardValue("PersonInfo","hitrate",sHitRate.toUtf8().data());
                    QString sHealth;
                    if(pAllInto->hearth() <= 0)
                    {
                        sHealth = QString::fromUtf8("死亡");
                    }
                    else if(pAllInto->hearth() == 100)
                    {
                        sHealth = QString::fromUtf8("完好");
                    }
                    else
                    {
                        sHealth = QString::fromUtf8("受伤");
                    }
                    l_merger.setClipboardValue("PersonInfo","heath",sHealth.toUtf8().data());
                    l_merger.setClipboardValue("PersonInfo","score",nScore);
                    l_merger.setClipboardValue("PersonInfo","hitInfo",sHitInfo.toUtf8().data());
                    l_merger.setClipboardValue("PersonInfo","hurtInfo",sHurtInfo.toUtf8().data());
                    l_merger.setClipboardValue("PersonInfo","remBullet",sGunNumInfo.toUtf8().data());
                }

                l_merger.paste("PersonInfo");
            }
        }



        /// 保存信息
        l_merger.save(sFileName.toLocal8Bit().data());

    }
    catch (const exception& p_exception)
    {
        /// 将错误信息写入日志文件
        CErrorReport::GetInstance()->writeError(QString::fromUtf8(p_exception.what()));
    }
}

/// 获取输出文档路径
const QString &CExportResult::GetPath()
{
    return(m_sReportPath);
}

void CExportResult::setCurrentSceName(const QString &sSceName)
{
    if(sSceName!=m_currentSceName)
    {
        m_currentSceName=sSceName;
    }
}

void CExportResult::setAveLocation(const QString &sLocation)
{
//    QString location=QString("{%1,%2}").arg(m_nCurrentLat).arg(m_nCurrentLon);
//    return location;
    if(sLocation!=m_aveLocation)
    {
        m_aveLocation=sLocation;
    }
}
