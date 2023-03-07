import QtQuick 2.0
import QtQuick.Controls 2.3
import "../Common"

Dialog{
    id: dialog
    property int nID: 0
    property string userType
    modal: true
    background:Rectangle {
        color: "transparent"
        Image {
            anchors.fill: parent
            source: "qrc:/Image/wuqi/08-bg.png"
        }
    }
    PopupTitle {
        name: ("给"+userType+'充弹')
        icon: "\ue795"
        x: 54 *dpx
        y: 44*dpy
    }

    signal danYaosignal(int shou,int bu,int ji,int juji,int shoulei);

    Column {
        id:allInfo
        spacing: 16
        anchors.centerIn: parent
        SoldierItem2 {
            title: "步      枪："
            //            danwei: "支"
        }
        SoldierItem2 {
            title: "机      枪："
            //            danwei: "支"
        }
        SoldierItem2 {
            title: "手      枪："
            //            danwei: "支"
        }
        SoldierItem2 {
            title: "手      雷："
            //            danwei: "支"
        }
        SoldierItem2 {
            title: "无1："
            visible: false
        }
        SoldierItem2 {
            title: "无2："
            visible: false
        }
        SoldierItem2 {
            title: "无3："
            visible: false
        }
        SoldierItem2 {
            title: "狙击步枪："
            //            danwei: "个"
        }
    }
    Row {
        spacing: 15 *dpx
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 40 *dpy
        x: 204.5*dpx
        PopupButton {
            background: Rectangle {
                color: "#265aef"
            }
            nameButton: "确定"
            onClicked: {
                var allNum=[8];
                for(var i=0; i<allInfo.children.length; i++)
                {
                    if(allInfo.children[i].name==="")
                    {
                        allNum[i]=0
                    }
                    else
                    {
                        allNum[i]=allInfo.children[i].name
                    }
                    console.log("枪型："+allNum[i])
                }
//                $app.settings.chongDan(nID,allNum);
                $app.allData.setAllMune(contextMenu2.userType,0,allNum)
                dialog.close()
            }
        }
        PopupButton {
            background: Rectangle {
                color: "#1d4f88"
            }
            nameButton: "取消"
            onClicked: {
                dialog.close()
            }
        }
    }


}









/*##^## Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
 ##^##*/
