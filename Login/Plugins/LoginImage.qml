import QtQuick 2.15
import QtQuick.Controls 2.15

Rectangle {
    width: 355 *dpx
    height: 50 *dpy
    color: Qt.rgba(0/255, 31/255, 94/255, 0.6);
    border.color: "#00baff"
    Image {
        id: lrImage
        y: 13*dpy
        x: 20*dpx
        width:  24*dpx
        height:  24*dpx
        source: "qrc:/Image/code_icon.png"
    }
}
