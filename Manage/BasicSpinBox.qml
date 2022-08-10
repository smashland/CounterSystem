import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Controls.impl 2.12
import QtQuick.Templates 2.12 as T

//qtquickcontrols2\src\imports\controls\SpinBox.qml
//from Customizing SpinBox
T.SpinBox {
    id: control

    property bool borderVisible: true          //显示边框
    property color borderColor: "#3b6daa"     //边框颜色
    property color textColor: "#ffffff"          //文本颜色
    property color bgNormalColor: "#1d4f88"      //文本背景色
    property color bgFocusColor: bgNormalColor //文本背景焦点色


    implicitWidth: 120
    implicitHeight: 30


    padding: 0
    leftPadding: padding + (down.indicator ? down.indicator.width : 0)
    rightPadding: padding + (up.indicator ? up.indicator.width : 0)

    font{
        family: "SimSun"
        pixelSize: 20
    }
    contentItem: Rectangle{
        z: 2
        color: control.activeFocus
               ?bgFocusColor
               :bgNormalColor;

        TextInput {
            anchors.fill: parent
            text: control.displayText
            horizontalAlignment: Qt.AlignHCenter
            verticalAlignment: Qt.AlignVCenter
            readOnly: !control.editable
            validator: control.validator
            inputMethodHints: control.inputMethodHints
            color: control.textColor
            selectByMouse: true
            selectedTextColor: "white"
//            selectionColor: "black"
            font: control.font
            renderType: Text.NativeRendering
        }

        Rectangle{
            width: parent.width
            height: 1
            color: borderVisible?borderColor:"transparent"
        }
        Rectangle{
            width: parent.width
            height: 1
            anchors.bottom: parent.bottom
            color: borderVisible?borderColor:"transparent"
        }
        Rectangle{
            width:1
            height: parent.height
            anchors.left: parent.left
            color: borderVisible?borderColor:"transparent"
        }
        Rectangle{
            width:1
            height: parent.height
            anchors.right: parent.right
            color: borderVisible?borderColor:"transparent"
        }
    }
    up.indicator:Rectangle
    {
        color:"#00000000"
    }
    down.indicator: Rectangle
    {
        color:"#00000000"
    }
}
