import QtQuick
import QtQuick.Controls
import QtQuick.Controls.Material

// mailto:someone@example.com?subject=Feedback&body=I%20want%20to%20say%20that...

PopupTemplate {
    id: root
    objectName: "emailPopup"

    headerText: qsTr("E-Mail")
    resultString: `mailto:${email.text}?subject=${subject.text}&body=${body.text}`

    TextField {
        id: email
        width: parent.width

        placeholderText: qsTr("E-mail address")

        validator: RegularExpressionValidator {
            regularExpression: new RegExp("^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$")
        }
    }

    TextField {
        id: subject
        width: parent.width
        placeholderText: qsTr("Subject")
    }

    TextArea {
        id: body
        placeholderText: qsTr("E-mail body")
        width: parent.width
        wrapMode: Text.WrapAtWordBoundaryOrAnywhere
    }
}

