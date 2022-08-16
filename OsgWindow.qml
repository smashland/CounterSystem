import QtQuick 2.2
import QtQuick.Window 2.2
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.1
import SceneGraphRendering 1.0
import Qt.labs.platform 1.1

Item
{
    id:rootItem
    anchors.fill: parent
    property var objSetting;

    /// 显示地图
    QuickOSGViewer
    {
        type: QuickOSGViewer.Item_3DMAP
        frameRate:60
        id: renderer
        anchors.fill: parent
        focus: true

        MouseArea
        {
            anchors.fill: renderer
            onPressed:
            {
                renderer.forceActiveFocus();
                mouse.accepted = false;
            }
            propagateComposedEvents: true
        }
    }

    function closeSettings()
    {
        if(null !== objSetting)
        {
            objSetting.destroy();
            renderer.forceActiveFocus();
        }
    }

    Component.onCompleted:
    {
        $app.setOsgItem(renderer);
        var cpShowSetting= Qt.createComponent("qrc:/Index.qml")
        objSetting = cpShowSetting.createObject(rootItem,{focus:true});
        if(null === objSetting)
        {
            console.log(cpShowSetting.errorString())
        }
    }
}
