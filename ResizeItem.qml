import QtQuick 2.0

Item {
    property int enableSize: 3
    property bool isPressed: false
    property point customPoint

    //左上角
    Item {
        id: leftTop
        width: enableSize
        height: enableSize
        anchors.left: parent.left
        anchors.top: parent.top
        z: 1
        MouseArea {
            anchors.fill: parent
            hoverEnabled: true
            propagateComposedEvents: true
            onPressed: press(mouse)
            cursorShape: containsMouse?Qt.SizeFDiagCursor:Qt.ArrowCursor;
            onReleased: release()
            onPositionChanged: positionChange(mouse, -1, -1)
        }
    }

    //Top
    Item {
        id: top
        height: enableSize
        anchors.left: leftTop.right
        anchors.right: rightTop.left
        anchors.top: parent.top
        z: 1000
        MouseArea {
            anchors.fill: parent
            hoverEnabled: true
            propagateComposedEvents: true
            onPressed: press(mouse)
            cursorShape: containsMouse?Qt.SizeVerCursor:Qt.ArrowCursor;
            onReleased: release()

            onMouseYChanged: positionChange(Qt.point(customPoint.x, mouseY), 1, -1)
        }
    }

    //右上角
    Item {
        id: rightTop
        width: enableSize
        height: enableSize
        anchors.right: parent.right
        anchors.top: parent.top
        z: 1000
        MouseArea {
            anchors.fill: parent
            hoverEnabled: true
            propagateComposedEvents: true
            onPressed: {
                press(mouse);
            }
            cursorShape: containsMouse?Qt.SizeBDiagCursor:Qt.ArrowCursor;
            onReleased: release()
            onPositionChanged: positionChange(mouse, 1, -1)
        }
    }

    //Left
    Item {
        id: left
        width: enableSize
        anchors.left: parent.left
        anchors.top: leftTop.bottom
        anchors.bottom: leftBottom.top
        z: 1000
        MouseArea {
            anchors.fill: parent
            hoverEnabled: true
            propagateComposedEvents: true
            onPressed: press(mouse)
            cursorShape: containsMouse?Qt.SizeHorCursor:Qt.ArrowCursor;
            onReleased: release()

            onMouseXChanged: positionChange(Qt.point(mouseX, customPoint.y), -1, 1)
        }
    }

    //Center - 5
    Item {
        id: center
        anchors.left: left.right
        anchors.right: right.left
        anchors.top: top.bottom
        anchors.bottom: bottom.top
        MouseArea {
            width: closebar.width
            height: closebar.height
            propagateComposedEvents: true
            property point clickPos
            onPressed: clickPos = Qt.point(mouse.x,mouse.y)
            onPositionChanged: {
                if(pressed && mainWindow.visibility !== mainWindow.Maximized && mainWindow.visibility !== mainWindow.FullScreen) {
                    var delta = Qt.point(mouse.x-clickPos.x, mouse.y-clickPos.y)
                    mainWindow.x += delta.x
                    mainWindow.y += delta.y
                }
            }
        }
    }

    //Right
    Item {
        id: right
        width: enableSize
        anchors.right: parent.right
        anchors.top: rightTop.bottom
        anchors.bottom: rightBottom.top
        z: 1000
        MouseArea {
            anchors.fill: parent
            hoverEnabled: true
            propagateComposedEvents: true
            onPressed: press(mouse)
            cursorShape: containsMouse?Qt.SizeHorCursor:Qt.ArrowCursor;
            onReleased: release()

            onMouseXChanged: positionChange(Qt.point(mouseX, customPoint.y), 1, 1)
        }
    }

    //左下角
    Item {
        id: leftBottom
        width: enableSize
        height: enableSize
        anchors.left: parent.left
        anchors.bottom: parent.bottom
        z: 1000
        MouseArea {
            anchors.fill: parent
            hoverEnabled: true
            propagateComposedEvents: true
            onPressed: press(mouse)
            cursorShape: containsMouse?Qt.SizeBDiagCursor:Qt.ArrowCursor;
            onReleased: release()

            onPositionChanged: positionChange(mouse, -1, 1)
        }
    }

    //bottom
    Item {
        id: bottom
        height: enableSize
        anchors.left: leftBottom.right
        anchors.right: rightBottom.left
        anchors.bottom: parent.bottom
        z: 1000
        MouseArea {
            anchors.fill: parent
            hoverEnabled: true
            propagateComposedEvents: true
            onPressed: press(mouse)
            cursorShape: containsMouse?Qt.SizeVerCursor:Qt.ArrowCursor;
            onReleased: release()

            onMouseYChanged: positionChange(Qt.point(customPoint.x, mouseY), 1, 1)
        }
    }

    //右下角
    Item {
        id:rightBottom
        width: enableSize
        height: enableSize
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        z: 1000
        MouseArea {
            anchors.fill: parent
            hoverEnabled: true
            cursorShape: containsMouse?Qt.SizeFDiagCursor:Qt.ArrowCursor;
            onPressed: press(mouse)
            onReleased: release()
            propagateComposedEvents: true
            onPositionChanged: positionChange(mouse,1,1)
        }
    }

    function press(mouse) {
        isPressed = true
        customPoint = Qt.point(mouse.x, mouse.y)
    }

    function release() {
        isPressed = false
        //customPoint = undefined
    }

    function positionChange(newPosition, directX/*x轴方向*/, directY/*y轴方向*/) {
        if(!isPressed) return

        var delta = Qt.point(newPosition.x-customPoint.x, newPosition.y-customPoint.y)
        var tmpW,tmpH

        if(directX >= 0)
            tmpW = mainWindow.width + delta.x
        else
            tmpW = mainWindow.width - delta.x

        if(directY >= 0)
            tmpH = mainWindow.height + delta.y
        else
            tmpH = mainWindow.height - delta.y

        if(tmpW < mainWindow.minimumWidth) {
            if(directX < 0)
                mainWindow.x += (mainWindow.width - mainWindow.minimumWidth)
            mainWindow.width = mainWindow.minimumWidth
        }
        else {
            mainWindow.width = tmpW
            if(directX < 0)
                mainWindow.x += delta.x
        }

        if(tmpH < mainWindow.minimumHeight) {
            if(directY < 0)
                mainWindow.y += (mainWindow.height - mainWindow.minimumHeight)
            mainWindow.height = mainWindow.minimumHeight
        }
        else {
            mainWindow.height = tmpH
            if(directY < 0)
                mainWindow.y += delta.y
        }
    }
}
