#include <QtEndian>
#include <QDir>
#include <QVariant>
#include "GlobalSettings.h"
#include "../ConfigInfo.h"
#include "../ParseData/MyParse/MyParsetype.h"
#include "../ParseData/DealDataManager.h"
#include "../DataManager/GlobalData.h"
#include "../DataManager/DataManager.h"
#include "../TimeServer/TimeServer.h"
#include "Src/DataManager/PersonInfo.pb.h"
CGlobalSettings::CGlobalSettings(QObject *parent) : QObject(parent)
{
    m_nType = CConfigInfo::GetInstance()->GetConnectionType();
    m_qConnectColor.setRgbF(1.0,1.0,1.0);
    m_qDisConnectColor.setRgbF(0.2,0.2,0.2);

    //    m_mapType2Color.insert(QString::fromUtf8("红方"),QColor(255,0,0));
    //    m_mapType2Color.insert(QString::fromUtf8("蓝方"),QColor(0,0,255));
    //    m_mapType2Color.insert(QString::fromUtf8("白方"),QColor(255,255,255));
    //    m_mapType2Color.insert(QString::fromUtf8("未知"),QColor(127,127,127));

    //    m_mapType2BackColor.insert(QString::fromUtf8("红方"),QColor(255,0,0,79));
    //    m_mapType2BackColor.insert(QString::fromUtf8("蓝方"),QColor(0,0,255,79));
    //    m_mapType2BackColor.insert(QString::fromUtf8("白方"),QColor(255,255,255,79));
    //    m_mapType2BackColor.insert(QString::fromUtf8("未知"),QColor(127,127,127,79));
    m_mapType2Color.insert(QString::fromUtf8("红方"),QColor(0,0,0,0));
    m_mapType2Color.insert(QString::fromUtf8("蓝方"),QColor(0,0,255,0));
    m_mapType2Color.insert(QString::fromUtf8("白方"),QColor(255,255,255,0));
    m_mapType2Color.insert(QString::fromUtf8("未知"),QColor(127,127,127,0));
    m_mapType2BackColor.insert(QString::fromUtf8("红方"),QColor(0,0,0,0));
    m_mapType2BackColor.insert(QString::fromUtf8("蓝方"),QColor(0,0,255,0));
    m_mapType2BackColor.insert(QString::fromUtf8("白方"),QColor(255,255,255,0));
    m_mapType2BackColor.insert(QString::fromUtf8("未知"),QColor(127,127,127,0));

    QVariantMap tmpMap;

    //// 得分设置
    tmpMap["type"]=QString::fromUtf8("头部:");
    tmpMap["number"]=CConfigInfo::GetInstance()->GetHurtMark(0);
    m_scoreSetting.push_back(tmpMap);
    tmpMap["type"]=QString::fromUtf8("胸部:");
    tmpMap["number"]=CConfigInfo::GetInstance()->GetHurtMark(1);
    m_scoreSetting.push_back(tmpMap);
    tmpMap["type"]=QString::fromUtf8("腹部:");
    tmpMap["number"]=CConfigInfo::GetInstance()->GetHurtMark(2);
    m_scoreSetting.push_back(tmpMap);
    tmpMap["type"]=QString::fromUtf8("背部:");
    tmpMap["number"]=CConfigInfo::GetInstance()->GetHurtMark(3);
    m_scoreSetting.push_back(tmpMap);
    tmpMap["type"]=QString::fromUtf8("胳膊:");
    tmpMap["number"]=CConfigInfo::GetInstance()->GetHurtMark(4);
    m_scoreSetting.push_back(tmpMap);
    tmpMap["type"]=QString::fromUtf8("腿部:");
    tmpMap["number"]=CConfigInfo::GetInstance()->GetHurtMark(5);
    m_scoreSetting.push_back(tmpMap);

    /// 损伤设置
    tmpMap["type"]=QString::fromUtf8("头部:");
    tmpMap["number"]=CConfigInfo::GetInstance()->GetHitDamage(0);
    m_harmSetting.push_back(tmpMap);
    tmpMap["type"]=QString::fromUtf8("胸部:");
    tmpMap["number"]=CConfigInfo::GetInstance()->GetHitDamage(1);
    m_harmSetting.push_back(tmpMap);
    tmpMap["type"]=QString::fromUtf8("腹部:");
    tmpMap["number"]=CConfigInfo::GetInstance()->GetHitDamage(2);
    m_harmSetting.push_back(tmpMap);
    tmpMap["type"]=QString::fromUtf8("背部:");
    tmpMap["number"]=CConfigInfo::GetInstance()->GetHitDamage(3);
    m_harmSetting.push_back(tmpMap);
    tmpMap["type"]=QString::fromUtf8("胳膊:");
    tmpMap["number"]=CConfigInfo::GetInstance()->GetHitDamage(4);
    m_harmSetting.push_back(tmpMap);
    tmpMap["type"]=QString::fromUtf8("腿部:");
    tmpMap["number"]=CConfigInfo::GetInstance()->GetHitDamage(5);
    m_harmSetting.push_back(tmpMap);

    /// 系统设置
    tmpMap["type"]=QString::fromUtf8("同步时间:");
    tmpMap["number"]=CConfigInfo::GetInstance()->GetSynTimes();
    m_sysSetting.push_back(tmpMap);

    tmpMap["type"]=QString::fromUtf8("重发次数:");
    tmpMap["number"]=CConfigInfo::GetInstance()->GetResendTimes();
    m_sysSetting.push_back(tmpMap);

    tmpMap["type"]=QString::fromUtf8("掉线判别:");
    tmpMap["number"]=CConfigInfo::GetInstance()->GetDroppedTimes();
    m_sysSetting.push_back(tmpMap);

    tmpMap["type"]=QString::fromUtf8("默认步枪子弹数:");
    tmpMap["number"]=CConfigInfo::GetInstance()->GetChargeBullets(1);
    m_sysSetting.push_back(tmpMap);

    tmpMap["type"]=QString::fromUtf8("默认手枪子弹数:");
    tmpMap["number"]=CConfigInfo::GetInstance()->GetChargeBullets(2);
    m_sysSetting.push_back(tmpMap);

    tmpMap["type"]=QString::fromUtf8("默认狙击枪子弹数:");
    tmpMap["number"]=CConfigInfo::GetInstance()->GetChargeBullets(7);
    m_sysSetting.push_back(tmpMap);
}

/// 根据归属方设置颜色
QColor CGlobalSettings::type2Color(const QString &sType)
{
    static QColor S_TEMP(127,127,127);
    auto itor = m_mapType2Color.find(sType);
    if(m_mapType2Color.end() != itor)
    {
        return(itor.value());
    }
    else
    {
        return(S_TEMP);
    }
}

QColor CGlobalSettings::type2BackColor(const QString &sType)
{
    static QColor S_TEMP(127,127,127);
    auto fineOne = m_mapType2BackColor.find(sType);
    if(m_mapType2BackColor.end() != fineOne)
    {
        return(fineOne.value());
    }
    else
    {
        return(S_TEMP);
    }
}

QStringList CGlobalSettings::types()
{
    return m_mapType2Color.keys();
}

int CGlobalSettings::index(const QString &sType)
{
    return(types().indexOf(sType));
}

/// 获取串口名字
QStringList CGlobalSettings::comNameList()
{
    return(CConfigInfo::GetInstance()->GetComNameList());
}

bool CGlobalSettings::isExistcomName(const QString &sComName)
{
    QStringList comList=CConfigInfo::GetInstance()->GetComNameList();
    if(comList.contains(sComName))
    {
        return true;
    }
    return false;
}

/// 设置串口名称
void CGlobalSettings::setComName(const QString &sComName)
{
    CConfigInfo::GetInstance()->GetComName() = sComName;
}

/// 设置wifi信息
void CGlobalSettings::setWifiInfo(const QString &sIP, ushort unPort)
{
    CConfigInfo::GetInstance()->SetIP(sIP);
    CConfigInfo::GetInstance()->SetPort(unPort);
}

QString CGlobalSettings::getSip()
{
    qDebug()<<"ip:"<< CConfigInfo::GetInstance()->GetIP().c_str();
    return CConfigInfo::GetInstance()->GetIP().c_str();
}

ushort CGlobalSettings::getPort()
{
    qDebug()<<"port"<<CConfigInfo::GetInstance()->GetPort();
    return  CConfigInfo::GetInstance()->GetPort();
}

/// 演习开始
void CGlobalSettings::setStart()
{
    m_bIsStart = true;
    CConfigInfo::GetInstance()->GetStart() = true;

    /// 设置同步时间
    CDealDataManager::GetInstance()->AllSycTime(CConfigInfo::GetInstance()->GetSynTimes());

    /// 设置损伤比例
    CConfigInfo::GetInstance()->AllSetHitDamae();

    /// 设置子弹数
    QList<QVariant> vList;
    for(int i=0;i<7;++i)
    {
        if(i==0)
        {
            vList.push_back(CConfigInfo::GetInstance()->GetChargeBullets(1));
        }
        else if(i==2)
        {
            vList.push_back(CConfigInfo::GetInstance()->GetChargeBullets(2));
        }
        else if(i==7)
        {
            vList.push_back(CConfigInfo::GetInstance()->GetChargeBullets(7));
        }
        else
        {
        vList.push_back(CConfigInfo::GetInstance()->GetDefaultBullets());
        }
    }

    CDealDataManager::GetInstance()->AllChongDan(vList);

    /// 发送演习开始
    CDealDataManager::GetInstance()->AllStart();

    /// 查询所有人的状态
    CDealDataManager::GetInstance()->QueryAll();
    /// 重置人员状态添加(测试)
    CDataManager::GetInstance()->ResetPersonInfo();

    /// 重置演习时间
    CTimeServer::GetInstance()->ResetSimTime();
    emit startStatusChanged(m_bIsStart);

    CDealDataManager::GetInstance()->clearBulletSum();

}
QString CGlobalSettings::getSysTime()
{
    QDateTime dateTime=QDateTime::currentDateTime();
    sBeginTime = dateTime.toString("yyyy-MM-dd HH:mm:ss");
    return (sBeginTime);
}

/// 演习结束
void CGlobalSettings::setStop()
{
    m_bIsStart = false;
    CConfigInfo::GetInstance()->GetStart()=false;
    CDealDataManager::GetInstance()->AllStop();
    emit startStatusChanged(m_bIsStart);
}

/// 开始回放
void CGlobalSettings::startReplay()
{
    m_bIsReplay = true;
    emit replayStatusChanged(m_bIsReplay);
}

/// 结束回放
void CGlobalSettings::endReplay()
{
    m_bIsReplay = false;
    emit replayStatusChanged(m_bIsReplay);
}

/// 闭锁
void CGlobalSettings::setBiSuo(quint16 nID)
{
    CDealDataManager::GetInstance()->PersonalBiSuo(nID);
}

/// 解锁
void CGlobalSettings::setJiesuoSuo(quint16 nID)
{
    CDealDataManager::GetInstance()->PersonalJieSuo(nID);
}

/// 解除旁白
void CGlobalSettings::setJieChu(quint16 nID)
{
    CDealDataManager::GetInstance()->PangBai();
}

/// 判死
void CGlobalSettings::setPanSi(quint16 nID)
{
    CDealDataManager::GetInstance()->PersonalPanSi(nID);
}

/// 复活
void CGlobalSettings::setFuHuo(quint16 nID)
{
    CDealDataManager::GetInstance()->PersonalFuHuo(nID);
}

/// 充弹
void CGlobalSettings::chongDan(quint16 nID, const QStringList &allInfo)
{
    QStringList tempInfo=allInfo;
    QList<int>  nTempInfo;
    auto pPerson = CDataManager::GetInstance()->GetOrCreatePersonInfo(nID);
    /// 判断剩余子弹数
    const ConnectStatus& conStatus = pPerson->curtstatus();
    int nBaty = pPerson->curtstatus().weapons_size();

    bool bLink1(false),bLink(false);
    int nNum(0);
    int temp=0;
    for(int nIndex=0; nIndex < nBaty; ++nIndex)
    {
        switch(conStatus.weapons(nIndex).weapontype())
        {
        case RIFLE:
            bLink1 = UNLINK != conStatus.weapons(nIndex).contype();
            if(bLink1)
                nNum = conStatus.weapons(nIndex).bulletnum();
            break;
        case PISTOL:
            bLink = UNLINK != conStatus.weapons(nIndex).contype();
            if(bLink)
                nNum += conStatus.weapons(nIndex).bulletnum();
            temp=allInfo.at(0).toInt();
            temp=temp+nNum;
//            tempInfo.append(QString::number(temp));
            tempInfo.replace(0,QString::number(temp));
            qDebug()<<"步枪枪数："<<nNum<<temp<<allInfo;
            break;
        case GRENAD:
            bLink1 = UNLINK != conStatus.weapons(nIndex).contype();
            if(bLink1)
                nNum = conStatus.weapons(nIndex).bulletnum();
            break;
        case MORTAR:
            bLink = UNLINK != conStatus.weapons(nIndex).contype();
            if(bLink)
                nNum += conStatus.weapons(nIndex).bulletnum();
            temp=allInfo.at(2).toInt();
            temp=temp+nNum;
            tempInfo.replace(2,QString::number(temp));
            qDebug()<<"shou枪枪数："<<nNum<<temp;
            break;
        case SUBMACHINE:
            bLink = UNLINK != conStatus.weapons(nIndex).contype();
            if(bLink)
                nNum += conStatus.weapons(nIndex).bulletnum();
            temp=allInfo.at(7).toInt();
            temp=temp+nNum;
            tempInfo.replace(7,QString::number(temp));
            qDebug()<<"狙击枪枪数："<<nNum<<temp;
             break;

        }
    }

    CDealDataManager::GetInstance()->PersonalChongDan(nID,tempInfo/*allInfo*/);

    for(int i=0;i<allInfo.size();i++)
    {
        nTempInfo.append(allInfo.at(i).toInt());
    }
    CDealDataManager::GetInstance()->SetBulletSum(nID,nTempInfo);
}

/// 配枪
void CGlobalSettings::peiQiang(quint16 nID, int nGunID)
{
    CDealDataManager::GetInstance()->PersonalPeiQiang(nID,nGunID);
}

void CGlobalSettings::sycTime(quint16 nID, quint16 nTime)
{
    CDealDataManager::GetInstance()->PersonalSycTime(nID,nTime);
}

/// 更新设置
void CGlobalSettings::changeSetting(const QString& sListType,const int& rIndex,const int& rInt)
{
    if("score" == sListType)
    {
        CConfigInfo::GetInstance()->SetHurtMark(rIndex,rInt);
    }
    else if("harm"==sListType)
    {
        CConfigInfo::GetInstance()->SetHitDamae(rIndex,rInt);
    }
    else if("sys" == sListType)
    {
        switch (rIndex)
        {
        case 0:
            CConfigInfo::GetInstance()->GetSynTimes()=rInt;
            CConfigInfo::GetInstance()->CalOfflineTime();
            break;
        case 1:
            CConfigInfo::GetInstance()->GetResendTimes()=rInt;
            break;
        case 2:
            CConfigInfo::GetInstance()->GetDroppedTimes()=rInt;
            CConfigInfo::GetInstance()->CalOfflineTime();
            break;
        case 3:
            // CConfigInfo::GetInstance()->SetHitDamae(rIndex,rInt);
//            if(CConfigInfo::GetInstance()->GetDefaultBullets()!=rInt)
//            {
//                CDealDataManager::GetInstance()->clearBulletSum();
//            }
//            CConfigInfo::GetInstance()->GetDefaultBullets()=rInt;
            CConfigInfo::GetInstance()->SetChargeBullets(1,rInt);
            break;
        case 4:
            CConfigInfo::GetInstance()->SetChargeBullets(2,rInt);
            break;
        case 5:
            CConfigInfo::GetInstance()->SetChargeBullets(7,rInt);
            break;
        }
    }
}

/// 设置连接颜色
void CGlobalSettings::setConnectColor(const QColor &qConColor)
{
    if(qConColor != m_qConnectColor)
    {
        m_qConnectColor = qConColor;
        emit(connectColorChanged(m_qConnectColor));
    }
}

/// 设置掉线颜色
void CGlobalSettings::setDisConnColor(const QColor &qDisConColor)
{
    if(qDisConColor != m_qDisConnectColor)
    {
        m_qDisConnectColor = qDisConColor;
        emit(connectColorChanged(m_qDisConnectColor));
    }
}

void CGlobalSettings::SetGlobalData(CGlobalData *pGlobalData)
{
    m_pGlobalData = pGlobalData;
}

/// 更新配置
void CGlobalSettings::updateConfig()
{
}
