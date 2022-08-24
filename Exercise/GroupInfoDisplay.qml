import QtQuick 2.12
import QtQuick.Controls 2.15
import "../Common"
Button {
    id: groupInfoDisplay
    width: 200*dpx
    height: 50 *dpy
    Image {
        anchors.fill: parent
        source: "qrc:/Image/Killing_packup.png"
    }
    checked:true
    checkable: false
    onClicked: {
       objVisible()
    }
    function objVisible()
    {
        unGroup.visible = groupInfoDisplay.checked
        blue.visible = groupInfoDisplay.checked
        red.visible = groupInfoDisplay.checked
    }


}
