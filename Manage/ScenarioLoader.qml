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
import "Plugins"

ManageRect{
    id: scenarioLoader
    rectWidth: 1226 *dpx
    rectHeight: 787 *dpy
    rectImage: "qrc:/Image/Popup_bg_27.png"

    property var scenarioInfo: null
    signal addScenario(string sceName)
    signal sceFindSignal(string sceName)
    property string impScePath: null

    CloseButton {
        anchors.right: scenarioLoader.right
        anchors.rightMargin: 70 *dpx
        anchors.top: scenarioLoader.top
        anchors.topMargin: 65 *dpy
        onClicked: footerBar.btnScenario.checked = false
    }
    PopupTitle {
        name: ("方案管理")
        icon: "\ue678"
        x: 74 *dpx
        y: 60*dpy
    }

    property var taskMap: {0:0}
//    property var qmlObj: null
    function openQml(obj,qmlUrl){
        var myComponent = Qt.createComponent(qmlUrl)
        if (Component.Ready === myComponent.status){
            var qmlObj = myComponent.createObject(scenarioLoader,{"anchors.centerIn":scenarioLoader,scenarioNewInfo:obj});
            if(qmlObj === null){
                taskMap[obj] = qmlObj;
                return(qmlObj);
            }

        }else{
            console.log(myComponent.errorString());
            myComponent.destroy();
            return(null);
        }

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
                id: newSce
                anchors.fill: parent
                onClicked: {
                    scenarioNew.visible= true
                    modifySceInfo = sceManager.createSceneri();
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
                     printSce.open()
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
                    listView.model= sceManager.listSces
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
                    saveSce.open()
                }
            }
        }
    }

    SearchItem {

    }

    ScePlayList{
        id: listView
        model:sceManager.listSces
        delegate: Rectangle {
            id: wrapper
            width: listView.width
            height: 50 *dpy
            Rectangle {
                anchors.fill: parent
                color: index%2 ? "#2D5689" : "#4671a6"
            }

            TextListItem {
                id: col1
                text: index+1
                width: 100 *dpx
                height: 50 *dpy
            }
            TextListItem {
                id: col2
                x: 170 *dpx
                text: modelData.sceName
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
                            sceFindSignal(modelData.sceName)
                            scenarioNew.visible = true
                        }
                    }
                }
                ViewButton {
                    name: qsTr("加载")
                    color: viewColor_xinjian
                    viewImage: "\ue607"
                    MouseArea{
                        anchors.fill: parent
                        onClicked: {

                        }
                    }
                }
                ViewButton {
                    name: qsTr("删除")
                    color: viewColor_shanchu
                    viewImage: "\ue61c"
                    MouseArea {
                        anchors.fill: parent
                        onClicked: {
                            sceManager.deleteScenario(modelData.sceName)
                        }
                    }
                }
            }
        }

    }

    FileDialog {
        id: printSce
        title: qsTr("请选择方案")
        nameFilters: [qsTr("(*.sce))")]
        onAccepted: {
            source: printSce.fileUrl
            impScePath=currentFile.toString().replace("file:///", "")
            sceManager.importSce(impScePath)
        }
    }
    FileDialog {
        id: saveSce
        title: qsTr("保存方案")
        fileMode: FileDialog.SaveFile
        folder: shortcuts.desktop
        nameFilters: [qsTr("(*.sce))")]
        onAccepted: {
            var scePath=String(saveSce.currentFile)
            scePath=scePath.substr(8)
            $app.allData.saveSceInfo(scePath)
        }
    }
}

