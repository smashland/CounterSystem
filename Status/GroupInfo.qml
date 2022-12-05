import QtQuick 2.0
import QtQuick.Controls 2.3
import "../Manage"

Rectangle
{
    id:rootRect
    signal personClickd(var nId,var mX,var mY)
    signal personDClick(var nId)
    property string groupType:""

    function addPerson(nPerson)
    {
        nPerson.type=rootRect.groupType
        listView.model.append(nPerson);
    }

    anchors.fill: parent

    Text {
        id: hongfang
        x: (parent.width - hongfang.contentWidth) / 2
        y: 20 *dpy
        text: groupType? qsTr(groupType):qsTr("人员信息");
        font.pixelSize: 22*dpx;
        color: "#ffffff";
        font.family: "MicrosoftYaHei-Bold";
    }
    Text {
        id: zongrenshu
        text: groupType?qsTr("总人数：")+listView.model.count:qsTr("在线人数：")+$app.allData.atLineNumber
        x: 20 *dpx
        y: 23 *dpy
        font.pixelSize: 14*dpx;
        color: groupType?"#ffffff":"green"
        font.family: "Microsoft YaHei";
    }

    Text {
        id: zaixianrenshu
        text: groupType?qsTr("战损人数:"+listView.model.deathNum):qsTr("总人数：")+$app.allData.allDataNumber
        anchors.right: parent.right
        anchors.rightMargin: 20
        y: 23 *dpy
        font.pixelSize: 14*dpx;
        color:groupType? "#FF8C00":"#ffffff";
        font.family: "Microsoft YaHei";
    }

    ListView
    {
        id:listView
        width: parent.width
        height: parent.height - 80*dpy
        anchors.top: parent.top
        anchors.topMargin: 50*dpy
        model:$app.allData.ceateType(groupType)
        clip: true
        ScrollBar.vertical: ScrollBar {
            id: scrollBar
        }
        delegate:MouseArea
        {
            acceptedButtons: Qt.LeftButton | Qt.RightButton
            id:mouseArea
            width: parent.width
            height: 50*dpy
            hoverEnabled: true
            drag.target: $app.settings.bIsStart ? null : forShow

            /// 鼠标释放
            onReleased:
            {
                if(forShow.Drag.target !== null)
                {
                    listView.model.remove(index);
                    forShow.Drag.drop();
                }
                else
                {
                    forShow.Drag.cancel();
                }
            }

            /// 鼠标按下
            onPressed:
            {
                parent.currentIndex = index;
                /// 鼠标右键弹出菜单
                if(Qt.RightButton === mouse.button)
                {
                    personClickd(modelData.id,mouseX,index * height + mouseY+53);
                }
            }

            /// 双击
            onDoubleClicked:
            {
                personDClick(modelData.id);
            }


            /// 用户信息
            PersonStatus
            {
                id:forShow
                outData:modelData;
                anchors.verticalCenter: parent.verticalCenter
                anchors.horizontalCenter: parent.horizontalCenter
                Drag.active: mouseArea.drag.active
                Drag.hotSpot.x: width/2
                Drag.hotSpot.y: height/2
                states: State
                {
                    when: mouseArea.drag.active
                    ParentChange
                    {
                        target: forShow;
                        parent:rootRect.parent
                    }

                    AnchorChanges
                    {
                        target: forShow;
                        anchors.verticalCenter: undefined;
                        anchors.horizontalCenter: undefined;
                    }
                }
            }
        }
    }
    function personData(model) {
        var res = "{ \"PersonArray\": [\n";

        console.log("count: " + model.count);

        for(var i = 0; i < model.count; ++i) {
            res += "\n{\t";
            var e = model.get(i);
            res += "\"Grouptype\": \""   +　e.Grouptype + "\",\n\t";    //阵营
            res += "\"ID\": \"" + e.ID + "\",\n\t";                     //id
            res += "\"ImagePath\": \"" + e.ImagePath + "\",\n\t";       //图片
            res += "\"Name\": " + e.name + "\n\t";                      //名字
            res += "\"Position\": " + e.Position + "\n\t";              //职位
            res += "\"Host\": " + e.Host + "\n\t";                      //是否人质

            if ( i === model.count -1)
                res += "\n}";
            else
                res += "\n},";
        }
        res += "\"Scename\": " + model + "\n\t";

        res += "\n]}";

        console.log("res: " + res );
        return res;
    }

}
