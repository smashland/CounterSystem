import QtQuick 2.0
import QtQuick.Controls 2.2
import "../Common"
import "../Exercise/Plugins"

Item
{
    id:rePlayShow
    property int nTimes:100
    property bool bStart: true

    Column {
        x: (index.width-width)/2
        Row
        {

            spacing: 10*dpx
            /// 演习开始按钮
            Row {
                Button
                {
                    id: start
                    width: bofang.contentWidth
                    height: bofang.contentHeight
                    property bool bStart: false
                    contentItem: Text {
                        id: bofang
                        //  x: 36 *dpx
                        z: 2
                        color: "#00CD66"
                        text: "\ue609"
                        font.family: "iconfont"
                        font.pixelSize: 32*dpx
                        verticalAlignment: Text.AlignVCenter
                    }
                    background: Rectangle{
                        color:"transparent"
                    }

                    onPressed:
                    {
                        if(bStart)
                        {
                            $app.allData.pauseReplay();
                            bofang.text= "\ue609"
                            time_run.stop()
//                            console.log("00000000000000000000000000")
                        }
                        else
                        {
                            if(rePlayShow.bStart)
                            {
                                $app.allData.beginReplay();
                                rePlayShow.bStart = false;
                                time_run.start();
//                                console.log("111111111111111111111111")
                            }
                            else
                            {
                                $app.allData.pauseReplay();
//                                console.log("2222222222222222222222222")
                                time_run.start();
                            }
                            bofang.text= "\ue626"
                        }
                        bStart = !bStart
                    }
                }

                Slider
                {
                    id:horizontalSlider
                    from: 0
                    value: 0
                    to: nTimes
                    stepSize:1
                    y:sliderBackground.implicitHeight
                    background:Rectangle{
                        id: sliderBackground
                        x: horizontalSlider.leftPadding
                        y: horizontalSlider.topPadding+horizontalSlider.availableHeight/2-height/2
                        color:"white"
                        implicitWidth: 260
                        implicitHeight: 6
                        width:implicitWidth
                        height: implicitHeight
                        Rectangle {
                            width:horizontalSlider.visualPosition *parent.width
                            height: parent.height
                            color:"#00CD66"
                        }
                    }

                    handle: Rectangle{
                        id:sliderHandle
                        x: horizontalSlider.leftPadding+horizontalSlider.visualPosition*(horizontalSlider.availableWidth)-2
                        y: horizontalSlider.topPadding+horizontalSlider.availableHeight/2-height/2
                        color: horizontalSlider.pressed?"#dbbb5a":"#00CD66"
                        implicitWidth: 12
                        implicitHeight: 12
                        radius: 6
                    }

                    onMoved:
                    {
                        $app.allData.setSimuTime(value)
                    }
                }

                Connections
                {
                    target: $app.allData
                    function onSimTimeChanged(simTime)
                    {
                        horizontalSlider.value = simTime;
                    }
                }
            }

            /// 关闭按钮
            Button
            {
                y: 1*dpy
                width: shanchu.contentWidth
                height: shanchu.contentHeight
                contentItem:Text {
                    id: shanchu
                    color: "#ffffff"
                    text: "\ueaf2"
                    font.family: "iconfont"
                    font.pixelSize: 28*dpx
                    verticalAlignment: Text.AlignVCenter
                }
                background: Rectangle{
                    color:"transparent"
                }

                onPressed:
                {
                    removeDialog_huifang.open()
                }
            }

        }

        RemoveDialog {
            id: removeDialog_huifang
            visible: false
            y: (index.height - removeDialog_huifang.height-parent.height)/2
            title:"退出"
            content1: "是否退出回放?"
            content2: exitShowLabel
            onYesPutDown: {
                rePlayShow.visible=false
                rePlayShow.bStart = true
                $app.settings.endReplay()
                $app.allData.endReplay()
                manoeuvre.imgSource = "qrc:/Image/Start_bg.png"
                manoeuvre.height = 136*dpx
                xianyin.isXianshi()
            }
            onNoPutDown: {

            }
        }
    }

    Text {
        id: timeText
        x: (index.width-width)/2
        y: 30*dpy
        text: formateTime(nTimes)
        height: 30
        font.pixelSize: 16*dpy
        color: "white"
        style:Text.Outline;styleColor: "black"
        font.family: "Microsoft YaHei"
    }
    function formateTime(time) {
        const h = parseInt(time / 3600)
        const minute = parseInt(time / 60 % 60)
        const second = Math.ceil(time % 60)
        const hours = h < 10 ? '0' + h : h
        const formatSecond = second > 59 ? 59 : second
        return `${hours > 0 ? `${hours}:` : ''}${minute < 10 ? '0' + minute : minute}:${formatSecond < 10 ? '0' + formatSecond : formatSecond}`
    }
    Timer{
        id:time_run
        interval: 1000
        repeat: true
        running: false
        triggeredOnStart: true
        onTriggered: {
            nTimes--
            if (formateTime(nTimes) <= "00:00") {
                time_run.stop()
                bofang.text= "\ue609"

                rePlayShow.visible=false
                rePlayShow.bStart = true
                $app.settings.endReplay()
                $app.allData.endReplay()
                manoeuvre.imgSource = "qrc:/Image/Start_bg.png"
                manoeuvre.height = 136*dpx
                xianyin.isXianshi()

                footerBar.btnPlayback.checked = true
            }
        }
    }
    CampHidden {
        id: xianyin
        y: 14*dpy
        x: 1670*dpx
        visible: true
    }

}
