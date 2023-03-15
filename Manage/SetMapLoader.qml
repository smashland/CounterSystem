import QtQuick 2.12
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import MyItem 1.0
import QtQuick.Dialogs 1.3
import Qt.labs.platform 1.1
import Qt.labs.qmlmodels 1.0
import "../Common"
import "../Exercise"
import "Plugins"

Rectangle {
    id: setMapLoade
    width: 710 *dpx
    height: 510 *dpy
    color: "transparent"
    MouseArea {
        anchors.fill: parent
        propagateComposedEvents: false
        enabled:true
        onWheel: {
            // 屏蔽滚轮事件，防止滚动方案列表时缩放地球
            //            mouse.accepted = false
        }
    }

    Connections{
        function onSignalAddMap(name,path,lat,lon,rdlat,rdlon)
        {
            var earth = earthManager.addMaps(name,path);
            if(null!==earth)
            {
                earth.earthName = name;
                earth.earthPath = path;
                earth.nLat = lat;
                earth.nLon = lon;
                earth.nRDLat = rdlat;
                earth.nRDLon = rdlon;
                console.log("测试路径："+name+" "+path+rdlat+rdlon)
                listView.model=earthManager.earthList
                earthManager.saveFile();
                mapAdd.visible = false;
                mapAdd.qingkong();
            }
            else{
                mapAdd.earthTip();
            }
        }
        target: mapAdd
    }
    Connections{
        ignoreUnknownSignals: true;
        target: earthManager
        onBeginEdit:{
            rootItem.cursorType=Qt.CrossCursor
            footerBar.btnSet.checked = false
        }
        onEndEdit:{
            rootItem.cursorType = Qt.ArrowCursor
            footerBar.btnSet.checked = true
        }
    }
    MapHelpList{
        id: listView
        width: 710 *dpx
        height: 510 *dpy
        model:earthManager.earthList
        currentIndex: -1
        spacing:2*dpy
        delegate: DelegateRectangle {
            id: wrapper
            property bool hoverd: false
            Rectangle {
                id: background
                anchors.fill: parent
                color: listView.currentIndex === index ? "#2D5689" : (hoverd ? "#2D5689" : "#4671a6")
            }

            TextListItem {
                id: fileName
                text: modelData.earthName
                anchors.centerIn: parent
            }
            MouseArea {
                id: mouseArea
                anchors.fill: parent
                //                    hoverEnabled: true
                onClicked: {
                    $app.earthChange(modelData.earthName,modelData.earthPath,modelData.nLat,modelData.nLon,modelData.nRDLat,modelData.nRDLon);
                    console.log("测试："+modelData.earthPath);
//                    earthManager.praseEarthXml(modelData.earthPath)
//                    $app.changeEarth(modelData.earthPath)
//                    earthManager.saveCurrentEarth(modelData.earthName,modelData.nLat,modelData.nLon);
//                    earthManager.praseCurrentEarth();
                    listView.currentIndex = index
                    mouse.accepted = false
                }
                //                    onEntered: {
                //                        wrapper.hoverd = true
                //                    }

                //                    onExited: wrapper.hoverd = false

            }
            ViewButton {
                name: qsTr("删除")
                color: viewColor_shanchu
                anchors.right: parent.right
                anchors.rightMargin: 10*dpx
                y: 10 *dpy
                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        if(earthManager.deleteEarth(modelData.earthName,modelData.earthPath))
                        {
                             listView.model=earthManager.earthList
                        }
//                        earthManager.deleteEarth(modelData.earthName,modelData.earthPath)
//                        listView.model=earthManager.earthList
                    }
                }
            }
        }
    }
    property var mapValue:{0:0}
    property var component;
    function openQml(obj) {
        component = Qt.createComponent("MapAdd.qml");
        if (component.status === Component.Ready) {
            var qmlObj = component.createObject(setMapLoade,{map:obj});
            if (qmlObj !== null) {
                mapValue[obj] = qmlObj;
                return(qmlObj);
            }
        } else {
            component.destroy();
            return(null);
        }
    }

    //    function finishQml(obj) {
    //        if (component.status === Component.Ready) {
    //            var qmlObj = component.createObject(setMapLoade,{map:obj});
    //            if (qmlObj !== null) {
    //                mapValue[obj] = qmlObj;
    //                return(qmlObj);
    //            }
    //        }else {

    //        }
    //    }

    property var mapName:fileName.text

    MapAdd {
        id: mapAdd
        width: 600*dpx
        height:450*dpy /*430*dpy*/
        //        anchors.centerIn: parent
        y:-20 * dpy
        visible: false
        z: 100
    }

    PopupButton {
        id:addMap
        anchors.bottom: parent.bottom
        x: 311*dpx
        background: Rectangle {
            color: "#265aef"
        }
        nameButton: "添加"
        onClicked: {
            mapAdd.visible = true
            //            footerBar.btnSet.checked = false
            //            openQml(earthManager.addMaps(mapName),"MapAdd.qml")
        }
    }

}
