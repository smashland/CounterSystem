//                                               底部播放条

import QtQuick 2.12
import QtQuick.Controls 2.15
import Qt.labs.platform 1.1
import Qt.labs.qmlmodels 1.0
import "../Status" as MyStatus
import "../RePlay" as MyRePlay
//import Qt.labs.settings 1.0

Item {
    id: manoeuvre
    width: mainWindow.width
    height: 136 *dpy
    Image {
        anchors.fill: parent
        source: "qrc:/Image/Start_bg.png"
    }
    signal yesPutDown()
    property var objSetting;
    property string hour:("00")
    property string minute: ("00")
    property string second: ("00")
    property string startTime;
    property string endTime;

    Row {
        x: 80*dpx
        y: (136 *dpy + 50 *dpy - yanxiTime.contentHeight)/2
        Text {
            id: yanxiTime
            width:yanxiTime.contentWidth
            height: yanxiTime.contentHeight
            text: qsTr("演习时间： ")
            font.pixelSize: 20*dpx;
            color: "#ffffff";
            font.family: "Microsoft YaHei";
        }
        Rectangle{
            //shi
            id:hour_rec
            width:hour_text.contentWidth
            height: hour_text.contentHeight
            color: "transparent"
            Label{
                id:hour_text
                text: manoeuvre.hour
                anchors.centerIn: parent
                font.bold: true
                font.pixelSize: 20*dpx;
                color: "#ffffff";
                font.family: "Microsoft YaHei";
            }
        }
        Rectangle{
            //fen
            id:dian
            width:hour_text.contentWidth
            height: hour_text.contentHeight
            color: "transparent"
            Label{
                id:dian_text
                text: ":"
                anchors.centerIn: parent
                font.bold: true
                font.pixelSize: 20*dpx;
                color: "#ffffff";
                font.family: "Microsoft YaHei";
            }
        }
        Rectangle{
            //fen
            id:minute_rec
            width:hour_text.contentWidth
            height: hour_text.contentHeight
            color: "transparent"
            Label{
                id:minute_text
                text: manoeuvre.minute
                anchors.centerIn: parent
                font.bold: true
                font.pixelSize: 20*dpx;
                color: "#ffffff";
                font.family: "Microsoft YaHei";
            }
        }
        Rectangle{
            //fen
            id:diandian
            width:hour_text.contentWidth
            height: hour_text.contentHeight
            color: "transparent"
            Label{
                id:diandian_text
                text: ":"
                anchors.centerIn: parent
                font.bold: true
                font.pixelSize: 20*dpx;
                color: "#ffffff";
                font.family: "Microsoft YaHei";
            }
        }

        Rectangle{
            //miao
            id:second_rec
            width:hour_text.contentWidth
            height: hour_text.contentHeight
            color: "transparent"
            Label{
                id:second_text
                text: manoeuvre.second
                anchors.centerIn: parent
                font.bold: true
                font.pixelSize: 20*dpx;
                color: "#ffffff";
                font.family: "Microsoft YaHei";
            }
        }
    }
    Timer{
        id:time_run
        interval: 1000
        repeat: true
        running: false
        triggeredOnStart: true
        onTriggered: {
            manoeuvre.second++
            if(manoeuvre.second == 60){
                manoeuvre.second= 0
                manoeuvre.minute++
                if(manoeuvre.minute == 60){
                    manoeuvre.minute = 0
                    manoeuvre.hour++
                    if(manoeuvre.hour == 24)
                        hour = 0
                    if(manoeuvre.hour < 10)
                        hour_text.text = "0"+manoeuvre.hour
                    else
                        hour_text.text = manoeuvre.hour
                }
                if(manoeuvre.minute < 10)
                    minute_text.text = "0" + manoeuvre.minute
                else
                    minute_text.text = manoeuvre.minute
            }
            if(manoeuvre.second < 10)
                second_text.text = "0" + manoeuvre.second
            else
                second_text.text = manoeuvre.second
        }

    }


    BeginButton {
        id:beginButton
        MouseArea {
            anchors.fill: parent
            onClicked: {
                time_run.start()
                killExpand.visible = true
                if($app.settings.bIsStart)
                {
                    showMainCircl()
                }
                changeStatus()
                closebar.visible = false
            }
        }
    }
    FinishButton {
        id: finishButton
        visible: false
        MouseArea {
            anchors.fill: parent
            onClicked: {
                showTest()
                changeStatus()
                exerciseResults.visible = true
                time_run.stop()
                manoeuvre.hour="00"
                manoeuvre.minute="00"
                manoeuvre.second="00"
                closebar.visible = true
                killExpand.visible = false
            }
        }
    }
    Connections
    {
        target: $app.settings
        function onReplayStatusChanged(bReplay)
        {
            if(bReplay)
            {
                beginButton.visible=false;
            }
            else
            {
                beginButton.visible=true;
            }
        }
    }

    function showMainCircl()
    {
        beginButton.visible = false
        finishButton.visible = true
//        if(null !== objSetting)
//        {
//            objSetting.visible = false
//        }
    }
    function showTest()
    {
        beginButton.visible = true
        finishButton.visible = false
//        if(null !== objSetting)
//        {
//            objSetting.visible = true
//        }
    }
    function changeStatus()
    {
        if($app.settings.bIsStart)
        {
            /// 演习结束
            $app.settings.setStop();
            $app.allData.calResult();
            endTime=$app.settings.getSysTime();
        }
        else
        {
            /// 演习开始清空状态
            showMainCircl()
            $app.allData.clearInfo();
            $app.settings.setStart();
            $app.settings.getSysTime();
            startTime=$app.settings.getSysTime();
        }
    }
    PropertyAnimation
    {
        id: fadeOut
        target: beginButton
        duration: 300
        property: "opacity"
        from: 1.0
        to: 0.0

        onStopped:
        {
            target.visible = false
        }
    }

    PropertyAnimation
    {
        id: fadeIn
        target: finishButton
        duration: 300
        property: "opacity"
        from: 0.0
        to: 1.0
        onStarted:
        {
            target.visible = true
        }
    }

    Rectangle {
        id: switchSet
        anchors.bottom: parent.bottom
        anchors.bottomMargin: -34*dpy
        anchors.right: parent.right
        anchors.rightMargin: -20 *dpx
        width: 140*dpx
        height: 68 *dpy
        color: Qt.rgba(36/255, 41/255, 57/255, 0.6);
        radius: 20*dpy

        Rectangle {
            x: 10*dpx
            y: 7*dpy
            color: "transparent"
            width: 20*dpx
            height: 20*dpx

            Text {
                anchors.fill: parent
                text: qsTr("\ue628")
                color: "#e7f6ff"
                font.family: "iconfont"
                font.pixelSize: 22*dpx
                verticalAlignment: Text.AlignVCenter
            }
        }
        Rectangle {
             y: 7*dpy
            x: 35*dpx
            color: "transparent"
            Text {
                text: qsTr("切换设置")
                font.pixelSize: 16*dpx;
                color: "#ffffff";
                font.family: "Microsoft YaHei"
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
            }
        }

        MouseArea {
            anchors.fill: parent
            onClicked: {
                manoeuvre.visible = false
                footerBar.visible = true
            }
        }
    }


}
