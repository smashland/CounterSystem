import QtQuick 2.0
import QtQuick.Controls 2.3
import QtQuick.Layouts 1.13

/// 人员状态显示
Rectangle
{
    property var outData: null
    property var fontSize: 18
    id:root
    width: parent.width
    height: 40
    color: Qt.rgba(18/255, 18/255, 18/255, 0.5);

    RowLayout
    {
        property var showHeigt: 30
        layoutDirection: Qt.LeftToRight

        id:infoshow
        anchors.fill: parent

        /// 圆形ID
//        RoundButton
//        {
//            id:showID
//            background: Rectangle
//            {
//                radius: infoshow.showHeigt
//                implicitWidth: infoshow.showHeigt
//                implicitHeight: infoshow.showHeigt
//                color:outData.bOnLine ? $app.settings.type2Color(outData.type) : "gray"
//            }
//            contentItem:Text
//            {
//                text: outData.id;

//                font.pixelSize: fontSize
//                font.bold: true
//                horizontalAlignment: Text.AlignHCenter
//                color:'white'
//                style:Text.Outline
//                styleColor:'black'
//            }
//        }

        Text
        {
            id: idText
            anchors.left: parent.left
            anchors.leftMargin: idText.contentWidth
            text: outData.id;
            font.pixelSize: fontSize
            font.bold: true
            horizontalAlignment: Text.AlignHCenter
            color:'white'
            style:Text.Outline
            styleColor:'black'
        }

        /// 人员名称
        Text
        {
            id:showName
//            text: outData.name;
            verticalAlignment: Text.AlignVCenter
            text:"人员"
            font.pixelSize: fontSize
            color:  "white"
            height: infoshow.showHeigt
            anchors.left: parent.left
            anchors.leftMargin: idText.contentWidth *2.5
        }

        Item
        {
            Layout.fillWidth: true
            Layout.fillHeight: true
        }


        /// 显示手枪连接状态
//        EquipConnStat
//        {
//            id: shouqiang
//            bConnected: outData.bPistol
//            text: '\ue034'
//        }
        //        /// 显示背心连接状态
        //        EquipConnStat
        //        {
        //            id: beixin
        //            text:'\ue025'
        //        }
        //        /// 显示手雷连接状态
        //        EquipConnStat
        //        {
        //            id: shoulei
        //            text:'\ue041'
        //        }
        //        /// 显示迫击炮连接状态
        //        EquipConnStat
        //        {
        //            id: paijipao
        //            text:'\ue02e'
        //        }
        //        /// 显示旗子连接状态
        //        EquipConnStat
        //        {
        //            id: qizi
        //            text:'\ue048'
        //        }

        /// 显示步枪枪连接状态
        EquipConnStat
        {
            id: jiqiang
            bConnected: outData.bRifle
            text: qsTr("\ue706")
            color: "#e7f6ff"
            font.family: "iconfont"
        }

        /// 显示头盔连接状态
        EquipConnStat
        {
            id: toukui
            bConnected: outData.bTK
            text: qsTr("\ue708")
            color: "#e7f6ff"
            font.family: "iconfont"
        }

        /// 显示GPS连接状态
//        EquipConnStat
//        {
//            id: locate
//            bConnected: outData.bGPS
//            text:'\ue053'
//        }

        /// 显示电量
//        Text
//        {
//            //anchors.top: locate.top
//            id:electricity
//            text: outData.nBaty+'%';
//            verticalAlignment: locate.verticalAlignment
//            styleColor: color
//            style: Text.Outline

//            color:  outData.bOnLine ? outData.nBaty > 59 ? "green" : outData.nBaty > 20 ? "yellow" : "red" : "gray"
//            height: 30
//        }
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

        Text {
            id:setRoot
            text: qsTr("\ue8b8")
            color: "#e7f6ff"
            font.family: "iconfont"
            font.pixelSize: 22*dpx
            verticalAlignment: Text.AlignVCenter
            MouseArea{
                anchors.fill: parent
                onClicked: {
                    contextMenu.x = root.x + mX
                    contextMenu.y = root.y + mY
                    contextMenu.userID = nId;
                    contextMenu.open();
                }
            }
        }

    }

    /// 健康生命条
//    ProgressBar
//    {
//        from: 0
//        to:100
//        id:health
////        value: outData.nHealth
//        value: outData.nBaty *0.01
//        anchors.top:infoshow.bottom
//        background: Rectangle
//        {
//            color: "#00000000"
//            implicitWidth: root.width
//            implicitHeight: 10
//        }
//        contentItem: Rectangle
//        {
//            width: health.visualPosition * health.width
//            height: health.height
//            /// 不在线则变灰
//            color: outData.bOnLine ?  health.value > 60 ?  "green" : health.value > 20 ? "yellow" : "red" : "gray";
//        }
//    }
    ProgressBar{
        id:health
        from: 0
        to: 1
        value: outData.nBaty *0.01
        width: parent.width
        height: 10
        anchors.top:infoshow.bottom
        background: Rectangle {
            implicitWidth: health.width
            implicitHeight: health.height
            color: "#121212"
            opacity: 0.7
        }

        contentItem: Item {
            Rectangle {
                width: health.visualPosition * health.width
                height: health.height
                color:  outData.bOnLine ? outData.nBaty > 59 ? "green" : outData.nBaty > 20 ? "yellow" : "red" : "gray"
            }
        }
    }
}
