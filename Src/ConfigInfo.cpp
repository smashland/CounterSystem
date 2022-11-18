#include <QApplication>
#include <QDir>
#include <QSerialPortInfo>
#include <QXmlStreamReader>
#include "ConfigInfo.h"
#include <fstream>
#include <google/protobuf/util/json_util.h>
#include "DataManager/Config.pb.h"
#include "ParseData/DealDataManager.h"
using namespace std;
/// 获取唯一实例
CConfigInfo* CConfigInfo::GetInstance()
{
    static CConfigInfo S_ConfigInfo;

    return(&S_ConfigInfo);
}

void CConfigInfo::CalOfflineTime()
{
    m_nOfflineTime = m_nSynTimes * m_nDroppedTimes;
}

int CConfigInfo::GetOfflineTime()
{
    return(m_nOfflineTime);
}

/// 配置信息
CConfigInfo::CConfigInfo()
{
    m_pConfig = Config::default_instance().New();
    /// 获取文件地址
    QString filePath = QApplication::applicationDirPath() + "/Data/Config/ConfigInfo.txt";

    m_sFileName = filePath.toLocal8Bit().data();

    m_nType = 0;


    PraseIni();
}

/// 解析配置文件
void CConfigInfo::PraseIni()
{
    ifstream in(m_sFileName);

    if (!in.is_open())
    {
        return;
    }

    std::string sInfo;

    in>>sInfo;

    if(google::protobuf::util::JsonStringToMessage(sInfo,m_pConfig).ok())
    {
        m_stComName = m_pConfig->mutable_coninfo()->scomname().c_str();

        m_nHitLineDelSec = m_pConfig->mutable_sysinfo()->ndelehitline();
        m_nSpeak = m_pConfig->mutable_sysinfo()->nopenspeak();
//        m_nIp = m_pConfig->mutable_coninfo()->sip();
        m_nSynTimes=m_pConfig->mutable_siminfo()->nsycntime();
        m_nDroppedTimes=m_pConfig->mutable_siminfo()->ntime2drop();
        m_bKillSelf=m_pConfig->mutable_siminfo()->bkillself();
        m_bCanHitDeath=m_pConfig->mutable_siminfo()->bdeakill();
        m_nDefaultBullets=m_pConfig->mutable_siminfo()->ninitbullets();

        m_vHurtMark.resize(m_pConfig->mutable_siminfo()->scoreset_size());

        for(int i=0;i<m_pConfig->mutable_siminfo()->scoreset_size();++i)
        {
            m_vHurtMark[i]=m_pConfig->mutable_siminfo()->scoreset(i).nscore();
        }

        m_vHurtMark.resize(6);

        m_vHitDamea.resize(m_pConfig->mutable_siminfo()->rateset_size());

        for(int i=0;i<m_pConfig->mutable_siminfo()->rateset_size();++i)
        {
            m_vHitDamea[i]=m_pConfig->mutable_siminfo()->rateset(i).nrate();
        }

        m_vHitDamea.resize(6);
    }
    else
    {
        m_bKillSelf = false;
        m_nHitLineDelSec = 1;
        m_nSpeak=0;
        /// 软件开始仿真
        m_bStart = false;
        m_bCanHitDeath = false;
        m_bReplay = false;


        /// 初始化判断掉线的次数
        m_nDroppedTimes = 5;
        m_nSynTimes = 5;
        m_nDefaultBullets=1000;

        m_vHurtMark.resize(6);
        m_vHurtMark[0]=m_vHurtMark[1]=m_vHurtMark[2]=m_vHurtMark[3]=5;
        m_vHurtMark[4]=m_vHurtMark[5]=2;

        m_vHitDamea.resize(6);
        m_vHitDamea[0]=m_vHitDamea[1]=m_vHitDamea[2]=m_vHitDamea[3]=100;
        m_vHitDamea[4]=m_vHitDamea[5]=50;
    }
    m_nResendTimes = 5;
    m_nOfflineTime = m_nSynTimes * m_nDroppedTimes;
}

void CConfigInfo::PraseXml()
{
    /// 获取文件地址
    QString filePath = QApplication::applicationDirPath() + "/Data/Earth/Geocentric.earth";
    QFile configFile(filePath);
    QMap<quint16,QString> tmpMapInfo;
    if(configFile.open(QIODevice::ReadOnly))
    {
        QXmlStreamReader xmlReader(&configFile);
        QXmlStreamReader::TokenType type;
        QString sElementName;
        quint16 nType;
        QString sInfo;
        while (!xmlReader.atEnd())
        {
            switch (type=xmlReader.readNext())
            {
            case QXmlStreamReader::StartElement:
                if(xmlReader.name() == "valuemap")
                {
                    tmpMapInfo.clear();
                    sElementName = xmlReader.attributes().value("type").toString();
                    m_mapAllInfo[sElementName].clear();
                }
                else if(xmlReader.name() == "value")
                {
                    nType = xmlReader.attributes().value("type").toUInt();
                    sInfo = xmlReader.attributes().value("name").toString();
                    m_mapAllInfo[sElementName].insert(nType,sInfo);
                }
                break;
            default:
                break;
            }
        }
        configFile.close();
    }
}

/// 保存Ini的文件
void CConfigInfo::SaveIni()
{
    std::string sInfo;

    m_pConfig->mutable_coninfo()->set_scomname(m_stComName.toUtf8().data());
    m_pConfig->mutable_sysinfo()->set_ndelehitline(m_nHitLineDelSec);
    m_pConfig->mutable_sysinfo()->set_nopenspeak(m_nSpeak);
//    m_pConfig->mutable_sysinfo()->set_sip(m_nIp);
    m_pConfig->mutable_siminfo()->set_nsycntime(m_nSynTimes);
    m_pConfig->mutable_siminfo()->set_ntime2drop(m_nDroppedTimes);
    m_pConfig->mutable_siminfo()->set_bkillself(m_bKillSelf);
    m_pConfig->mutable_siminfo()->set_bdeakill(m_bCanHitDeath);
    m_pConfig->mutable_siminfo()->set_ninitbullets(m_nDefaultBullets);

    m_pConfig->mutable_siminfo()->clear_scoreset();

    for(int i=0;i<m_vHurtMark.size();++i)
    {
        auto pHitScore = m_pConfig->mutable_siminfo()->add_scoreset();
        switch(i)
        {
        case 0:
            pHitScore->set_hitpart(HEAD);
            break;
        case 1:
            pHitScore->set_hitpart(CHEST);
            break;
        case 2:
            pHitScore->set_hitpart(ABDOMEN);
            break;
        case 3:
            pHitScore->set_hitpart(BACK);
            break;
        case 4:
            pHitScore->set_hitpart(LEFT_ARM);
            break;
        case 5:
            pHitScore->set_hitpart(LEFT_LEG);
            break;
        }

        pHitScore->set_nscore(m_vHurtMark[i]);
    }

    m_pConfig->mutable_siminfo()->clear_rateset();

    for(int i=0;i<m_vHitDamea.size();++i)
    {
        auto rateSet = m_pConfig->mutable_siminfo()->add_rateset();
        switch(i)
        {
        case 0:
            rateSet->set_hitpart(HEAD);
            break;
        case 1:
            rateSet->set_hitpart(CHEST);
            break;
        case 2:
            rateSet->set_hitpart(ABDOMEN);
            break;
        case 3:
            rateSet->set_hitpart(BACK);
            break;
        case 4:
            rateSet->set_hitpart(LEFT_ARM);
            break;
        case 5:
            rateSet->set_hitpart(LEFT_LEG);
            break;
        }

        rateSet->set_nrate(m_vHitDamea[i]);
    }

    if(google::protobuf::util::MessageToJsonString(*m_pConfig,&sInfo).ok())
    {
        ofstream out(m_sFileName);

        if (out.is_open())
        {
            out<<sInfo;
        }
    }
}

/// 获取串口名称
QStringList CConfigInfo::GetComNameList()
{
    static QStringList s_listCom;

    s_listCom.clear();

    auto listPortInfo = QSerialPortInfo::availablePorts();
    foreach (auto portInfo, listPortInfo)
    {
        if(!portInfo.isBusy())
        {
            s_listCom.push_back(portInfo.portName());
        }
    }
    /// 返回串口名称
    return(s_listCom);
}

void CConfigInfo::SetIP(const QString &sIP)
{
    qDebug()<<"测试设置IP"<<sIP<<" "<<sIP.toUtf8().data();
    m_pConfig->mutable_coninfo()->set_sip(sIP.toUtf8().data());
}

const string &CConfigInfo::GetIP()
{
    return(m_pConfig->mutable_coninfo()->sip());
}

uint CConfigInfo::GetPort()
{
    return(m_pConfig->mutable_coninfo()->sport());
}

void CConfigInfo::SetPort(uint nPort)
{
    m_pConfig->mutable_coninfo()->set_sport(nPort);
}

int CConfigInfo::GetConnectionType()
{
    return(m_pConfig->mutable_coninfo()->contype());
}

int CConfigInfo::GetHurtMark(int nType)
{
    if(nType < m_vHurtMark.size())
    {
        return(m_vHurtMark[nType]);
    }
    else
    {
        return(0);
    }
}

int CConfigInfo::CalHurtMark(int nHurtType)
{
    switch (nHurtType)
    {
    case 1:
    case 2:
    case 3:
    case 4:
        return(GetHurtMark(nHurtType-1));
        break;
    case 5:
    case 6:
        return(m_vHurtMark[4]);
        break;
    case 7:
    case 8:
        return(m_vHurtMark[5]);
        break;
    default:
        return(0);
    }
}

void CConfigInfo::SetHurtMark(int nIndex, int nValue)
{
    if(nIndex < m_vHurtMark.size())
    {
        m_vHurtMark[nIndex]=nValue;
    }
}

int CConfigInfo::GetHitDamage(int nType)
{
    if(nType < m_vHitDamea.size())
    {
        return(m_vHitDamea[nType]);
    }
    else
    {
        return(0);
    }
}

int CConfigInfo::CalHitDamage(int nHurtType)
{
    switch (nHurtType)
    {
    case 1:
    case 2:
    case 3:
    case 4:
        return(GetHitDamage(nHurtType-1));
        break;
    case 5:
    case 6:
        return(m_vHitDamea[4]);
        break;
    case 7:
    case 8:
        return(m_vHitDamea[5]);
        break;
    default:
        return(0);
    }
}

void CConfigInfo::SetHitDamae(int nIndex, int nValue)
{
    if(nIndex < m_vHitDamea.size())
    {
        m_vHitDamea[nIndex]=nValue;
    }
}

/// 设置损伤比例
void CConfigInfo::AllSetHitDamae()
{
    QByteArray damegeInfo;
    for(int i=0;i<6;++i)
    {
        damegeInfo.append(m_vHitDamea[i]);
        if(i>3)
        {
            damegeInfo.append(m_vHitDamea[i]);
        }
    }
    CDealDataManager::GetInstance()->Damege(damegeInfo);
}

/// 获取中文名
const QString &CConfigInfo::GetBodyName(int nType)
{
    static QString S_HEAD=QString::fromUtf8("头部");
    static QString S_CHEST=QString::fromUtf8("胸部");
    static QString S_ABDOMEN=QString::fromUtf8("腹部");
    static QString S_BACK=QString::fromUtf8("背部");
    static QString S_LEFT_ARM=QString::fromUtf8("左臂");
    static QString S_RIGHT_ARM=QString::fromUtf8("右臂");
    static QString S_LEFT_LEG=QString::fromUtf8("左腿");
    static QString S_RIGHT_LEG=QString::fromUtf8("右腿");
    static QString S_UNKOWN=QString::fromUtf8("未知");

    switch(nType)
    {
    case 1:
        return(S_HEAD);
    case 2:
        return(S_CHEST);
    case 3:
        return(S_ABDOMEN);
    case 4:
        return(S_BACK);
    case 5:
        return(S_LEFT_ARM);
    case 6:
        return(S_RIGHT_ARM);
    case 7:
        return(S_LEFT_LEG);
    case 8:
        return(S_RIGHT_LEG);
    default:
        return(S_UNKOWN);
    }
}

void CConfigInfo::SetSpeack(bool IsSpeack)
{
    if(IsSpeack)
    {
      m_nSpeak=1;
    }
    else
    {
       m_nSpeak=2;
    }
    m_pConfig->mutable_sysinfo()->set_nopenspeak(m_nSpeak);
}

int CConfigInfo::GetSpeack()
{
    return m_pConfig->mutable_sysinfo()->nopenspeak();
}

/// 析构数据数据
CConfigInfo::~CConfigInfo()
{
    SaveIni();
    delete m_pConfig;
}
