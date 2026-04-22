#include "Patient.h"
#include <iostream>
#include <iomanip>
using namespace std;

Patient::Patient()
    : Person(), patientID(""), diagnosis(""), admitDate(""),
      assignedRoomNo(-1), assignedDoctorID(""), isPaid(false) {}

Patient::Patient(string name, string id, string phone, int age,
                 string patientID, string diagnosis, string admitDate,
                 int roomNo, string doctorID)
    : Person(name, id, phone, age),
      patientID(patientID), diagnosis(diagnosis), admitDate(admitDate),
      assignedRoomNo(roomNo), assignedDoctorID(doctorID), isPaid(false) {}

string Patient::getPatientID()        const { return patientID; }
string Patient::getDiagnosis()        const { return diagnosis; }
string Patient::getAdmitDate()        const { return admitDate; }
int    Patient::getAssignedRoomNo()   const { return assignedRoomNo; }
string Patient::getAssignedDoctorID() const { return assignedDoctorID; }
bool   Patient::getIsPaid()           const { return isPaid; }

void Patient::setPatientID(const string& pid)       { patientID        = pid; }
void Patient::setDiagnosis(const string& d)         { diagnosis        = d;   }
void Patient::setAdmitDate(const string& date)      { admitDate        = date; }
void Patient::setAssignedRoomNo(int roomNo)         { assignedRoomNo   = roomNo; }
void Patient::setAssignedDoctorID(const string& did){ assignedDoctorID = did; }
void Patient::setIsPaid(bool paid)                  { isPaid           = paid; }

void Patient::displayInfo() const {
    cout << left
         << setw(12) << patientID
         << setw(20) << getName()
         << setw(15) << getPhone()
         << setw(5)  << getAge()
         << setw(20) << diagnosis
         << setw(12) << admitDate
         << setw(6)  << assignedRoomNo
         << setw(10) << assignedDoctorID
         << (isPaid ? "Paid" : "Unpaid") << "\n";
}
