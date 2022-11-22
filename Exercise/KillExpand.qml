//                                                          设置窗口条展开
import QtQuick 2.12
import QtQuick.Controls 2.15
import "../Common"
Item {
    id: killExpand
    width: 1040*dpx
    height: 50 *dpy
    Image {
        anchors.fill: parent
        source: "qrc:/Image/Killing_unfold.png"
    }
    Text {
        x: 10*dpx
        width: 50 *dpx
        height: 50*dpy
        text: qsTr("\ue705")
        color: "#ffb128"
        font.family: "iconfont"
        font.pixelSize: 22*dpx
        verticalAlignment: Text.AlignVCenter
        MouseArea {
            anchors.fill: parent
            onClicked: {
                killExpand.visible = false
                kill.visible = true
            }
        }
    }

    Text {
        x: 50 *dpx
        height: 50*dpy
        text: qsTr("击杀情况")
        color: "#ffb128"
        font.family: "MicrosoftYaHei-Bold"
        font.pixelSize: 22*dpx
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
    }

    Text {
        anchors.right: parent.right
        anchors.rightMargin: 50*dpx
        height: 50*dpy
        text: qsTr("查看更多 >")
        color: "#ffb128"
        font.family: "MicrosoftYaHei-Bold"
        font.pixelSize: 22*dpx
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
        MouseArea {
            anchors.fill: parent
            onClicked: {
                killSituation.visible = true
            }
        }
    }


    Rectangle
    {
        id:showNotice
        width: 196*dpx
        height: 50*dpy
        x: 150*dpx
        color: "transparent"
        clip: true
        focus: true
        TextArea
        {
            id:showText
            color:$app.typeColor
            font.pointSize: 14*dpy
            width: showText.contentWidth + 5*dpx
            height: 50*dpy
            verticalAlignment: Text.AlignVCenter
            font.family: "Microsoft YaHei";
            font.bold: true
            Connections
            {
                target: $app.settings
                function onStartStatusChanged(bIsStart)
                {
                    if(bIsStart)
                    {
                        showText.text=""
                    }
                }
            }

            NumberAnimation on x {
                id: enter
                from: 0
                to: - (showText.width - 190* dpx)
                duration: 1000
                running: false
            }
        }

        //上面显示的击杀情况
        Connections
        {
            target: $app
            function onNotic(sNoticInfo)
            {
                showText.text += sNoticInfo+ " "
//                showText.text += '\n'
                console.log(showText.contentWidth)
                if(showText.width > showNotice.width) {
                    enter.running = true
                }
            }
        }

    }



}
