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

#include "sms.h"
#include "sms_p.h"
#include "mmdebug_p.h"

#ifdef MMQT_STATIC
#include "dbus/fakedbus.h"
#else
#include "dbus/dbus.h"
#endif

#include <ModemManager/ModemManager.h>

ModemManager::SmsPrivate::SmsPrivate(const QString &path, Sms *q)
#ifdef MMQT_STATIC
    : smsIface(QLatin1String(MMQT_DBUS_SERVICE), path, QDBusConnection::sessionBus())
#else
    : smsIface(QLatin1String(MMQT_DBUS_SERVICE), path, QDBusConnection::systemBus())
#endif
    , q_ptr(q)
{
    if (smsIface.isValid()) {
        uni = path;
        state = (MMSmsState) smsIface.state();
        pduType = (MMSmsPduType) smsIface.pduType();
        number = smsIface.number();
        text = smsIface.text();
        smsc = smsIface.SMSC();
        data = smsIface.data();
        validity = smsIface.validity();
        smsClass = smsIface.smsClass();
        deliveryReportRequest = smsIface.deliveryReportRequest();
        messageReference = smsIface.messageReference();
        timestamp =  QDateTime::fromString(smsIface.timestamp(), Qt::ISODate);
        dischargeTimestamp = QDateTime::fromString(smsIface.dischargeTimestamp(), Qt::ISODate);
        deliveryState = (MMSmsDeliveryState) smsIface.deliveryState();
        storage = (MMSmsStorage) smsIface.storage();
#if MM_CHECK_VERSION(1, 2, 0)
        serviceCategory = (MMSmsCdmaServiceCategory) smsIface.serviceCategory();
        teleserviceId = (MMSmsCdmaTeleserviceId) smsIface.teleserviceId();
#endif
    }
}

ModemManager::Sms::Sms(const QString &path, QObject *parent)
    : QObject(parent)
    , d_ptr(new SmsPrivate(path, this))
{
    Q_D(Sms);

    qRegisterMetaType<MMSmsDeliveryState>();
    qRegisterMetaType<MMSmsPduType>();
    qRegisterMetaType<MMSmsState>();
    qRegisterMetaType<MMSmsStorage>();
#if MM_CHECK_VERSION(1, 2, 0)
    qRegisterMetaType<MMSmsCdmaServiceCategory>();
    qRegisterMetaType<MMSmsCdmaTeleserviceId>();
#endif

#ifdef MMQT_STATIC
    QDBusConnection::sessionBus().connect(QLatin1String(MMQT_DBUS_SERVICE), path, QLatin1String(DBUS_INTERFACE_PROPS), QStringLiteral("PropertiesChanged"), d,
                                         SLOT(onPropertiesChanged(QString,QVariantMap,QStringList)));
#else
    QDBusConnection::systemBus().connect(QLatin1String(MMQT_DBUS_SERVICE), path, QLatin1String(DBUS_INTERFACE_PROPS), QStringLiteral("PropertiesChanged"), d,
                                         SLOT(onPropertiesChanged(QString,QVariantMap,QStringList)));
#endif
}

ModemManager::Sms::~Sms()
{
    delete d_ptr;
}

QString ModemManager::Sms::uni() const
{
    Q_D(const Sms);
    return d->uni;
}

QDBusPendingReply<> ModemManager::Sms::send()
{
    Q_D(Sms);
    return d->smsIface.Send();
}

QDBusPendingReply<> ModemManager::Sms::store(MMSmsStorage storage)
{
    Q_D(Sms);
    return d->smsIface.Store(storage);
}

MMSmsState ModemManager::Sms::state() const
{
    Q_D(const Sms);
    return d->state;
}

MMSmsPduType ModemManager::Sms::pduType() const
{
    Q_D(const Sms);
    return d->pduType;
}

QString ModemManager::Sms::number() const
{
    Q_D(const Sms);
    return d->number;
}

QString ModemManager::Sms::text() const
{
    Q_D(const Sms);
    return d->text;
}

QString ModemManager::Sms::SMSC() const
{
    Q_D(const Sms);
    return d->smsc;
}

QByteArray ModemManager::Sms::data() const
{
    Q_D(const Sms);
    return d->data;
}

ModemManager::ValidityPair ModemManager::Sms::validity() const
{
    Q_D(const Sms);
    return d->validity;
}

int ModemManager::Sms::smsClass() const
{
    Q_D(const Sms);
    return d->smsClass;
}

bool ModemManager::Sms::deliveryReportRequest() const
{
    Q_D(const Sms);
    return d->deliveryReportRequest;
}

uint ModemManager::Sms::messageReference() const
{
    Q_D(const Sms);
    return d->messageReference;
}

QDateTime ModemManager::Sms::timestamp() const
{
    Q_D(const Sms);
    return d->timestamp;
}

QDateTime ModemManager::Sms::dischargeTimestamp() const
{
    Q_D(const Sms);
    return d->dischargeTimestamp;
}

MMSmsDeliveryState ModemManager::Sms::deliveryState() const
{
    Q_D(const Sms);
    return d->deliveryState;
}

MMSmsStorage ModemManager::Sms::storage() const
{
    Q_D(const Sms);
    return d->storage;
}
#if MM_CHECK_VERSION(1, 2, 0)
MMSmsCdmaServiceCategory ModemManager::Sms::serviceCategory() const
{
    Q_D(const Sms);
    return d->serviceCategory;
}

MMSmsCdmaTeleserviceId ModemManager::Sms::teleserviceId() const
{
    Q_D(const Sms);
    return d->teleserviceId;
}
#endif

void ModemManager::Sms::setTimeout(int timeout)
{
    Q_D(Sms);
    d->smsIface.setTimeout(timeout);
}

int ModemManager::Sms::timeout() const
{
    Q_D(const Sms);
    return d->smsIface.timeout();
}

void ModemManager::SmsPrivate::onPropertiesChanged(const QString &interfaceName, const QVariantMap &changedProperties, const QStringList &invalidatedProperties)
{
    Q_UNUSED(invalidatedProperties);
    Q_Q(Sms);

    if (interfaceName == QLatin1String(MMQT_DBUS_INTERFACE_SMS)) {
        QVariantMap::const_iterator it = changedProperties.constFind(QLatin1String(MM_SMS_PROPERTY_STATE));
        if (it != changedProperties.constEnd()) {
            state = (MMSmsState) it->toUInt();
            qCDebug(MMQT) << state;
            Q_EMIT q->stateChanged(state);
        }
        it = changedProperties.constFind(QLatin1String(MM_SMS_PROPERTY_PDUTYPE));
        if (it != changedProperties.constEnd()) {
            pduType = (MMSmsPduType) it->toUInt();
            Q_EMIT q->pduTypeChanged(pduType);
        }
        it = changedProperties.constFind(QLatin1String(MM_SMS_PROPERTY_NUMBER));
        if (it != changedProperties.constEnd()) {
            number = it->toString();
            Q_EMIT q->numberChanged(number);
        }
        it = changedProperties.constFind(QLatin1String(MM_SMS_PROPERTY_SMSC));
        if (it != changedProperties.constEnd()) {
            smsc = it->toString();
            Q_EMIT q->SMSCChanged(smsc);
        }
        it = changedProperties.constFind(QLatin1String(MM_SMS_PROPERTY_DATA));
        if (it != changedProperties.constEnd()) {
            data = it->toByteArray();
            Q_EMIT q->dataChanged(data);
        }
        it = changedProperties.constFind(QLatin1String(MM_SMS_PROPERTY_TEXT));
        if (it != changedProperties.constEnd()) {
            text = it->toString();
            Q_EMIT q->textChanged(text);
        }
        it = changedProperties.constFind(QLatin1String(MM_SMS_PROPERTY_VALIDITY));
        if (it != changedProperties.constEnd()) {
            validity = it->value<ValidityPair>();
            Q_EMIT q->validityChanged(validity);
        }
        it = changedProperties.constFind(QLatin1String(MM_SMS_PROPERTY_CLASS));
        if (it != changedProperties.constEnd()) {
            smsClass = it->toInt();
            Q_EMIT q->smsClassChanged(smsClass);
        }
        it = changedProperties.constFind(QLatin1String(MM_SMS_PROPERTY_DELIVERYREPORTREQUEST));
        if (it != changedProperties.constEnd()) {
            deliveryReportRequest = it->toBool();
            Q_EMIT q->deliveryReportRequestChanged(deliveryReportRequest);
        }
        it = changedProperties.constFind(QLatin1String(MM_SMS_PROPERTY_MESSAGEREFERENCE));
        if (it != changedProperties.constEnd()) {
            messageReference = it->toUInt();
            Q_EMIT q->messageReferenceChanged(messageReference);
        }
        it = changedProperties.constFind(QLatin1String(MM_SMS_PROPERTY_TIMESTAMP));
        if (it != changedProperties.constEnd()) {
            timestamp = QDateTime::fromString(it->toString(), Qt::ISODate);
            Q_EMIT q->timestampChanged(timestamp);
        }
        it = changedProperties.constFind(QLatin1String(MM_SMS_PROPERTY_DISCHARGETIMESTAMP));
        if (it != changedProperties.constEnd()) {
            dischargeTimestamp = QDateTime::fromString(it->toString(), Qt::ISODate);
            Q_EMIT q->dischargeTimestampChanged(dischargeTimestamp);
        }
        it = changedProperties.constFind(QLatin1String(MM_SMS_PROPERTY_DELIVERYSTATE));
        if (it != changedProperties.constEnd()) {
            deliveryState = (MMSmsDeliveryState) it->toUInt();
            Q_EMIT q->deliveryStateChanged(deliveryState);
        }
        it = changedProperties.constFind(QLatin1String(MM_SMS_PROPERTY_STORAGE));
        if (it != changedProperties.constEnd()) {
            storage = (MMSmsStorage) it->toUInt();
            Q_EMIT q->storageChanged(storage);
        }
#if MM_CHECK_VERSION(1, 2, 0)
        it = changedProperties.constFind(QLatin1String(MM_SMS_PROPERTY_SERVICECATEGORY));
        if (it != changedProperties.constEnd()) {
            serviceCategory = (MMSmsCdmaServiceCategory) it->toUInt();
            Q_EMIT q->serviceCategoryChanged(serviceCategory);
        }
        it = changedProperties.constFind(QLatin1String(MM_SMS_PROPERTY_TELESERVICEID));
        if (it != changedProperties.constEnd()) {
            teleserviceId = (MMSmsCdmaTeleserviceId) it->toUInt();
            Q_EMIT q->teleserviceIdChanged(teleserviceId);
        }
#endif
    }
}
