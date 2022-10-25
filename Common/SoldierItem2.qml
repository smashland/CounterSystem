import QtQuick 2.12
import QtQuick.Controls 2.15

Row
{
    property alias title: title.text
    property alias name: name.text
    property alias danwei: danwei.text
    spacing: 10

    Text {
        id: title
        color: "#f6f6f6"
        height: 34*dpx
        font.pixelSize: 16*dpx;
        font.family: "Microsoft YaHei";
        verticalAlignment: Text.AlignVCenter
    }
    TextField {
        id:name
        color: "#4582c7"
        font.pixelSize: 16*dpx;
        font.bold: true
        placeholderText:"请填写数量"
        font.family: "Microsoft YaHei";
        verticalAlignment: Text.AlignVCenter
        width: 350*dpx
        height: 34*dpx
        background: Rectangle {
            anchors.fill: parent
            color: "#1d4f88"
            border.color: "#3b6daa"
        }
    }
    Text {
        id:danwei
        color: "#9fc9f8"
        height: 34*dpx
        font.pixelSize: 16*dpx;
        font.bold: true
        font.family: "Microsoft YaHei";
        verticalAlignment: Text.AlignVCenter
    }
}
