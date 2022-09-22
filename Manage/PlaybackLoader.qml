//                                       回放管理
//import QtQuick 1.1
import QtQuick 2.12
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import Qt.labs.platform 1.1
import Qt.labs.qmlmodels 1.0
import "../Common"
import "../Exercise"
import "../Status" as MyStatus
import "../RePlay" as MyRePlay

Rectangle {
    id: playbackLoader
    anchors.fill: parent
    color: "transparent"
    signal openReplay()

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
            anchors.topMargin: 70 *dpy
            onClicked: footerBar.btnPlayback.checked = false
        }
        PopupTitle {
            name: ("回放管理")
            icon: "\ue678"
            x: 74*dpx
            y: 60*dpy
        }

        Row
        {
            x: 80 *dpx
            y: 115 *dpy
            spacing: 15*dpx

            ViewButton {
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
        }

        SearchItem {

        }


        Rectangle {
            x: 80*dpx
            y: 170*dpy
            width: 1066 *dpx
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

                    Text {
                        text: "序号"
                        width: 100 *dpx
                        height: 30 *dpy
                        color: "#ffffff"
                        font.pixelSize: 16
                        font.family: "Microsoft YaHei";
                        font.bold: true
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                    }
                    Text {
                        x: 170 *dpx
                        text: "方案名称"
                        width: 200 *dpx
                        height: 30 *dpy
                        color: "#ffffff"
                        font.pixelSize: 16
                        font.family: "Microsoft YaHei";
                        font.bold: true
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                    }
                    Text {
                        x: 572 *dpx
                        text: "操作"
                        width: 370 *dpx
                        height: 30 *dpy
                        color: "#ffffff"
                        font.pixelSize: 16
                        font.family: "Microsoft YaHei";
                        font.bold: true
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                    }
                    //                }
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

                    Text {
                        id: col1
                        text: index + 1
                        width: 100 *dpx
                        height: 50 *dpy
                        color: "#ffffff"
                        font.pixelSize: 16*dpx
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                    }
                    Text {
                        id: col2
                        x: 170 *dpx
                        text: modelData
                        width: 200 *dpx
                        height: 50 *dpy
                        color: "#ffffff"
                        font.pixelSize: 16
                        font.family: "Microsoft YaHei"
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
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
//                                     replayFile.open();
                                    ctrReplay.nTimes = $app.allData.openReplayFile("file:///"+modelData);
                                    ctrReplay.visible = true;
                                    $app.settings.startReplay()
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
                                    removeDialog_shanchuhuifang.visible = true
                                }
                            }
                        }
                    }
                    RemoveDialog {
                        id: removeDialog_shanchuhuifang
                        visible: false
                        anchors.centerIn: parent
                        content1: "此操作永久删除该回放记录，"
                        content2: "确认要删除吗？"
                        onYesPutDown: {
                            wrapper.ListView.view.model.remove(index)
                        }
                    }
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
                    console.log(currentFile)
                    ctrReplay.nTimes = $app.allData.openReplayFile(currentFile);
                    ctrReplay.visible = true;
                    $app.settings.startReplay()
                }
            }




            Component {
                id: szyModel;
                ListModel {
                    ListElement{
                        name: "1"
                        cost: "轻武器激光对抗系统1"
                    }
                }

            }

            ListView {
                id: listView
                anchors.fill: parent
                delegate: delegate
                model: szyModel.createObject(listView)
                header: headerView
                focus: true
                clip: true
                ScrollBar.vertical: ScrollBar {
                    id: scrollBar
                }
            }



        }
    }

}

