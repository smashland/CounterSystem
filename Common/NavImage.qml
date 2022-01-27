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
        Image {
            id: minImage
            width: 18 *dpx
            height: 18 *dpx
            source: "qrc:/Image/icon/icon_zuixiaohua.svg"
        }
    }
    Rectangle {
        width: 18 *dpx
        height: 18 *dpx
        color: "transparent"
        Image {
            id: maxImage
            width: 18 *dpx
            height: 18 *dpx
            source: "qrc:/Image/icon/icon_zuidahua.svg"
        }
    }
    Rectangle {
        width: 18 *dpx
        height: 18 *dpx
        color: "transparent"
        Image {
            id: closeImage
            width: 18 *dpx
            height: 18 *dpx
            source: "qrc:/Image/icon/guanbi1.svg"
        }
        MouseArea {
            anchors.fill: parent
            onClicked: {
                Qt.quit()
            }
        }
    }
}
