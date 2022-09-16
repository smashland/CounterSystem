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
    width: fullScreen ? 1920 : Screen.desktopAvailableWidth
    height: fullScreen ? 1080 : Screen.desktopAvailableHeight
    property bool fullScreen: true

//    flags: fullScreen ? Qt.Window : Qt.FramelessWindowHint
    visible: true
    color: "transparent"
    //    flags: Qt.FramelessWindowHint|Qt.Window
    readonly property real dpx:mainWindow.width/1920.0
    readonly property real dpy:mainWindow.height/1080.0

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
    function  showMainWindow()
    {
        $app.initSystem();
        $app.startConnect();
        loadQml("qrc:/OsgWindow.qml");
    }

    /// 检查许可失败
    function checkLicenseFaild(errorInfo)
    {
        exitPopupLable.text = errorInfo + " " + exitShowLabel;
        exitPopup.open();
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

    /// 退出弹出框
    Popup
    {
        id: exitPopup
        anchors.centerIn: parent
        width: parent.width
        height: parent.height
        modal: true
        background: Rectangle
        {
            opacity:0.0
        }

        /// 退出警告背景
        Rectangle
        {
            id:backeRect
            width: 400
            height: 200
            anchors.centerIn: parent
            color: "#88FF0000"
            border.color: "#FFFF0000"
        }

        /// 退出警告内容
        Label
        {
            id:exitPopupLable
            anchors.top: backeRect.top
            anchors.topMargin: 50
            anchors.horizontalCenter: parent.horizontalCenter
            text: exitShowLabel
            color:"#FFFFFFFF"
            font
            {
                pixelSize:22
                bold:true
            }
        }

        Row
        {
            anchors.bottom: backeRect.bottom;
            anchors.bottomMargin: 50
            anchors.horizontalCenter: parent.horizontalCenter;

            spacing: 50;
            /// 加载两个退出按钮
            Loader
            {
                property string textForShow: '是'
                id:yesLoader
                sourceComponent:flatButton
            }
            Loader
            {
                property string textForShow: '否'
                id:noLoader
                sourceComponent:flatButton
            }
        }

        onClosed:
        {
            /// 将焦点退还给当前显示的对象
            if(null !== $obShow)
            {
                $obShow.forceActiveFocus()
            }
        }
    }

    // 连接退出框的“是”
    Connections
    {
        target: yesLoader.item
        function onClicked()
        {
            $app.exitApp();
            Qt.quit();
        }
    }

    // 连接退出框的“否”
    Connections
    {
        target: noLoader.item
        function onClicked()
        {
            exitPopup.close();
            if(exitShowLabel !== exitPopupLable.text)
            {
                exitPopupLable.text = exitShowLabel;
            }
        }
    }
    RemoveDialog {
        id: removeDialog_quit
        visible: false
        content1: "此操作将退出程序，"
        content2: "确认要退出吗？"
        onYesPutDown: {
            $app.exitApp();
            Qt.quit()
        }
    }

}
