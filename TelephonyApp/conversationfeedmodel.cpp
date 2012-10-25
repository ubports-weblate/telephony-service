/*
 * Copyright (C) 2012 Canonical, Ltd.
 *
 * Authors:
 *  Gustavo Pichorim Boiko <gustavo.boiko@canonical.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; version 3.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "conversationfeedmodel.h"

ConversationFeedModel::ConversationFeedModel(QObject *parent) :
    QAbstractListModel(parent)
{
    QHash<int, QByteArray> roles = roleNames();
    roles[ContactId] = "contactId";
    roles[ContactAlias] = "contactAlias";
    roles[ContactAvatar] = "contactAvatar";
    roles[Timestamp] = "timestamp";
    roles[Incoming] = "incoming";
    roles[ItemType] = "itemType";
    roles[FeedItem] = "item";
    setRoleNames(roles);
}

ConversationFeedModel::DisplayStrategy ConversationFeedModel::displayStrategy() const
{
    return ShowAllEvents;
}

QString ConversationFeedModel::groupingKeyForIndex(const QModelIndex &index) const
{
    return QString::null;
}

bool ConversationFeedModel::matchesSearch(const QString &searchTerm, const QModelIndex &index) const
{
    // TODO: implement
    return true;
}

QString ConversationFeedModel::itemType(const QModelIndex &index) const
{
    return "default";
}

QVariant ConversationFeedModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || index.row() < 0 || index.row() > mItems.count()) {
        return QVariant();
    }

    ConversationFeedItem *item = mItems[index.row()];

    switch (role) {
    case ContactId:
        return item->contactId();
    case ContactAlias:
        return item->contactAlias();
    case ContactAvatar:
        return item->contactAvatar();
    case Timestamp:
        return item->timestamp();
    case Incoming:
        return item->incoming();
    case ItemType:
        return itemType(index);
    case FeedItem:
        return QVariant::fromValue(const_cast<QObject *>(static_cast<const QObject *>(item)));
    }

    return QVariant();
}

int ConversationFeedModel::rowCount(const QModelIndex &parent) const
{
    return mItems.count();
}

void ConversationFeedModel::addItem(ConversationFeedItem *item)
{
    beginInsertRows(QModelIndex(), mItems.count(), mItems.count());
    mItems.append(item);
    endInsertRows();
}

void ConversationFeedModel::removeItem(ConversationFeedItem *item)
{
    int index = mItems.indexOf(item);
    if (index < 0) {
        return;
    }

    beginRemoveRows(QModelIndex(), index, index);
    mItems.removeAt(index);
    delete item;
    endRemoveRows();
}

void ConversationFeedModel::clear()
{
    beginRemoveRows(QModelIndex(), 0, mItems.count()-1);
    qDeleteAll(mItems);
    mItems.clear();
    endRemoveRows();
}
