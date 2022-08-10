import QtQuick 2.7
import QtQuick.Controls 2.3
import QtQuick.Window 2.2

//
RoundButton
{
    property var maxX: Screen.width - roundButton.width
    property var maxY: Screen.height - roundButton.height
    signal rightClick()
    signal leftClick()
    signal startReplay()

    id: roundButton
    x: 30
    y: Screen.height - 150
    width:120
    height:120
    contentItem: Text
    {
        id:buttonLabel
        text:$app.allData.atLineNumber +'/' + $app.allData.allDataNumber
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
        style: Text.Outline
        styleColor: "#55FFFFFF"
        font.pointSize:20
        color:bottonBackground.border.color
    }

    background:Rectangle
    {
        id:bottonBackground
        radius:roundButton.radius
        border.width:4
        border.color:$app.settings.bIsStart ? "#FF0000" : "#00FF00"
        color:"#00000000"
    }

    MouseArea
    {
        id:mouseArea
        anchors.fill: parent
        property real lastX: 0
        property real lastY: 0
        property bool bClicked: false
        cursorShape:Qt.PointingHandCursor
        acceptedButtons: Qt.LeftButton | Qt.RightButton |Qt.MidButton

        onHoveredChanged:
        {
            mouseArea.cursorShape = Qt.PointingHandCursor;
        }

        onClicked:
        {
            //鼠标按下时，记录鼠标初始位置

            lastX = mouseX
            lastY = mouseY
            console.log("000000000000000")

            switch(mouse.button)
            {
            case Qt.RightButton: /// 切换演习状态
                rightClick()
                console.log("1111111111111111111111")
                break;
            case Qt.LeftButton:/// 弹出菜单
                if($app.settings.bIsStart)
                {
                    leftClick()
                    console.log("22222222222222222222")
                }
                else
                {
                    menu.popup(mouseArea.width/2,mouseArea.height/2);
                }

                //mouse.accepted=true;
                break;
            }
        }
		onDoubleClicked:{
		}

        /// 鼠标位置移动
        onPositionChanged:
        {
            if (Qt.MidButton === pressedButtons && pressed)
            {
                mouseArea.cursorShape=Qt.DragCopyCursor
                //鼠标按住的前提下，坐标改变时，计算偏移量，应用到目标item的坐标上即可
                roundButton.x += mouseX - lastX
                roundButton.y += mouseY - lastY

                if(roundButton.x < 0)
                {
                    roundButton.x = 0;
                }
                else if(roundButton.x > roundButton.maxX)
                {
                    roundButton.x = roundButton.maxX;
                }

                if(roundButton.y < 0)
                {
                    roundButton.y = 0;
                }
                else if(roundButton.y > roundButton.maxY)
                {
                    roundButton.y = roundButton.maxY;
                }
            }
        }
    }

    CircleMenu
    {
        boundingItem: null
        id:menu
        onOpenReplay:
        {
            startReplay();
        }
    }
}

