/*
    Copyright 2008 Will Stephenson <wstephenson@kde.org>
    Copyright 2010 Lamarque Souza <lamarque@kde.org>
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

#ifndef MODEMMANAGER_SMS_P_H
#define MODEMMANAGER_SMS_P_H

#include "dbus/smsinterface.h"
#include "sms.h"

namespace ModemManager
{

class SmsPrivate : public QObject
{
    Q_OBJECT
public:
    explicit SmsPrivate(const QString &path, Sms *q);
    OrgFreedesktopModemManager1SmsInterface smsIface;

    QString uni;
    MMSmsState state;
    MMSmsPduType pduType;
    QString number;
    QString text;
    QString smsc;
    QByteArray data;
    ValidityPair validity;
    int smsClass;
    bool deliveryReportRequest;
    uint messageReference;
    QDateTime timestamp;
    QDateTime dischargeTimestamp;
    MMSmsDeliveryState deliveryState;
    MMSmsStorage storage;
#if MM_CHECK_VERSION(1, 2, 0)
    MMSmsCdmaServiceCategory serviceCategory;
    MMSmsCdmaTeleserviceId teleserviceId;
#endif

    Q_DECLARE_PUBLIC(Sms)
    Sms *q_ptr;
private Q_SLOTS:
    void onPropertiesChanged(const QString &interface, const QVariantMap &properties, const QStringList &invalidatedProps);
};

} // namespace ModemManager

#endif
