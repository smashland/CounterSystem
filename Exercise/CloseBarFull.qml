//                                                          设置窗口条
import QtQuick 2.12
import QtQuick.Controls 2.15
import "../Common"
Item {
    id: closebarFull
    width: mainWindow.width
    height: 60 *dpy
    Image {
        anchors.fill: parent
        source: "qrc:/Image/Case_bg.png"
    }

}
