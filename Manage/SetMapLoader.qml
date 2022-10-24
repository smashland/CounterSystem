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
        delegate: Rectangle {
            id: wrapper
            width: listView.width
            height: 50 *dpy
            Rectangle {
                anchors.fill: parent
                color: index%2 ? "#2D5689" : "#4671a6"
            }

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

    PopupButton {
        anchors.bottom: parent.bottom
        x: 311*dpx
        background: Rectangle {
            color: "#265aef"
        }
        nameButton: "添加"
        onClicked: {
            mapAdd.visible = true
        }
    }


}
