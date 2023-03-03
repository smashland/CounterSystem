import QtQuick 2.0
import QtQuick.Window 2.2

DropArea
{
    id:root
    property alias type: group.groupType
    property alias source: zhenyingtu.source

    width: 340 *dpx
    height: Screen.desktopAvailableHeight*0.4

    onWidthChanged:
    {
        width=340 *dpx
    }
    MouseArea {
        anchors.fill: parent
        onWheel: {
            // 屏蔽滚轮事件，防止滚动方案列表时缩放地球
        }
    }
    Image {
        id:zhenyingtu
        anchors.fill: parent
//        source: "qrc:/Image/Grey_bg_all.png"
    }
    GroupInfo
    {
        id:group
        color:$app.settings.type2Color(groupType)

        /// 当颜色修改时设置半透明
        onColorChanged:
        {
            color.a = 0
        }

        /// 单击人员信息
        onPersonClickd:
        {
            contextMenu.x = root.x + mX
            contextMenu.y = root.y + mY
            contextMenu.userID = nId;
            contextMenu.open();
        }

        onTitleClickd:
        {
            contextMenu2.x = root.x + group.width/2
            contextMenu2.y = root.y + 43*dpy
            contextMenu2.open();
        }

        /// 双击显示人员信息
        onPersonDClick:
        {
            allInfo.outData = $app.allData.getPersonAllInfo(nId);
            var rows=4;
            if(allInfo.outData.bPistol)
            {
                ++rows;
            }

            if(allInfo.outData.bRifle)
            {
                ++rows;
            }

            allInfo.rowNum = rows;
            allInfo.open();
        }
    }

    onDropped:
    {
        group.addPerson(drag.source.outData);
        $app.allData.changeGroup(drag.source.outData.id,drag.source.outData.type);
    }
}
