//                                        击杀情况
import QtQuick 2.12
import QtQuick.Controls 2.15

Item {
    width: 830 *dpx
    height: 500 *dpy
    Image {
        id: loginImage
        anchors.fill: parent
        source: "qrc:/Image/Popup_bg_20.png"
    }

    Row {
        x: 24 *dpx
        y: 24 *dpx
        spacing: 10*dpx
        Image {
            width: 24*dpx
            height: 24*dpx
            anchors.fill:parent
            source: "qrc:/Image/icon/tongzhigonggao.svg"
        }
        Text {
            text: qsTr("击杀情况")
            font.pixelSize: 24*dpx;
            color: "#ffffff";
            font.family: "MicrosoftYaHei-Bold"
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
        }
    }

    Rectangle {
        x: 30
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


//    Rectangle {
//        x: 30
//        anchors.bottom: parent.bottom
//        anchors.bottomMargin: 30
//        width: 770
//        height: 414 *dpy
//        color: "transparent"

//        Component {
//            id: listviewDelegate
//            Item {
//                id: wrapper
//                width: parent.width
//                height: 50
//                Rectangle {
//                    color: index%2 ? "#4671a6" : "#2D5689"
//                    anchors.fill: parent
//                }
//                Text {
//                    id: name
//                    x: 20
//                    text: name
//                    color: "#f2faff"
//                    font.pixelSize: 14
//                    font.family: "MicrosoftYaHei";
//                }
//            }
//        }
//        ListModel {
//            id: listmodel
//            ListElement {
//                name: "wwww"
//            }
//            ListElement {
//                name: "wwww"
//            }
//            ListElement {
//                name: "wwww"
//            }
//        }

//        ListView {
//            id: listview
//            anchors.fill: parent
//            clip: true
//            spacing: 1*dpy
//            focus: true
//            model: listmodel
//            delegate: listviewDelegate
//            ScrollBar.vertical: ScrollBar {
//                id: scrollBar
//            }
//        }


//    }




}
