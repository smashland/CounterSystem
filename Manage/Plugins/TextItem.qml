import QtQuick 2.12
import QtQuick.Controls 2.15

Text {
    id: textItem
    property alias name: textItem.text
    width: textItem.contentWidth
    height: 34 *dpy
    color: "#ffffff"
//    text: "机器码："
    font.pixelSize: 17*dpx;
    font.family: "Microsoft YaHei";
    verticalAlignment: Text.AlignVCenter
}
