#include "Bill.h"
#include <iostream>
#include <iomanip>
using namespace std;

Bill::Bill()
    : billID(""), patientID(""), daysStayed(0),
      roomRate(0.0), doctorFee(0.0), medCharges(0.0),
      totalAmount(0.0), isPaid(false) {}

Bill::Bill(string billID, string patientID, int days,
           double roomRate, double doctorFee, double medCharges)
    : billID(billID), patientID(patientID), daysStayed(days),
      roomRate(roomRate), doctorFee(doctorFee), medCharges(medCharges),
      isPaid(false) {
    recalculate();
}

string Bill::getBillID()      const { return billID; }
string Bill::getPatientID()   const { return patientID; }
int    Bill::getDaysStayed()  const { return daysStayed; }
double Bill::getRoomRate()    const { return roomRate; }
double Bill::getDoctorFee()   const { return doctorFee; }
double Bill::getMedCharges()  const { return medCharges; }
double Bill::getTotalAmount() const { return totalAmount; }
bool   Bill::getIsPaid()      const { return isPaid; }

void Bill::setIsPaid(bool paid)         { isPaid     = paid; }
void Bill::setMedCharges(double m)      { medCharges = m; recalculate(); }

void Bill::recalculate() {
    totalAmount = (roomRate * daysStayed) + doctorFee + medCharges;
}

void Bill::displayInfo() const {
    cout << fixed << setprecision(2);
    cout << left
         << setw(10) << billID
         << setw(12) << patientID
         << setw(6)  << daysStayed
         << setw(10) << roomRate
         << setw(10) << doctorFee
         << setw(12) << medCharges
         << setw(12) << totalAmount
         << (isPaid ? "Paid" : "Unpaid") << "\n";
}
