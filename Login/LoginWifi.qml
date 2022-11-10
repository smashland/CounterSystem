import QtQuick 2.12
import QtGraphicalEffects 1.15
import QtQuick.Controls 2.15
import MyItem 1.0
import "../Manage/Plugins"
import "../Common"
import "Plugins"

Column {
    signal toConnect()
    property var ip: [4]
    property int nport: 0

    id: columnTextField
    spacing: 20*dpy
    Row
    {
        id: row
        TextListItem {
            id: ipText
            text: "IP 地址："
            heightTitle: 34*dpx
            font.bold: false
        }

        Repeater
        {
            id:repeater
            model: 3
            x:ipText.contentWidth+80*dpx
            Row
            {
                TextFieldItem {
                    id:textField
//                    color: Qt.rgba(255/255, 255/255, 255/255, 0.8);
                    background: Rectangle {
                        color: Qt.rgba(0/255, 31/255, 94/255, 0.6);
                        border.color: "#00baff"
                    }
                    text: $app.settings.getSip()
                    font.bold: false
                    validator: RegExpValidator
                    {
                        regExp:0 === index ? /(?!0)(?!.*\.$)((1?\d?\d|25[0-5]|2[0-4]\d))/ :/(?!.*\.$)((1?\d?\d|25[0-5]|2[0-4]\d))/
                    }
                    onActiveFocusChanged:
                    {
                        if(!activeFocus)
                        {
                            ip[index] = textField.text
                        }
                    }
                }

                TextListItem {
                    text: "."
                    heightTitle: 34*dpx
                    font.bold: false
                }
            }
        }
        TextFieldItem
        {
            id:outInput
            width: 100*dpx
//            color: Qt.rgba(255/255, 255/255, 255/255, 0.8);
            background: Rectangle {
                color: Qt.rgba(0/255, 31/255, 94/255, 0.6);
                border.color: "#00baff"
            }
            text: $app.settings.getSip()
            font.bold: false
            validator: RegExpValidator{regExp:/(?!0)(?!.*\.$)((1?\d?\d|25[0-5]|2[0-4]\d))/}
            onActiveFocusChanged:
            {
                if(!activeFocus)
                {
                    ip[3] = outInput.text
                }
            }
        }
    }
    Row {
        TextListItem {
            id:dkh
            text: "端口号："
            heightTitle: 34*dpx
            font.bold: false
        }

        TextFieldItem {
            id:portInput
            width: 100*dpx
            x:dkh.contentWidth+80*dpx
//            color: Qt.rgba(255/255, 255/255, 255/255, 0.8);
            background: Rectangle {
                color: Qt.rgba(0/255, 31/255, 94/255, 0.6);
                border.color: "#00baff"
            }
            font.bold: false
            validator: IntValidator{bottom: 0;top:65535;}
            text: $app.settings.getPort()
            onActiveFocusChanged:
            {
                if(!activeFocus)
                {
                    nport = portInput.text
                }
            }
        }

    }


    LoginButton {
        MouseArea {
            anchors.fill: parent
            onClicked:
            {
                var sIp='';
                for(var nIndex=0; nIndex<4; ++nIndex)
                {
                    sIp += ip[nIndex];
                    if(3 !== nIndex)
                    {
                        sIp+='.'
                    }
                }

                console.log(sIp,nport);
                $app.settings.setWifiInfo(sIp,nport);
                $app.startConnect();
                $licCheck.saveLicense(lrText.text);
                $licCheck.checkLicense()
                toConnect();
            }
        }
    }
}

