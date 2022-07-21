import QtQuick 2.6
import QtQuick.Controls 2.3
import QtQuick.Layouts 1.0
import QtQuick.Controls.Material 2.1


Popup
{
    signal toConnect();
    id:showComName
    width: parent.width
    height: parent.height

    onClosed:
    {
        if(null !== $obShow)
        {
            $obShow.forceActiveFocus();
        }
    }

    background: Rectangle
    {
        opacity:0.0
    }

    ColumnLayout
    {
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        ComboBox
        {
            id: control
            model: $app.settings.comNameList();

            /// 弹出的combobox的选项
            delegate: ItemDelegate
            {
                width: control.width
                contentItem: Text
                {
                    text: modelData
                    color: "#FFFF00"
                    font.bold: true
                    elide: Text.ElideRight
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                }
                background: Rectangle
                {
                    border.color:"#FFFF00"
                    color:"#000000"
                }

                highlighted: control.highlightedIndex === index
            }

            /// 绘制下拉箭头
            indicator: Canvas
            {
                id: canvas
                x: control.width - width - control.rightPadding
                y: control.topPadding + (control.availableHeight - height) / 2
                width: 12
                height: 8
                contextType: "2d"

                Connections
                {
                    target: control
                    function onPressedChanged(){canvas.requestPaint()}
                }

                onPaint:
                {
                    context.reset();
                    context.moveTo(0, 0);
                    context.lineTo(width, 0);
                    context.lineTo(width / 2, height);
                    context.closePath();
                    context.fillStyle = "#FFFF00";
                    context.fill();
                }
            }

            contentItem: Text
            {
                leftPadding: 0
                rightPadding: control.indicator.width + control.spacing

                text: control.displayText
                font.bold:true

                color: "#FFFF00"
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                elide: Text.ElideRight
            }

            background: Rectangle
            {
                implicitWidth: 120
                implicitHeight: 40
                opacity:0
                radius: 2
            }

            popup: Popup
            {
                y: control.height - 1
                width: control.width
                implicitHeight: contentItem.implicitHeight
                padding: 1

                contentItem: ListView
                {
                    clip: true
                    implicitHeight: contentHeight
                    model: control.popup.visible ? control.delegateModel : null
                    currentIndex: control.highlightedIndex

                    ScrollIndicator.vertical: ScrollIndicator { }
                }

                background: Rectangle
                {
                    border.color: "#FFFF00"
                    color: "#00000000"
                    radius: 2
                }
            }
        }

        Button
        {
            width: control.width
            flat: true
            contentItem: Text
            {
                color:"#FFFF00"
                text:"连接"
                font.pixelSize:22
                font.bold:true
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }

            onClicked:
            {
                showComName.close();
                $app.settings.setComName(control.currentText);
                $app.startConnect();
                toConnect();
            }
        }
    }
}
