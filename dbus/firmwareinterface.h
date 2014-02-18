/*
 * This file was generated by qdbusxml2cpp version 0.7
 * Command line was: qdbusxml2cpp -N -m -i generic-types.h -p firmwareinterface introspection/org.freedesktop.ModemManager1.Modem.Firmware.xml
 *
 * qdbusxml2cpp is Copyright (C) 2013 Digia Plc and/or its subsidiary(-ies).
 *
 * This is an auto-generated file.
 * Do not edit! All changes made to it will be lost.
 */

#ifndef MODEMMANAGERQT_FIRMWAREINTERFACE_H
#define MODEMMANAGERQT_FIRMWAREINTERFACE_H

#include <QtCore/QObject>
#include <QtCore/QByteArray>
#include <QtCore/QList>
#include <QtCore/QMap>
#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QtCore/QVariant>
#include <QtDBus/QtDBus>

#include "generic-types.h"

/*
 * Proxy class for interface org.freedesktop.ModemManager1.Modem.Firmware
 */
class OrgFreedesktopModemManager1ModemFirmwareInterface: public QDBusAbstractInterface
{
    Q_OBJECT
public:
    static inline const char *staticInterfaceName()
    { return "org.freedesktop.ModemManager1.Modem.Firmware"; }

public:
    OrgFreedesktopModemManager1ModemFirmwareInterface(const QString &service, const QString &path, const QDBusConnection &connection, QObject *parent = 0);

    ~OrgFreedesktopModemManager1ModemFirmwareInterface();

public Q_SLOTS: // METHODS
    inline QDBusPendingReply<QString, QVariantMapList> List()
    {
        QList<QVariant> argumentList;
        return asyncCallWithArgumentList(QLatin1String("List"), argumentList);
    }
    inline QDBusPendingReply<> Select(const QString &uniqueid)
    {
        QList<QVariant> argumentList;
        argumentList << QVariant::fromValue(uniqueid);
        return asyncCallWithArgumentList(QLatin1String("Select"), argumentList);
    }

Q_SIGNALS: // SIGNALS
};

#endif
