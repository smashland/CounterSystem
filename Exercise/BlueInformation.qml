//                                                            蓝色人员
import QtQuick 2.12
import QtQuick.Controls 2.15
import "../Common"

Item {
    width: 370 *dpx
    height: 420 *dpy
    Image {
        anchors.fill: parent
        source: "qrc:/Image/Blue_bg_all.png"
    }

    Text {
        id: lanfang
        x: (parent.width - lanfang.contentWidth) / 2
        y: 20 *dpy
        text: qsTr("蓝方")
        font.pixelSize: 22*dpx;
        color: "#ffffff";
        font.family: "MicrosoftYaHei-Bold";
    }
    Text {
        id: zongrenshu
        text: qsTr("总人数：")
        x: 20
        y: 25 *dpy
        font.pixelSize: 14*dpx;
        color: "#ffffff";
        font.family: "MicrosoftYaHei-Bold";
    }

    Text {
        id: zaixianrenshu
        text: qsTr("战损人数：")
        anchors.right: parent.right
        anchors.rightMargin: 20
        y: 25 *dpy
        font.pixelSize: 14*dpx;
        color: "#ec4747";
        font.family: "MicrosoftYaHei-Bold";
    }

    Rectangle {
        x: 20
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 20
        width: 330
        height: 314 *dpy
        color: "transparent"

        Component {
            id: delegate
            Item {
                id: wrapper
                width: parent.width
                height: 44 *dpy
                Rectangle {
                    anchors.fill: parent
                    opacity: 0.5
                    color: Qt.rgba(18/255, 18/255, 18/255, 0.5);
                }
                MouseArea {
                    anchors.fill: parent
                    hoverEnabled: true
                    onClicked: {
                        mouse.accepted = true
                        wrapper.ListView.view.currentIndex = index
                    }
                }
                Text {
                    text: name
                    x: 20 *dpx
                    height: 36 *dpy
                    color: "#ffffff"
                    font.pixelSize: 16*dpx
                    verticalAlignment: Text.AlignVCenter
                }
                Row {
                    spacing: 12*dpx
                    anchors.right: parent.right
                    anchors.rightMargin: 10
                    y: 10
                    Rectangle {
                        width:24*dpy
                        height: 24*dpy
                        color: "transparent"
                        Image {
                            anchors.fill: parent
                            source: "qrc:/Image/icon/wuqi.svg"
                        }
                    }
                    Rectangle {
                        width:24*dpy
                        height: 24*dpy
                        color: "transparent"
                        Image {
                            anchors.fill: parent
                            source: "qrc:/Image/icon/toukui.svg"
                        }
                    }
                    Rectangle {
                        width:30*dpx
                        height: 16*dpy
                        color: "transparent"
                        y: 4 *dpy
                        Text {
                            text: qsTr(progressBar.value*100 + "%")
                            verticalAlignment: Text.AlignVCenter
                            horizontalAlignment: Text.AlignHCenter
                            anchors.fill: parent
                            font.pixelSize: 14*dpx
                            color: "#3f9c41"
                            font.family: "Microsoft YaHei"
                        }
                    }
                    Rectangle {
                        id: setListview
                        width:16*dpy
                        height: 16*dpy
                        color: "transparent"
                        y: 4 *dpy
                        Image {
                            anchors.fill: parent
                            source: "qrc:/Image/icon/shezhixitongshezhigongnengshezhishuxing.svg"
                        }
                        MouseArea {
                            anchors.fill: parent
                            onClicked: contextMenu.visible = true
                        }
                    }
                }
                Rectangle {
                    y: 36*dpy
                    ProgressBar{
                        id:progressBar
                        value: 0.2
                        width: 330
                        height: 10
                        background: Rectangle {
                            implicitWidth: progressBar.width
                            implicitHeight: progressBar.height
                            color: "#121212"
                            opacity: 0.7
                        }

                        contentItem: Item {
                            Rectangle {
                                width: progressBar.visualPosition * progressBar.width
                                height: progressBar.height
                                color: "#3f9c41"
                            }
                        }
                    }
                  }
            }
        }

        Component {
            id: listModel;
            ListModel {
                ListElement{
                    name: "1sdS速度"
                }
                ListElement{
                    name: "1sdS速度"
                }
            }

        }

        ListView {
            id: listView
            anchors.fill: parent
            delegate: delegate
            spacing: 1*dpy
            model: listModel.createObject(listView)
            focus: true
            ScrollBar.vertical: ScrollBar {
                id: scrollBar
            }

        }

    }
    SetList {
        id: contextMenu
        visible: false
    }


}
