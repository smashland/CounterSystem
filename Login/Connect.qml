import QtQuick 2.12
import QtGraphicalEffects 1.15
import QtQuick.Controls 2.15
Rectangle {
    id: connect
//    y: 950 *dpy
    width: 1920 *dpx
    height: 42 *dpy
    color: "transparent"
    Image {
        width: 1920 *dpx
        height: 42 *dpy
        source: "qrc:/Image/Footer_line.png"
    }
    Text {
        id: footerText
        x: (mainWindow.width - footerText.contentWidth)/2
        y: footerText.contentHeight
        text: qsTr("版本号：2021 v1.0   |   售后联系方式：13383318813 (微信同)");
        font.pixelSize: 14*dpx;
        color: "#d7deff";
        font.family: "Microsoft YaHei";
    }
}
