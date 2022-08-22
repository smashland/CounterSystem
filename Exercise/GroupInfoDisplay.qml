import QtQuick 2.12
import QtQuick.Controls 2.15
import "../Common"
Item {
    id: groupInfoDisplay
    width: 200*dpx
    height: 50 *dpy
    Image {
        anchors.fill: parent
        source: "qrc:/Image/Killing_packup.png"
    }
    MouseArea
    {
        id: mouseArea
        anchors.fill: parent
        onClicked: {

        }
    }


}
