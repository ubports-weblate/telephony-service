/**
 * Copyright (C) 2013 Canonical, Ltd.
 *
 * This program is free software: you can redistribute it and/or modify it under
 * the terms of the GNU General Public License version 3, as published by
 * the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranties of MERCHANTABILITY,
 * SATISFACTORY QUALITY, or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * Authors: Gustavo Pichorim Boiko <gustavo.boiko@canonical.com>
 */

#ifndef MOCKCONNECTIONDBUS_H
#define MOCKCONNECTIONDBUS_H

#include <QDBusContext>
#include <QObject>

class MockConnectionAdaptor;
class MockConnection;

class MockConnectionDBus : public QObject, public QDBusContext
{
    Q_OBJECT
public:
    explicit MockConnectionDBus(MockConnection *parent);

    bool connectToBus();
    void PlaceIncomingMessage(const QString &message, const QVariantMap &properties);
    QString PlaceCall(const QVariantMap &properties);
    void HangupCall(const QString &callerId);
    void SetCallState(const QString &phoneNumber, const QString &state);
    void SetOnline(bool online);
    void SetPresence(const QString &status, const QString &statusMessage);

    // voicemail stuff
    void SetVoicemailIndicator(bool active);
    void SetVoicemailNumber(const QString &number);
    void SetVoicemailCount(int count);

    // emergency numbers stuff
    void SetEmergencyNumbers(const QStringList &numbers);

    // USSD stuff
    QString Serial();

Q_SIGNALS:
    // signals that will be relayed into the bus
    void MessageRead(const QString &messageId);
    void MessageSent(const QString &mesasge, const QVariantMap &properties);
    void CallReceived(const QString &callerId);
    void CallEnded(const QString &callerId);
    void CallStateChanged(const QString &callerId, const QString &objectPath, const QString &state);
    void ConferenceCreated(const QString &objectPath);
    void ChannelMerged(const QString &objectPath);
    void ChannelSplitted(const QString &objectPath);

private:
    MockConnectionAdaptor *mAdaptor;
    MockConnection *mConnection;
};

#endif // MOCKCONNECTIONDBUS_H
