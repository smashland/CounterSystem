import QtQuick 2.15
import QtQuick.Controls 2.15
import "Plugins"

Column {
    spacing: 50*dpy
    signal toConnect()
    property alias name: control.currentText
    LoginImage {
        LoginTextField {
            ComboBox
            {
                id: control
                width: parent.width
                height: parent.height
                anchors.right: parent.right
                model: $app.settings.comNameList();
                /// 弹出的combobox的选项
                delegate: ItemDelegate
                {
                    width: control.width
                    contentItem: Text
                    {
                        text: modelData
                        color:  Qt.rgba(255/255, 255/255, 255/255, 0.8);
                        font.pixelSize: 16*dpx
                        font.bold: true
                        elide: Text.ElideRight
                        verticalAlignment: Text.AlignVCenter
                        horizontalAlignment: Text.AlignHCenter
                    }
                    background: Rectangle
                    {
                        border.color:"#00baff"
                        color: "transparent"
                    }

                    highlighted: control.highlightedIndex === index
                }

                /// 绘制下拉箭头
                indicator: Canvas
                {
                    id: canvas
                    x: control.width - width - control.rightPadding
                    y: control.topPadding + (control.availableHeight - height) / 2
                    width: 12*dpx
                    height: 8*dpy
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
                        context.fillStyle = "#00baff";
                        context.fill();
                    }
                }

                contentItem: Text
                {
                    leftPadding: 0
                    rightPadding: control.indicator.width + control.spacing

                    text: control.displayText
                    font.bold:true

                    font.pixelSize: 16*dpx
                    color: Qt.rgba(255/255, 255/255, 255/255, 0.8);
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
                        border.color: "#00baff"
                        color: Qt.rgba(0/255, 31/255, 94/255, 0.8);
                        //                                opacity:0.8
                        radius: 2
                    }
                }
            }
        }
    }
    LoginButton {
        MouseArea {
            anchors.fill: parent
            onClicked:
            {
                if(control.currentText!=="")
                {
                    $app.settings.setComName(control.currentText);
                    $app.startConnect();
                    $licCheck.saveLicense(lrText.text);
                    $licCheck.checkLicense()
                    toConnect();
                }
                else
                {
                    comErrorDialog.visible = true
                }
            }
        }
    }
    onPressedChanged: {
        control.model=$app.settings.comNameList();
    }
}

