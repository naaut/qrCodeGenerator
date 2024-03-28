import QtQuick
import QtQuick.Controls
import QtQuick.Controls.Material

// BEGIN:VCARD
// VERSION:3.0
// FN:John Doe
// TEL;TYPE=WORK,VOICE:(111) 555-1212
// EMAIL:johndoe@example.com
// END:VCARD

PopupTemplate {
    id: root
    objectName: "vCardPopup"

    headerText: qsTr("Contact Info (vCard)")
    resultString: {
        let result = "BEGIN:VCARD\nVERSION:3.0\n";

        if (fullName.text) {
            result += `FN:${fullName.text}\n`;
        }

        // if (organization.text) {
        //     result += `ORG:${organization.text}\n`;
        // }

        if (title.text) {
            result += `TITLE:${title.text}\n`;
        }

        if (phoneNumber.text) {
            result += `TEL:${phoneNumber.text}\n`;
        }

        if (email.text) {
            result += `EMAIL:${email.text}\n`;
        }

        result += "END:VCARD"

        return result;
    }

    TextField {
        id: fullName
        width: parent.width
        placeholderText: qsTr("Full Name")
    }

    // TextField {
    //     id: organization
    //     width: parent.width
    //     placeholderText: qsTr("Organization")
    // }

    TextField {
        id: title
        width: parent.width
        placeholderText: qsTr("Title")
    }

    TextField {
         id: phoneNumber
         width: parent.width
         placeholderText: qsTr("Phone Number")
         inputMethodHints: Qt.ImhDialableCharactersOnly
     }

    TextField {
        id: email
        width: parent.width

        placeholderText: qsTr("E-mail address")

        validator: RegularExpressionValidator {
            regularExpression: new RegExp("^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$")
        }
    }
}

