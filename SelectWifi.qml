import QtQuick 2.7
import QtQuick.Controls 2.3
import QtQuick.Shapes 1.0
import QtQuick.Layouts 1.3

Popup
{
    property var ip: [4]
    property int nport: 0

    signal toConnect();

    id:selectWifi
    width: parent.width
    height: parent.height


    onClosed:
    {
        if(null !== $obShow)
        {
            $obShow.forceActiveFocus();
        }
    }

    background: Rectangle
    {
        opacity:0.0
    }

    ColumnLayout
    {
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        Rectangle
        {
            color: "#00000000"
            Layout.fillHeight: true
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
        }

        RowLayout
        {
            id: row
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter

            Rectangle
            {
                Layout.fillWidth: true

            }

            Text
            {
                text: "IP:"
                color: "yellow"
                font.bold: true
                font.pixelSize:22
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignBottom
            }

            Repeater
            {
                id:repeater
                model: 3

                Row
                {
                    TextInput
                    {
                        id:textField
                        width: 40
                        maximumLength:3
                        horizontalAlignment: Text.AlignHCenter
                        font.bold:true
                        font.pixelSize:22
                        color:"yellow"
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
                    Shape
                    {
                        ShapePath
                        {
                            id:path
                            strokeWidth: 2
                            strokeColor: "yellow"
                            startX: textField.x;
                            startY: textField.y + textField.height + 2;
                            PathLine
                            {
                                x: path.startX+40;
                                y: path.startY
                            }
                        }
                    }

                    Text
                    {
                        text: "."
                        color: "yellow"
                        font.bold: true
                        font.pixelSize:22
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignBottom
                    }
                }
            }

            TextInput
            {
                id:outInput
                maximumLength:3
                horizontalAlignment: Text.AlignHCenter
                font.bold:true
                font.pixelSize:22
                color:"yellow"
                Layout.preferredWidth: 40
                validator: RegExpValidator{regExp:/(?!0)(?!.*\.$)((1?\d?\d|25[0-5]|2[0-4]\d))/}
                onActiveFocusChanged:
                {
                    if(!activeFocus)
                    {
                        ip[3] = outInput.text
                    }
                }

            }
            Shape
            {
                ShapePath
                {
                    id:outpath
                    strokeWidth: 2
                    strokeColor: "yellow"
                    startX: outInput.x;
                    startY: outInput.y + outInput.height + 2;
                    PathLine
                    {
                        x: outpath.startX+40;
                        y: outpath.startY
                    }
                }
            }

            Text
            {
                text: ":"
                color: "yellow"
                font.bold: true
                font.pixelSize:22
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignBottom
            }

            TextInput
            {
                id:portInput
                maximumLength:5
                horizontalAlignment: Text.AlignHCenter
                font.bold:true
                font.pixelSize:22
                color:"yellow"
                Layout.preferredWidth: 65
                validator: IntValidator{bottom: 0;top:65535;}

                onActiveFocusChanged:
                {
                    if(!activeFocus)
                    {
                        nport = portInput.text
                    }
                }
            }

            Shape
            {
                ShapePath
                {
                    id:portpath
                    strokeWidth: 2
                    strokeColor: "yellow"
                    startX: portInput.x;
                    startY: portInput.y + portInput.height + 2;
                    PathLine
                    {
                        x: portpath.startX+65;
                        y: portpath.startY
                    }
                }
            }

            Rectangle
            {
                Layout.fillWidth: true

            }
        }

        Button
        {
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
            flat: true
            contentItem: Text
            {
                color:"#FFFF00"
                text:"连接"
                font.pixelSize:22
                font.bold:true
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }

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

                selectWifi.close();
                $app.settings.setWifiInfo(sIp,nport);
                $app.startConnect();
                toConnect();
            }
        }
        Rectangle
        {
            color: "#00000000"
            Layout.fillHeight: true
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter

        }
    }
}


/*##^## Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
 ##^##*/
