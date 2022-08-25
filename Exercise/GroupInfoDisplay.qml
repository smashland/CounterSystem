import QtQuick 2.12
import QtQuick.Controls 2.15
import "../Common"
Rectangle {
    id: groupInfoDisplay
    width: 200*dpx
    height: 50 *dpy

    MouseArea {
        anchors.fill: parent
        onClicked: {
           objVisible()
        }
    }

    Image {
        id:xianshi
        anchors.fill: parent
        source: "qrc:/Image/Killing_packup.png"
        MouseArea {
            anchors.fill: parent
            onClicked: {
               objVisiblefalse()
                xianshi.visible = false
                yincang.visible = true
            }
        }
    }
    Image {
        id: yincang
        anchors.fill: parent
        source: "qrc:/Image/Circle.png"
        visible: false
        MouseArea {
            anchors.fill: parent
            onClicked: {
               objVisibletrue()
                xianshi.visible = true
                yincang.visible = false
            }
        }
    }
    function objVisiblefalse()
    {
        unGroup.visible = false
        blue.visible = false
        red.visible = false
    }
    function objVisibletrue()
    {
        unGroup.visible = true
        blue.visible = true
        red.visible = true
    }


}
