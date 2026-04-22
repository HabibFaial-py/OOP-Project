#include "Doctor.h"
#include <iostream>
#include <iomanip>
#include <sstream>
using namespace std;

Doctor::Doctor()
    : Person(), doctorID(""), specialty(""), consultationFee(0.0), availableDays("") {}

Doctor::Doctor(string name, string id, string phone, int age,
               string doctorID, string specialty, double fee, string days)
    : Person(name, id, phone, age),
      doctorID(doctorID), specialty(specialty),
      consultationFee(fee), availableDays(days) {}

string Doctor::getDoctorID()        const { return doctorID; }
string Doctor::getSpecialty()       const { return specialty; }
double Doctor::getConsultationFee() const { return consultationFee; }
string Doctor::getAvailableDays()   const { return availableDays; }

void Doctor::setDoctorID(const string& did)    { doctorID        = did; }
void Doctor::setSpecialty(const string& s)     { specialty       = s;   }
void Doctor::setConsultationFee(double fee)    { consultationFee = fee; }
void Doctor::setAvailableDays(const string& d) { availableDays   = d;   }

bool Doctor::isAvailableOn(const string& day) const {
    // availableDays is a comma-separated string e.g. "Mon,Wed,Fri"
    stringstream ss(availableDays);
    string token;
    while (getline(ss, token, ',')) {
        if (token == day) return true;
    }
    return false;
}

void Doctor::displayInfo() const {
    cout << left
         << setw(10) << doctorID
         << setw(20) << getName()
         << setw(15) << getPhone()
         << setw(5)  << getAge()
         << setw(20) << specialty
         << setw(10) << fixed << setprecision(2) << consultationFee
         << availableDays << "\n";
}
