//                                                            蓝色人员
import QtQuick 2.12
import QtQuick.Controls 2.15
import "../Common"
import "../Setting" as Settings

Item {
    width: 370 *dpx
    height: 420 *dpy
    property var outData: null
    Image {
        anchors.fill: parent
        source: "qrc:/Image/Blue_bg_all.png"
    }

    Text {
        id: lanfang
        x: (parent.width - lanfang.contentWidth) / 2
        y: 20 *dpy
        text: qsTr("蓝方")
        font.pixelSize: 22*dpx;
        color: "#ffffff";
        font.family: "MicrosoftYaHei-Bold";
    }
    Text {
        id: zongrenshu
        text: qsTr("总人数：")
        x: 20
        y: 25 *dpy
        font.pixelSize: 14*dpx;
        color: "#ffffff";
        font.family: "MicrosoftYaHei-Bold";
    }

    Text {
        id: zaixianrenshu
        text: qsTr("战损人数：")
        anchors.right: parent.right
        anchors.rightMargin: 20
        y: 25 *dpy
        font.pixelSize: 14*dpx;
        color: "#ec4747";
        font.family: "MicrosoftYaHei-Bold";
    }

    Rectangle {
        id:root
        x: 20
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 20
        width: 330
        height: 314 *dpy
        color: "transparent"

        Component {
            id: delegate
            Item {
                id: wrapper
                width: parent.width
                height: 44 *dpy
                Rectangle {
                    anchors.fill: parent
                    opacity: 0.5
                    color: Qt.rgba(18/255, 18/255, 18/255, 0.5);
                }
                MouseArea {
                    anchors.fill: parent
                    hoverEnabled: true
                    onClicked: {
                        mouse.accepted = true
                        wrapper.ListView.view.currentIndex = index
                    }
                }
                Text {
                    text: outData.name
                    x: 20 *dpx
                    height: 36 *dpy
                    color: "#ffffff"
                    font.pixelSize: 16*dpx
                    verticalAlignment: Text.AlignVCenter
                }
                Row {id:infoshow
                    spacing: 12*dpx
                    anchors.right: parent.right
                    anchors.rightMargin: 10
                    y: 10
                    Rectangle {
                        width:24*dpy
                        height: 24*dpy
                        color: "transparent"

                        EquipConnStat {
                            id:jiqiang
                            anchors.fill: parent
                            text: qsTr("\ue708")
                            color: "#e7f6ff"
                            font.family: "iconfont"
                            font.pixelSize: 22*dpx
                            verticalAlignment: Text.AlignVCenter
                            bConnected: outData.bRifle
                        }
                    }
                    Rectangle {
                        width:24*dpy
                        height: 24*dpy
                        color: "transparent"

                        EquipConnStat {
                            id:toukui
                            anchors.fill: parent
                            bConnected: outData.bTK
                            text: qsTr("\ue706")
                            color: "#e7f6ff"
                            font.family: "iconfont"
                            font.pixelSize: 22*dpx
                            verticalAlignment: Text.AlignVCenter
                        }
                    }
                    Rectangle {
                        width:30*dpx
                        height: 16*dpy
                        color: "transparent"
                        y: 4 *dpy
                        //                        Text {
                        //                            text: qsTr(progressBar.value*100 + "%")
                        //                            verticalAlignment: Text.AlignVCenter
                        //                            horizontalAlignment: Text.AlignHCenter
                        //                            anchors.fill: parent
                        //                            font.pixelSize: 14*dpx
                        //                            color: "#3f9c41"
                        //                            font.family: "Microsoft YaHei"
                        //                        }
                        Text
                        {
                            //anchors.top: locate.top
                            id:electricity
                            text: outData.nBaty+'%'
                            verticalAlignment: locate.verticalAlignment
                            styleColor: color
                            //                            style: Text.Outline
                            color:  outData.bOnLine ? outData.nBaty > 59 ? "green" : outData.nBaty > 20 ? "yellow" : "red" : "gray"
                            anchors.fill: parent
                            font.pixelSize: 14*dpx
                            font.family: "Microsoft YaHei"
                        }
                    }
                    Rectangle {
                        id: setListview
                        width:16*dpy
                        height: 16*dpy
                        color: "transparent"
                        y: 4 *dpy

                        Text {
                            anchors.fill: parent
                            text: qsTr("\ue8b8")
                            color: "#e7f6ff"
                            font.family: "iconfont"
                            font.pixelSize: 22*dpx
                            verticalAlignment: Text.AlignVCenter
                        }
                        MouseArea {
                            anchors.fill: parent
                            onClicked: contextMenu.visible = true
                        }
                    }
                }
                Rectangle {
                    y: 36*dpy
                    ProgressBar{
                        id:health
                        value: outData.nHealth
                        from: 0
                        to:100
                        width: 330
                        height: 10
                        background: Rectangle {
                            implicitWidth: health.width
                            implicitHeight: health.height
                            color: "#121212"
                            opacity: 0.7
                        }

                        contentItem: Item {
                            Rectangle {
                                width: health.visualPosition * health.width
                                height: health.height
                                color: outData.bOnLine ?  health.value > 60 ?  "green" : health.value > 20 ? "yellow" : "red" : "gray";
                            }
                        }
                    }

                }
            }
        }

        Component {
            id: listModel;
            ListModel {
                ListElement{
                    name: "1sdS速度"
                }
                ListElement{
                    name: "1sdS速度"
                }
            }

        }

        ListView {
            id: listView
            anchors.fill: parent
            delegate: delegate
            spacing: 1*dpy
            model: listModel.createObject(listView)
            focus: true
            ScrollBar.vertical: ScrollBar {
                id: scrollBar
            }

        }

    }
    SetList {
        id: contextMenu
        visible: false
    }
    /// 充弹窗口
    Settings.ChongDan
    {
        anchors.centerIn: parent
        id:chongdan
        width: 500
        height: 500
    }

    Dialog
    {
        id:peiqiang
        anchors.centerIn: parent
        property var nID: 0
        title: "给"+nID+'号配枪'
        modal: true
        standardButtons: Dialog.Ok | Dialog.Cancel

        TextField
        {
            id:qianghao
            maximumLength:4
            placeholderText:'枪号'
            validator: IntValidator
            {
                bottom:1
                top:9999
            }
        }
        onAccepted:
        {
            $app.settings.peiQiang(nID,qianghao.text);
        }
    }

    Dialog
    {
        id:sycntime
        property var nID: 0
        title: "给"+nID+"同步时间";
        modal: true
        standardButtons: Dialog.Ok | Dialog.Cancel

        TextField
        {
            id:setTime
            maximumLength:4
            placeholderText:'时间(s):'
            validator: IntValidator
            {
                bottom:1
                top:60
            }
        }
        onAccepted:
        {
            $app.settings.sycTime(nID,setTime.text);
        }
    }


}
