/*
 * This file was generated by qdbusxml2cpp version 0.7
 * Command line was: qdbusxml2cpp -m -p mm-manager-clientinterface /home/ilia/libnm-qt/libmm-qt/dbus/introspection/mm-manager-client.xml
 *
 * qdbusxml2cpp is Copyright (C) 2011 Nokia Corporation and/or its subsidiary(-ies).
 *
 * This is an auto-generated file.
 * This file may have been hand-edited. Look for HAND-EDIT comments
 * before re-generating it.
 */

#include "mm-manager-clientinterface.h"

/*
 * Implementation of interface class OrgFreedesktopModemManagerInterface
 */

OrgFreedesktopModemManagerInterface::OrgFreedesktopModemManagerInterface(const QString &service, const QString &path, const QDBusConnection &connection, QObject *parent)
    : QDBusAbstractInterface(service, path, staticInterfaceName(), connection, parent)
{
}

OrgFreedesktopModemManagerInterface::~OrgFreedesktopModemManagerInterface()
{
}


#include "mm-manager-clientinterface.moc"