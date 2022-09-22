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
    Image {
        anchors.fill: parent
        source: "qrc:/Image/Popup_bg_21.png"
    }

    PopupTitle {
        name: ("添加地图")
        icon: "\ue795"
        x: 44 *dpx
        y: 34*dpy
    }

    FileDialog {
        id: fileDialog
        folder: shortcuts.home
        title: qsTr("请选择文件")
        nameFilters: [qsTr("图片 (*.tiff)"),qsTr("文件 (*.xml)"),  qsTr("全部文件 (*.*)")]
        currentFile: document.source
        onAccepted: {

        }
    }
    Column {
        x: 44 *dpx
        y: 84*dpy
        spacing: 15*dpy
        Row {
            spacing: 30*dpx
            SoldierItem {
                text: "地图路径:"
                name: ""
            }
            Button {
                id: xuanzelujing
                width: 100*dpx
                height: 33 *dpy
                background: Rectangle{
                    color: "#000080"
                    Text {
                        id: xzlj
                        text: "选择路径"
                        color: "#ffffff"
                        font.pixelSize: 16*dpx;
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
            text: "       经度:"
            name: ""
        }
        SoldierItem {
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
        anchors.bottomMargin: 35*dpy
        x: 266*dpx
        background: Rectangle {
            color: "#265aef"
        }
        nameButton: "确定"
        onClicked: {

        }
    }

}
