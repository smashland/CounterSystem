//                                         删除
import QtQuick 2.12
import QtQuick.Controls 2.15
import "../Common"


Popup
{
    id: removeDialog
    width: 458 *dpx
    height: 308 *dpy
    x:(parent.width-width)/2
    y:(parent.height-height)/2
    focus: true
    visible: true

    property alias content1: shanchuText.text
    property alias content2: shanchubool.text

    signal yesPutDown()
    signal noPutDown()
    background: BorderImage {
        source: "qrc:/Image/Popup_bg_24.png"
    }


    Rectangle
    {
        anchors.fill: parent
        color: "transparent"
//        Image {
//            id: name
//            anchors.fill: parent
//            source: "qrc:/Image/Popup_bg_24.png"
//        }
        PopupTitle {
            name: ("删除")
        }
        TransverseLine {
            x: 80 *dpx
            y: 95*dpy
        }
    }

    Row {
        x: (438*dpx-shanchuText.contentWidth)/2
        y: 126 *dpy
        spacing: 14 *dpx
        Text {
            width: 44
            height: 44
            text: qsTr("\ue65C")
            color: "yellow"
            font.family: "iconfont"
            font.pixelSize: 44*dpx
            verticalAlignment: Text.AlignVCenter
        }
        Column {
            spacing: 5
            Text {
                id: shanchuText
//                text: qsTr("此操作将永久删除该方案，")
                color: "#ffffff"
                font.pixelSize: 16
                font.family: "Microsoft YaHei"
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }
            Text {
                id: shanchubool
//                text: qsTr("确定删除吗？")
                color: "#ffffff"
                font.pixelSize: 14
                font.family: "Microsoft YaHei"
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }
        }
    }
    Row {
        spacing: 15 *dpx
        anchors.bottom: parent.bottom;
        anchors.bottomMargin: 50
        anchors.horizontalCenter: parent.horizontalCenter;
        x: 133*dpx
        PopupButton {
            id: yesButton
            background: Rectangle {
                color: "#265aef"
            }

            nameButton: "确定"
        }
        PopupButton {
            id: noButton
            background: Rectangle {
                color: "#1d4f88"
            }
            nameButton: "取消"
        }
    }
    Connections {
        target: yesButton
        function onClicked()
        {
            removeDialog.visible = false
            yesPutDown()
        }
    }
    Connections {
        target: noButton
        function onClicked()
        {
            removeDialog.visible = false
            noPutDown()
        }
    }


}

