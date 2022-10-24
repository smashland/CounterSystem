
import QtQuick 2.12
import QtQuick.Controls 2.15
Row {
    spacing: 10*dpx
    property alias name: checkText.text
    property bool boolCheck: check.checked
    CheckBox {
        id: check
        y: 1*dpy
        width: 17*dpx
        height: 17*dpy
//        checked:true
        indicator: Rectangle {
            width: check.width
            height: check.height
            color: "#1d4f88"
            border.color: "#3b6daa"
            Image {
                width: check.width
                height: check.height
                source: check.checked ? "qrc:/Image/true.png" : ""
            }
        }

    }
    Text {
        id: checkText
//        text: qsTr("断开自动重连")
        color: "#d5e2f5"
        font.pixelSize: 14*dpx
        font.family: "Microsoft YaHei"
    }
}
