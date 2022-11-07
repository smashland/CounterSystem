//                                        单选框
import QtQuick 2.12
import QtQuick.Controls 2.15
Item {
//    spacing: 10*dpx
    property alias name: checkText.text
    property bool boolCheck: $app.openSpeak
    CheckBox {
        id: check
        y: 2*dpy
        width: 17*dpx
        height: 17*dpy
        checked:$app.openSpeak
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
        onClicked: {$app.setOpenSpeak(check.checked);}
    }
    Text {
        id: checkText
        x: 27*dpx
        color: "#d5e2f5"
        font.pixelSize: 14*dpx
        font.family: "Microsoft YaHei"
    }
}
