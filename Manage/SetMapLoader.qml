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

    Connections{
        function onSignalAddMap(name,path,lat,lon)
        {
            var earth = earthManager.addMaps(name);
            if(null!==earth)
            {
                earth.earthName = name;
                earth.earthPath = path;
                earth.nLat = lat;
                earth.nLon = lon;
                listView.model=earthManager.earthList
            }
            else{

            }

        }
        target: mapAdd
    }

    MapHelpList{
        id: listView
        width: 710 *dpx
        height: 510 *dpy
        model:sceManager.listSces
        delegate: DelegateRectangle {
            id: wrapper

            TextListItem {
                id: fileName
                text: modelData.earthName
                anchors.centerIn: parent
            }
            MouseArea {
                anchors.fill: parent
                hoverEnabled: true
                onClicked: {
                    earthManager.praseEarthXml(modelData.earthPath)
                    $app.changeEarth(modelData.earthPath)
                }
            }
        }

    }

    property var component;
    function openQml() {
        component = Qt.createComponent("MapAdd.qml");
        if (component.status === Component.Ready || component.status === Component.Error) {
            finishQml()
        } else {
//            component.addMap.connect(finishQml);
        }
    }

    function finishQml() {
        if (component.status === Component.Ready) {
            var image = component.createObject(setMapLoade, {"anchors.centerIn":setloader});
            if (image === null) {
                console.log("Error creating button");
            }
        } else if (component.status === Component.Error) {
            console.log("Error loading component:", component.errorString());
        }
    }

    MapAdd {
        id: mapAdd
        width: 600*dpx
        height: 430*dpy
//        anchors.centerIn: parent
        visible: false
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
//            mapAdd.visible = true
            openQml()
        }
    }


}
