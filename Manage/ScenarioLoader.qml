//                                       帮助管理
//import QtQuick 1.1
import QtQuick 2.12
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import Qt.labs.platform 1.1
import Qt.labs.qmlmodels 1.0
import "../Common"
import "../Exercise"

//Item {
//    id: scenarioLoader
//    width: 1126 *dpx
//    height: 727 *dpy
//    Image {
//        id: loginImage
//        anchors.fill: parent
//        source: "qrc:/Image/Login_bg.jpg"
//    }
Rectangle {
    id: scenarioLoader
    anchors.fill: parent
    color: "transparent"
    Item {
        id: backgroundItem
        width: 1126 *dpx
        height: 727 *dpy
        anchors.centerIn: parent
        Image {
            id: loginImage
            anchors.fill: parent
            source: "qrc:/Image/Popup_bg_20.png"
        }
        CloseButton {
            anchors.right: backgroundItem.right
            anchors.rightMargin: 50 *dpx
            anchors.top: backgroundItem.top
            anchors.topMargin: 50 *dpy
            onClicked: scenarioLoader.visible = false
        }
    Row {
        id: titleRow
        x: 24 *dpx
        y: 24 *dpx
        spacing: 10*dpx
        Rectangle {
            color: "transparent"
            width: 16*dpx
            height: 16*dpx
            Image {
                anchors.fill:parent
                source: "file"
            }
        }
        Rectangle {
            width: fagl.contentWidth
            color: "transparent"
            Text {
                id: fagl
                text: qsTr("方案管理")
                font.pixelSize: 24*dpx;
                color: "#ffffff";
                font.family: "MicrosoftYaHei-Bold"
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
            }
        }
    }

    Row {
        x: 200 *dpx
        y: 24 *dpx
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
        x: 30 *dpx
        y: 110 *dpy
        spacing: 15*dpx
        ViewButton {
            name: qsTr("新建")
            color: viewColor_xinjian
            viewImage: "qrc:/Image/icon/chuangjiantianjiapiliangtianjia.svg"
            MouseArea{
                anchors.fill: parent
                onClicked: scenarioNew.visible= true
            }
        }
        ViewButton {
            name: qsTr("导入")
            color: viewColor_daoru
            viewImage: "qrc:/Image/icon/daoru.svg"
        }
        ViewButton {
            name: qsTr("全部刷新")
            color: viewColor_shuaxin
            viewImage: "qrc:/Image/icon/shuaxin1.svg"
        }
    }

    Rectangle {
        y: 110*dpy
        anchors.right: parent.right
        anchors.rightMargin: 30*dpx
        width:  400*dpx
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
            anchors.rightMargin: 20*dpx
            width:   24*dpy
            height:  24*dpy
            Image {
                id: search1
                anchors.fill: parent
                source: "qrc:/Image/icon/sousuo-2.svg"
            }
            background: Rectangle {
                color: "transparent"
            }
        }

    }

    Rectangle {
        x: 30
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 30
        width: 1066
        height: 550 *dpy
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

//                RowLayout {
////                    spacing: 8
//                    anchors.fill: parent
//                    arrayWidthSpacing: [20, 30]
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
                            viewImage: "qrc:/Image/icon/bianji-3.svg"
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
                            viewImage: "qrc:/Image/icon/jiazai.svg"
                        }
                        ViewButton {
                            name: qsTr("刷新")
                            color: viewColor_shuaxin
                            viewImage: "qrc:/Image/icon/shuaxin1.svg"
                        }
                        ViewButton {
                            name: qsTr("删除")
                            color: viewColor_shanchu
                            viewImage: "qrc:/Image/icon/guanbi1.svg"
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
