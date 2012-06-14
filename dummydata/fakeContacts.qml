import QtQuick 1.1

ListModel {
    function fromId(id) {
        return get(id)
    }

    // mimic telepathy contacts API
    Component.onCompleted: {
        var contact
        for(var i = 0; i < count; i++) {
            contact = get(i)
            setProperty(i, "avatar", {"imageUrl": "../dummydata/" + contact.photo})
            setProperty(i, "emailAddress", {"emailAddress": contact.email})
            setProperty(i, "phoneNumber", {"number": contact.phone})
            setProperty(i, "phoneNumbers", [{"number": contact.phone, "contexts": "Mobile"}])
            setProperty(i, "emails", [{"emailAddress": contact.email}])
            setProperty(i, "onlineAccounts", [{"accountUri": "someone@jabber.org", "serviceProvider": "Jabber"}])
            setProperty(i, "addresses", [{"street": "123 Some street", "city": "Some Place", "state": "Some State", "country": "Some Country"}])
            setProperty(i, "contact", contact)
        }
    }

    ListElement {
        displayLabel: "Allison Reeves"
        displayName: "Allison Reeves"
        email: "a.reeves@mail.com"
        phone: "555-434-6888"
        phoneType: "Mobile"
        photo: "allisonreeves.jpg"
        favourite: true
        location: "New York"
        presence: 1
    }
    ListElement {
        displayLabel: "Frank Johnson"
        displayName: "Frank Johnson"
        email: "frank.johnson@mail.com"
        phone: "555-224-5532"
        phoneType: "Mobile"
        photo: "frankjohnson.jpg"
        favourite: false
        location: "London"
        presence: 1
    }
    ListElement {
        displayLabel: "George Still"
        displayName: "George Still"
        email: "georgestill@mail.com"
        phone: "+34 555-334-6545"
        phoneType: "Russia"
        photo: "georgestill.jpg"
        favourite: true
        location: "San Francisco"
        presence: 1
    }
    ListElement {
        displayLabel: "Rachel Jones"
        displayName: "Rachel Jones"
        email: "rach.jones@mail.com"
        phone: "+1 555-346-7657"
        phoneType: "Work"
        photo: "racheljones.jpg"
        favourite: true
        location: "San Francisco"
        presence: 1
    }
    ListElement {
        displayLabel: "Steve Jackson"
        displayName: "Steve Jackson"
        email: "steve.capone@mail.com"
        phone: "+55 555-444-333-312-121"
        phoneType: "Work"
        photo: "stevejackson.jpg"
        favourite: false
        location: "Oakland"
        presence: 1
    }
    ListElement {
        displayLabel: "Tina Gray"
        displayName: "Tina Gray"
        email: "t.gray@mail.com"
        phone: "555-434-6543"
        phoneType: "Brazil"
        photo: "tinagray.jpg"
        favourite: false
        location: "Barcelona"
        presence: 1
    }
}