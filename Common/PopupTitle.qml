import QtQuick 2.12
import QtQuick.Controls 2.15



Row {
    x: 74 *dpx
    y: 54 *dpx
    spacing: 10*dpx
    property alias name: titleText.text
    property alias icon: iconText.text
    Text {
        id: iconText
        color: "#ffffff"
        font.family: "iconfont"
        font.pixelSize: 22*dpx
        verticalAlignment: Text.AlignVCenter
    }
    Text {
        id:titleText
//        text: qsTr("演习结果")
        font.pixelSize: 24*dpx;
        color: "#ffffff";
        font.family: "MicrosoftYaHei-Bold"
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
    }
}

