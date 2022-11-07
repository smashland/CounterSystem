import QtQuick 2.12

Text {
    property alias text: tabtitle.text
    property alias widthTitle: tabtitle.width
    property alias heightTitle: tabtitle.height
    id: tabtitle
    color: "#ffffff"
    font.pixelSize: 16*dpx
    font.family: "Microsoft YaHei";
    font.bold: true
    horizontalAlignment: Text.AlignHCenter
    verticalAlignment: Text.AlignVCenter
}
