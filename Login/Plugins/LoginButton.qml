import QtQuick 2.12
import QtGraphicalEffects 1.15
import QtQuick.Controls 2.15

Rectangle {
    id: loginButton
//    x: 110 *dpx
//    y: 82 *dpy + shouquan.contentHeight + 80 *dpy + columnTextField.height
    width:  355*dpx
    height:  44*dpy
    LinearGradient {
        anchors.fill: loginButton
        source: loginButton
        start: Qt.point(0, 0)
        end: Qt.point(0, loginButton.height)
        gradient: Gradient {
            GradientStop { position: 0.0; color: "#d4f4ff"}
            GradientStop { position: 1.0; color: "#2b9afa"}
        }
    }
    Text {
        anchors.fill:parent
        font.pixelSize: 20*dpx;
        color: "#003868";
        font.family: "Microsoft YaHei"
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
        text: "连 接"
    }

}
