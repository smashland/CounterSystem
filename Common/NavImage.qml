import QtQuick 2.12
 import QtGraphicalEffects 1.15

//Item {
//    id: navImage

//}

Row {
    spacing: 20 *dpx
    Rectangle {
        width: 18 *dpx
        height: 18 *dpx
        color: "transparent"

        Text {
            anchors.fill: parent
            text: qsTr("\ue6fc")
            color: "#e7f6ff"
            font.family: "iconfont"
            font.pixelSize: 22*dpx
            verticalAlignment: Text.AlignVCenter
        }
    }
    Rectangle {
        width: 18 *dpx
        height: 18 *dpx
        color: "transparent"

        Text {
            anchors.fill: parent
            text: qsTr("\ue702")
            color: "#e7f6ff"
            font.family: "iconfont"
            font.pixelSize: 22*dpx
            verticalAlignment: Text.AlignVCenter
        }
    }
    Rectangle {
        width: 18 *dpx
        height: 18 *dpx
        color: "transparent"

        Text {
            anchors.fill: parent
            text: qsTr("\ue61c")
            color: "#e7f6ff"
            font.family: "iconfont"
            font.pixelSize: 22*dpx
            verticalAlignment: Text.AlignVCenter
        }
        MouseArea {
            anchors.fill: parent
            onClicked: {
                Qt.quit()
            }
        }
    }
}
