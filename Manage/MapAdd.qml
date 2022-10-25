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
    signal signalAddMap(string name,string path,int lat,int lon)    //添加地图

    Image {
        anchors.fill: parent
        source: "qrc:/Image/wuqi/08-bg.png"
    }   
    CloseButton {
        anchors.right: mapAdd.right
        anchors.rightMargin: 65 *dpx
        anchors.top: mapAdd.top
        anchors.topMargin: 55 *dpy
        onClicked: mapAdd.visible = false
    }

    PopupTitle {
        name: ("添加地图")
        icon: "\ue795"
        x: 60 *dpx
        y: 50*dpy
    }

    FileDialog {
        id: fileDialog
        folder: shortcuts.home
        title: qsTr("请选择文件")
        nameFilters: [qsTr("图片 (*.tif)"),qsTr("文件 (*.xml)"),  qsTr("全部文件 (*.*)")]
        onAccepted: {
            var earthPath=String(fileDialog.currentFile)
            earthPath=earthPath.substr(8)
            mapPath.name=earthPath
            console.log("地图路径"+earthPath);
        }
    }
    Column {
        x: 96 *dpx
        y: 96*dpy
        spacing: 12*dpy
        SoldierItem {
            id:mapName
            text: "地图名称:"
            name: ""
        }
        Row {
            spacing: 30*dpx
            SoldierItem {
                id:mapPath
                text: "地图路径:"
                name: ""
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
            text: "       经度:"
            name: ""
        }
        SoldierItem {
            id:mapLon
            text: "       纬度:"
            name: ""
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
    }
    PopupButton {
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 47*dpy
        x: 256*dpx
        background: Rectangle {
            color: "#265aef"
        }
        nameButton: "确定"
        onClicked: {
            signalAddMap(mapName.name,mapPath.name,mapLat.name,mapLon.name);
            earthManager.saveFile();
            mapAdd.visible = false
        }
    }

}
