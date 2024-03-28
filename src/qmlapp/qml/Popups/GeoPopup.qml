import QtQuick
import QtQuick.Controls
import QtQuick.Controls.Material

// geo:40.689247,-74.044502

PopupTemplate {
    id: root
    objectName: "geoPopup"

    headerText: qsTr("Geolocation point")
    resultString: `geo:${latitude.text},${longitude.text}`

    TextField {
        id: latitude
        width: parent.width
        placeholderText: qsTr("Latitude")
        validator: DoubleValidator {
            bottom: -90
            top: 90
            decimals: 6
            notation: DoubleValidator.StandardNotation
        }
    }

    TextField {
        id: longitude
        width: parent.width
        placeholderText: qsTr("Longitude")
        validator: DoubleValidator {
            bottom: -180
            top: 180
            decimals: 6
            notation: DoubleValidator.StandardNotation
        }
    }
}

