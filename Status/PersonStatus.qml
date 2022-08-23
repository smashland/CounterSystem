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
    z:10

    RowLayout
    {
        property var showHeigt: 30
        layoutDirection: Qt.LeftToRight

        id:infoshow
        anchors.fill: parent

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
//            text:""
            font.pixelSize: fontSize
            color:  "white"
            height: infoshow.showHeigt
            anchors.left: parent.left
            anchors.leftMargin: idText.contentWidth *2.5

        }
        Connections {
            ignoreUnknownSignals: true
            target: personPopup
            function onNameChanged(personName)
            {
                showName.text = personName;
            }
        }

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
        EquipConnStat
        {
            id: jujibuqiang
            bConnected: outData.bRifle//狙击步枪
            source: "qrc:/Image/wuqi/jujibuqiang.png"
        }
        EquipConnStat
        {
            id: shoulei
            bConnected: outData.bRifle//手雷
            source: "qrc:/Image/wuqi/shoulei.png"
        }
        EquipConnStat
        {
            id: baozhawu
            bConnected: outData.bRifle//爆炸物
            source: "qrc:/Image/wuqi/baozhawu.png"
        }

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

        Text {
            id:setRoot
            width: setRoot.contentWidth
            height: setRoot.contentHeight
            text: qsTr("\ue8b8")
            color: "#e7f6ff"
            font.family: "iconfont"
            font.pixelSize: 22*dpx
            verticalAlignment: Text.AlignVCenter
            MouseArea
            {
                anchors.fill: parent
                onPressed:
                {
                    personClickd(modelData.id,setRoot.x,setRoot.y+setRoot.contentHeight);//root.height+(root.height-setRoot.contentHeight)
                }

            }
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
                color: outData.bOnLine ?  health.value > 60 ?  "green" : health.value > 20 ? "yellow" : "red" : "gray";
            }
        }
    }
}
