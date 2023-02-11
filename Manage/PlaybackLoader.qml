//                                       回放管理
import QtQuick 2.12
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import Qt.labs.platform 1.1
import Qt.labs.qmlmodels 1.0
import "../Common"
import "../Exercise"
import "Plugins"
import "../Status" as MyStatus
import "../RePlay" as MyRePlay

ManageRect{
    id: playbackLoader
    rectWidth: 1226 *dpx
    rectHeight: 787 *dpy
    rectImage: "qrc:/Image/Popup_bg_27.png"

    signal openReplay()

    CloseButton {
        anchors.right: playbackLoader.right
        anchors.rightMargin: 70 *dpx
        anchors.top: playbackLoader.top
        anchors.topMargin: 65 *dpy
        onClicked: footerBar.btnPlayback.checked = false
    }
    PopupTitle {
        name: ("回放管理")
        icon: "\ue678"
        x: 74*dpx
        y: 60*dpy
    }

    ViewButton {
        x: 80 *dpx
        y: 115 *dpy
        name: qsTr("全部刷新")
        color: viewColor_shuaxin
        viewImage: "\ue600"
        MouseArea{
            anchors.fill: parent
            //                    onClicked: playbackRefresh.visible= true
            onClicked: {
                listView.model = $app.openPath();
            }
        }
    }
    ScePlayList{
        id: listView
        model: $app.openPath()
        delegate: DelegateRectangle {
            id: wrapper

            TextListItem {
                id: col1
                text: index + 1
                width: 100 *dpx
                height: 50 *dpy
            }
            TextListItem {
                id: col2
                x: 170 *dpx
                text: modelData
                width: 200 *dpx
                height: 50 *dpy
            }
            TextListItem {
                id: col3
                x: 400 *dpx
                //                        text: manoeuvre.endTime
                width: 200 *dpx
                height: 50 *dpy
            }
            Row {
                x: 670 *dpx
                y: 10 *dpy
                width: 370 *dpx
                height: 30 *dpy
                spacing: 15 * dpx

                ViewButton {
                    name: qsTr("加载")
                    color: viewColor_xinjian
                    viewImage: "\ue607"
                    MouseArea{
                        anchors.fill: parent
                        onClicked: {
                            $app.allData.initReplay()
                            ctrReplay.visible = true;
                            ctrReplay.bStart=true;
                            ctrReplay.nTimeText=ctrReplay.nTimes = $app.allData.openReplayFile("file:///"+appDir+"/Data/Szy/"+modelData+".szy");
                            $app.settings.startReplay()
                            footerBar.btnPlayback.checked = false
                            manoeuvre.imgSource = "qrc:/Image/Set_up_bg.png"
                            manoeuvre.height = 100*dpx
                            killExpand.visible = true
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
                            $app.allData.deleteReplayFile(modelData);
                            listView.model = $app.openPath();
                        }
                    }
                }
            }
//            RemoveDialog {
//                id: removeDialog_shanchuhuifang
//                visible: false
////                anchors.centerIn: parent
//                 x: (playbackLoader.width - removeDialog_shanchuhuifang.width)/2
//                 y: (playbackLoader.height - removeDialog_shanchuhuifang.height)/2
//                content1: "此操作永久删除该回放记录，"
//                content2: "确认要删除吗？"
//                onYesPutDown: {
//                    $app.allData.deleteReplayFile(modelData);
//                    listView.model = $app.openPath();
//                }
//            }
        }
    }
    FileDialog
    {
        id:replayFile
        folder:$app.appPath
        fileMode:FileDialog.OpenFile
        title: qsTr("打开演习数据")
        nameFilters: [qsTr("演习数据(*.szy)")]
        onAccepted:
        {
            ctrReplay.nTimes = $app.allData.openReplayFile(currentFile);
            ctrReplay.visible = true;
            $app.settings.startReplay()
        }
    }

}

