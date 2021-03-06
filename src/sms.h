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

#ifndef MODEMMANAGERQT_SMS_H
#define MODEMMANAGERQT_SMS_H

#include <modemmanagerqt_export.h>

#include <QObject>
#include <QSharedPointer>
#include <QDBusPendingReply>

#include "generictypes.h"

namespace ModemManager
{

class SmsPrivate;

/**
* Provides an interface to manipulate and control an SMS
*
* Note: MMSmsStorage, MMSmsState, MMSmsPduType and MMSmsDeliveryState enums are defined in <ModemManager/ModemManager-enums.h>
* See http://www.freedesktop.org/software/ModemManager/api/1.0.0/ModemManager-Flags-and-Enumerations.html
*/
class MODEMMANAGERQT_EXPORT Sms : public QObject
{
Q_OBJECT
Q_DECLARE_PRIVATE(Sms)

public:
    typedef QSharedPointer<Sms> Ptr;
    typedef QList<Ptr> List;

    explicit Sms(const QString &path, QObject *parent = nullptr);
    ~Sms();

    QString uni() const;

    /**
    * Send the SMS
    */
    QDBusPendingReply<> send();

    /**
    * Store the SMS
    *
    * @param storage the storage location of the SMS (empty for default storage)
    */
    QDBusPendingReply<> store(MMSmsStorage storage = MM_SMS_STORAGE_UNKNOWN);

    /**
    * This method returns the state of the SMS
    */
    MMSmsState state() const;

    /**
    * This method returns the Protocol Data Unit (PDU) type of the SMS
    */
    MMSmsPduType pduType() const;

    /**
    * This method returns the phone number to which the SMS is addressed to
    */
    QString number() const;

    /**
    * This method returns the text of the SMS. text() and data() are not valid at the same time
    */
    QString text() const;

    /**
    * This method returns the SMS service center number
    */
    QString SMSC() const;

    /**
    * This method returns the SMS message data. text() and data() are not valid at the same time
    */
    QByteArray data() const;

    /**
    * This method returns the validity of the SMS
    *
    * @return A ValidityPair struct composed of a MMSmsValidityType type and a value indicating the validity of the SMS
    */
    ValidityPair validity() const;

    /**
    * This method returns the 3GPP class of the SMS
    */
    int smsClass() const;

    /**
     * @return @c true if a delivery report is requested, @c false otherwise
     */
    bool deliveryReportRequest() const;

    /**
    * This method returns the message reference of the last PDU sent/received in the SMS.
    * The message reference is the number used to identify the SMS in the SMSC.
    * If the PDU type is MM_SMS_PDU_TYPE_STATUS_REPORT, this field identifies the Message Reference of the PDU associated to the status report
    */
    uint messageReference() const;

    /**
    * Time when the SMS arrived at the SMSC
    */
    QDateTime timestamp() const;

    /**
    * Time when the SMS left the SMSC
    */
    QDateTime dischargeTimestamp() const;

    /**
    * This method returns the delivery state of the SMS
    */
    MMSmsDeliveryState deliveryState() const;

    /**
    * This method returns the storage area/location of the SMS
    */
    MMSmsStorage storage() const;
#if MM_CHECK_VERSION(1, 2, 0)
    /**
     * @return service category for CDMA SMS, as defined in 3GPP2 C.R1001-D (section 9.3).
     * @since 1.1.91
     */
    MMSmsCdmaServiceCategory serviceCategory() const;

    /**
     * @return teleservice IDs supported for CDMA SMS, as defined in 3GPP2 X.S0004-550-E
     * (section 2.256) and 3GPP2 C.S0015-B (section 3.4.3.1)
     * @since 1.1.91
     */
    MMSmsCdmaTeleserviceId teleserviceId() const;
#endif

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
    /**
    * This signal is emitted when the state of the SMS has changed
    *
    * @param newState the new state of the SMS
    */
    void stateChanged(MMSmsState newState);
    void pduTypeChanged(MMSmsPduType pduType);
    void numberChanged(const QString &number);
    void SMSCChanged(const QString &smsc);
    void dataChanged(const QByteArray &data);
    void textChanged(const QString &text);
    void validityChanged(const ModemManager::ValidityPair &validity);
    void smsClassChanged(int smsClass);
    void deliveryReportRequestChanged(bool deliveryReportRequest);
    void messageReferenceChanged(uint messageReference);
    void timestampChanged(const QDateTime &timestamp);
    void dischargeTimestampChanged(const QDateTime &dischargeTimestamp);
    /**
    * This signal is emitted when the delivery state of the SMS has changed
    *
    * @param newDeliveryState the new delivery state of the SMS
    */
    void deliveryStateChanged(MMSmsDeliveryState newDeliveryState);
    void storageChanged(MMSmsStorage storage);
    void serviceCategoryChanged(MMSmsCdmaServiceCategory serviceCategory);
    void teleserviceIdChanged(MMSmsCdmaTeleserviceId teleserviceId);

private:
    SmsPrivate *const d_ptr;
};

} // namespace ModemManager

#endif
