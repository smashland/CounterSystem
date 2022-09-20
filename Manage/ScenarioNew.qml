//                                                  新建方案
import QtQuick 2.12
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls.Styles 1.4
import "../Common"
import "../Exercise"
import MyItem 1.0

Item {
    id: scenarionew
    property var title: ""
    width: 1165 *dpx
    height: 710 *dpy
    Image {
        id: loginImage
        anchors.fill: parent
        source: "qrc:/Image/Popup_bg_21.png"
    }
    CloseButton {
        anchors.right: scenarionew.right
        anchors.rightMargin: 70 *dpx
        anchors.top: scenarionew.top
        anchors.topMargin: 70 *dpy
        onClicked: scenarionew.visible = false
    }

    PopupTitle {
        name: ("新建")
    }
    TransverseLine {
        x: 80 *dpx
        y: 95*dpy
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
    Rectangle {
        y: weizhixinxi.contentHeight + weizhixinxi.y + 10 *dpy
        x: 90 *dpx
        width: 985 *dpx
        height: 2 *dpy
        color: "#3b6daa"
    }

    Rectangle {
        x: 90 *dpx
        y: weizhixinxi.contentHeight + weizhixinxi.y + 10 *dpy + 10 *dpy
        width: 985
        height: 144 *dpy
        color: "transparent"

        Component {
            id: headerView
            Item {
                width: parent.width
                height: 40 *dpy
                Rectangle {
                    anchors.fill: parent
                    color: "#2D5689"
                }

                Row {
                    spacing: 56 *dpx
                    x: 25 *dpx
                    height: 40 *dpy
                    Text {
                        text: "设备编号"
                        width: 70 *dpx
                        height: 40 *dpy
                        color: "#ffffff"
                        font.pixelSize: 16
                        font.family: "Microsoft YaHei";
                        font.bold: true
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                    }
                    Text {
                        //                        x: 170 *dpx
                        text: "人员姓名"
                        width: 80 *dpx
                        height: 40 *dpy
                        color: "#ffffff"
                        font.pixelSize: 16
                        font.family: "Microsoft YaHei";
                        font.bold: true
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                    }
                    Text {
                        //                        x: 572 *dpx
                        text: "人员职务"
                        width: 110 *dpx
                        height: 40 *dpy
                        color: "#ffffff"
                        font.pixelSize: 16
                        font.family: "Microsoft YaHei";
                        font.bold: true
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                    }

                    Text {
                        //                        x: 572 *dpx
                        text: "红蓝方"
                        width: 80 *dpx
                        height: 40 *dpy
                        color: "#ffffff"
                        font.pixelSize: 16
                        font.family: "Microsoft YaHei";
                        font.bold: true
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                    }
                    Text {
                        //                        x: 572 *dpx
                        text: "是否是人质"
                        width: 138 *dpx
                        height: 40 *dpy
                        color: "#ffffff"
                        font.pixelSize: 16
                        font.family: "Microsoft YaHei";
                        font.bold: true
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                    }
                    Text {
                        //                        x: 572 *dpx
                        text: "操作"
                        width: 180 *dpx
                        height: 40 *dpy
                        color: "#ffffff"
                        font.pixelSize: 16
                        font.family: "Microsoft YaHei";
                        font.bold: true
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                    }
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

                Row {
                    spacing: 56 *dpx
                    x: 25*dpx
                    height: 40 *dpy
                    //                    arrayWidthSpacing: [20, 30]
                    Text {
                        text: nID
                        width: 70 *dpx
                        height: 50 *dpy
                        color: "#ffffff"
                        font.pixelSize: 16
                        font.family: "Microsoft YaHei";
                        font.bold: true
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                    }
                    Text {
                        //                        x: 170 *dpx
                        text: sName
                        width: 80 *dpx
                        height: 50 *dpy
                        color: "#ffffff"
                        font.pixelSize: 16
                        font.family: "Microsoft YaHei";
                        font.bold: true
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                    }
                    Text {
                        //                        x: 572 *dpx
                        text: nLevel
                        width: 110 *dpx
                        height: 50 *dpy
                        color: "#ffffff"
                        font.pixelSize: 16
                        font.family: "Microsoft YaHei";
                        font.bold: true
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                    }

                    Text {
                        //                        x: 572 *dpx
                        text: nGroup
                        width: 80 *dpx
                        height: 50 *dpy
                        color: "#ffffff"
                        font.pixelSize: 16
                        font.family: "Microsoft YaHei";
                        font.bold: true
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                    }
                    Text {
                        //                        x: 572 *dpx
                        text: bHost ? "是人质" : "不是人质"
                        width: 138 *dpx
                        height: 50 *dpy
                        color: "#ffffff"
                        font.pixelSize: 16
                        font.family: "Microsoft YaHei";
                        font.bold: true
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                    }
                    Row {
                        y: 10 *dpy
                        //                        width: 370 *dpx
                        //                        height: 30 *dpy
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
                            name: qsTr("加载")
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
            focus: true
        }
    }


    //    Item {
    //        x: 90 *dpx
    //        y: weizhixinxi.contentHeight + weizhixinxi.y + 10 *dpy + 10 *dpy + 146*dpy + 52 *dpy
    //        width: 985
    //        height: 40 *dpy
    //        Rectangle {
    //            anchors.fill: parent
    //            color: "#2D5689"
    //            Text {
    //                anchors.fill: parent
    //                text: qsTr("+ 添加人员")
    //                font.pixelSize: 17*dpx;
    //                verticalAlignment: Text.AlignVCenter
    //                horizontalAlignment: Text.AlignHCenter
    //                color: "#ffffff"
    //                font.family: "Microsoft YaHei"
    //                font.bold: true
    //            }
    //        }
    //    }


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
                }
            }
        }
        PopupButton {
            background: Rectangle {
                color: "#1d4f88"
            }
            nameButton: "取消"
            onClicked: scenarionew.visible = false
        }
    }
}
