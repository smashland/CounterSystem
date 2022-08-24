//                                                  新建方案
import QtQuick 2.12
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls.Styles 1.4
import "../Common"
import "../Exercise"

Item {
    id: scenarionew
    width: 1165 *dpx
    height: 710 *dpy
    Image {
        id: loginImage
        anchors.fill: parent
        source: "qrc:/Image/Popup_bg_21.png"
    }
    CloseButton {
        anchors.right: scenarionew.right
        anchors.rightMargin: 70 *dpx
        anchors.top: scenarionew.top
        anchors.topMargin: 70 *dpy
        onClicked: scenarionew.visible = false
    }

    PopupTitle {
        name: ("新建")
    }
    TransverseLine {
        x: 80 *dpx
        y: 95*dpy
    }

    Rectangle {
        id: nameItem
        x: 90 *dpx
        y: 140 * dpy
        Rectangle {
            color: "transparent"
            Text {
                id: nameItemText
                width: nameItemText.contentWidth
                height: 40 *dpy
                color: "#ffffff"
                text: qsTr("方案名称:")
                font.pixelSize: 17*dpx;
                font.family: "Microsoft YaHei";
                verticalAlignment: Text.AlignVCenter
            }
        }
        Rectangle {
            x: nameItemText.contentWidth + 20 *dpx
            width: 440*dpx
            height: 40 *dpy
            color: "#1d4f88"
            border.color: "#26abef"
            TextInput {
                id: nameItemContent
                x: 10 *dpx
                width: 190*dpx
                height: 34 *dpy
                font.pixelSize: 17*dpx
                color: "#ffffff"
                clip: true
                font.family: "Microsoft YaHei"
                verticalAlignment: Text.AlignVCenter
            }

        }
    }
    Rectangle {
        x: 90 *dpx
        y: 160 * dpy + nameItemContent.height
        Text {
            id: tianjiarenyuan
            width: tianjiarenyuan.contentWidth
            //            height: 40 *dpy
            color: "#ffffff"
            text: qsTr("添加人员:")
            font.pixelSize: 17*dpx;
            font.family: "Microsoft YaHei";
            verticalAlignment: Text.AlignVCenter
        }
        RowLayout {
            id: columText
            x: tianjiarenyuan.contentWidth + 20 *dpx
            spacing: 40 *dpx
            RadioButton {
                id:control
                checked: true
                text: qsTr("是")
                indicator: Rectangle {
                    implicitWidth: 18
                    implicitHeight: 18
                    x: control.leftPadding
                    y: parent.height / 2 - height / 2
                    radius: 9
                    border.color: control.down ? "#ffffff" : "#26abef"

                    Rectangle {
                        width: 12
                        height: 12
                        radius: 6
                        anchors.centerIn: parent
                        color: control.down ? "#ffffff" : "#1d4f88"
                        visible: control.checked
                    }
                }

                contentItem: Text {
                    text: control.text
                    opacity: enabled ? 1.0 : 0.3
                    color: "#ffffff"
                    font.pixelSize: 17*dpx;
                    verticalAlignment: Text.AlignVCenter
                    leftPadding: control.indicator.width + control.spacing
                }
            }
            RadioButton {
                id: control1
                text: qsTr("否")
                indicator: Rectangle {
                    implicitWidth: 18
                    implicitHeight: 18
                    x: control1.leftPadding
                    y: parent.height / 2 - height / 2
                    radius: 9
                    border.color: control1.down ? "#ffffff" : "#26abef"

                    Rectangle {
                        width: 12
                        height: 12
                        radius: 6
                        anchors.centerIn: parent
                        color: control1.down ? "#ffffff" : "#1d4f88"
                        visible: control1.checked
                    }
                }

                contentItem: Text {
                    text: control1.text
                    opacity: enabled ? 1.0 : 0.3
                    color: "#ffffff"
                    font.pixelSize: 17*dpx;
                    verticalAlignment: Text.AlignVCenter
                    leftPadding: control1.indicator.width + control1.spacing
                }
            }

        }
    }


    Text {
        id: weizhixinxi
        x: 90 *dpx
        y: 160 * dpy + nameItemContent.height + tianjiarenyuan.contentHeight + 30 *dpy
        width: weizhixinxi.contentWidth
        height: weizhixinxi.contentHeight
        text: qsTr("人员信息表")
        font.pixelSize: 18*dpx;
        color: "#ffffff";
        font.family: "Microsoft YaHei"
    }
    Rectangle {
        y: weizhixinxi.contentHeight + weizhixinxi.y + 10 *dpy
        x: 90 *dpx
        width: 985 *dpx
        height: 2 *dpy
        color: "#3b6daa"
    }

    Rectangle {
        x: 90 *dpx
        y: weizhixinxi.contentHeight + weizhixinxi.y + 10 *dpy + 10 *dpy
        width: 985
        height: 144 *dpy
        color: "transparent"

        Component {
            id: headerView
            Item {
                width: parent.width
                height: 40 *dpy
                Rectangle {
                    anchors.fill: parent
                    color: "#2D5689"
                }

                Row {
                    spacing: 56 *dpx
                    x: 25 *dpx
                    height: 40 *dpy
                    Text {
                        text: "设备编号"
                        width: 70 *dpx
                        height: 40 *dpy
                        color: "#ffffff"
                        font.pixelSize: 16
                        font.family: "Microsoft YaHei";
                        font.bold: true
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                    }
                    Text {
                        //                        x: 170 *dpx
                        text: "人员姓名"
                        width: 80 *dpx
                        height: 40 *dpy
                        color: "#ffffff"
                        font.pixelSize: 16
                        font.family: "Microsoft YaHei";
                        font.bold: true
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                    }
                    Text {
                        //                        x: 572 *dpx
                        text: "人员职务"
                        width: 110 *dpx
                        height: 40 *dpy
                        color: "#ffffff"
                        font.pixelSize: 16
                        font.family: "Microsoft YaHei";
                        font.bold: true
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                    }
//                    Text {
//                        //                        x: 572 *dpx
//                        text: "通讯装备"
//                        width: 110 *dpx
//                        height: 40 *dpy
//                        color: "#ffffff"
//                        font.pixelSize: 16
//                        font.family: "Microsoft YaHei";
//                        font.bold: true
//                        horizontalAlignment: Text.AlignHCenter
//                        verticalAlignment: Text.AlignVCenter
//                    }
                    Text {
                        //                        x: 572 *dpx
                        text: "红蓝方"
                        width: 80 *dpx
                        height: 40 *dpy
                        color: "#ffffff"
                        font.pixelSize: 16
                        font.family: "Microsoft YaHei";
                        font.bold: true
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                    }
                    Text {
                        //                        x: 572 *dpx
                        text: "是否是人质"
                        width: 138 *dpx
                        height: 40 *dpy
                        color: "#ffffff"
                        font.pixelSize: 16
                        font.family: "Microsoft YaHei";
                        font.bold: true
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                    }
                    Text {
                        //                        x: 572 *dpx
                        text: "操作"
                        width: 180 *dpx
                        height: 40 *dpy
                        color: "#ffffff"
                        font.pixelSize: 16
                        font.family: "Microsoft YaHei";
                        font.bold: true
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                    }
                }
            }
        }

        Component {
            id: delegate
            Item {
                id: wrapper
                width: parent.width
                height: 50 *dpy
                Rectangle {
                    anchors.fill: parent
                    color: index%2 ? "#2D5689" : "#4671a6"
                }

                Row {
                    spacing: 56 *dpx
                    x: 25*dpx
                    height: 40 *dpy
                    //                    arrayWidthSpacing: [20, 30]
                    Text {
                        text: "0"
                        width: 70 *dpx
                        height: 50 *dpy
                        color: "#ffffff"
                        font.pixelSize: 16
                        font.family: "Microsoft YaHei";
                        font.bold: true
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                    }
                    Text {
                        //                        x: 170 *dpx
                        text: "人姓名"
                        width: 80 *dpx
                        height: 50 *dpy
                        color: "#ffffff"
                        font.pixelSize: 16
                        font.family: "Microsoft YaHei";
                        font.bold: true
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                    }
                    Text {
                        //                        x: 572 *dpx
                        text: "职务"
                        width: 110 *dpx
                        height: 50 *dpy
                        color: "#ffffff"
                        font.pixelSize: 16
                        font.family: "Microsoft YaHei";
                        font.bold: true
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                    }
//                    Text {
//                        //                        x: 572 *dpx
//                        text: "通讯备"
//                        width: 110 *dpx
//                        height: 50 *dpy
//                        color: "#ffffff"
//                        font.pixelSize: 16
//                        font.family: "Microsoft YaHei";
//                        font.bold: true
//                        horizontalAlignment: Text.AlignHCenter
//                        verticalAlignment: Text.AlignVCenter
//                    }
                    Text {
                        //                        x: 572 *dpx
                        text: "方"
                        width: 80 *dpx
                        height: 50 *dpy
                        color: "#ffffff"
                        font.pixelSize: 16
                        font.family: "Microsoft YaHei";
                        font.bold: true
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                    }
                    Text {
                        //                        x: 572 *dpx
                        text: "是人质"
                        width: 138 *dpx
                        height: 50 *dpy
                        color: "#ffffff"
                        font.pixelSize: 16
                        font.family: "Microsoft YaHei";
                        font.bold: true
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                    }
                    Row {
                        y: 10 *dpy
                        //                        width: 370 *dpx
                        //                        height: 30 *dpy
                        spacing: 15 * dpx
                        ViewButton {
                            name: qsTr("修改")
                            color: viewColor_shuaxin
                            viewImage: "\ue6a5"

                        }
                        ViewButton {
                            name: qsTr("加载")
                            color: viewColor_xinjian
                            viewImage: "\ue607"
                        }
                    }
                }

            }
        }

        Component {
            id: phoneModel;
            ListModel {
                ListElement{
                    name: "1"
                    cost: "轻武器激光对抗系统1"
                }
            }

        }

        ListView {
            id: listView
            anchors.fill: parent
            delegate: delegate
            model: phoneModel.createObject(listView)
            header: headerView
            focus: true
        }
    }

    Item {
        x: 90 *dpx
        y: weizhixinxi.contentHeight + weizhixinxi.y + 10 *dpy + 10 *dpy + 146*dpy
        width: 985
        height: 50 *dpy

        Rectangle {
            anchors.fill: parent
            color: "#4671a6"
        }

        Row {
            spacing: 54 *dpx
            x: 25 *dpx
            height: 40 *dpy
            Rectangle {
                y: 10 *dpy
                width: 70 *dpx
                height: 30 *dpy
                color: "#1d4f88"
                border.color: "#3b6daa"
                TextInput {
                    x: 10 *dpx
                    width: 60*dpx
                    height: 30 *dpy
                    font.pixelSize: 15*dpx
                    color: "#ffffff"
                    clip: true
                    font.family: "Microsoft YaHei"
                    verticalAlignment: Text.AlignVCenter
                }
            }
            Rectangle {
                y: 10 *dpy
                width: 80 *dpx
                height: 30 *dpy
                color: "#1d4f88"
                border.color: "#3b6daa"
                TextInput {
                    x: 10 *dpx
                    width: 70*dpx
                    height: 30 *dpy
                    font.pixelSize: 15*dpx
                    color: "#ffffff"
                    clip: true
                    font.family: "Microsoft YaHei"
                    verticalAlignment: Text.AlignVCenter
                }
            }
            ComboBox {
                id: combobox_renyuan
                y: 10*dpy
                width: 110 *dpx
                height: 30 *dpy
                model: ["士兵"]
                delegate: ItemDelegate {
                    width: 110 *dpx
                    height: 30 *dpy
                    contentItem: Text {
                        text: modelData
                        color: "black"
                        font.pixelSize: 16
                        font.family: "Microsoft YaHei"
                        verticalAlignment: Text.AlignVCenter
                    }
                }
                contentItem: Text {
                    leftPadding: 10*dpx
                    text: combobox_renyuan.displayText
                    font.pixelSize: 16
                    color: "#ffffff"
                    font.family: "Microsoft YaHei"
                    verticalAlignment: Text.AlignVCenter
                }
                background: Rectangle {
                    implicitWidth: 110*dpx
                    implicitHeight: 30 *dpy
                    color: "#1d4f88"
                    border.color: "#26abef"
                }
            }
            ComboBox {
                id: combobox_redblue
                y: 10*dpy
                width: 110 *dpx
                height: 30 *dpy
                model: ["蓝","红"]
                delegate: ItemDelegate {
                    width: 80 *dpx
                    height: 30 *dpy
                    contentItem: Text {
                        text: modelData
                        color: "black"
                        font.pixelSize: 16
                        font.family: "Microsoft YaHei"
                        verticalAlignment: Text.AlignVCenter
                    }
                }
                contentItem: Text {
                    leftPadding: 10*dpx
                    text: combobox_redblue.displayText
                    font.pixelSize: 16
                    color: "#ffffff"
                    font.family: "Microsoft YaHei"
                    verticalAlignment: Text.AlignVCenter
                }
                background: Rectangle {
                    implicitWidth: 80*dpx
                    implicitHeight: 30 *dpy
                    color: "#1d4f88"
                    border.color: "#26abef"
                }
            }
            Row {
                width: 120 *dpx
                y: 10 *dpy
                spacing: 14 *dpx
                RadioButton {
                    id:control3
                    checked: true
                    text: qsTr("是")
                    indicator: Rectangle {
                        implicitWidth: 18
                        implicitHeight: 18
                        y: parent.height / 2 - height / 2
                        radius: 9
                        border.color: control3.down ? "#ffffff" : "#26abef"

                        Rectangle {
                            width: 12
                            height: 12
                            radius: 6
                            anchors.centerIn: parent
                            color: control3.down ? "#ffffff" : "#1d4f88"
                            visible: control3.checked
                        }
                    }

                    contentItem: Text {
                        text: control3.text
                        opacity: enabled ? 1.0 : 0.3
                        color: "#ffffff"
                        font.pixelSize: 17*dpx;
                        verticalAlignment: Text.AlignVCenter
                        leftPadding: 20*dpx
                    }
                }
                RadioButton {
                    id: control4
                    text: qsTr("否")
                    indicator: Rectangle {
                        implicitWidth: 18
                        implicitHeight: 18
                        y: parent.height / 2 - height / 2
                        radius: 9
                        border.color: control4.down ? "#ffffff" : "#26abef"

                        Rectangle {
                            width: 12
                            height: 12
                            radius: 6
                            anchors.centerIn: parent
                            color: control4.down ? "#ffffff" : "#1d4f88"
                            visible: control4.checked
                        }
                    }

                    contentItem: Text {
                        text: control4.text
                        opacity: enabled ? 1.0 : 0.3
                        color: "#ffffff"
                        font.pixelSize: 17*dpx;
                        verticalAlignment: Text.AlignVCenter
                        leftPadding: 20*dpx
                    }
                }
            }

            ViewButton {
                y: 10 *dpy
                name: qsTr("确定")
                color: viewColor_xinjian
                viewImage: "\ue8ad"
            }
        }

    }
    Item {
        x: 90 *dpx
        y: weizhixinxi.contentHeight + weizhixinxi.y + 10 *dpy + 10 *dpy + 146*dpy + 52 *dpy
        width: 985
        height: 40 *dpy
        Rectangle {
            anchors.fill: parent
            color: "#2D5689"
            Text {
                anchors.fill: parent
                text: qsTr("+ 添加人员")
                font.pixelSize: 17*dpx;
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                color: "#ffffff"
                font.family: "Microsoft YaHei"
                font.bold: true
            }
        }
    }
    Row {
        spacing: 15 *dpx
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 60 *dpy
        x: 444*dpx
        PopupButton {
            background: Rectangle {
                color: "#265aef"
            }

            nameButton: "确定"

        }
        PopupButton {
            background: Rectangle {
                color: "#1d4f88"
            }
            nameButton: "取消"
        }
    }


}
