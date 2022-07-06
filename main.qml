import QtQuick 2.15
import QtQuick.Window 2.15
import MyItem 1.0
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

    property var $app: AppGlobal{}
    property var $appWindow: mainWindow
    property var $cpShow:null
    property var $obShow:null

    /// 用于加载组件
    function loadQml(qmlUrl)
    {
        if(null !== $obShow)
        {
            $obShow.visible = false;
            $obShow.destroy();
        }

        if(null !== $cpShow)
        {
            $cpShow.destroy();
        }

        $cpShow= Qt.createComponent(qmlUrl)

        if (Component.Ready === $cpShow.status)
        {
            $obShow = $cpShow.createObject(mainWindow)
            if(null !== $obShow)
            {
                $obShow.forceActiveFocus();
                return(true);
            }
        }
        else
        {
            return(false);
        }
    }

    LoginCenter {
        id: loginCenter
        anchors.fill: parent
        visible: true
    }

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
