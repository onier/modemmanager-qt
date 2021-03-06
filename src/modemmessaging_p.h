/*
    Copyright 2013 Anant Kamath <kamathanant@gmail.com>
    Copyright 2013 Lukas Tinkl <ltinkl@redhat.com>
    Copyright 2013-2015 Jan Grulich <jgrulich@redhat.com>

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) version 3, or any
    later version accepted by the membership of KDE e.V. (or its
    successor approved by the membership of KDE e.V.), which shall
    act as a proxy defined in Section 6 of version 3 of the license.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef MODEMMANAGER_MODEMMESSAGING_P_H
#define MODEMMANAGER_MODEMMESSAGING_P_H

#include "dbus/messaginginterface.h"
#include "interface_p.h"
#include "modemmessaging.h"
#include "sms.h"

namespace ModemManager
{

class ModemMessagingPrivate : public InterfacePrivate
{
public:
    explicit ModemMessagingPrivate(const QString &path, ModemMessaging *q);
    OrgFreedesktopModemManager1ModemMessagingInterface modemMessagingIface;

    QMap<QString, ModemManager::Sms::Ptr> messageList;
    QList<MMSmsStorage> supportedStorages;
    MMSmsStorage defaultStorage;
    ModemManager::Sms::Ptr findMessage(const QString &uni);
    ModemManager::Sms::List messages();

    Q_DECLARE_PUBLIC(ModemMessaging)
    ModemMessaging *q_ptr;
private Q_SLOTS:
    void onPropertiesChanged(const QString &interface, const QVariantMap &properties, const QStringList &invalidatedProps) override;
    void onMessageAdded(const QDBusObjectPath &path, bool received);
    void onMessageDeleted(const QDBusObjectPath &path);
};

} // namespace ModemManager

#endif
