//                                               底部播放条

import QtQuick 2.12
import QtQuick.Controls 2.15
import Qt.labs.platform 1.1
import Qt.labs.qmlmodels 1.0
import "../Status" as MyStatus
import "../RePlay" as MyRePlay
import "Plugins"

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
        id:yanxishijianItem
        x: 80*dpx
        y: (136 *dpy + 50 *dpy - yanxiTime.contentHeight)/2
        visible: false
        Text {
            id: yanxiTime
            width:yanxiTime.contentWidth
            height: yanxiTime.contentHeight
            text: qsTr("演习时间： ")
            font.pixelSize: 20*dpx;
            color: "#ffffff";
            font.family: "Microsoft YaHei";
        }
        TimeText{
            //shi
            id:hour_rec
            text: manoeuvre.hour
        }
        TimeText{
            //dian
            id:dian_rec
            text: ":"
        }
        TimeText{
            //fen
            id:minute_rec
            text: manoeuvre.minute
        }
        TimeText{
            //dian
            id:dian_rec2
            text: ":"
        }
        TimeText{
            //shi
            id:second_rec
            text: manoeuvre.second
        }
    }
    CampHidden {
        id: xianyin
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
                        hour_rec.text = "0"+manoeuvre.hour
                    else
                        hour_rec.text = manoeuvre.hour
                }
                if(manoeuvre.minute < 10)
                    minute_rec.text = "0" + manoeuvre.minute
                else
                    minute_rec.text = manoeuvre.minute
            }
            if(manoeuvre.second < 10)
                second_rec.text = "0" + manoeuvre.second
            else
                second_rec.text = manoeuvre.second
        }

    }


    ControlButtons {
        id:beginButton
        jianbianColor: "#00baff"
        icon: qsTr("\ue623")
        text: qsTr("开始")
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
                yanxishijianItem.visible = true
                xianyin.visible = true
            }
        }
    }
    ControlButtons {
        id: finishButton
        jianbianColor: "#59eba5"
        icon: qsTr("\ue638")
        text: qsTr("结束")
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
                yanxishijianItem.visible = false
                xianyin.visible = false
                xianyin.isXianshi()
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
    }
    function showTest()
    {
        beginButton.visible = true
        finishButton.visible = false
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

    ToggleSettings {
        anchors.bottom: parent.bottom
        anchors.bottomMargin: -34*dpy
        anchors.right: parent.right
        anchors.rightMargin: -20 *dpx
    }


}
