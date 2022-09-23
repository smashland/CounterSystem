//                                                  新建方案
import QtQuick 2.12
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls.Styles 1.4
import "../Common"
import "../Exercise"
import MyItem 1.0

Item {
    id: scenarioNew
    property var title: ""
    property var scenarioNewInfo: ""
    width: 1165 *dpx
    height: 710 *dpy
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
            Text {
                id: nameItemText
                width: nameItemText.contentWidth
                height: 40 *dpy
                color: "#ffffff"
                text: qsTr("方案名称:")
                font.pixelSize: 17*dpx;
                font.family: "Microsoft YaHei";
                verticalAlignment: Text.AlignVCenter
            }
        }
        Rectangle {
            x: nameItemText.contentWidth + 20 *dpx
            width: 440*dpx
            height: 40 *dpy
            color: "#1d4f88"
            border.color: "#26abef"
            TextInput {
                id: nameItemContent
                x: 10 *dpx
                text: ""
                width: 420*dpx
                height: 40 *dpy
                font.pixelSize: 17*dpx
                color: "#ffffff"
                clip: true
                font.family: "Microsoft YaHei"
                verticalAlignment: Text.AlignVCenter

                onEditingFinished: {
                    sceManager.setSceName(nameItemContent.text)
                }
            }

        }
    }
    onTitleChanged: {
        nameItemContent.text = scenarionew.title
    }

    Text {
        id: weizhixinxi
        x: 90 *dpx
        y: 160 * dpy + nameItemContent.height + 30 *dpy
        width: weizhixinxi.contentWidth
        height: weizhixinxi.contentHeight
        text: qsTr("人员信息表")
        font.pixelSize: 18*dpx;
        color: "#ffffff";
        font.family: "Microsoft YaHei"
    }
    Text {
        id: renyuanshuliang
        y: 160 * dpy + nameItemContent.height + 33 *dpy
        anchors.right: parent.right
        anchors.rightMargin: 90*dpx
        width: renyuanshuliang.contentWidth
        height: renyuanshuliang.contentHeight
        text: qsTr("人员总数：") + phoneModel.count
        font.pixelSize: 16*dpx;
        font.bold: true
        color: "#55e5aa";
        font.family: "Microsoft YaHei"
    }
    Rectangle {
        y: weizhixinxi.contentHeight + weizhixinxi.y + 10 *dpy
        x: 90 *dpx
        width: 985 *dpx
        height: 2 *dpy
        color: "#3b6daa"
    }

    Rectangle {
        id: renyuantianjia
        x: 90 *dpx
        y: weizhixinxi.contentHeight + weizhixinxi.y + 10 *dpy + 10 *dpy
        width: 985
        height: 335 *dpy
        color: "transparent"

        Component {
            id: headerView
            Item {
                width: renyuantianjia.width
                height: 40 *dpy
                Rectangle {
                    anchors.fill: parent
                    color: "#2D5689"
                }
                Row {
                    spacing: 56 *dpx
                    x: 25 *dpx
                    height: 40 *dpy
                    TextItem {
                        text: "设备编号"
                        widthTitle: 70 *dpx
                        heightTitle: 40 *dpy
                    }
                    TextItem {
                        text: "人员姓名"
                        widthTitle: 80 *dpx
                        heightTitle: 40 *dpy
                    }
                    TextItem {
                        text: "人员职务"
                        widthTitle: 110 *dpx
                        heightTitle: 40 *dpy
                    }
                    TextItem {
                        text: "红蓝方"
                        widthTitle: 80 *dpx
                        heightTitle: 40 *dpy
                    }
                    TextItem {
                        text: "是否是人质"
                        widthTitle: 138 *dpx
                        heightTitle: 40 *dpy
                    }
                    TextItem {
                        text: "操作"
                        widthTitle: 180 *dpx
                        heightTitle: 40 *dpy
                    }
                }
            }
        }

        Component {
            id: delegate
            Item {
                id: wrapper
                width: renyuantianjia.width
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
                        text: nID
                        width: 70 *dpx
                        height: 50 *dpy
                    }
                    TextItem {
                        id:name
                        text: sName
                        width: 80 *dpx
                        height: 50 *dpy
                    }
                    TextItem {
                        id:level
                        text: nLevel
                        width: 110 *dpx
                        height: 50 *dpy
                    }

                    TextItem {
                        id:group
                        text: nGroup
                        width: 80 *dpx
                        height: 50 *dpy
                    }
                    TextItem {
                        id:host
                        text: bHost ? "是" : "否"
                        width: 138 *dpx
                        height: 50 *dpy
                    }
                    Row {
                        y: 10 *dpy
                        spacing: 15 * dpx
                        ViewButton {
                            name: qsTr("修改")
                            color: viewColor_shuaxin
                            viewImage: "\ue6a5"
                            MouseArea {
                                anchors.fill: parent
                                onClicked:personAdd.visible = true
                                Connections{
                                    function onOk(id,name,level,group,isHost)
                                    {
                                        phoneModel.append({"nID":id,"sName":name,"nLevel":level,"nGroup":group,"bHost":isHost})
                                    }

                                    target: personAdd
                                }
                            }
                        }
                        ViewButton {
                            name: qsTr("删除")
                            color: viewColor_xinjian
                            viewImage: "\ue607"

                        }
                    }
                }

            }
        }

        ListModel {
            id: phoneModel;
            ListElement{
                nID: 12
                sName: "1"
                nLevel: 2
                nGroup:1
                bHost: false
            }
        }

        ListView {
            id: listView
            anchors.fill: parent
            delegate: delegate
            model: phoneModel
            header: headerView
            clip: true
            focus: true
            ScrollBar.vertical: ScrollBar {
                id: scrollBar
            }


        }

    }
    onScenarioNewInfoChanged: {
        if(scenarioNewInfo === null) {
            nameItemContent.text = ""
            listView.model = ""
        }else {
            nameItemContent.text = scenarioNewInfo.Scename
            listView.model = scenarioNewInfo.phoneModel
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
            onClicked: personAdd.visible = true
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
                    scenarioLoader.addScenario(nameItemContent.text);
                    sceManager.addScenario(nameItemContent.text);
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
                scenarionew.visible = false
            }
        }
    }
}
