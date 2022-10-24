import QtQuick 2.12
import QtQuick.Controls 2.15

TextField {
    id:textField
    color: "#4582c7"
    font.pixelSize: 16*dpx;
    font.bold: true
    font.family: "Microsoft YaHei";
    verticalAlignment: Text.AlignVCenter
    width: 50*dpx
    height: 34*dpy
    background: Rectangle {
        color: "#1d4f88"
        border.color: "#3b6daa"
    }
    selectByMouse: true
    selectionColor: "#0187d6"
}
