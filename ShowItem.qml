import QtQuick 2.2
import MyItem 1.0
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.1
import QtGraphicalEffects 1.0

Rectangle
{
    id: rectangle
    anchors.fill: parent
    width: 638
    height: 371
    color:  '#00000000'

//    signal nextFrame(var licInfo)

//    /// 收到机器码信息
//    function recive(str)
//    {
//        needLic.updateString(str);
//        element.text = str;
//    }

    // 自定义组件，获取背景图片
    Blur
    {
        id:target
        anchors.fill: parent
        visible: false
    }

    FastBlur
    {
        anchors.fill: parent
        source: target
        radius: 20
    }


    Keys.enabled: true
    Keys.onEscapePressed:
    {
        $app.exitApp();
    }

    Component.onCompleted:
    {
        rectangle.forceActiveFocus();
    }

    /// 显示二维码
    Rect
    {
        id:needLic
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter
        width: parent.height/2
        height: parent.height/2
        visible: true
    }

    /// 显示二维码对应的文字
    Text
    {
        id: element
        enabled: false
        anchors.top: needLic.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        font.pixelSize: 18
    }

//    RowLayout
//    {
//        id: rowLayout
//        anchors.horizontalCenter: parent.horizontalCenter
//        anchors.top: element.bottom
//        anchors.topMargin: 10

//        Text
//        {
//            id: element1
//            text: "许可码"
//            enabled: false
//            font.pixelSize: 17
//        }

//        TextField
//        {
//            id: textField
//            width: 500
//            placeholderText:element1.text
//        }

//        Button
//        {
//            id: button
//            text:"保存"
//            font.pixelSize: 17
//            hoverEnabled: true
//            checkable:true
//            background: Rectangle
//            {
//                opacity: 0.0
//            }

//            contentItem: Label
//            {
//                id:showInfo
//                text: button.text
//                font: button.font
//                verticalAlignment: Text.AlignVCenter
//                color: '#FFFF0000'
//            }

//            /// 鼠标划过的时候字体变颜色
//            onHoveredChanged:
//            {
//                if(hovered)
//                {
//                    showInfo.color = '#FFFFFF00'
//                }
//                else
//                {
//                    showInfo.color='#FFFF0000'
//                }
//            }

//            /// 将获取到的许可码，给上层界面
//            onClicked:
//            {

////                loadQml("qrc:/Login/LoginCenter.qml")
//                nextFrame(textField.text)
//            }
//        }
//    }
}
