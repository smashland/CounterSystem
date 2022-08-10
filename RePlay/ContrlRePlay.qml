import QtQuick 2.0
import QtQuick.Controls 2.2
import ".."
Item
{
    id:rePlayShow
    property int nTimes:100
    property bool bStart: true

    Text {
        x: 80 *dpx
        y: contentHeight
        height: 100 *dpy
        text: qsTr("方案名称：")
        font.pixelSize: 20*dpx;
        color: "#ffffff";
        font.bold: true
        font.family: "MicrosoftYaHei Bold"

    }
    Column {
        x: (index.width-width)/2
        Row
        {

            spacing: bofang.contentWidth/2
            /// 演习开始按钮
            Button
            {
                id: start
                width: bofang.contentWidth
                height: bofang.contentHeight
                property bool bStart: false
                contentItem:             Text {
                    id: bofang
                    //                x: 36 *dpx
                    z: 2
                    color: "green"
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
                        bofang.text= "非主流"
                    }
                    else
                    {
                        if(rePlayShow.bStart)
                        {
                            $app.allData.beginReplay();
                            rePlayShow.bStart = false;
                        }
                        else
                        {
                            $app.allData.pauseReplay();
                        }

                        bofang.text= "\ue609"
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
                        color:"green"
                    }
                }

                handle: Rectangle{
                    id:sliderHandle
                    x: horizontalSlider.leftPadding+horizontalSlider.visualPosition*(horizontalSlider.availableWidth)-2
                    y: horizontalSlider.topPadding+horizontalSlider.availableHeight/2-height/2
                    color: horizontalSlider.pressed?"red":"orange"
                    implicitWidth: 16
                    implicitHeight: 16
                    radius: 8
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


            /// 关闭按钮
            Button
            {
                width: shanchu.contentWidth
                height: shanchu.contentHeight
                contentItem:Text {
                    id: shanchu
                    color: "#ffffff"
                    text: "\ueaf2"
                    font.family: "iconfont"
                    font.pixelSize: 32*dpx
                    verticalAlignment: Text.AlignVCenter
                }
                background: Rectangle{
                    color:"transparent"
                }

                onPressed:
                {
                    confirm.open();
                }
            }
        }

        ConfirmPopUp
        {
            id:confirm;

            exitShowLabel:"是否退出回放"
            onYesPutDown:
            {
                rePlayShow.visible=false
                rePlayShow.bStart = true
                $app.settings.endReplay()
                $app.allData.endReplay()
            }
            onNoPutDown:
            {
            }
        }

        Text {
            x:(parent.width-width)/2
            text: qsTr("演习时长")+nTimes+qsTr("秒")
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            height: 30
            font.pixelSize: 15
            color: "white"
            style:Text.Outline;styleColor: "black"
        }

    }

    //    Dialog
    //    {
    //        x: -renderer.width/2
    //        y: -renderer.height/2
    //        id:exitReplay
    //        Text {
    //            anchors.fill: parent
    //            id: name
    //            text: qsTr("退出回放?")
    //        }
    //        modal: true
    //        standardButtons: Dialog.Ok | Dialog.Cancel
    //        onAccepted:
    //        {

    //        }
    //    }
}
