//                                       设置管理
import QtQuick 2.12
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
//import QtQuick.Controls 2.14 as QC14
import "../Common"
import "../Exercise"
import QtQuick.Controls.Styles 1.2
import "Plugins"

ManageRect{
    id: setloader
    rectWidth: 1102 *dpx
    rectHeight: 680 *dpy
    rectImage: "qrc:/Image/Popup_bg_20.png"
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
                }

            }

        }
    }


    //    QC14.GroupBox
    BasicGroupBox
    {
        id: scoreGroupBox
        y: 100*dpy
        title: qsTr("命中计分:")
        ListView
        {
            property var name: "score"
            clip: true
            id: scoreList
            anchors.leftMargin: 60
            anchors.topMargin: 20
            anchors.fill: parent
            delegate: contactDelegate
            model:$app.settings.scoreSetting
        }

    }

    //    QC14.GroupBox
    BasicGroupBox
    {
        id: harmGroupBox
        y: 100*dpy
        title: qsTr("损伤设置:")
        ListView
        {
            property var name: "harm"
            id: harmList
            anchors.leftMargin: 60
            anchors.topMargin: 20
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
        anchors.topMargin: 20
        title: qsTr("系统设置:")

        ListView
        {
            property var name: "sys"
            id: systemList
            anchors.leftMargin: 60
            anchors.topMargin: 20
            anchors.fill: parent
            delegate: contactDelegate
            model:$app.settings.systemSetting
            clip: true
        }

        Row {
            x:60*dpx
            y:150*dpy
            spacing: 10*dpx
            CheckBox {
                id: voiceControl
                y: 1*dpy
                width: 17*dpx
                height: 17*dpy
                checked:$app.setOpenSpeak
                indicator: Rectangle {
                    width: voiceControl.width
                    height: voiceControl.height
                    color: "#1d4f88"
                    border.color: "#3b6daa"
                    Image {
                        id: tick
                        width: voiceControl.width
                        height: voiceControl.height
                        source: voiceControl.checked ? "qrc:/Image/true.png" : ""
                    }
                }
                onClicked: {
                    if(voiceControl.checked)
                    {
                        $app.setOpenSpeak(true);
                    }
                    else
                    {
                        $app.setOpenSpeak(false);
                    }
                }
            }
            Text {
                text: qsTr("开启语音")
                color: "#d5e2f5"
                font.pixelSize: 14*dpx
                font.family: "Microsoft YaHei"
            }
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
                Text { Layout.preferredWidth: 120;text:modelData.type ;font.pixelSize: 20*dpx;color: "#ffffff"}

                //                QC14.SpinBox
                BasicSpinBox
                {
                    value:modelData.number;
                    from: 1
                    to: modelData.type === "默认子弹数:" ? 9999 : 100
                    editable: true
                    borderVisible: true
                }
            }
        }
    }
    SetMapLoader {
        id: setMapLoader
        x: 300
        y: 120
        visible: false
    }






}
