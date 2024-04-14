import QtQuick
import QtQuick.Controls

import injector


QmlInjector {
    id: root
    objectName: "baseInjectorPage"

    signal close
    signal firstActivated
    signal backInActive

    property bool firstActivation: true

    StackView.onActivated: {
        if (root.firstActivation) {
            root.firstActivation = false;
            firstActivated();
        } else {
            root.backInActive();
        }
    }

    Keys.onPressed: (event) => {
        if (event.key === Qt.Key_Escape) {
            event.accepted = true;
            console.log(`Closing page ${root.objectName}`)
            root.close();
        }
    }
}

