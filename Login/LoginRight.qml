import QtQuick 2.12
import QtGraphicalEffects 1.15
import QtQuick.Controls 2.15
import "../Common"

Item
{
    id: loginRight
    anchors.fill: parent
    Image {
        id: loginImage
        anchors.fill: parent
        source: "qrc:/Image/Login_bg.jpg"
    }
//    Image {
//        anchors.fill: parent
//        source: "qrc:/Image/Login_box_2.png"
//    }
    NavImage {
        anchors.top: parent.top
        anchors.topMargin: 30 *dpy
        anchors.right: parent.right
        anchors.rightMargin: 30 *dpx
    }

//    Login {
//        id: loginRect
//        x: (mainWindow.width-loginRect.width)/2
//        y: (mainWindow.height-loginRect.height)/2
//    }
//    Connect {
//        id: connect
//        y: 950 *dpy
//    }
}
