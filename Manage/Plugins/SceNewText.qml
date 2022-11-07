import QtQuick 2.12
import QtQuick.Controls 2.15
import "../../Common"
import "../../Exercise"

Text {
    id: scenewText
    property alias title: scenewText.text
    width: scenewText.contentWidth
    height: scenewText.contentHeight
    font.bold: true
    color: "#55e5aa";
    font.family: "Microsoft YaHei"

}
