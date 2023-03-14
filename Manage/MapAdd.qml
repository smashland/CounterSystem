import QtQuick 2.0
import QtQuick.Controls 2.3
import QtQuick.Dialogs 1.3
import Qt.labs.platform 1.1
import Qt.labs.qmlmodels 1.0

import "../Common"
import "../Exercise"

Rectangle {
    id: mapAdd
    color: "transparent"
    signal signalAddMap(string name,string path,var lat,var lon,var rdlat,var rdlon)    //        添加地图
    property var map: null

    MouseArea {
        anchors.fill: parent
        propagateComposedEvents: false
        enabled:true
        onWheel: {
            // 屏蔽滚轮事件，防止滚动方案列表时缩放地球
            mouse.accepted = false
        }
    }

    Image {
        //        anchors.fill: parent
        width: 600*dpx
        height: 550*dpy/*255*dpy*/
        source: "qrc:/Image/wuqi/08-bg.png"
    }
    CloseButton {
        x: 515*dpx
        y: 55*dpy
        onClicked: {
            qingkong()
            mapAdd.visible = false
        }
    }

    PopupTitle {
        name: ("添加地图")
        icon: "\ue795"
        x: 60 *dpx
        y: 60*dpy/* 50*dpy*/
    }

    FileDialog {
        id: fileDialog
        folder: shortcuts.home
        title: qsTr("请选择文件")
        nameFilters: [qsTr("图片 (*.png)"),qsTr("图片 (*.jpg)"),qsTr("图片 (*.tif)"),qsTr("文件 (*.xml)")/*, qsTr("全部文件 (*.*)")*/]
        onAccepted: {
            var earthPath=String(fileDialog.currentFile)
            earthPath=earthPath.substr(8)
            mapPath.name=earthPath
        }
    }
    Column {
        x: 96 *dpx
        y: 110*dpy/*96*dpy*/
        spacing: 12*dpy
        SoldierItem {
            id:mapName
            text: "  地图名称:"
            name: map.earthName
        }
        Row {
            spacing: 30*dpx
            SoldierItem {
                id:mapPath
                text: "  地图路径:"
                name: map.earthPath
            }
            Button {
                id: xuanzelujing
                width: 90*dpx
                height: 33 *dpy
                background: Rectangle{
                    color: "#000080"
                    Text {
                        id: xzlj
                        text: "选择路径"
                        color: "#ffffff"
                        font.pixelSize: 15*dpx;
                        font.family: "Microsoft YaHei";
                        anchors.centerIn: parent
                    }
                }
                onClicked: fileDialog.open()
            }
        }


        Text {
            id: tishi
            width: tishi.contentWidth
            height: tishi.contentHeight
            color: "#FFA500"
            text: "（如果是瓦片地图，请选择tms.xml文件）"
            font.pixelSize: 13*dpx;
            font.family: "Microsoft YaHei";
            verticalAlignment: Text.AlignVCenter
        }
        SoldierItem {
            id:mapLat
            text: " 左上角经度:"
            name: map.nLat
        }
        SoldierItem {
            id:mapLon
            text: " 左上角纬度:"
            name: map.nLon
        }
        SoldierItem {
            id:mapRDLat
            text: " 右下角经度:"
            name: map.nRDLat
        }
        SoldierItem {
            id:mapRDLon
            text: " 右下角纬度:"
            name: map.nRDLon
        }
        Text {
            id: tishi2
            width: tishi2.contentWidth
            height: tishi2.contentHeight
            color: "#FFA500"
            text: "（如果没有具体经纬度，点确定保存当前视口经纬度。）"
            font.pixelSize: 13*dpx;
            font.family: "Microsoft YaHei";
            verticalAlignment: Text.AlignVCenter
        }
        PopupButton {
//            y: 187*dpy
            x: 185*dpx

            background: Rectangle {
                color: "#265aef"
            }
            nameButton: "确定"
            onClicked: {
                if(mapName.name===""||mapPath.name==="")
                {
                    earthPopup.text="地图名称或路径不能为空"
                    earthPopup.visible=true
                    timer.start()
                    console.log("地图名称或者路径不能为空");
                }
                else
                {
                    signalAddMap(mapName.name,mapPath.name,mapLat.name,mapLon.name,mapRDLat.name,mapRDLon.name);
                    //                  signalAddMap(mapName.name,mapPath.name);
                }
            }
        }
    }
//    PopupButton {
//        y: 187*dpy
//        x: 256*dpx
//        background: Rectangle {
//            color: "#265aef"
//        }
//        nameButton: "确定"
//        onClicked: {
//            if(mapName.name===""||mapPath.name==="")
//            {
//                earthPopup.text="地图名称或路径不能为空"
//                earthPopup.visible=true
//                timer.start()
//                console.log("地图名称或者路径不能为空");
//            }
//            else
//            {
//                signalAddMap(mapName.name,mapPath.name,mapLat.name,mapLon.name);
//                //                  signalAddMap(mapName.name,mapPath.name);
//            }
//        }
//    }

    ScePopup {
        id: earthPopup
        visible: false
        anchors.centerIn: parent
    }
    Timer {
        id: timer
        interval: 2500
        repeat: fasle
        running: fasle
        triggeredOnStart: false
        onTriggered: {
            earthPopup.visible = false
        }
    }
    function earthTip()
    {
        earthPopup.text="地图名称重复，请重新输入"
        earthPopup.visible=true
        timer.start()
    }
    function qingkong() {
        mapPath.name = ""
        //        mapLon.name = ""
        mapName.name = ""
        //        mapLat.name = ""
    }

}
