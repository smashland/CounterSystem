import QtQuick 2.12

Text {
    id: tabtitle
    property alias text: tabtitle.text
    property alias widthTitle: tabtitle.width
    property alias heightTitle: tabtitle.height
    color: "#ffffff"
    font.pixelSize: 16
    font.family: "Microsoft YaHei";
    font.bold: true
    horizontalAlignment: Text.AlignHCenter
    verticalAlignment: Text.AlignVCenter
}
