﻿import QtQuick 2.0
import QtQuick.Controls 2.2
import "../Common"
import "../Exercise/Plugins"
Item
{
    id:rePlayShow
    property int nTimes:0
    property bool bStart: true
    property int nSlider:horizontalSlider.value
    property int nTimeText:nTimes
    Column {
        x: (index.width-width)/2
        Row
        {
            spacing:1*dpx /*10*dpx*/
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
                        text: "\ue609"   ///609:暂停的三角标志
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
                            console.log("测试继续回放时间"+nTimes)
                            console.log("测试继续回放！！！"+bStart)
                            $app.allData.pauseReplay();
                            bofang.text= "\ue609";
                        }
                        else
                        {
                            console.log("测试开始回放时间"+nTimes+" "+bStart)
                            if(rePlayShow.bStart)
                            {
                                console.log("测试开始回放！！！"+rePlayShow.bStart)
                                //
                                bofang.text= "\ue626"
                                $app.setClearNoticText();
                                nTimeText=nTimes
                                $app.allData.setReplayFlags(false)
                                $app.allData.beginReplay();
                                rePlayShow.bStart = false;
                                killExpand.clearShowText();


                            }
                            else
                            {
                                console.log("测试开始暂停！！！"+rePlayShow.bStart)
                                //                                bofang.text= "\ue609";
                                $app.allData.pauseReplay();
                                //                                rePlayShow.bStart = true;
                            }
                            bofang.text= "\ue626"
                        }
                        bStart = !bStart;
                    } //on
                }

                Slider
                {
                    id:horizontalSlider
                    from: 0
                    //                    value: 0
                    to: nTimes
                    stepSize:1
                    y:sliderBackground.implicitHeight
                    snapMode :Slider.SnapOnRelease
                    onValueChanged:
                    {
                        if(nTimeText>0)
                        {
                            nTimeText--
                            if (nTimeText===0&&horizontalSlider.value == nTimes) {
                                bofang.text= "\ue609"
                                start.bStart=false
                                rePlayShow.bStart = true
                                $app.allData.endNoInitRePlay()
                            }
                        }
                    }

                    background:Rectangle{
                        // 进度条
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
                        // 滑块
                        id:sliderHandle
                        x: horizontalSlider.leftPadding+horizontalSlider.visualPosition*(horizontalSlider.availableWidth)-2
                        y: horizontalSlider.topPadding+horizontalSlider.availableHeight/2-height/2
                        color: horizontalSlider.pressed?"#dbbb5a":"#00CD66"
                        implicitWidth: 12
                        implicitHeight: 12
                        radius: 6
                        //                        antialiasing: true
                    }

                    onMoved:
                    {
//                        killExpand.clearShowText();
//                        $app.setClearNoticText();
                        $app.allData.setSimuTime(value)
                        nTimeText=nTimes-value/*nTimes*/
                    }

                }

                Connections
                {
                    target: $app.allData
                    function onSimTimeChanged(simTime)
                    {
                        horizontalSlider.value = simTime;
                    }
                    function onClearShowText()
                    {
                        killExpand.clearShowText();
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
                bofang.text= "\ue609"
                start.bStart=false
                rePlayShow.visible=false
                rePlayShow.bStart = true
                $app.settings.endReplay()
                $app.allData.endReplay()
                manoeuvre.imgSource = "qrc:/Image/Start_bg.png"
                manoeuvre.height = 136*dpx
                xianyin.isXianshi()
                killExpand.visible = false
                killSituation.visible = false
                $app.setClearNoticText();
            }
            onNoPutDown: {

            }
        }
    }

    Text {
        id: timeText
        x: (index.width-width)/2
        y: 30*dpy
        text: formateTime(nTimeText)
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

    CampHidden {
        id: xianyin
        y: 14*dpy
        x: 1670*dpx
        visible: true
    }

}
