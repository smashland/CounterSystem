//                                                  新建方案
import QtQuick 2.12
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls.Styles 1.4
import "../Common"
import "../Exercise"
import "Plugins"
import MyItem 1.0

Item {
    id: scenarioNew
    property var title: ""
    property var scenarioNewInfo:null
    property int nCount: 0

    signal findPersonSignal(int id)    //查找人员

    width: 1165 *dpx
    height: 710 *dpy

    Connections{
        function onOk(id,name,level,group,isHost)
        {
            var person = modifySceInfo.addPerson(id);
            if(null!==person)
            {
                person.name = name;
                person.position = level;
                person.groupType = group;
                person.hostage = isHost;
                listView.model=modifySceInfo.listPerson
                nCount = modifySceInfo.getCount();
            }
            else{
                console.log("编号数值重复，请重新输入");
            }

        }
        target: personAdd
    }


    Connections{
        function onSceFindSignal(sceName)
        {
            modifySceInfo=sceManager.findScenario(sceName)
            if(null!==modifySceInfo)
            {
                nameItemContent.text=modifySceInfo.sceName
                listView.model=modifySceInfo.listPerson
                nCount =  modifySceInfo.getCount();
                console.log("查看方案")
            }
            else
            {
                console.log("修改方案错误")
            }
        }
        target: scenarioLoader
    }
    Image {
        id: loginImage
        anchors.fill: parent
        source: "qrc:/Image/Popup_bg_21.png"
    }
    CloseButton {
        anchors.right: scenarioNew.right
        anchors.rightMargin: 73 *dpx
        anchors.top: scenarioNew.top
        anchors.topMargin: 70 *dpy
        onClicked: scenarioNew.visible = false
    }

    PopupTitle {
        name: ("方案设置")
        x: 74*dpx
        y: 64*dpy
    }

    Rectangle {
        id: nameItem
        x: 90 *dpx
        y: 140 * dpy
        Rectangle {
            color: "transparent"
            SceNewText {
                id: nameItemText
                height: 40 *dpy
                color: "#ffffff"
                text: qsTr("方案名称:")
                font.pixelSize: 17*dpx
                verticalAlignment: Text.AlignVCenter
            }
        }
        Rectangle {
            x: nameItemText.contentWidth + 20 *dpx
            width: 440*dpx
            height: 40 *dpy
            color: "#1d4f88"
            border.color: "#26abef"
            InputItem {
                id: nameItemContent
                x: 10 *dpx
                text:modifySceInfo.sceName
                width: 420*dpx
                height: 40 *dpy
            }
        }
    }

    SceNewText {
        id: weizhixinxi
        x: 90 *dpx
        y: 160 * dpy + nameItemContent.height + 30 *dpy
        text: qsTr("人员信息表")
        font.pixelSize: 18*dpx
        color: "#ffffff"
    }
    SceNewText {
        id: renyuanshuliang
        y: 160 * dpy + nameItemContent.height + 33 *dpy
        anchors.right: parent.right
        anchors.rightMargin: 90*dpx
        text: qsTr("人员总数：")+nCount
        font.pixelSize: 16*dpx
    }
    Rectangle {
        y: weizhixinxi.contentHeight + weizhixinxi.y + 10 *dpy
        x: 90 *dpx
        width: 985 *dpx
        height: 2 *dpy
        color: "#3b6daa"
    }

    SceNewList{
        id: listView
        y: weizhixinxi.contentHeight + weizhixinxi.y + 20 *dpy
        model:modifySceInfo.listPerson
        delegate: Rectangle {
            id: wrapper
            width: listView.width
            height: 50 *dpy
            Rectangle {
                anchors.fill: parent
                color: index%2 ? "#2D5689" : "#4671a6"
            }
            Row {
                spacing: 56 *dpx
                x: 25*dpx
                height: 40 *dpy
                TextItem {
                    id: id
                    text: modelData.id
                    width: 70 *dpx
                    height: 50 *dpy
                }
                TextItem {
                    id:name
                    text: modelData.name
                    width: 80 *dpx
                    height: 50 *dpy
                }
                TextItem {
                    id:level
                    text: modelData.position
                    width: 110 *dpx
                    height: 50 *dpy
                }

                TextItem {
                    id:group
                    text: modelData.groupType
                    width: 80 *dpx
                    height: 50 *dpy
                }
                TextItem {
                    id:host
                    text: modelData.hostage ? "是" : "否"
                    width: 138 *dpx
                    height: 50 *dpy
                }
                Row {
                    y: 10 *dpy
                    spacing: 15 * dpx
                    ViewButton {
                        name: qsTr("修改人员")
                        color: viewColor_shuaxin
                        viewImage: "\ue6a5"
                        MouseArea {
                            anchors.fill: parent
                            onClicked:
                            {
                                findPersonSignal(modelData.id)
                                personAdd.visible = true
                            }
                        }
                    }
                    ViewButton {
                        name: qsTr("删除")
                        color: viewColor_xinjian
                        viewImage: "\ue607"
                        MouseArea {
                            anchors.fill: parent
                            onClicked:
                            {
                                modifySceInfo.deletePerson(modelData.id)
                                nCount =  modifySceInfo.getCount();
                               listView.model = modifySceInfo.listPerson;
                            }
                        }
                    }
                }
            }
        }
    }
    function openQml(obj,qmlUrl){
        var component = Qt.createComponent(qmlUrl)
        if (Component.Ready === component.status){
            var qmlObj = component.createObject(null)//,{note:obj}
            if(null !== qmlObj){
//                note2Window[obj] = qmlObj;
                return(qmlObj);
            }
        }else{
            console.log(component.errorString());
            component.destroy();
            return(null);
        }
    }

    Row {
        spacing: 15 *dpx
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 60 *dpy
        x: 444*dpx
        PopupButton {
            background: Rectangle {
                color: "#265aef"
            }
            nameButton: "添加人员"
            onClicked: {
                personAdd.visible = true
            }
        }

        PopupButton {
            background: Rectangle {
                color: "#265aef"
            }

            nameButton: "确定"
            onClicked: {
                if(nameItemContent.text === '') {
                    console.log("没有方案名称")
                }else {
                    if(null===modifySceInfo)
                    {
                        console.log("modifySceInfo函数为空")
                    }
                    sceManager.addScenari(nameItemContent.text,modifySceInfo);
                    sceManager.write();
                    scenarioNew.visible = false
                }
            }
        }
        PopupButton {
            background: Rectangle {
                color: "#1d4f88"
            }
            nameButton: "取消"
            onClicked:
            {
                scenarioNew.visible = false
            }
        }
    }
}
