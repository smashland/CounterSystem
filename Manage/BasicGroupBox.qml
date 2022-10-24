import QtQuick 2.0
import QtQuick.Window 2.15
import QtQuick.Controls 1.3
import QtQuick.Controls.Private 1.0

GroupBox {
    id: groupBoxId
    width:680*dpx
    height:230*dpy
    visible: false

    flat : false
    style: Style {
        property Component panel: Rectangle {
            color: "transparent"
            border.color: "#3b6daa"
            Rectangle{
                id:titleBackground
                width: title.width
                height: title.height
                implicitHeight:title.height
                color: "#3b6daa"
                x:20*dpx
                y: -10*dpy
                Text{
                    id:title
                    text: groupBoxId.title
                    font.pixelSize: 20
                    color:"white" //修改title 颜色
                }
            }
        }
    }
}
