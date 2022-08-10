import QtQuick 2.2
import QtQuick.Controls 2.15

Popup
{
    property alias exitShowLabel: confirmPopupLable.text
    signal yesPutDown()
    signal noPutDown()

    closePolicy:Popup.NoAutoClose

    /// 白色字体
    Component
    {
        id: flatButton
        Button
        {
            flat: true
            contentItem: Label
            {
                color:'#FFFFFF'
                text: textForShow
                font
                {
                    pixelSize:22
                    bold:true
                }
                horizontalAlignment:Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }
        }
    }

    id: confirmPopUP
    anchors.centerIn: Overlay.overlay
    width: parent.width
    height: parent.height
    modal: true
    background: Rectangle
    {
        opacity:0.0
    }

    /// 退出警告背景
    Rectangle
    {
        id:backeRect
        width: 400
        height: 200
        anchors.centerIn: parent
        color: "#88FF0000"
        border.color: "#FFFF0000"
    }

    /// 退出警告内容
    Label
    {
        id:confirmPopupLable
        anchors.top: backeRect.top
        anchors.topMargin: 50
        anchors.horizontalCenter: parent.horizontalCenter;
        color:"#FFFFFFFF"
        font
        {
            pixelSize:22
            bold:true
        }
    }

    Row
    {
        anchors.bottom: backeRect.bottom;
        anchors.bottomMargin: 50
        anchors.horizontalCenter: parent.horizontalCenter;

        spacing: 50;
        /// 加载两个退出按钮
        Loader
        {
            property var textForShow: '是吗'
            id:yesLoader
            sourceComponent:flatButton
        }
        Loader
        {
            property var textForShow: '否'
            id:noLoader
            sourceComponent:flatButton
        }
    }

    Connections
    {
        target: yesLoader.item
        function onClicked()
        {
            confirmPopUP.close();
            yesPutDown()
        }
    }

    Connections
    {
        target: noLoader.item
        function onClicked()
        {
            confirmPopUP.close();
            noPutDown()
        }
    }

    onClosed:
    {
        /// 将焦点退还给当前显示的对象
        if(null !== $obShow)
        {
            $obShow.forceActiveFocus();
        }
    }
}
