import QtQuick 2.15
import QtQuick.Controls 2.15
SpinBox {
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
            id:inputText
            anchors.fill: parent
            text: control.value
            horizontalAlignment: Qt.AlignHCenter
            verticalAlignment: Qt.AlignVCenter
            readOnly: !control.editable
            validator: control.validator
            inputMethodHints: control.inputMethodHints
            color: control.textColor
            selectByMouse: true
            selectedTextColor: "white"
            selectionColor: "#0187d6"
            font: control.font
            renderType: Text.NativeRendering
            onTextEdited:
            {
                var nValue=Number.fromLocaleString(locale, inputText.text);
                if(nValue !== control.value)
                {
                    if(nValue>control.to)
                    {
                        control.value = control.to;
                    }
                    else if(nValue < control.bottom || Number.isNaN(nValue))
                    {
                        control.value = control.from;
                    }
                    else
                    {
                        control.value = nValue;
                    }

                    inputText.text = control.value;
                    $app.settings.changeSetting(showListItem.parent.parent.name,index,control.value);
                }
            }
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

    valueFromText: function(text, locale)
    {

        var nValue=Number.fromLocaleString(locale, text);

        console.log("valueFromText:",nValue);
        if(nValue<=control.to && nValue>=control.from)
        {
            return(nValue);
        }
        else if(nValue>control.to)
        {
            return(control.to)
        }
        else
        {
            return(control.from)
        }
    }
}
