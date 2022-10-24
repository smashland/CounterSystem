import QtQuick 2.15
import QtQuick.Controls 2.15
//                                               阵营显隐

Button {
    id: xianyin
    anchors.left: yanxishijianItem.right
    anchors.leftMargin: 30*dpx
    anchors.top: yanxishijianItem.top
    anchors.topMargin: -3*dpy
    width: xianyinText.contentWidth + 30*dpx
    height: 33*dpy
    visible: false
    checked:true
    contentItem: Text {
        id: xianyinText
        text: qsTr("显示/隐藏")
        font.pixelSize: 15*dpx
        color: "#ffffff"
        font.family: "Microsoft YaHei"
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
    }
    background: Rectangle {
        radius: 18*dpy
        color: "#dbbb5a"
    }
    onClicked: {
        if(xianyin.checked){
            isXianshi()
        }else{
            isYincang()
        }
    }
    function isXianshi() {
        blue.visible = true
        red.visible = true
    }
    function isYincang() {
        blue.visible = false
        red.visible = false
    }
}
