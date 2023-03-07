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
    property var imgSource: "qrc:/Image/Start_bg.png"
    Image {
        anchors.fill: parent
        source: imgSource
    }
    MouseArea {
        anchors.fill: parent
        onWheel: {
            // 屏蔽滚轮事件，防止滚动方案列表时缩放地球
        }
    }
    signal yesPutDown()
    property var objSetting;
    //    property string hour:("00")
    //    property string minute: ("00")
    //    property string second: ("00")
    property string startTime;
    property string endTime;
    property int hour:0
    property int minute: 0
    property int second: 0

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
            text:$app.allData.nCTimes /*manoeuvre.second*/
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
            //            console.log("interval:", interval)
            manoeuvre.second++
            if(manoeuvre.second == 60){
                manoeuvre.second= 0
                manoeuvre.minute++
                if(manoeuvre.minute === 60){
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

    //显示演习时间
    Connections
    {
        target: $app.allData
        function onUnTimesChanged(time)
        {
            timeTextInfo(second_rec,time%3600%60)
            timeTextInfo(minute_rec,parseInt(time%3600/60))
            timeTextInfo(hour_rec,parseInt(time/3600))
        }
    }
    function timeTextInfo(string,time)
    {
        if(time<10)
        {
            string.text="0"+time;
        }
        else
        {
            string.text=time
        }
    }

    // 开始演习
    ControlButtons {
        id:beginButton
        jianbianColor: "#00baff"
        icon: qsTr("\ue623")
        text: qsTr("开始")
        MouseArea {
            anchors.fill: parent
            onClicked: {
<<<<<<< HEAD
//                time_run.start()
=======
                console.log("开始时间："+Qt.formatDateTime(new Date(), "yyyy-MM-dd hh:mm:ss.zzz ddd"))
                //                time_run.start()
>>>>>>> 612fb6c233c464d88d7b53a832a04eb5db7e6e87
                killExpand.visible = true
                if($app.settings.bIsStart)
                {
                    showMainCircl()
                }
                changeStatus()
                //                console.log("开始时间："+$app.allData.getStartTime);
                //                second_rec.text=$app.allData.nCTimes
                closebar.visible = false
                yanxishijianItem.visible = true
                xianyin.visible = true
                zhansun.visible = true
                toggleSettings.visible = false

            }
        }
    }
    // 结束演习
    ControlButtons {
        id: finishButton
        jianbianColor: "#59eba5"
        icon: qsTr("\ue638")
        text: qsTr("结束")
        visible: false
        MouseArea {
            anchors.fill: parent
            onClicked: {
                console.log("结束演习："+Qt.formatDateTime(new Date(), "yyyy-MM-dd hh:mm:ss.zzz ddd"))
                //                time_run.stop()
                showTest()
                changeStatus()
                exerciseResults.visible = true
                hour_rec.text=minute_rec.text=second_rec.text="00"
                manoeuvre.hour=manoeuvre.minute=manoeuvre.second=0
                //                manoeuvre.hour="00"
                //                manoeuvre.minute="00"
                //                manoeuvre.second="00"
                closebar.visible = true
                killExpand.visible = false
                yanxishijianItem.visible = false
                xianyin.visible = false
                xianyin.isXianshi()
                zhansun.visible = false
                toggleSettings.visible = true
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
            $app.setClearNoticText();
            $app.allData.calResult();
            endTime=$app.settings.getSysTime();
            $app.setAveLocation();
        }
        else
        {
            /// 演习开始清空状态
            showMainCircl()
            $app.allData.clearInfo();
            $app.settings.setStart();
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
        id: toggleSettings
        anchors.bottom: parent.bottom
        anchors.bottomMargin: -34*dpy
        anchors.right: parent.right
        anchors.rightMargin: -20 *dpx
    }

    Button {
        id: zhansun
        anchors.right: parent.right
        anchors.rightMargin: 80*dpx
        anchors.top: yanxishijianItem.top
        anchors.topMargin: -3*dpy
        width: zhansunext.contentWidth + 30*dpx
        height: 33*dpy
        visible: false
        checked:true
        contentItem: Text {
            id: zhansunext
            text: qsTr("实时战损")
            font.pixelSize: 15*dpx
            color: "#ffffff"
            font.family: "Microsoft YaHei"
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
        }
        background: Rectangle {
            radius: 18*dpy
            color: "#dbbb5a"
        }
        onClicked: {
            battleDamage.visible = true
        }
    }


}
