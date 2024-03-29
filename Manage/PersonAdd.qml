﻿import QtQuick 2.7
import QtQuick.Controls 2.3
import QtQuick.Layouts 1.3
import QtQuick.Dialogs 1.3
import Qt.labs.platform 1.1
import "../Common"
import "../Exercise"
import "Plugins"
Rectangle
{
    id: personAdd
    width: 651*dpx
    height: 510*dpy
    anchors.centerIn: parent
    //    modal: true
    property string imagePath;
    property var position:{0};
    property var zhenying:{0};

    signal ok(int id,string name,int level,int group,bool isHost,string imPath);

    property var rowNum;
    property bool bConnected:true

    Connections{
        function onFindPersonSignal(id)
        {
            var person =  modifySceInfo.findPerson(id)
            if(null!==person)
            {
                shebeiId.name=person.id
                personName.name=person.name
                //                combobox_renyuan.currentText=person.position?"军官":"士兵"
                if(person.position===0)
                {
                    combobox_renyuan.currentText=""
                }else if(person.position===1){
                    combobox_renyuan.currentText="士兵"
                }else if(person.position===2){
                    combobox_renyuan.currentText="军官"
                }
                zhenying.currentText=person.groupType?"红":"蓝"
                if(person.hostage)
                {
                    control3.checked=true
                }
                else
                {
                    control4.checked=true
                }

                avatarImage.source="file:///"+person.imagePath
            }

        }
        target: scenarioNew
    }
    color:"transparent"
    Image {
        anchors.fill: parent
        source: "qrc:/Image/Popup_bg_27.png"
    }
    PopupTitle {
        id: popuptitle
        x: 40*dpx
        y: 38*dpy
        name: qsTr("人员设置")
        icon: qsTr("\ue8b8")
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
            source:"qrc:/Image/soldiers.png"
        }
        Image {
            id:avatarImage
            anchors.fill: parent
            source: fileDialog.file/*fileDialog.fileUrl*/
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
        title: qsTr("请选择文件")
        nameFilters: [qsTr("(*.png)"),qsTr("(*.jpg)"),qsTr("全部文件 (*.*)")]
        currentFile: document.source
        onAccepted: {
            source: fileDialog.fileUrl
            imagePath=currentFile.toString().replace("file:///", "");
        }
        onRejected: {
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
            z: 999
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
            ComboBoxItem{
                id: combobox_renyuan
                width: 200 *dpx
                height: 34 *dpy
                listheight: 110 *dpx
                listelementheight: 30*dpy
                z:99
                items: [
                    {target:"士兵"},
                    {target:"军官"}
                ]
                onCurrentTextChanged:
                    /*  onCurrentIndexChanged:*/ {
                    //                    var type = combobox_renyuan.currentIndex;
                    //                    if(type === 0){
                    //                        combobox_renyuan.currentText = "士兵"
                    //                    }else if(type === 1) {
                    //                        combobox_renyuan.currentText = "军官"
                    //                    }

                    var type = combobox_renyuan.currentText;
                    if(type === "士兵"){
                        position=1
                    }else if(type === "军官") {
                        position=2
                    }else if(type === "") {
                        position=0
                    }
                }
            }
        }
        Row {
            spacing: 20*dpx
            z: 998
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
            ComboBoxItem{
                id: zhenying
                width: 200 *dpx
                height: 34 *dpy
                listheight: 110 *dpx
                listelementheight: 30*dpy
                items: [
                    {target:"蓝"},
                    {target:"红"}
                ]
                onCurrentIndexChanged: {
                    var type = zhenying.currentIndex;
                    if(type === 0){
                        zhenying.currentText = "蓝"
                    }else if(type === 1) {
                        zhenying.currentText = "红"
                    }
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
                            width: 12*dpy
                            height: 12*dpy
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
                var type;
                if( zhenying.currentText==="蓝")
                {
                    type=0
                }
                else if( zhenying.currentText==="红")
                {
                    type=1
                }
                ok(shebeiId.name,personName.name, position,
                   type,control3.checked,imagePath);
                //                ok(shebeiId.name,personName.name, position/*combobox_renyuan.currentIndex*/,
                //                   zhenying.currentText,control3.checked,imagePath);
            }

        }
        PopupButton {
            background: Rectangle {
                color: "#1d4f88"
            }
            nameButton: "取消"
            onClicked: {
                personAdd.visible = false
                qingkong()
            }
        }
    }
    ScePopup {
        id: scePopup
        visible: false
        anchors.centerIn: parent
        text: "人员ID重复，请重新输入！"
    }
    function scePopupSignal(sceSignal)
    {
        scePopup.visible=sceSignal
    }
    function qingkong() {
        shebeiId.name=""
        personName.name=""
        combobox_renyuan.currentText=""
        zhenying.currentText=""
        avatarImage.source="qrc:/Image/soldiers.png"
        control3.checked = false
        control4.checked = false
        position=0
    }

}

