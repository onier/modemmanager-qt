/*
    Copyright 2008 Will Stephenson <wstephenson@kde.org>
    Copyright 2010 Lamarque Souza <lamarque@kde.org>
    Copyright 2013 Jan Grulich <jgrulich@redhat.com>

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

#ifndef MODEMMANAGERQT_MODEMLOCATION_P_H
#define MODEMMANAGERQT_MODEMLOCATION_P_H

#include "dbus/locationinterface.h"
#include "interface_p.h"
#include "modemlocation.h"

namespace ModemManager
{

class ModemLocationPrivate: public InterfacePrivate
{
public:
    explicit ModemLocationPrivate(const QString &path, ModemLocation *q);
    OrgFreedesktopModemManager1ModemLocationInterface modemLocationIface;

    QFlags<MMModemLocationSource> capabilities;
    QFlags<MMModemLocationSource> enabledCapabilities;
    bool signalsLocation;
    LocationInformationMap location;

    Q_DECLARE_PUBLIC(ModemLocation)
    ModemLocation *q_ptr;
private Q_SLOTS:
   void onPropertiesChanged(const QString &interface, const QVariantMap &properties, const QStringList &invalidatedProps) override;
};

} // namespace ModemManager

#endif
