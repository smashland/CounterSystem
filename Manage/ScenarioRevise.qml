//                                                  新建方案
import QtQuick 2.12
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls.Styles 1.4
import "../Common"
import "../Exercise"

Item {
    id: scenarioRevise
    width: 1065 *dpx
    height: 600 *dpy
    Image {
        id: loginImage
        anchors.fill: parent
        source: "qrc:/Image/Popup_bg_21.png"
    }
    CloseButton {
        anchors.right: scenarioRevise.right
        anchors.rightMargin: 50 *dpx
        anchors.top: scenarioRevise.top
        anchors.topMargin: 50 *dpy
        onClicked: scenarioRevise.visible = false
    }

    Rectangle {
        x: 40 *dpx
        y: 40 *dpx
        color: "transparent"
        Text {
            text: qsTr("新建")
            font.pixelSize: 24*dpx;
            color: "#ffffff";
            font.bold: true
            font.family: "MicrosoftYaHei Bold"
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
        }
    }

    Rectangle {
        id: nameItem
        x: 40 *dpx
        y: 110 * dpy
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
        x: 40 *dpx
        y: 130 * dpy + nameItemContent.height
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
        x: 40 *dpx
        y: 130 * dpy + nameItemContent.height + tianjiarenyuan.contentHeight + 30 *dpy
        width: weizhixinxi.contentWidth
        height: weizhixinxi.contentHeight
        text: qsTr("人员信息表")
        font.pixelSize: 18*dpx;
        color: "#ffffff";
        font.family: "Microsoft YaHei"
    }
    Rectangle {
        y: weizhixinxi.contentHeight + weizhixinxi.y + 10 *dpy
        x: 40 *dpx
        width: 985 *dpx
        height: 2 *dpy
        color: "#3b6daa"
    }

    Rectangle {
        x: 40 *dpx
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
                    spacing: 30 *dpx
                    x: 10 *dpx
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
                    Text {
                        //                        x: 572 *dpx
                        text: "通讯装备"
                        width: 110 *dpx
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
                    spacing: 30 *dpx
                    x: 10*dpx
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
                    Text {
                        //                        x: 572 *dpx
                        text: "通讯备"
                        width: 110 *dpx
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
                            viewImage: "qrc:/Image/icon/bianji-3.svg"

                        }
                        ViewButton {
                            name: qsTr("加载")
                            color: viewColor_xinjian
                            viewImage: "qrc:/Image/icon/jiazai.svg"
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
        x: 40 *dpx
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
