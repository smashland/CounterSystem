import QtQuick 2.15
import QtQuick.Controls 2.15

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

