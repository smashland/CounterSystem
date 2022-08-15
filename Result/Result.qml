import QtQuick 2.14
import QtQuick.Window 2.14
import Qt.labs.platform 1.1
import QtQuick.Controls 2.14 as QC14
import QtQuick.Controls 1.4 as QC114
import QtQuick.Layouts 1.14

QC14.Dialog
{
    id:resultDialog
    anchors.centerIn: parent
    width: 800
    height: 570
    title: qsTr("演习结果")
    modal: true

    ColumnLayout
    {
        QC114.TableView
        {
            id:resultTable
            Layout.preferredWidth: resultDialog.width-20
            Layout.preferredHeight: 100

            alternatingRowColors : false
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



        RowLayout
        {
            QC14.Button
            {
                text: qsTr("打印演习报告")
                onClicked:
                {
                    printWPS.open();
                }
            }
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

    onVisibleChanged:
    {
        if(!visible)
        {
            $app.allData.clearInfo();
            $app.allData.removeSavedFile();
        }
    }
}
