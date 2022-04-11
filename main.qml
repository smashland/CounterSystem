import QtQuick 2.15
import QtQuick.Window 2.15
import "Login"
import "Manage"
import "Exercise"
import "Common"

Window {
    id: mainWindow
    width: 1920
    height: 1080
    visible: true
    color: "transparent"
    flags: Qt.FramelessWindowHint|Qt.Window
    readonly property real dpx:mainWindow.width/1920.0
    readonly property real dpy:mainWindow.height/1080.0

    Index {
        id: index
        anchors.fill: parent
        visible: true
    }
//    LoginCenter {
//        id: loginCenter
//        anchors.fill: parent
//        visible: true
//    }


    PopupDef {
        id: popupRectDef
        visible: false
        x:(mainWindow.width-popupRectDef.width)/2
        y:(mainWindow.height-popupRectDef.height)/2
    }
    PopupWin {
        id: popupRectWin
        visible: false
        x:(mainWindow.width-popupRectWin.width)/2
        y:(mainWindow.height-popupRectWin.height)/2
    }

}
