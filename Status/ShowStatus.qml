import QtQuick 2.0
import QtQuick.Controls 2.3
import "../Setting" as Settings

Item
{
    anchors.fill: parent

    GroupDropArea
    {
        id:unGroup
        type:""
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.leftMargin: 50
        anchors.topMargin: 20
        visible: !$app.settings.bIsStart&&!$app.settings.bIsReplay
    }

    GroupDropArea
    {
        id:blue
        type:"蓝方"

        anchors.right: parent.right;
        anchors.top: parent.top
        anchors.rightMargin: 50
        anchors.topMargin: 20
    }

    GroupDropArea
    {
        id:red
        type:"红方"

        anchors.right: ($app.settings.bIsStart || $app.settings.bIsReplay) ? undefined : parent.right
        anchors.top: ($app.settings.bIsStart || $app.settings.bIsReplay) ? parent.top : blue.bottom
        anchors.left: ($app.settings.bIsStart || $app.settings.bIsReplay) ? parent.left : undefined

        anchors.leftMargin: 50
        anchors.rightMargin: 50
        anchors.topMargin: 20
    }

    Menu
    {
        id: contextMenu
        property int userID
        MenuItem
        {
            text: "充弹"
            onTriggered:
            {
                chongdan.nID=contextMenu.userID;
                chongdan.open();
            }
        }
        MenuItem { text: "配枪" ;onTriggered: { peiqiang.nID = contextMenu.userID;peiqiang.open();}}
        MenuItem { text: "闭锁" ;onTriggered:$app.settings.setBiSuo(contextMenu.userID)}
        MenuItem { text: "解锁" ;onTriggered:$app.settings.setJiesuoSuo(contextMenu.userID)}
        MenuItem { text: "解除旁白";onTriggered:$app.settings.setJieChu(contextMenu.userID) }
        MenuItem { text: "判死";onTriggered:$app.settings.setPanSi(contextMenu.userID)}
        MenuItem { text: "复活" ;onTriggered:{$app.settings.setFuHuo(contextMenu.userID)}}
        MenuItem { text: "关机" }
        MenuItem { text: "同步时间";onTriggered:{sycntime.nID = contextMenu.userID;sycntime.open();}}
        MenuItem { text: "定位";onTriggered:{$app.allData.dingWei(contextMenu.userID)}}
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

    /// 用户的详细信息
    PersonAllInfo
    {
        id:allInfo
        visible: false
    }
}
