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

    LoginCenter {
        id: loginCenter
        anchors.fill: parent
        visible: true
    }
    // 通过license校验显示主界面
        function  showMainWindow()
        {
            /// 检查许可的工作已经完成
            objCheckLic.destroy();
    //        if($app.initSystem()&&$app.startConnect())
    //        {
    //            popupRectWin.open();
    //        }
        }


        // 保存许可文件
        function saveLicense(licInfo)
        {
              if(objCheckLic.saveLicense(licInfo))
              {
                  if($app.initSystem()&&$app.startConnect())
                  {
                      loadQml("qrc:/OsgWindow.qml");
//                      popupRectWin.open();
                  }
              }
        }

        // 没有许可或者许可失败 获取硬件信息
        function getMachineInfo(sMachineInfo)
        {
            console.log("许可码"+sMachineInfo);
            if(loadQml("qrc:/Login/LoginCenter.qml"))
            {
                  $obShow.nextFrame.connect(saveLicense)
                  $obShow.recive(sMachineInfo)
            }

        }

        /// 检查许可失败
        function checkLicenseFaild(errorInfo)
        {
            exitPopupLable.text = errorInfo + " " + exitShowLabel;
            exitPopup.open();
        }

    //     许可校验
        LicItem
        {
            id:objCheckLic;
            /// 组件加载完成校验 许可
            Component.onCompleted:
            {
                objCheckLic.checked.connect(showMainWindow)
                objCheckLic.showError.connect(checkLicenseFaild);
                objCheckLic.checkLicense()
            }

        }

    //    // 连接失败
    //    PopupDef {
    //        id: popupRectDef
    ////        visible: false
    //        x:(mainWindow.width-popupRectDef.width)/2
    //        y:(mainWindow.height-popupRectDef.height)/2
    //    }

    //    // 连接成功
    //    PopupWin {
    //        id: popupRectWin
    ////        visible: false
    //        x:(mainWindow.width-popupRectWin.width)/2
    //        y:(mainWindow.height-popupRectWin.height)/2
    //    }

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

    // 退出弹出框
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
            console.log("on no clicked")
            exitPopup.close();
            if(exitShowLabel !== exitPopupLable.text)
            {
                if(null === $obShow)
                {
                    getMachineInfo(objCheckLic.getMD5MachineInfo());
                }
                exitPopupLable.text = exitShowLabel;
            }
        }
    }

    // 退出系统弹出退出弹出框
    Connections
    {
        target: $app
        function onExitSystem()
        {
            exitPopup.open()
            if(!$app.settings.bIsStart)
            {
                exitPopup.open()
            }
        }
    }
}
