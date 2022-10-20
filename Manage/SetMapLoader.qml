import QtQuick 2.12
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import MyItem 1.0
import QtQuick.Dialogs 1.3
import Qt.labs.platform 1.1
import Qt.labs.qmlmodels 1.0
import "../Common"
import "../Exercise"

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

    Rectangle {

        width: 710 *dpx
        height: 510 *dpy
        color: "transparent"

        Component {
            id: delegate
            Item {
                id: wrapper
                width: parent.width
                height: 38 *dpy
                Rectangle {
                    anchors.fill: parent
                    color: index%2 ? "#4671a6" : "#2D5689"
                }
                MouseArea {
                    anchors.fill: parent
                    hoverEnabled: true
                    onClicked: {
                        mouse.accepted = true
                        wrapper.ListView.view.currentIndex = index
//                        $app.openFile("file:///"+modelData)
                    }
                }
                Text {
                    id:fileName
                    text: modelData.earthName
                    anchors.centerIn: parent
                    color: "#ffffff"
                    font.pixelSize: 16*dpx
                    font.family: "MicrosoftYaHei";
                    verticalAlignment: Text.AlignVCenter
                }
            }
        }

        Component {
            id: listModel;
            ListModel {

            }

        }

        ListView {
            id: listView
            anchors.fill: parent
            delegate: delegate
            spacing: 1*dpy
            model: earthManager.earthList
            focus: true
            clip: true
            ScrollBar.vertical: ScrollBar {
                id: scrollBar
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
