import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.1
import MyItem 1.0
import "Login"
import "Manage"
import "Exercise"
import "Common"

Window {
    id: mainWindow
    width: Screen.width
    height: Screen.height
    property bool fullScreen: true

//    flags: fullScreen ? Qt.Window : Qt.FramelessWindowHint
    visible: true
    color: "transparent"
    modality: Qt.ApplicationModal
    flags: Qt.FramelessWindowHint|Qt.Window
    readonly property real dpx:mainWindow.width/width
    readonly property real dpy:mainWindow.height/height

    property var $app: AppGlobal{}
    property var $licCheck:LicItem{}
    property var $appWindow: mainWindow
    property var $cpShow:null
    property var $obShow:null
    property string exitShowLabel: "确定要退出吗?"

    screen:Qt.application.screens[0]

    onVisibilityChanged:
    {
        switch(visibility)
        {
        case 2:
            flags = Qt.FramelessWindowHint|Qt.Window
            width= mainWindow.width + 1
            height= mainWindow.height + 1
            break;
        case 3:
            flags = Qt.Window
            break;
        }
    }

    function fullWindow() {
        mainWindow.visibility = Window.FullScreen;
    }

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

    // 通过license校验显示主界面
    function showMainWindow()
    {
        $app.initSystem();
        $app.startConnect();
        loadQml("qrc:/OsgWindow.qml");
    }

    /// 检查许可失败
    function checkLicenseFaild(errorInfo)
    {
        removeDialog_shouquanma.content1= errorInfo+"，"
        removeDialog_shouquanma.open();
    }

    /// 组件加载完成校验 许可
    Component.onCompleted:
    {
        loadQml("qrc:/Login/LoginCenter.qml");
        $licCheck.checked.connect(showMainWindow)
        $licCheck.showError.connect(checkLicenseFaild);
        $obShow.recive($licCheck.getMD5MachineInfo());
    }

    // 退出程序框上的是和否
    Component
    {
        id: flatButton
        Button
        {
            flat: true
            contentItem: Label
            {
                color:'#FFFFFF'
                text: textForShow
                font
                {
                    pixelSize:22
                    bold:true
                }
                horizontalAlignment:Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }
        }
    }

    RemoveDialog {
        id: removeDialog_shouquanma
        visible: false
        title:"退出"
        content1: "此操作将退出程序，"
        content2: exitShowLabel
        onYesPutDown: {
            $app.exitApp();
            Qt.quit();
        }
        onNoPutDown: {
            removeDialog_shouquanma.close()
            if(exitShowLabel !== removeDialog_shouquanma.content1)
            {
                removeDialog_shouquanma.content1 = exitShowLabel;
            }
        }
    }
    RemoveDialog {
        id: removeDialog_quit
        visible: false
        title:"退出"
        content1: "此操作将退出程序，"
        content2: exitShowLabel
        onYesPutDown: {
            $app.exitApp();
            Qt.quit()
        }
    }

    RemoveDialog {
        id: comErrorDialog
        visible: false
        title:"错误"
        content1: "串口选择错误，"
        content2: "请重新选择！"
        onYesPutDown: {
            comErrorDialog.close()
//            $app.exitApp();
//            Qt.quit();
        }
//        onNoPutDown: {
//            comErrorDialog.close()
//            if(exitShowLabel !== removeDialog_shouquanma.content1)
//            {
//                removeDialog_shouquanma.content1 = exitShowLabel;
//            }
//        }
    }

}
