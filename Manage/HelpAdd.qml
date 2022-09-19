import QtQuick 2.12
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import MyItem 1.0
import "../Common"
import "../Exercise"

Rectangle {
    id: helpAdd
    width: 450 *dpx
    height: 350 *dpy
    color: "transparent"
    PopupButton {
        anchors.bottom: parent.bottom
        x: 181*dpx
        background: Rectangle {
            color: "#265aef"
        }
        nameButton: "添加"
//        onClicked:
    }

    Rectangle {

        width: 450 *dpx
        height: 310 *dpy
        color: "transparent"

        Component {
            id: delegate
            Item {
                id: wrapper
                width: parent.width
                height: 38 *dpy
                Rectangle {
                    anchors.fill: parent
                    color: index%2 ? "#4671a6" : "#2D5689"
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
                    anchors.centerIn: parent
                    color: "#ffffff"
                    font.pixelSize: 16*dpx
                    font.family: "MicrosoftYaHei";
                    verticalAlignment: Text.AlignVCenter
                }
            }
        }

        Component {
            id: listModel;
            ListModel {

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
