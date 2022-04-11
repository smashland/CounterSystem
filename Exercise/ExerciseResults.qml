//                                        击杀情况
import QtQuick 2.12
import QtQuick.Controls 2.15
import Qt.labs.qmlmodels 1.0
import "../Common"

Item {
    width: 1184 *dpx
    height: 760 *dpy
    Image {
        id: loginImage
        anchors.fill: parent
        source: "qrc:/Image/Popup_bg_20.png"
    }

    PopupTitle {
        name: "演习结果"
        icon:"\ue654"
    }
    TransverseLine {
        x: 80 *dpx
        y: 95*dpy
    }

    Rectangle{
        id:header
        y: 136*dpy
        x: 80 *dpx
        width: 1024 *dpx
        height: 40*dpy

        Row{
            spacing: 0

            Repeater{
                model: ["属方","总人数","受伤人数","死亡人数","得分情况"]

                Rectangle{
                    width: header.width/5
                    height: header.height
                    color: "#4671a6"
                    Text {
                        text: modelData
                        anchors.centerIn: parent
                        font.pointSize: 14*dpx
                        color: "white"
                    }
                }
            }
        }
    }

    TableView {
        id: tableview
        y: 176*dpy
        x: 80 *dpx
        width: 1024 *dpx
        height: 102 *dpy
        clip: true

        model: TableModel {
            TableModelColumn { display: "party" }
            TableModelColumn { display: "total" }
            TableModelColumn { display: "hurt" }
            TableModelColumn { display: "die" }
            TableModelColumn { display: "fraction" }

            rows: [
                {
                    "party": "红",
                    "total": "199",
                    "hurt": "5",
                    "die": "9",
                    "fraction":"99"
                },
                {
                    "party": "蓝",
                    "total": "199",
                    "hurt": "5",
                    "die": "9",
                    "fraction":"99"
                },

            ]
        }

        delegate: Rectangle {
            implicitWidth: 204.8*dpx
            implicitHeight: 50*dpy
            color:index%2 ? "#4671a6" : "#2D5689"

            Text {
                text: display
                anchors.centerIn: parent
                height: 50 *dpy
                color: "#ffffff"
                font.pixelSize: 18*dpx
                font.family: "MicrosoftYaHei";
                verticalAlignment: Text.AlignVCenter
            }
        }
    }

    Row {
       spacing: 24 *dpx
       y: 298 *dpy
       x: 80 *dpx
       Rectangle {
           width :500*dpx
           height: 320*dpy
//           color: "#4a78b1"
           color: Qt.rgba(74/255,120/255,177/255,0.3)
           LoopChart {
                width :500
                height: 500
           }
       }

       Rectangle {
           width :500*dpx
           height: 320*dpy
//           color: "#4a78b1"
           color: Qt.rgba(74/255,120/255,177/255,0.3)
       }
    }

    Row {
        spacing: 15 *dpx
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 60 *dpy
        x: 375.5*dpx
        PopupButton {
            id: save
             width: 150*dpx
            background: Rectangle {
                color: "#265aef"
                Text {
                    id: popupText
                    height: 36 *dpy
                    width: 150*dpx
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                    text: "保存演习数据"
                    font.pixelSize: 16*dpx
                    color: "#ffffff"
                    font.family: "Microsoft YaHei"
                }
            }

//            nameButton: "保存演习数据"

        }
        PopupButton {
//            id: print
            width: 150*dpx
           background: Rectangle {
               color: "#265aef"
               Text {
                   height: 36 *dpy
                   width: 150*dpx
                   verticalAlignment: Text.AlignVCenter
                   horizontalAlignment: Text.AlignHCenter
                   text: "打印演习报告"
                   font.pixelSize: 16*dpx
                   color: "#ffffff"
                   font.family: "Microsoft YaHei"
               }
           }

//            nameButton: "打印演习报告"

        }
        PopupButton {
            background: Rectangle {
                color: "#1d4f88"
            }
            nameButton: "取消"
        }
    }
}
