import QtQuick 2.12
import QtQuick.Controls 2.15

Rectangle {
    id: soldierItem
    property alias text: soldierItemText.text
    property alias name: soldierItemContent.text
    width: soldierItemText.contentWidth + 200*dpx
    height: 34 *dpy
    color: "transparent"

    Rectangle {
        color: "transparent"
        Text {
            id: soldierItemText
            width: soldierItemText.contentWidth
            height: 34 *dpy
            color: "#ffffff"
            font.pixelSize: 17*dpx;
            font.family: "Microsoft YaHei";
            verticalAlignment: Text.AlignVCenter
        }
    }
    Rectangle {
        x: soldierItemText.contentWidth + 20 *dpx
        width: 200*dpx
        height: 34 *dpy
        color: "#1d4f88"
        border.color: "#3b6daa"
        TextInput {
            id: soldierItemContent
            x: 10 *dpx
            width: 180*dpx
            height: 34 *dpy
            font.pixelSize: 17*dpx
            color: "#ffffff"
            clip: true
            font.family: "Microsoft YaHei"
            verticalAlignment: Text.AlignVCenter

            onEditingFinished: {
                    scePersonInfo.id=soldierItemContent.text
            }
        }
    }
}
