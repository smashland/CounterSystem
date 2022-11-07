import QtQuick 2.0
import QtQuick.Controls 2.12
import QtQml 2.12
//kunag
ScrollView
{
    id:showNotice
    width: 770*dpx
    height: 380*dpy
//    y:parent.height + height
//    anchors.right:  parent.right
    anchors.centerIn: parent
//    color: "transparent"

    TextArea
    {
        id:showText
        color: $app.typeColor
        font.pointSize: 16*dpy
        font.bold: true
        background: Rectangle
        {
            color:"#2D5689"
            opacity:showNotice.visible ? 0.5 : 0.0
        }

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
//            hidTimer.restart();
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

}
