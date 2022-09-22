import QtQuick 2.7
import QtQuick.Controls 2.3
import QtQuick.Layouts 1.3
import QtQuick.Dialogs 1.3
import Qt.labs.platform 1.1
import "../Common"
import "../Exercise"
Popup
{
    id: personAdd
    width: 651*dpx
    height: 510*dpy
    anchors.centerIn: parent
    modal: true
    property string imagePath;

//    signal ok(int id,string name,int level,int group,bool isHost);
    signal ok(int id,string name,int level,int group,bool isHost);

    property var outData
    property var rowNum;
    property var bConnected:true

    /// 背景半透明
    background:Rectangle
    {
        color:"transparent"
        Image {
            anchors.fill: parent
            source: "qrc:/Image/Popup_bg_20.png"
        }
    }

    PopupTitle {
        id: popuptitle
        x: 50 *dpx;
        y: 50 *dpy
        name: qsTr("添加人员")
        icon: qsTr("\ue8b8")
    }
    TransverseLine {
        x: 50 *dpx
        y: popuptitle.height + 80 *dpy
    }

    Rectangle {
        x: 50 *dpx
        y: 106*dpy
        color: "transparent"
        width: 141*dpx
        height: 173*dpy
        Image {
            id: morentouxiang
            anchors.fill:parent
            source: "qrc:/Image/soldiers.png"
        }
        Image {
            anchors.fill: parent
            source: fileDialog.fileUrl
        }
    }
    Rectangle {
        x: 50 *dpx
        y: 300*dpy
        width: 141*dpx
        height: 33*dpy
        color: "#1d4f88"
        border.color: "#3b6daa"
        Text {
            id: sahngchuantouxiang
            text: qsTr("点击上传头像")
            font.family: "Microsoft YaHei"
            anchors.centerIn: parent
            color: "#ffffff"
        }
        MouseArea {
            anchors.fill: parent
            onClicked: {
                fileDialog.open()
            }
        }
    }
    FileDialog {
        id: fileDialog
        folder: shortcuts.home
//        onAccepted: {
//            source: fileDialog.fileUrl
//        }
        title: qsTr("请选择文件")
        nameFilters: [qsTr("(*.png)"),qsTr("(*.jpg)"),qsTr("全部文件 (*.*)")]
        currentFile: document.source
        onAccepted: {
            source: fileDialog.fileUrl
            imagePath=currentFile.toString().replace("file:///", "");
        }
        onRejected: {
//            console.log("Canceled")
        }
        Component.onCompleted: visible = flase
    }
    Column {
        x: 278 *dpx
        y: 106 *dpy
        spacing: 20*dpy

        SoldierItem {
            id:shebeiId
            text: "设备编号: "
            name:""
        }

        SoldierItem {
            id:personName
            text: "人员姓名: "
            name:""
        }
        Row {
            spacing: 20*dpx
            Text {
                id: soldierItemText
                width: soldierItemText.contentWidth
                height: 34 *dpy
                text: "人员职务: "
                color: "#ffffff"
                font.pixelSize: 17*dpx;
                font.family: "Microsoft YaHei";
                verticalAlignment: Text.AlignVCenter
            }
            ComboBox {
                id: combobox_renyuan
                width: 200 *dpx
                height: 34 *dpy
                model: ["士兵"]
                delegate: ItemDelegate {
                    width: 110 *dpx
                    height: 30 *dpy
                    contentItem: Text {
                        text: modelData
                        color: "black"
                        font.pixelSize: 16
                        font.family: "Microsoft YaHei"
                        verticalAlignment: Text.AlignVCenter
                    }
                }
                contentItem: TextInput {
                    leftPadding: 10*dpx
                    text: combobox_renyuan.displayText
                    font.pixelSize: 16
                    color: "#ffffff"
                    font.family: "Microsoft YaHei"
                    verticalAlignment: Text.AlignVCenter
                }
                background: Rectangle {
                    implicitWidth: 110*dpx
                    implicitHeight: 30 *dpy
                    color: "#1d4f88"
                    border.color: "#26abef"
                }
            }
        }
        Row {
            spacing: 20*dpx
            Text {
                id: zhenyingxuanze
                width: zhenyingxuanze.contentWidth
                height: 34 *dpy
                text: "阵营选择: "
                color: "#ffffff"
                font.pixelSize: 17*dpx;
                font.family: "Microsoft YaHei";
                verticalAlignment: Text.AlignVCenter
            }
            ComboBox {
                id: zhenying
                width: 200 *dpx
                height: 34 *dpy
                model: ["蓝","红"]
                delegate: ItemDelegate {
                    width: 110 *dpx
                    height: 30 *dpy
                    contentItem: Text {
                        text: modelData
                        color: "black"
                        font.pixelSize: 16
                        font.family: "Microsoft YaHei"
                        verticalAlignment: Text.AlignVCenter
                    }
                }
                contentItem: TextInput {
                    leftPadding: 10*dpx
                    text: zhenying.displayText
                    font.pixelSize: 16
                    color: "#ffffff"
                    font.family: "Microsoft YaHei"
                    verticalAlignment: Text.AlignVCenter
                }
                background: Rectangle {
                    implicitWidth: 110*dpx
                    implicitHeight: 30 *dpy
                    color: "#1d4f88"
                    border.color: "#26abef"
                }
            }
        }
        Row {
            spacing: 20*dpx
            Text {
                id: shifourenzhi
                width: shifourenzhi.contentWidth
                height: 34 *dpy
                text: "是否人质: "
                color: "#ffffff"
                font.pixelSize: 17*dpx;
                font.family: "Microsoft YaHei";
                verticalAlignment: Text.AlignVCenter
            }
            Row {
                width: 120 *dpx
                y: 3 *dpy
                spacing: 14 *dpx
                RadioButton {
                    id:control3
                    checked: true
                    text: qsTr("是")
                    indicator: Rectangle {
                        implicitWidth: 18
                        implicitHeight: 18
                        y: parent.height / 2 - height / 2
                        radius: 9
                        border.color: control3.down ? "#ffffff" : "#26abef"
                        Rectangle {
                            width: 12
                            height: 12
                            radius: 6
                            anchors.centerIn: parent
                            color: control3.down ? "#ffffff" : "#1d4f88"
                            visible: control3.checked
                        }
                    }
                    contentItem: Text {
                        text: control3.text
                        opacity: enabled ? 1.0 : 0.3
                        color: "#ffffff"
                        font.pixelSize: 17*dpx;
                        verticalAlignment: Text.AlignVCenter
                        leftPadding: 20*dpx
                    }
                }
                RadioButton {
                    id: control4
                    text: qsTr("否")
                    indicator: Rectangle {
                        implicitWidth: 18
                        implicitHeight: 18
                        y: parent.height / 2 - height / 2
                        radius: 9
                        border.color: control4.down ? "#ffffff" : "#26abef"
                        Rectangle {
                            width: 12
                            height: 12
                            radius: 6
                            anchors.centerIn: parent
                            color: control4.down ? "#ffffff" : "#1d4f88"
                            visible: control4.checked
                        }
                    }
                    contentItem: Text {
                        text: control4.text
                        opacity: enabled ? 1.0 : 0.3
                        color: "#ffffff"
                        font.pixelSize: 17*dpx;
                        verticalAlignment: Text.AlignVCenter
                        leftPadding: 20*dpx
                    }
                }
            }
        }

    }

    Row {
        spacing: 15 *dpx
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 40 *dpy
        x: (personAdd.width-191*dpx)/2
        PopupButton {
            background: Rectangle {
                color: "#265aef"
            }

            nameButton: "确定"
            onClicked: {
                sceManager.addPerson(shebeiId.name,personName.name, combobox_renyuan.currentIndex,
                                     zhenying.currentIndex,control3.checked,imagePath);
                ok(shebeiId.name,personName.name, combobox_renyuan.currentIndex,
                   zhenying.currentIndex,control3.checked);
                personAdd.visible = false
                ///// 给调用界面
            }

        }
        PopupButton {
            background: Rectangle {
                color: "#1d4f88"
            }
            nameButton: "取消"
            onClicked: {
                personAdd.visible = false
            }
        }
    }
}

