import QtQuick 2.6
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import QtQuick.Layouts 1.0
import MyItem 1.0

/// 启动界面
Item
{
    id:root
    focus: true
    Keys.enabled: true
    Keys.onEscapePressed:
    {
        $app.exitApp();
    }

    anchors.centerIn: parent

    /// 启动页面
    Image
    {
        id:background
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        source: $app.localUrl + $app.appPath + "/Data/Image/1.jpg"
    }

    /// 进度条
    RowLayout
    {
        id: rowLayout
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: background.bottom
        anchors.bottomMargin: 50

        Text
        {
            id:showInfo;
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            text: "连接中"
            color: "#FFFF00"
            font
            {
                pixelSize:22
                bold:true
            }
        }

        ProgressBar
        {
            id:connctIndicator
            indeterminate: true
            style: ProgressBarStyle
            {
                background: Rectangle
                {
                    radius: 2
                    color: "transparent"
                    implicitWidth: 200
                    implicitHeight: 24
                }
                progress: Rectangle
                {
                    color: "transparent"

                    // Indeterminate animation by animating alternating stripes:
                    Item
                    {
                        anchors.fill: parent
                        anchors.margins: 1
                        visible: connctIndicator.indeterminate
                        clip: true
                        Row
                        {
                            Repeater
                            {
                                Rectangle
                                {
                                    y: connctIndicator.height/2 - height/2
                                    color: index % 2 ? "#FFFF00" : "transparent"
                                    width: 10 ;
                                    height: width;
                                    radius: width
                                }
                                model: connctIndicator.width / 10 + 2
                            }
                            XAnimator on x
                            {
                                from: -20 ; to: 0
                                loops: Animation.Infinite
                                running: connctIndicator.indeterminate
                                duration:500
                            }
                        }
                    }
                }
            }
        }
    }

    Timer
    {
        id:timer
        interval:5000
        running:false
        onTriggered:
        {
            if(0 === $app.settings.conType)
            {
                connectFaild();
            }
        }
    }

    SelectWifi
    {
        id:showWifi;
        visible: false
        onToConnect:
        {
            tryToConnect();
        }
    }

    /// 连接失败
    function connectFaild()
    {
        connctIndicator.visible = false;

        if(1 === $app.settings.conType)
        {
            showInfo.text = "连接失败";
            showComName.open();
        }
        else
        {
            showWifi.open();
            showInfo.text = "连接超时";
        }

        showInfo.color="#FF0000"
    }

    /// 试着连接
    function tryToConnect()
    {
        showInfo.text = "连接中";
        showInfo.color = "#FFFF00"
        connctIndicator.visible = true;

        timer.start();
    }

    /// 连接串口
    SelectComName
    {
        id:showComName;
        modal: true;
        onToConnect:
        {
            tryToConnect();
        }
    }

    Connections
    {
        target: $app
        function onConnected()
        {
            showInfo.text = "连接成功";
            showInfo.color = "#00FF00";

            if($appWindow.loadQml("qrc:/OsgWindow.qml"))
            {
                $appWindow.showFullScreen();
                //$appWindow.showMaximized();
            }
        }

        /// 连接失败
        function onDisConnected()
        {
            connectFaild();
        }
    }

    Component.onCompleted:
    {
        $app.initSystem();
        $app.startConnect();
        timer.start();
    }
}
