//                                        击杀情况
import QtQuick 2.12
//import QtQuick.Controls 2.15
import Qt.labs.qmlmodels 1.0
import Qt.labs.platform 1.1
import QtQuick.Controls 1.4 as QC114
import QtQuick.Controls.Styles 1.4
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.14
import "../Common"
import "../Result"


Item {
    id: exerciseResults
    width: 1184 *dpx
    height: 760 *dpy

    Image {
        id: loginImage
        anchors.fill: parent
        source: "qrc:/Image/Popup_bg_20.png"
    }

    PopupTitle {
        name: "演习结果"
        icon:"\ue654"
    }
    TransverseLine {
        x: 80 *dpx
        y: 95*dpy
    }
    CloseButton {
        anchors.right: exerciseResults.right
        anchors.rightMargin: 70 *dpx
        anchors.top: exerciseResults.top
        anchors.topMargin: 60 *dpy
        onClicked: exerciseResults.visible = false
    }

    QC114.TableView
    {
        id:resultTable
        y: 136*dpy
        x: 80 *dpx
        width: 1024 *dpx
        height: 142*dpy

        style:TableViewStyle
        {
            id:tstyle;
            backgroundColor:"#4671a6"; //"#4671a6" : "#2D5689"

            //设置表头的样式
            headerDelegate :Rectangle{
                implicitWidth: 100
                implicitHeight: 40
                color: "#4671a6"
                Text{
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.verticalCenter: parent.verticalCenter
                    text: styleData.value
                    color: "white"
                    font.pixelSize: 20
                    font.bold: true
                }
            }

            // 设置行
            rowDelegate:Rectangle
            {
                height:51;
                color:styleData.alternate ? "#4671a6":"#2D5689"
            }

            // 设置单元格
            itemDelegate: Text
            {
                text:styleData.value;
                font.pointSize:18;
                color:"#ffffff"
                verticalAlignment:Text.AlignVCenter;
                horizontalAlignment:Text.AlignHCenter;
            }
        }
        QC114.TableViewColumn
        {
            role: "belong"
            title: qsTr("属方")
            width: resultTable.viewport.width/resultTable.columnCount
        }
        QC114.TableViewColumn
        {
            role: "all"
            title: qsTr("总人数")
            width: resultTable.viewport.width/resultTable.columnCount
        }
        QC114.TableViewColumn
        {
            role: "hurt"
            title: qsTr("受伤人数")
            width: resultTable.viewport.width/resultTable.columnCount
        }
        QC114.TableViewColumn
        {
            role: "dealth"
            title: qsTr("死亡人数")
            width: resultTable.viewport.width/resultTable.columnCount
        }
        QC114.TableViewColumn
        {
            role: "score"
            title: qsTr("得分情况")
            width: resultTable.viewport.width/resultTable.columnCount
        }
        model: $app.allData.listResult;        
    }

    Row {
        spacing: 24 *dpx
        y: 298 *dpy
        x: 80 *dpx
        Repeater {
            model: $app.allData.allResult
            Rectangle {
                width :500*dpx
                height: 320*dpy
                color: Qt.rgba(74/255,120/255,177/255,0.3)

                Text
                {
                    x: 40 *dpx
                    y: 20 *dpy
                    text:qsTr(modelData.belong+"伤亡情况")
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                    font.pixelSize: 20*dpx
                    color: "#ffffff"
                    font.family: "MicrosoftYaHei"
                }

                RedChart {
                     width :500
                     height: 320
//                     title: modelData.belong
                     hurtData:modelData.hurt
                     deathData:modelData.dealth
                     okData:modelData.ok
                }

            }
        }
    }

    Row {
        spacing: 15 *dpx
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 60 *dpy
        x: 375.5*dpx
        PopupButton {
            id: save
             width: 150*dpx
            background: Rectangle {
                color: "#265aef"
                Text {
                    id: popupText
                    height: 36 *dpy
                    width: 150*dpx
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                    text: "保存演习数据"
                    font.pixelSize: 16*dpx
                    color: "#ffffff"
                    font.family: "Microsoft YaHei"
                }
            }

//            nameButton: "保存演习数据"
            onClicked: {
                openFile.open()
            }

        }
        FileDialog
        {
            id:openFile
            folder:$app.appPath
            fileMode:FileDialog.SaveFile
            title: qsTr("保存演习数据")
            nameFilters: [qsTr("演习数据(*.szy)")]
            onAccepted:
            {
                $app.allData.saveData(currentFile);
            }
        }
        PopupButton {
//            id: print
            width: 150*dpx
           background: Rectangle {
               color: "#265aef"
               Text {
                   height: 36 *dpy
                   width: 150*dpx
                   verticalAlignment: Text.AlignVCenter
                   horizontalAlignment: Text.AlignHCenter
                   text: "打印演习报告"
                   font.pixelSize: 16*dpx
                   color: "#ffffff"
                   font.family: "Microsoft YaHei"
               }
           }

//            nameButton: "打印演习报告"
           onClicked:
           {
               printWPS.open();
           }

        }
        FileDialog
        {
            id:printWPS
            folder:$app.appPath
            fileMode:FileDialog.SaveFile
            title: qsTr("保存演习报告")
            nameFilters: [qsTr("演习报告(*.docx)")]
            onAccepted:
            {
                $app.allData.createReport(currentFile);
            }
        }
        PopupButton {
            background: Rectangle {
                color: "#1d4f88"
            }
            nameButton: "取消"
            onClicked: exerciseResults.visible = false
        }
    }
}
