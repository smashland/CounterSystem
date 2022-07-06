import QtQuick 2.15
import QtQuick.Controls 2.15

Menu
{
    id: contextMenu
    implicitWidth: 100*dpx
    MenuItem
    {
        text: "充弹"
    }
    MenuItem { text: "配枪"}
    MenuItem { text: "闭锁"}
    MenuItem { text: "解锁"}
    MenuItem { text: "解除旁白"}
    MenuItem { text: "判死"}
    MenuItem { text: "复活"}
    MenuItem { text: "关机"}
    MenuItem { text: "同步时间"}
    MenuItem { text: "定位"}
}
//Menu {
//    id: option_menu

//    MenuItem {

//        implicitWidth: 120*dpx
//        implicitHeight: 30*dpy
//        background: Rectangle {
//            id:building_button
//            color:"#20252c"
//            border.color: "#d5e2f5"
//            Text {
//                anchors.left: parent.left
//                anchors.leftMargin: 34*dpx
//                anchors.top: parent.top
//                anchors.topMargin: 5*dpy
//                text: qsTr("添加楼房")
//                color: "#d5e2f5"
//            }
//        }

//    }

//    MenuItem {
//        id:building_button2
//        implicitWidth: 120*dpx
//        implicitHeight: 30*dpy
//        background: Rectangle {
//            color: "#20252c"
//            border.color: "#d5e2f5"
//            Text {
//                anchors.left: parent.left
//                anchors.leftMargin: 34*dpx
//                anchors.top: parent.top
//                anchors.topMargin: 5*dpy
//                text: qsTr("添加平房")
//                color: "#d5e2f5"
//            }
//        }

//    }
//}
