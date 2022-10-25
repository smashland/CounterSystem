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

    ScrollView
    {
        id:showNotice
        width: 500*dpx
        height: 50*dpy
        anchors.centerIn: parent
//        color: "transparent"
        TextArea
        {
            id:showText
            color: "white"
            font.pointSize: 16*dpy
            font.bold: true
            anchors.centerIn: parent
            Connections
            {
                target: $app.settings
                function onStartStatusChanged(bIsStart)
                {
                    if(bIsStart)
                    {
                        showText.text=""
                        showNotice.y=showNotice.parent.height + showNotice.height
                    }
                }
            }
        }

        Connections
        {
            target: $app
            function onNotic(sNoticInfo)
            {
                showText.text += sNoticInfo
                showText.text += '\n'
                if(!enter.running)
                {
                    enter.running=true
                    leave.stop()
                }
                hidTimer.restart();
            }
        }

        NumberAnimation on y
        {
            id:enter
            to:showNotice.parent.height - showNotice.height
            duration: 1000
            running:false
            onStopped:
            {
                y=showNotice.parent.height - showNotice.height
            }
        }

        NumberAnimation on y
        {
            id:leave
            to:showNotice.parent.height + showNotice.height
            duration: 1000
            running:false
            onStopped:
            {
                y=showNotice.parent.height + showNotice.height
            }
        }

        Timer
        {
            id:hidTimer
            interval: 5000;
            running: true;
            repeat: false
            onTriggered:
            {
                leave.running=true;
            }
        }
    }



}
