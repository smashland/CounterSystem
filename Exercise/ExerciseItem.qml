import QtQuick 2.12
import QtQuick.Controls 2.15

Row
{
    property alias title: title.text
    property alias name: name.text
    spacing: 10

    Text {
        id: title
        color: "#ffffff"
        font.pixelSize: 16*dpx;
        font.family: "Microsoft YaHei";
        verticalAlignment: Text.AlignVCenter
    }
    Text {
        id:name
        color: "#ffffff"
        font.pixelSize: 16*dpx;
        font.bold: true
        font.family: "Microsoft YaHei";
        verticalAlignment: Text.AlignVCenter
    }
}
