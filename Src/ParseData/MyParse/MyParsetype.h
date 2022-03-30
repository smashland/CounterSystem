#ifndef MYPARSETYPE_H
#define MYPARSETYPE_H

#include "../../API-CRCheck.h"
static const uchar CS_buffer[9] = {0xAA,0X1D,0xff,0xff,0x95,0,0,0,0};
static const double CS_INT2DOUBLE(1./3600000.);
static const double CS_INT2FLOAT(1.0/10.);
static quint16 g_nGunType(0u);
static const quint16 g_unBroadCost(0xffff);

/// 用户发送数据协议
enum USER_CMD
{
    QUERY=0x01,    /// 查询命令
    SET_1,         /// 广播控制命令
    SET_2,         /// 点对点控制命令
    EVENT          /// 主动上传事件
};

/// 装备状态
enum EQUIPMENT_STATUS
{
    TouKui_Con=0x01,    /// 头盔连接状态
    GPS_Connct=0x02,    /// GPS连接状态
    WEAPON_Con=0x04,    /// 武器连接状态
    Baty_Value=0x08,    /// 电池电量
    Person_Sta=0x10,    /// 人员状态
    Bullet_Val=0x20,    /// 子弹数量
    Hit_Happen=0x40     /// 命中事件
};

/// 设置命令
enum SET_CMD
{
    HEART_TIME=0xA1,     /// 心跳时间
    DRILL_START,         /// 演习开始 A2
    DRILL_END,           /// 演习结束 A3
    SET_DEATH,           /// 判死    A4
    SET_REVIVE,          /// 复活    A5
    HURT_VALUE,          /// 损伤比例 A6
    LOCK_GUN,            /// 锁枪命令 A7
    ADD_BULLET,          /// 补充子弹 A8
    REALSE,              /// 解除旁白 A9
    ADD_GUN=0xAB,        /// 配枪 AB
    GIVE_TIME,           /// 给设备设置仿真时间 AC
    START_3RD=0xB0,      /// 开启第三者模式 B0
    STOP_3RD,            /// 关闭第三者模式 B1
    HIT_NOTICE,          /// 命中提示
    JUDGE_DEATH=0xB4,    /// 裁判枪判死
    CALIBRAION           /// 校准电压
};
#endif // MYPARSETYPE_H
