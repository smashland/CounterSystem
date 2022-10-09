import QtQuick 2.12
import QtQuick.Controls 2.15
import "../../Common"
import "../../Exercise"

ListView {
    id: listView
    //            anchors.fill: parent
    x: 80*dpx
    y: 170*dpy
    width: 1066*dpx
    height: 550 *dpy
    //            color: "transparent"
    //            delegate: delegate

    header:ListHeader{
        id: headerView
    }
    focus: true
    clip: true
    ScrollBar.vertical: ScrollBar {
        id: scrollBar
    }
}
