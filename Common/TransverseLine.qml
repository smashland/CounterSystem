import QtQuick 2.12
import QtQuick.Controls 2.15
import QtGraphicalEffects 1.15

Row {
    spacing: 6*dpx
    Rectangle {
        width: 25 *dpx
        height: 2*dpy
        color: "#0187d6"
    }
    Rectangle {
        width: 188 *dpx
        height: 2*dpy
        color: "#0187d6"
        LinearGradient {
            anchors.fill: parent
            source: parent
            start: Qt.point(0, 0)
            end: Qt.point(0, 188)
            gradient: Gradient {
                GradientStop { position: 0.0; color: "#0187d6" }
                GradientStop { position: 1.0; color: "#7ec9e6" }
            }
        }
    }
}
