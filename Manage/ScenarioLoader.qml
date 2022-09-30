//                                       方案管理
//import QtQuick 1.1
import QtQuick 2.12
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import Qt.labs.platform 1.1
import Qt.labs.qmlmodels 1.0
import "../Common"
import "../Exercise"
import "../Status"

Rectangle {
    id: scenarioLoader
    anchors.fill: parent
    color: "transparent"
    property var scenarioInfo: null
    signal addScenario(string sceName)
    signal sceFindSignal(string sceName)

    Connections{
        function onNewSce(sceName)
        {
            var scenario=scenarioLoader.addScenario(sceName)
            scenario.sceName=sceName
            listView.model=scenarioInfo.getSceAll()

//            var scenario=sceManager.addScenario(sceName)
//            console.log("测试新建方案")
//            listView.model=sceManager.getSceAll();
        }
        target:scenarioNew
    }

    Item {
        id: backgroundItem
        width: 1226 *dpx
        height: 787 *dpy
        anchors.centerIn: parent
        MouseArea {
            anchors.fill: parent
            onWheel: {
                // 屏蔽滚轮事件，防止滚动方案列表时缩放地球
            }
        }
        Image {
            id: loginImage
            anchors.fill: parent
            source: "qrc:/Image/Popup_bg_20.png"
        }
        CloseButton {
            anchors.right: backgroundItem.right
            anchors.rightMargin: 70 *dpx
            anchors.top: backgroundItem.top
            anchors.topMargin: 65 *dpy
            onClicked: footerBar.btnScenario.checked = false
        }
        PopupTitle {
            name: ("方案管理")
            icon: "\ue678"
            x: 74 *dpx
            y: 60*dpy
        }

        Row
        {
            x: 80 *dpx
            y: 115 *dpy
            spacing: 15*dpx
            ViewButton {
                name: qsTr("新建")
                color: viewColor_xinjian
                viewImage: "\ue624"
                MouseArea{
                    anchors.fill: parent
                    onClicked: {
                        scenarioNew.visible= true
                        scenarioNew.scenarioNewInfo = sceManager.createSceneri();
                    }
                }
            }
            ViewButton {
                name: qsTr("导入")
                color: viewColor_daoru
                viewImage: "\ue645"

                MouseArea {
                    anchors.fill: parent
                    onClicked: {
//                         sceManager.showPersonInfo(11) //测试人员信息
                    }
                }
            }
            ViewButton {
                name: qsTr("全部刷新")
                color: viewColor_shuaxin
                viewImage: "\ue600"
                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        $app.allData.clearAllInfo();
                        sceManager.read();
                    }
                }
            }
            ViewButton {
                name: qsTr("保存方案")
                color: viewColor_shuaxin
                viewImage: "\ue600"
                MouseArea {
                    anchors.fill: parent
                    onClicked: {

                    }
                }
            }
        }

        SearchItem {

        }

        Rectangle {
            x: 80*dpx
            y: 170*dpy
            width: 1066*dpx
            height: 550 *dpy
            color: "transparent"

            Component {
                id: headerView
                Item {
                    width: parent.width
                    height: 30 *dpy
                    Rectangle {
                        anchors.fill: parent
                        color: "#2D5689"
                    }
                    TextItem {
                        text: "序号"
                        width: 100 *dpx
                        height: 30 *dpy
                    }
                    TextItem {
                        x: 170 *dpx
                        text: "方案名称"
                        width: 200 *dpx
                        height: 30 *dpy
                    }
                    TextItem {
                        x: 572 *dpx
                        text: "操作"
                        width: 370 *dpx
                        height: 30 *dpy
                    }
                }
            }

            Component {
                id: delegate
                Item {
                    id: wrapper
                    width: parent.width
                    height: 50 *dpy
                    Rectangle {
                        anchors.fill: parent
                        color: index%2 ? "#2D5689" : "#4671a6"
                    }

                    TextItem {
                        id: col1
                        text: index+1
                        width: 100 *dpx
                        height: 50 *dpy
                    }
                    TextItem {
                        id: col2
                        x: 170 *dpx
                        text: sceName
                        width: 200 *dpx
                        height: 50 *dpy
                    }
                    Row {
                        x: 620 *dpx
                        y: 10 *dpy
                        width: 370 *dpx
                        height: 30 *dpy
                        spacing: 15 * dpx
                        ViewButton {
                            name: qsTr("修改方案")
                            color: viewColor_shuaxin
                            viewImage: "\ue6a5"
                            MouseArea {
                                anchors.fill: parent
                                onClicked: {
                                    sceFindSignal(modelData)
//                                    sceManager.findScenario(modelData)
                                    scenarioNew.visible = true
                                    wrapper.ListView.view.currentIndex = index
                                    mouse.accepted = true
                                    scenarioNew.scenarioNewInfo = wrapper.ListView.view.model.get(index)
//                                    sceManager.showScenfo();
                                }
                            }
                        }
                        ViewButton {
                            name: qsTr("加载")
                            color: viewColor_xinjian
                            viewImage: "\ue607"
                        }
                        ViewButton {
                            name: qsTr("删除")
                            color: viewColor_shanchu
                            viewImage: "\ue61c"
                            MouseArea {
                                anchors.fill: parent
                                onClicked: {
                                    sceManager.deleteScenario(col2.text)
//                                    listView.removeOne()
                                    sceManager.removeScenario(modelData)
                                    wrapper.ListView.view.model.remove(index)
                                }
                            }
                        }
                    }



                }
            }

            Component {
                id: phoneModel;
                ListModel {
//                    ListElement{
//                        cost: "轻武器激光对抗系统1"
//                    }

                }

            }

            ListView {
                id: listView
                anchors.fill: parent
                delegate: delegate
                model: phoneModel.createObject(listView)
//                model: sceManager.showSceList()
                header: headerView
                focus: true
                clip: true
                ScrollBar.vertical: ScrollBar {
                    id: scrollBar
                }
                function addOne(sceName) {
                    model.append({
                                    "cost":sceName
                                })
                }

                Component.onCompleted: {
                    scenarioLoader.addScenario.connect(listView.addOne)
                }

            }

        }
    }

}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/
