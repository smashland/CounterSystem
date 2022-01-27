import QtQuick 2.0
import QtQuick.Controls 2.15

Button
{
    id:closeButton
    width:  20*dpx
    height:  20*dpy

    background:Rectangle{
        id: closeBackground
        anchors.fill: parent
        color:"transparent"
        Image{
            anchors.fill: parent
            source: "qrc:/Image/Cancel.png"
        }
    }
}
