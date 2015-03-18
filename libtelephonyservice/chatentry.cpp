/*
 * Copyright (C) 2015 Canonical, Ltd.
 *
 * Authors:
 *  Tiago Salem Herrmann <tiago.herrmann@canonical.com>
 *
 * This file is part of telephony-service.
 *
 * telephony-service is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; version 3.
 *
 * telephony-service is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "telepathyhelper.h"
#include "accountentry.h"
#include "chatentry.h"

#include <TelepathyQt/Contact>
#include <TelepathyQt/PendingReady>
#include <TelepathyQt/Connection>

ChatEntry::ChatEntry(const Tp::TextChannelPtr &channel, QObject *parent) :
    QObject(parent),
    mChannel(channel)
{
    mAccount = TelepathyHelper::instance()->accountForConnection(mChannel->connection());
    Q_FOREACH (Tp::ContactPtr contact, mChannel->groupContacts(false)) {
        ContactChatState *state = new ContactChatState(contact->id(), mChannel->chatState(contact));
        mChatStates[contact->id()] = state;
    }

    connect(channel.data(), SIGNAL(chatStateChanged(const Tp::ContactPtr &, Tp::ChannelChatState)),
                            this, SLOT(onChatStateChanged(const Tp::ContactPtr &,Tp::ChannelChatState)));
    connect(channel.data(), SIGNAL(groupMembersChanged(
            const Tp::Contacts &groupMembersAdded,
            const Tp::Contacts &groupLocalPendingMembersAdded,
            const Tp::Contacts &groupRemotePendingMembersAdded,
            const Tp::Contacts &groupMembersRemoved,
            const Tp::Channel::GroupMemberChangeDetails &details)), this, SIGNAL(participantsChanged()));
}

ChatEntry::~ChatEntry()
{
    QMapIterator<QString, ContactChatState*> it(mChatStates);
    while (it.hasNext()) {
        it.next();
        it.value()->deleteLater();
    }
}

void ChatEntry::onChatStateChanged(const Tp::ContactPtr &contact, Tp::ChannelChatState state)
{
    if (mChatStates.contains(contact->id())) {
        mChatStates[contact->id()]->setState(state);
        return;
    }
    ContactChatState *newState = new ContactChatState(contact->id(), state);
    mChatStates[contact->id()] = newState;
    Q_EMIT chatStatesChanged();
}

ChatType ChatEntry::chatType()
{
    return (ChatType)mChannel->targetHandleType();
}

Tp::TextChannelPtr ChatEntry::channel()
{
    return mChannel;
}

QStringList ChatEntry::participants()
{
    QStringList participantList;
    Q_FOREACH (Tp::ContactPtr contact, mChannel->groupContacts(false)) {
        participantList << contact->id();
    }
    return participantList;
}

AccountEntry *ChatEntry::account()
{
    return mAccount;
}

QList<ContactChatState*> ChatEntry::chatStates()
{
    return mChatStates.values();
}
