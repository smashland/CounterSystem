import QtQuick 2.15
import QtQuick.Controls 2.15

Rectangle{
    //shi
    id:rec
    width:timeText.contentWidth
    height: timeText.contentHeight
    color: "transparent"
    property alias text: timeText.text
    Label{
        id:timeText
        text: ""
        anchors.centerIn: parent
        font.bold: true
        font.pixelSize: 20*dpx;
        color: "#ffffff";
        font.family: "Microsoft YaHei";
    }
}
