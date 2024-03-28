import QtQuick
import QtQuick.Controls
import QtQuick.Controls.Material

// https://t.me/username

PopupTemplate {
    id: root
    objectName: "socialMediaPopup"

    headerText: qsTr("Crypto Payment Address")
    resultString: `${socialMediaType.currentValue}${username.text}`

    ComboBox {
        id: socialMediaType
        width: parent.width

        currentIndex: 0
        textRole: "text"
        valueRole: "value"

        model: ListModel {
            ListElement { text: qsTr("Telegram"); value: "https://t.me/" }
            ListElement { text: qsTr("WhatsApp"); value: "https://wa.me/" }  // index 1
            ListElement { text: qsTr("Instagram"); value: "https://www.instagram.com/" }
            ListElement { text: qsTr("Facebook"); value: "https://www.facebook.com/" }
            ListElement { text: qsTr("Twitter"); value: "https://twitter.com/" }
            ListElement { text: qsTr("LinkedIn"); value: "https://www.linkedin.com/in/" }
            ListElement { text: qsTr("YouTube"); value: "https://www.youtube.com/channel/" } // index 6
            ListElement { text: qsTr("VK (VKontakte)"); value: "https://vk.com/username" }
            ListElement { text: qsTr("Snapchat"); value: "https://www.snapchat.com/add/username" }
            ListElement { text: qsTr("Pinterest"); value: "https://www.pinterest.com/username" }
            ListElement { text: qsTr("TikTok"); value: "https://www.tiktok.com/@username" }
            ListElement { text: qsTr("Spotify"); value: "https://open.spotify.com/user/username" }
            ListElement { text: qsTr("Spotify Playlist"); value: "https://open.spotify.com/playlist/" } // index 12
            ListElement { text: qsTr("SoundCloud"); value: "https://soundcloud.com/username" }
        }
    }

    TextField {
        id: username
        width: parent.width
        placeholderText: {
            if (socialMediaType.currentIndex === 1) {
                return qsTr("Phone Number");
            }

            if (socialMediaType.currentIndex === 6) {
                return qsTr("Channel Id");
            }

            if (socialMediaType.currentIndex === 12) {
                return qsTr("Playlist Id");
            }

            return qsTr("Username");
        }
    }
}

