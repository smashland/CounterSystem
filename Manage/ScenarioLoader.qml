//                                       方案管理
//import QtQuick 1.1
import QtQuick 2.12
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import Qt.labs.platform 1.1
import Qt.labs.qmlmodels 1.0
import "../Common"
import "../Exercise"

Rectangle {
    id: scenarioLoader
    anchors.fill: parent
    color: "transparent"
    Item {
        id: backgroundItem
        width: 1226 *dpx
        height: 787 *dpy
        anchors.centerIn: parent
        Image {
            id: loginImage
            anchors.fill: parent
            source: "qrc:/Image/Popup_bg_20.png"
        }
        CloseButton {
            anchors.right: backgroundItem.right
            anchors.rightMargin: 70 *dpx
            anchors.top: backgroundItem.top
            anchors.topMargin: 70 *dpy
            onClicked: footerBar.btnScenario.checked = false
        }
        PopupTitle {
            name: ("方案管理")
            icon: "\ue678"
        }
        TransverseLine {
            x: 80 *dpx
            y: 95*dpy
        }

        Row {
            x: 250 *dpx
            y: 54 *dpx
            spacing: 10*dpx
            Rectangle {
                color: "transparent"
                width: 20*dpx
                height: 20*dpx
                Image {
                    anchors.fill:parent
                    source: "qrc:/Image/icon/tishi.svg"
                }
            }
            Rectangle {

                color: "transparent"
                Text {
                    text: qsTr("点击修改可跳转方案管理页面手动拖拽进行修改，也可选择修改页面进行修改")
                    font.pixelSize: 16*dpx;
                    color: "#faba2f";
                    font.family: "Microsoft YaHei"
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                }
            }
        }

        Row
        {
            x: 80 *dpx
            y: 115 *dpy
            spacing: 15*dpx
            ViewButton {
                name: qsTr("新建")
                color: viewColor_xinjian
                viewImage: "\ue624"
                MouseArea{
                    anchors.fill: parent
                    onClicked: scenarioNew.visible= true
                }
            }
            ViewButton {
                name: qsTr("导入")
                color: viewColor_daoru
                viewImage: "\ue645"
            }
            ViewButton {
                name: qsTr("全部刷新")
                color: viewColor_shuaxin
                viewImage: "\ue600"
                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        $app.allData.clearAllInfo();
                    }
                }
            }
        }

        Rectangle {
            y: 115*dpy
            anchors.right: parent.right
            anchors.rightMargin: 80*dpx
            width:  380*dpx
            height:  34*dpy
            color: "#082e5c"
            radius: 2
            border.color: "#32b8ff"

            TextInput {
                id: scenarioTextInput
                width: 380*dpx
                x: 20*dpx
                height: 34*dpy
                color: "#dcecff"
                activeFocusOnPress: true
                clip: true
                verticalAlignment: Text.AlignVCenter
                font.pixelSize: 14*dpx
            }

            Button {
                id: search
                y: 2 *dpy
                anchors.right: parent.right
                anchors.rightMargin: 10*dpx
                width:   24*dpy
                height:  24*dpy

                Text {
                    id: iconText
                    width: 24*dpx
                    height: 24*dpx
                    text: qsTr("\ue6f3")
                    color: "#ffffff"
                    font.family: "iconfont"
                    font.pixelSize: 22*dpx
                    verticalAlignment: Text.AlignVCenter
                }
                background: Rectangle {
                    color: "transparent"
                }
            }

        }

        Rectangle {
            x: 80
            y: 170
            width: 1066
            height: 520 *dpy
            color: "transparent"

            Component {
                id: headerView
                Item {
                    width: parent.width
                    height: 30 *dpy
                    Rectangle {
                        anchors.fill: parent
                        color: "#2D5689"
                    }
                    Text {
                        text: "序号"
                        width: 100 *dpx
                        height: 30 *dpy
                        color: "#ffffff"
                        font.pixelSize: 16
                        font.family: "Microsoft YaHei";
                        font.bold: true
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                    }
                    Text {
                        x: 170 *dpx
                        text: "方案名称"
                        width: 200 *dpx
                        height: 30 *dpy
                        color: "#ffffff"
                        font.pixelSize: 16
                        font.family: "Microsoft YaHei";
                        font.bold: true
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                    }
                    Text {
                        x: 572 *dpx
                        text: "操作"
                        width: 370 *dpx
                        height: 30 *dpy
                        color: "#ffffff"
                        font.pixelSize: 16
                        font.family: "Microsoft YaHei";
                        font.bold: true
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                    }
                    //                }
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


                    Text {
                        id: col1
                        text: name
                        width: 100 *dpx
                        height: 50 *dpy
                        color: "#ffffff"
                        font.pixelSize: 16*dpx
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                    }
                    Text {
                        id: col2
                        x: 170 *dpx
                        text: cost
                        width: 200 *dpx
                        height: 50 *dpy
                        color: "#ffffff"
                        font.pixelSize: 16
                        font.family: "Microsoft YaHei"
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                    }
                    Row {
                        x: 572 *dpx
                        y: 10 *dpy
                        width: 370 *dpx
                        height: 30 *dpy
                        spacing: 15 * dpx
                        ViewButton {
                            name: qsTr("修改")
                            color: viewColor_shuaxin
                            viewImage: "\ue6a5"
                            MouseArea {
                                anchors.fill: parent
                                onClicked: {
                                    scenarioRevise.visible = true
                                }
                            }
                        }
                        ViewButton {
                            name: qsTr("加载")
                            color: viewColor_xinjian
                            viewImage: "\ue607"
                        }
                        ViewButton {
                            name: qsTr("刷新")
                            color: viewColor_shuaxin
                            viewImage: "\ue600"
                        }
                        ViewButton {
                            name: qsTr("删除")
                            color: viewColor_shanchu
                            viewImage: "\ue61c"
                            MouseArea {
                                anchors.fill: parent
                                onClicked: {
                                    scenarioRemove.visible = true
                                }
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
    }
}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/
