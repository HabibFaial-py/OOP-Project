#include "Appointment.h"
#include <iostream>
#include <iomanip>
using namespace std;

string Appointment::statusToString(Status s) {
    switch (s) {
        case SCHEDULED:  return "SCHEDULED";
        case COMPLETED:  return "COMPLETED";
        case CANCELLED:  return "CANCELLED";
    }
    return "SCHEDULED";
}

Appointment::Status Appointment::stringToStatus(const string& s) {
    if (s == "COMPLETED") return COMPLETED;
    if (s == "CANCELLED") return CANCELLED;
    return SCHEDULED;
}

Appointment::Appointment()
    : apptID(""), patientID(""), doctorID(""),
      date(""), time(""), status(SCHEDULED) {}

Appointment::Appointment(string apptID, string patientID, string doctorID,
                         string date, string time)
    : apptID(apptID), patientID(patientID), doctorID(doctorID),
      date(date), time(time), status(SCHEDULED) {}

string              Appointment::getApptID()    const { return apptID; }
string              Appointment::getPatientID() const { return patientID; }
string              Appointment::getDoctorID()  const { return doctorID; }
string              Appointment::getDate()      const { return date; }
string              Appointment::getTime()      const { return time; }
Appointment::Status Appointment::getStatus()    const { return status; }
string              Appointment::getStatusStr() const { return statusToString(status); }

void Appointment::setStatus(Status s) { status = s; }

void Appointment::displayInfo() const {
    cout << left
         << setw(10) << apptID
         << setw(12) << patientID
         << setw(10) << doctorID
         << setw(12) << date
         << setw(8)  << time
         << statusToString(status) << "\n";
}
