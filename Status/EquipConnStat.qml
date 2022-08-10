import QtQuick 2.0

Text
{
    property var bConnected:true

    font.family: $app.webFont
    horizontalAlignment: Text.AlignHCenter
    verticalAlignment: Text.AlignVCenter
    height: 30
    font.pixelSize: 18
    color: outData.bOnLine ? bConnected ? $app.settings.connectColor : $app.settings.disConnColor : "gray"
    visible: bConnected
}
