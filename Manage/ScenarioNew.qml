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
        function onOk(id,name,level,group,isHost,imPath)
        {
            var person = modifySceInfo.addPerson(id);
            if(null!==person)
            {
                person.name = name;
                person.position = level;
                person.groupType = group;
                person.hostage = isHost;
                person.imagePath=imPath;
                listView.model=modifySceInfo.listPerson
                nCount = modifySceInfo.getCount();
            }
            else{
                scePopup.visible = true
                timer.start()
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
        onClicked: {
            scenarioNew.visible = false
            qingkong()
        }
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
                TextListItem {
                    id: id
                    text: modelData.id
                    width: 70 *dpx
                    height: 50 *dpy
                }
                TextListItem {
                    id:name
                    text: modelData.name
                    width: 80 *dpx
                    height: 50 *dpy
                }
                TextListItem {
                    id:level
                    text: if(modelData.position===0)/*?"军官":"士兵"*/
                          {
                              level.text=" "
                          }else if(modelData.position===1){
                              level.text="士兵"
                          } else if(modelData.position===2){
                              level.text="军官"
                          }
                    width: 110 *dpx
                    height: 50 *dpy
                }

                TextListItem {
                    id:group
                    text: modelData.groupType?"红":"蓝"
                    width: 80 *dpx
                    height: 50 *dpy
                }
                TextListItem {
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
//                openPerson("PersonAdd.qml")
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
                    if(null===sceManager.addScenari(nameItemContent.text,modifySceInfo))
                    {
                        scePopup2.visible = true
                        timer.start()
                    }
                    sceManager.write();
                    scenarioNew.visible = false
                    qingkong()
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

    Timer {
        id: timer
        interval: 2500
        repeat: fasle
        running: fasle
        triggeredOnStart: false
        onTriggered: {
            scePopup.visible = false
            scePopup2.visible = false
        }
    }
    function qingkong() {
        nameItemContent.text=""
        listView.model=""
    }
}
