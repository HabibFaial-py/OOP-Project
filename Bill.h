#ifndef BILL_H
#define BILL_H

#include <string>
using namespace std;

class Bill {
private:
    string billID;
    string patientID;
    int    daysStayed;
    double roomRate;
    double doctorFee;
    double medCharges;
    double totalAmount;
    bool   isPaid;

public:
    Bill();
    Bill(string billID, string patientID, int days,
         double roomRate, double doctorFee, double medCharges);

    // Getters
    string getBillID()      const;
    string getPatientID()   const;
    int    getDaysStayed()  const;
    double getRoomRate()    const;
    double getDoctorFee()   const;
    double getMedCharges()  const;
    double getTotalAmount() const;
    bool   getIsPaid()      const;

    // Setters
    void setIsPaid(bool paid);
    void setMedCharges(double m);

    void recalculate();
    void displayInfo() const;
};

#endif
