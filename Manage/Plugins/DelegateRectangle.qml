import QtQuick 2.12

Rectangle {
    id: wrapper
    width: listView.width
    height: 50 *dpy
    Rectangle {
        anchors.fill: parent
        color: index%2 ? "#2D5689" : "#4671a6"
    }
}
