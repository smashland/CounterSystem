//                                       设置管理
import QtQuick 2.12
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls.Styles 1.2
import QtQuick.Shapes 1.0
import "../Common"
import "../Exercise"
import "Plugins"
import "../Setting"
import "../Login"

ManageRect{
    id: setloader
    rectWidth: 1102 *dpx
    rectHeight: 680 *dpy
    rectImage: "qrc:/Image/Popup_bg_27.png"

    CloseButton {
        anchors.right: setloader.right
        anchors.rightMargin: 65 *dpx
        anchors.top: setloader.top
        anchors.topMargin: 58 *dpy
        onClicked: footerBar.btnSet.checked = false
    }

    PopupTitle {
        name: ("设置管理")
        icon: "\ue795"
        x: 74*dpx
        y: 54*dpy
    }

    Rectangle {
        id: xuanzeButton
        x: 80*dpx
        y: 110*dpy
        width: 190*dpx
        height: 522*dpy
        color: "#0a3365"
        ButtonGroup{
            buttons: columnEditBtns.children
        }
        Column {
            id:columnEditBtns
            //        anchors.verticalCenter: parent.verticalCenter
            spacing:  0*dpx
            SwitchButton{
                id: name_text
                text: qsTr("用户设置") //PersonAllInfo.qml
                onClicked: {
                    scoreGroupBox.visible=false
                    harmGroupBox.visible=true
                    systemGroupBox.visible=true
                    setMapLoader.visible = false
                    setNet.visible = false
                }
            }
            SwitchButton{
                id: map_text
                text: qsTr("地图设置")
                onClicked: {
                    scoreGroupBox.visible=false
                    harmGroupBox.visible=false
                    systemGroupBox.visible=false
                    setMapLoader.visible = true
                    setNet.visible = false
                }

            }
            SwitchButton {
                id: defen_text
                text: qsTr("得分设置")
                onClicked: {
                    harmGroupBox.visible=false
                    systemGroupBox.visible=false
                    scoreGroupBox.visible=true
                    setMapLoader.visible = false
                    setNet.visible = false
                }

            }
            SwitchButton {
                id: yunxing_text
                text: qsTr("连接设置")
                onClicked: {
                    harmGroupBox.visible=false
                    systemGroupBox.visible=false
                    scoreGroupBox.visible=false
                    setMapLoader.visible = false
                    setNet.visible = true
                }

            }

        }
    }

    Rectangle {
        id: set
        x: 320*dpx
        y: 100*dpy
        width:710*dpx
        height: 530*dpy
        color: "transparent"
        clip: true
        BasicGroupBox
        {
            id: scoreGroupBox
            y:15*dpy
            title: qsTr("命中计分:")
            ListView
            {
                property var name: "score"
                clip: true
                id: scoreList
                anchors.leftMargin: 60*dpx
                anchors.topMargin: 20*dpy
                anchors.fill: parent
                delegate: contactDelegate
                model:$app.settings.scoreSetting
            }

        }

        //    QC14.GroupBox
        BasicGroupBox
        {
            id: harmGroupBox
            y:15*dpy
            title: qsTr("损伤设置:")
            ListView
            {
                property var name: "harm"
                id: harmList
                anchors.leftMargin: 60*dpx
                anchors.topMargin: 20*dpy
                anchors.fill: parent
                delegate: contactDelegate
                model:$app.settings.harmSetting
                clip: true
            }

        }

        //    QC14.GroupBox
        BasicGroupBox
        {
            id: systemGroupBox
            anchors.top: harmGroupBox.bottom
            anchors.topMargin: 20*dpy
            title: qsTr("系统设置:")

            ListView
            {
                property var name: "sys"
                id: systemList
                anchors.leftMargin: 60*dpx
                anchors.topMargin: 20*dpy
                anchors.fill: parent
                delegate: contactDelegate
                model:$app.settings.systemSetting
                clip: true
            }

            CheckBoxItem {
                id:voiceControl
                anchors.left: parent.left
                anchors.leftMargin: 60*dpx
                anchors.top: parent.top
                anchors.topMargin: 210*dpy
                name: qsTr("开启语音")
            }
        }

        Component
        {
            id: contactDelegate
            Item
            {
                id:showListItem
                width:100 ; height: 30
                RowLayout
                {
                    Text {
                        Layout.preferredWidth: 170;
                        text:modelData.type;
                        font.pixelSize: 20*dpx;
                        color: "#ffffff"
                    }

                    //                QC14.SpinBox
                    BasicSpinBox
                    {
                        value:modelData.number;
                        from: 1
                        to: if(modelData.type === "默认步枪子弹数:")
                            {
                                return 9999
                            }
                            else if(modelData.type === "默认手枪子弹数:")
                            {
                                return 9999
                            }
                            else if(modelData.type === "默认狙击枪子弹数:")
                            {
                                return 9999
                            }
                            else{
                                return 100
                            }
                        editable: true
                        borderVisible: true
                    }
                }
            }
        }

        SetNet {
            id:setNet
            visible: false
        }

        SetMapLoader {
            id: setMapLoader
            visible: false
        }

    }

}
