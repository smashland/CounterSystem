//                                        击杀情况
import QtQuick 2.12
import QtQuick.Controls 2.15
import "../Common"

Item {
    width: 930 *dpx
    height: 560 *dpy
    Image {
        id: loginImage
        anchors.fill: parent
        source: "qrc:/Image/Popup_bg_20.png"
    }

    PopupTitle {
        name: qsTr("击杀情况")
        icon: "\ue602"
    }
    TransverseLine {
        x: 80 *dpx
        y: 95*dpy
    }

    Rectangle {
        x: 80
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 30
        width: 770
        height: 414 *dpy
        color: "transparent"

        Component {
            id: delegate
            Item {
                id: wrapper
                width: parent.width
                height: 58 *dpy
                Rectangle {
                    anchors.fill: parent
                    opacity: 0.5
                    color: index%2 ? "#4671a6" : "#2D5689"
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
                    height: 50 *dpy
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
