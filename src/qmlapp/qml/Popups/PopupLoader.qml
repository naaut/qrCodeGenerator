import QtQuick


Loader {
    id: root

    active: false

    function open(source, properties) {
        if (!active) {
            root.setSource(source, properties);
            active = true;
        }
    }

    onLoaded: {
        if (item) {
            item.open();
        }
    }

    Connections {
        target: root.item
        ignoreUnknownSignals: true

        function onClosed() {
            root.active = false;
            root.sourceComponent = undefined;
        }
    }
}
