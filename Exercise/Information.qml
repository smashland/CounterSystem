//                                        人员信息
import QtQuick 2.12
import QtQuick.Controls 2.15

Item {
    width: 340
    height: 880 *dpy


    Image {
        anchors.fill: parent
        source: "qrc:/Image/Grey_bg_all.png"
    }

    Text {
        id: informationName
        x: (parent.width - informationName.contentWidth) / 2
        y: 20 *dpy
        text: qsTr("人员信息")
        font.pixelSize: 22*dpx;
        color: "#ffffff";
        font.family: "MicrosoftYaHei-Bold";
    }
    Text {
        id: zaixianrenshu
        text: qsTr("在线人数：")
        x: 20
        y: 20 *dpy + informationName.contentHeight + 12 *dpy
        font.pixelSize: 14*dpx;
        color: "#2dc47f";
        font.family: "MicrosoftYaHei-Bold";
    }
    Text {
        id: zongrenshu
        text: qsTr("总人数：")
        anchors.right: parent.right
        anchors.rightMargin: 20
        y: 20 *dpy + informationName.contentHeight + 12 *dpy
        font.pixelSize: 14*dpx;
        color: "#ffffff";
        font.family: "MicrosoftYaHei-Bold";
    }

    Rectangle {
        x: 20
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 20
        width: 300
        height: 774 *dpy
        color: "transparent"

        Component {
            id: delegate
            Item {
                id: wrapper
                width: parent.width
                height: 36 *dpy
                Rectangle {
                    anchors.fill: parent
                    opacity: 0.5
                    color: listView.currentIndex == index ? "#4781c8" : "#121212"
                }
                MouseArea {
                    anchors.fill: parent
                    hoverEnabled: true
                    onClicked: {
                        mouse.accepted = true
                        wrapper.ListView.view.currentIndex = index
                        soldier.visible = true
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


}
