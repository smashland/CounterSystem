import QtQuick 2.0
import QtQuick.Controls 2.3
import QtQuick.Layouts 1.13

/// 人员状态显示
Rectangle
{
    property var outData: null
    property var fontSize: 16

    id:root
    width: (parent.width-20)*dpx
    height: 40*dpy
    color: "black"
    opacity: 0.8
    z:10

    Text
    {
        id:showid
        text: outData.id;
        verticalAlignment: Text.AlignVCenter
        font.family: "Microsoft YaHei"
        font.pixelSize: fontSize
        color:  "white"
        height: parent.height
        anchors.left: parent.left
        anchors.leftMargin: 10
    }

    Text
    {
        id:showName
        text: outData.name;
        verticalAlignment: Text.AlignVCenter
        font.family: "Microsoft YaHei"
        font.pixelSize: fontSize
        color:  "white"
        height: parent.height
        anchors.left: parent.left
        anchors.leftMargin: 10 + showid.contentWidth
    }

    RowLayout
    {
        property var showHeigt: 30
//        layoutDirection: Qt.LeftToRight

        id:infoshow
        anchors.fill: parent
        anchors.right: parent.right
        anchors.rightMargin: 10

        /// 人员名称

        Item
        {
            Layout.fillWidth: true
            Layout.fillHeight: true
        }

        /// 显示步枪枪连接状态
        EquipConnStat
        {
            id: jiqiang
            bConnected: outData.bRifle
            source: "qrc:/Image/wuqi/buqiang.png"
        }
        /// 显示手枪连接状态
        EquipConnStat
        {
            id: shouqiang
            bConnected: outData.bPistol
            source: "qrc:/Image/wuqi/shouqiang.png"
        }
//        EquipConnStat
//        {
//            id: jujibuqiang
//            bConnected: outData.bRifle//狙击步枪
//            source: "qrc:/Image/wuqi/jujibuqiang.png"
//        }
//        EquipConnStat
//        {
//            id: shoulei
//            bConnected: outData.bRifle//手雷
//            source: "qrc:/Image/wuqi/shoulei.png"
//        }
//        EquipConnStat
//        {
//            id: baozhawu
//            bConnected: outData.bRifle//爆炸物
//            source: "qrc:/Image/wuqi/baozhawu.png"
//        }

        /// 显示头盔连接状态
        EquipConnStat
        {
            id: toukui
            bConnected: outData.bTK
            source: "qrc:/Image/wuqi/toukui.png"
        }

        /// 显示GPS连接状态
        EquipConnStat
        {
            id: locate
            bConnected: outData.bGPS
            source: "qrc:/Image/wuqi/dingwei.png"
        }

        /// 显示电量
        Text
        {
            //anchors.top: locate.top
            id:electricity
            text: outData.nBaty+'%'
            verticalAlignment: locate.verticalAlignment
            styleColor: color
            //                            style: Text.Outline
            color:  outData.bOnLine ? outData.nBaty > 59 ? "green" : outData.nBaty > 20 ? "yellow" : "red" : "gray"
            font.pixelSize: 14*dpx
            font.family: "Microsoft YaHei"
        }
    }

    /// 健康生命条
    ProgressBar{
        id:health
        from: 0
        to: 100
        value: outData.nHealth
        width: parent.width
        height: 10
        anchors.top:infoshow.bottom
        background: Rectangle {
            implicitWidth: health.width
            implicitHeight: health.height
            color: "#00000000"
            opacity: 0.7
        }

        contentItem: Item {
            Rectangle {
                width: health.visualPosition * health.width
                height: health.height
                color: outData.bOnLine ?  health.value > 60 ?  "green" : health.value > 20 ? "yellow" : "red" : "#8B8989";
            }
        }
    }
}
