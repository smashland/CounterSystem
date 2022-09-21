import QtQuick 2.12
import QtQuick.Controls 2.15
import QtGraphicalEffects 1.15

Column {
    id: popupTitle
    property alias name: titleText.text
    property alias icon: iconText.text
    spacing: 13*dpy
    Row {
        spacing: 10*dpx
        Text {
            id: iconText
            color: "#ffffff"
            font.family: "iconfont"
            font.pixelSize: 22*dpx
            verticalAlignment: Text.AlignVCenter
        }
        Text {
            id:titleText
            font.pixelSize: 24*dpx;
            color: "#ffffff";
            font.family: "MicrosoftYaHei-Bold"
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
        }
    }
    Row {
        spacing: 6*dpx
        Rectangle {
            width: 25 *dpx
            height: 2*dpy
            color: "#0187d6"
        }
        Rectangle {
            width: 188 *dpx
            height: 2*dpy
            color: "#0187d6"
        }
    }
}



