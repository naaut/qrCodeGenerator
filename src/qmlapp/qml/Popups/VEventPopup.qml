import QtQuick
import QtQuick.Controls
import QtQuick.Controls.Material

// BEGIN:VEVENT
// SUMMARY:Appointment
// LOCATION:location
// DESCRIPTION:Meeting with business partner.
// DTSTART:20240315T170000Z
// DTEND:20240315T180000Z
// END:VEVENT

PopupTemplate {
    id: root
    objectName: "vEventPopup"

    headerText: qsTr("Calendar Event (vEvent)")
    resultString: {
        let result = "BEGIN:VEVENT\n";

        if (summary.text) {
            result += `SUMMARY:${summary.text}\n`;
        }

        if (location.text) {
            result += `LOCATION:${location.text}\n`;
        }

        if (description.text) {
            result += `DESCRIPTION:${description.text}\n`;
        }

        if (startDate.text) {
            result += `DTSTART:${startDate.text}\n`;
        }

        if (endDate.text) {
            result += `DTEND:${endDate.text}\n`;
        }

        result += "END:VEVENT";

        return result;
    }

    TextField {
        id: summary
        width: parent.width
        placeholderText: qsTr("Summary")
    }

    TextField {
        id: description
        width: parent.width
        placeholderText: qsTr("Description")
    }

    TextField {
        id: location
        width: parent.width
        placeholderText: qsTr("Location")
    }

    TextField {
        id: startDate
        width: parent.width
        placeholderText: qsTr("Start Date/Time (YYYY-MM-DD HH:MM)")
    }

    TextField {
        id: endDate
        width: parent.width
        placeholderText: qsTr("End Date/Time (YYYY-MM-DD HH:MM)")
    }
}

