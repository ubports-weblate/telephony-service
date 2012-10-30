import QtQuick 2.0
import Ubuntu.Components 0.1

AbstractButton {
    id: listItem

    width: units.gu(31)

    property bool isIcon: false
    property alias iconSource: icon.source
    property url placeholderIconSource
    property alias text: label.text
    property alias subtext: sublabel.text
    property bool selected: false
    property bool textBold: false
    property int padding: units.gu(1)

    property bool __hasSubLabel: subtext != ""
    property color __textColor: (selected || textBold) ? "#f37505" : Qt.rgba(0.4, 0.4, 0.4, 1.0)

    Item {
        id: body
        anchors.fill: parent

        Item {
            id: iconContainer

            anchors.top: parent.top
            anchors.bottom: parent.bottom
            anchors.left: parent.left
            width: units.gu(7)

            FramedImage {
                id: icon

                anchors.centerIn: parent
                anchors.verticalCenterOffset: units.dp(1)
                width: listItem.isIcon ? units.gu(2) : units.gu(5)
                height: width
                fallbackSource: listItem.placeholderIconSource
                frameVisible: !listItem.isIcon
                opacity: listItem.enabled ? 1.0 : 0.5
            }
        }

        TextCustom {
            id: label

            property bool centered: !listItem.__hasSubLabel

            anchors.top: !centered ? parent.top : undefined
            anchors.topMargin: !centered ? listItem.padding - units.gu(0.5) : 0
            anchors.left: iconContainer.right
            anchors.leftMargin: units.dp(1)
            anchors.right: parent.right
            anchors.rightMargin: listItem.padding
            anchors.verticalCenter: centered ? parent.verticalCenter : undefined
            fontSize: "medium"
            font.bold: textBold
            elide: Text.ElideRight

            color: listItem.__textColor
            style: Text.Raised
            styleColor: "white"
            opacity: listItem.enabled ? 1.0 : 0.5
        }

        TextCustom {
            id: sublabel

            anchors.left: label.left
            anchors.leftMargin: label.anchors.leftMargin
            anchors.top: label.bottom
            anchors.topMargin: units.dp(1)
            anchors.right: parent.right
            anchors.rightMargin: listItem.padding
            fontSize: "small"
            font.bold: textBold
            elide: Text.ElideRight

            color: listItem.__textColor
            style: Text.Raised
            styleColor: "white"
            opacity: listItem.enabled ? 1.0 : 0.5
        }
    }
}