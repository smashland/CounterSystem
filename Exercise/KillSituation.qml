//                                        击杀情况
import QtQuick 2.12
import QtQuick.Controls 2.15
import "../Common"
import "../Status" as MyStatus
import "../RePlay" as MyRePlay

Item {
    id:killSituation
    width: 860 *dpx
    height: 560 *dpy
    Image {
        id: loginImage
        anchors.fill: parent
        source: "qrc:/Image/Popup_bg_13.png"
    }

    PopupTitle {
        name: qsTr("击杀情况")
        icon: "\ue602"
        x: 60*dpx
        y: 44*dpy
    }

    CloseButton {
        anchors.right: killSituation.right
        anchors.rightMargin: 60 *dpx
        anchors.top: killSituation.top
        anchors.topMargin: 50 *dpy
        onClicked: killSituation.visible = false
    }
    MyStatus.BoardNotice
    {

    }

}
