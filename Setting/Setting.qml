import QtQuick 2.7
import QtQuick.Layouts 1.14
import QtQuick.Controls 2.14 as QC14
import "../Status" as Status

QC14.Popup
{

    id: popup
    width: 500
    height: 700
    anchors.centerIn: parent
    modal: true

    background:Rectangle
    {
        anchors.fill: parent
        color:'#88ffffff'
    }


    Component
    {
        id: contactDelegate
        Item
        {
            id:showListItem
            width:100 ; height: 30
            RowLayout
            {
                Text { Layout.preferredWidth: 50;text:modelData.type }
                QC14.SpinBox
                {
                    id:control
                    value:modelData.number;
                    from: 1
                    to: modelData.type === "默认子弹数:" ? 9999 : 100
                    editable: true
                    valueFromText: function(text, locale)
                    {
                        var nValue=Number.fromLocaleString(locale, text);

                        if(nValue<=control.to && nValue>=control.from)
                        {
                            return(nValue);
                        }
                        else if(nValue>control.to)
                        {
                            return(control.to)
                        }
                        else
                        {
                            return(control.from)
                        }
                    }
                    up.indicator:Rectangle
                    {
                        color:"#00000000"
                    }
                    down.indicator: Rectangle
                    {
                        color:"#00000000"
                    }

                    /// 当值修改的时候提交更改
                    onValueModified:
                    {
                        $app.settings.changeSetting(showListItem.parent.parent.name,index,value);
                    }
                }
            }
        }
    }



    QC14.ScrollView
    {
        id: myscrollView
        anchors.fill: parent
        clip: true


        QC14.GroupBox
        {
            id: scoreGroupBox
            height: 240
            anchors.right: parent.right
            anchors.left: parent.left
            clip: true
            anchors.top: parent.top
            title: qsTr("命中计分:")

            ListView
            {
                property var name: "score"
                clip: true
                id: scoreList
                anchors.leftMargin: 60
                anchors.topMargin: 0
                anchors.fill: parent
                delegate: contactDelegate
                model:$app.settings.scoreSetting
            }

        }

        QC14.GroupBox
        {
            id: harmGroupBox
            height: 240
            anchors.left: parent.left
            anchors.right: parent.right
            enabled: true
            clip: true
            anchors.top: scoreGroupBox.bottom
            title: qsTr("损伤设置:")

            ListView
            {
                property var name: "harm"
                id: harmList
                anchors.leftMargin: 60
                anchors.topMargin: 0
                anchors.fill: parent
                delegate: contactDelegate
                model:$app.settings.harmSetting
                clip: true
            }

        }

        QC14.GroupBox
        {
            id: systemGroupBox
            height: 180
            anchors.left: parent.left
            anchors.right: parent.right
            clip: true
            anchors.top: harmGroupBox.bottom
            title: qsTr("系统设置:")

            ListView
            {
                property var name: "sys"
                id: systemList
                anchors.leftMargin: 60
                anchors.topMargin: 0
                anchors.fill: parent
                delegate: contactDelegate
                model:$app.settings.systemSetting
                clip: true
            }
        }
    }
}
