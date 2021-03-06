/*
    Copyright 2014 Lukas Tinkl <ltinkl@redhat.com>
    Copyright 2015 Jan Grulich <jgrulich@redhat.com>

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

#ifndef MODEMMANAGERQT_MODEMSIGNAL_H
#define MODEMMANAGERQT_MODEMSIGNAL_H

#include <modemmanagerqt_export.h>
#include "interface.h"

#include <QObject>
#include <QSharedPointer>

namespace ModemManager
{

class ModemSignalPrivate;

/**
 * @brief The ModemSignal class
 *
 * This class provides access to extended signal quality information.
 *
 * @since 1.1.94
 */
class MODEMMANAGERQT_EXPORT ModemSignal: public Interface
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(ModemSignal)

public:
    typedef QSharedPointer<ModemSignal> Ptr;
    typedef QList<Ptr> List;

    explicit ModemSignal(const QString &path, QObject *parent = nullptr);
    ~ModemSignal();

    /**
     * @return refresh rate for the extended signal quality information updates, in seconds.
     * A value of 0 disables the retrieval of the values.
     */
    uint rate() const;

    /**
     * @return Dictionary of available signal information for the CDMA1x access technology.
     *
     * This dictionary is composed of a string key, with an associated data which contains type-specific information.
     * @param rssi The CDMA1x RSSI (Received Signal Strength Indication), in dBm, given as a floating point value (signature "d").
     * @param ecio The CDMA1x Ec/Io, in dBm, given as a floating point value (signature "d").
     */
    QVariantMap cdma() const;

    /**
     * @return Dictionary of available signal information for the CDMA EV-DO access technology.
     *
     * This dictionary is composed of a string key, with an associated data which contains type-specific information.
     * @param rssi The CDMA EV-DO RSSI (Received Signal Strength Indication), in dBm, given as a floating point value (signature "d").
     * @param ecio The CDMA EV-DO Ec/Io, in dBm, given as a floating point value (signature "d").
     * @param sinr CDMA EV-DO SINR level, in dB, given as a floating point value (signature "d").
     * @param io The CDMA EV-DO Io, in dBm, given as a floating point value (signature "d").
     */
    QVariantMap evdo() const;

    /**
     * @return Dictionary of available signal information for the GSM/GPRS access technology.
     *
     * This dictionary is composed of a string key, with an associated data which contains type-specific information.
     * @param rssi The GSM RSSI (Received Signal Strength Indication), in dBm, given as a floating point value (signature "d").
     */
    QVariantMap gsm() const;

    /**
     * @return Dictionary of available signal information for the UMTS (WCDMA) access technology.
     *
     * This dictionary is composed of a string key, with an associated data which contains type-specific information.
     * @param rssi The LTE RSSI (Received Signal Strength Indication), in dBm, given as a floating point value (signature "d").
     * @param rsrq The LTE RSRQ (Reference Signal Received Quality), in dB, given as a floating point value (signature "d").
     * @param rsrp The LTE RSRP (Reference Signal Received Power), in dBm, given as a floating point value (signature "d").
     * @param snr The LTE S/R ratio, in dB, given as a floating point value (signature "d").
     */
    QVariantMap lte() const;

    /**
     * @return Dictionary of available signal information for the UMTS (WCDMA) access technology.
     *
     * This dictionary is composed of a string key, with an associated data which contains type-specific information.
     * @param rssi The UMTS RSSI (Received Signal Strength Indication), in dBm, given as a floating point value (signature "d").
     * @param ecio The UMTS Ec/Io, in dBm, given as a floating point value (signature "d").
     */
    QVariantMap umts() const;

    /**
     * Setup extended signal quality information retrieval.
     * @param rate refresh rate to set, in seconds. 0 to disable retrieval.
     */
    QDBusPendingReply<void> setup(uint rate);

    /**
     * Sets the timeout in milliseconds for all async method DBus calls.
     * -1 means the default DBus timeout (usually 25 seconds).
     */
    void setTimeout(int timeout);

    /**
     * Returns the current value of the DBus timeout in milliseconds.
     * -1 means the default DBus timeout (usually 25 seconds).
     */
    int timeout() const;

Q_SIGNALS:
    void rateChanged(uint rate);
    void cdmaChanged(const QVariantMap &cdma);
    void evdoChanged(const QVariantMap &evdo);
    void gsmChanged(const QVariantMap &gsm);
    void umtsChanged(const QVariantMap &umts);
    void lteChanged(const QString &lte);
};

} // namespace ModemManager

#endif
