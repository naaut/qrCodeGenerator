import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Controls.Material

Page {
    id: root
    objectName: "TemplatesScreen"

    default property alias container: mainContentColumn

    signal apply(var incomingString)
    signal close()

    focus: true

    Column {
        width: parent.width

        Column {
            id: mainContentColumn
            width: parent.width


        }

        Button {
            width: parent.width
            text: qsTr("Apply")

            onClicked: root.apply("mainContentColumn");
        }
    }

    Keys.onPressed: (event)=> {
        if (event.key == Qt.Key_Escape) {
            event.accepted = true;
            console.log(`closing page ${root.objectName}`)
            root.close();
        }
    }
}

