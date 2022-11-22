import QtQuick 2.12
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls.Styles 1.2
import "../Common"
import "../Exercise"
import "Plugins"
import "../Setting"
import "../Login"

Rectangle {
    id: setNet

    width:710*dpx
    height: 530*dpy
    color: "transparent"
    property string ip: "0.0.0.0"
    property int nport: 0

    property int iTime: 0

    Component.onCompleted:
    {
        if(1 === $app.settings.conType)
        {
            chuankouGroupBox.visible = true
        }
        else
        {
            wifiGroupBox.visible = true
        }
    }

    Timer {
        id: timer
        interval: iTime
        running: false
        onTriggered: {
            $app.settings.setWifiInfo(outInput.text,portInput.text);
            $app.startConnect();
        }
    }

    BasicGroupBox
    {
        id: wifiGroupBox
        y: 15*dpy
        title: qsTr("网络设置:")
        height: 280*dpy
        visible: false
        Item {
            anchors.left: parent.left
            anchors.leftMargin: 60*dpx
            anchors.top: parent.top
            anchors.topMargin: 35*dpy
            height: 17*dpy
            CheckBox {
                id: check
                y: 2*dpy
                width: 17*dpx
                height: 17*dpy
                checked:true
                indicator: Rectangle {
                    width: check.width
                    height: check.height
                    color: "#1d4f88"
                    border.color: "#3b6daa"
                    Image {
                        width: check.width
                        height: check.height
                        source: check.checked ? "qrc:/Image/true.png" : ""
                    }
                }
                onClicked: {
                    if(checked === true) {
                        timer.start();
                    }else if(checked === false) {
                        timer.stop();
                    }
                }
            }
            Text {
                id: checkText
                x: 27*dpx
                color: "#d5e2f5"
                font.pixelSize: 14*dpx
                font.family: "Microsoft YaHei"
                text: qsTr("断开自动重连")
            }
        }
        Column {
            x:60*dpx
            y:60*dpy
            spacing:15*dpy

            Row {
                TextListItem {
                    id:chonglian
                    text: "断开重连的时间间隔："
                    heightTitle: 34*dpx
                    font.bold: false
                }

                TextFieldItem {
                    id:chonglianTime
                    width: 100*dpx
                    x:chonglian.contentWidth+80*dpx
                    text:"5"
                    validator: IntValidator{bottom: 0;top:99999;}
                    onTextEdited: {
                        iTime = (chonglianTime.text) * 1000
                    }
                }
            }

            Row
            {
                id: row
                TextListItem {
                    id: ipText
                    text: "IP 地址："
                    heightTitle: 34*dpx
                    font.bold: false
                }

                TextFieldItem
                {
                    id:outInput
                    width: 150*dpx
                    text: $app.settings.getSip()
                }
            }
            Row {
                TextListItem {
                    id:dkh
                    text: "端口号："
                    heightTitle: 34*dpx
                    font.bold: false
                }

                TextFieldItem {
                    id:portInput
                    width: 100*dpx
                    x:dkh.contentWidth+80*dpx
                    validator: IntValidator{bottom: 0;top:65535;}
                    text: $app.settings.getPort()
                }

            }
        }
        PopupButton {
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 17*dpy
            x: 256*dpx
            background: Rectangle {
                color: "#265aef"
            }
            nameButton: "连接"
            onClicked: {
                if(outInput.text!==""&&portInput.text!=="")
                {
                    $app.settings.setWifiInfo(outInput.text,portInput.text);
                    $app.startConnect();
                }
                else
                {
                    if(outInput.text===""||portInput.text!=="")
                    {
                        sIpErrorDialog.visible=true
                    }
                }

            }
        }
    }

    BasicGroupBox
    {
        id: chuankouGroupBox
        y: 15*dpy
        height: 150*dpy
        title: qsTr("串口设置:")
        visible: false
        Text {
            id: chuankouhao
            x:60*dpx
            y:30*dpy
            width: chuankouhao.contentWidth
            height: 34 *dpy
            text: "串口号: "
            color: "#ffffff"
            font.pixelSize: 17*dpx;
            font.family: "Microsoft YaHei";
            verticalAlignment: Text.AlignVCenter
        }
        Rectangle {
            x:chuankouhao.contentWidth+80*dpx
            y:30*dpy
            width: 350 *dpx
            height: 34 *dpy
            color: "transparent"
            TextField {
                anchors.fill: parent
                color: "#4582c7"
                font.pixelSize: 16*dpx
                font.family: "Microsoft YaHei"
                clip: true
                verticalAlignment: Text.AlignVCenter
                leftPadding:  52*dpx
                readOnly:true
                activeFocusOnPress:true
                background: Rectangle {
                    color: "#1d4f88"
                    border.color: "#3b6daa"
                }
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
                            color: "#4582c7"
                            font.pixelSize: 16*dpx
                            font.bold: true
                            elide: Text.ElideRight
                            verticalAlignment: Text.AlignVCenter
                            horizontalAlignment: Text.AlignHCenter
                        }
                        background: Rectangle
                        {/*
                            border.color:"#00baff"*/
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
                            context.fillStyle = "#4582c7";
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
                            //                                border.color: "#00baff"
                            color: Qt.rgba(0/255, 31/255, 94/255, 0.8);
                            //                                opacity:0.8
                            radius: 2
                        }
                    }
                    onPressedChanged: {
                        control.model=$app.settings.comNameList();
                    }

                }
            }

        }
        PopupButton {
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 17*dpy
            x: 256*dpx
            background: Rectangle {
                color: "#265aef"
            }
            nameButton: "连接"
            onClicked: {
                if(control.currentText!=="")
                {
                    if($app.settings.isExistcomName(control.currentText))
                    {
                        $app.settings.setComName(control.currentText);
                        $app.startConnect();
                        toConnect();
                    }
                    else
                    {
                        comErrorDialog.visible = true
                        control.model=$app.settings.comNameList();

                    }

                }
                else
                {
                    if(control.currentText==="")
                    {
                        comErrorDialog.visible = true
                    }
                }

            }
        }

    }
}
