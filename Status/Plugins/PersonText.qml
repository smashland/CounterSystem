import QtQuick 2.12
import QtQuick.Controls 2.15

Text
{
    property alias text: show.text
    property alias color: show.color
    property var fontSize: 16 *dpy
    id:show
    verticalAlignment: Text.AlignVCenter
    font.family: "Microsoft YaHei"
    font.pixelSize: fontSize
    color: outData.bRenZhi?"green":"white"
    height: parent.height
}
