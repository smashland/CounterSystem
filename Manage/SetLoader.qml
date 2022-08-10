//                                       设置管理
import QtQuick 2.12
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
//import QtQuick.Controls 2.14 as QC14
import "../Common"
import "../Exercise"

Rectangle {
    id: setloader
    anchors.fill: parent
    color: "transparent"
    Item {
        id: backgroundItem
        width: 1102 *dpx
        height: 680 *dpy
        anchors.centerIn: parent
        Image {
            id: loginImage
            anchors.fill: parent
            source: "qrc:/Image/Popup_bg_20.png"
        }
        CloseButton {
            anchors.right: backgroundItem.right
            anchors.rightMargin: 60 *dpx
            anchors.top: backgroundItem.top
            anchors.topMargin: 60 *dpy
            onClicked: setloader.visible = false
        }

        PopupTitle {
            name: ("击杀情况")
            icon: "\ue795"
        }
        TransverseLine {
            x: 80 *dpx
            y: 95*dpy
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
                }
            }
            SwitchButton{
                id: map_text
                text: qsTr("地图设置")
                onClicked: {
                    scoreGroupBox.visible=false
                    harmGroupBox.visible=false
                    systemGroupBox.visible=false
                }

            }
            SwitchButton {
                id: defen_text
                text: qsTr("得分设置")
                onClicked: {
                    harmGroupBox.visible=false
                    systemGroupBox.visible=false
                    scoreGroupBox.visible=true
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
                    id:control
                    value:modelData.number;
                    from: 1
                    to: modelData.type === "默认子弹数:" ? 9999 : 100
                    editable: true
                    borderVisible: true


                    valueFromText: function(text, locale)
                    {
                        var nValue=Number.fromLocaleString(locale, text);

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

                    /// 当值修改的时候提交更改
                    onValueModified:
                    {
                        $app.settings.changeSetting(showListItem.parent.parent.name,index,value);
                    }
                }
            }
        }
    }

}
