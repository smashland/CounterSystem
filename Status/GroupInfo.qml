import QtQuick 2.0
import QtQuick.Controls 2.3

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
        text: qsTr("红方")
        font.pixelSize: 22*dpx;
        color: "#ffffff";
        font.family: "MicrosoftYaHei-Bold";
    }

    Text {
        id: zongrenshu
        text: qsTr("总人数：")+$app.allData.allDataNumber
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

    ScrollView
    {
        anchors.fill: parent;
        clip: true;
        ListView
        {
            id:listView
            width: parent.width
            height: parent.height - 80
            anchors.top: parent.top
            anchors.topMargin: 50
            model:$app.allData.ceateType(groupType)

            delegate:MouseArea
            {
                acceptedButtons: Qt.LeftButton | Qt.RightButton
                id:mouseArea
                width: parent.width
                height: 50

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
                        personClickd(modelData.id,mouseX,index * height + mouseY);
                        console.log("youjian-----------")
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
    }
}
