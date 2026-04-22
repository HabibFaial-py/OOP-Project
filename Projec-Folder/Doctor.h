#ifndef DOCTOR_H
#define DOCTOR_H

#include "Person.h"
#include <string>
using namespace std;

class Doctor : public Person {
private:
    string doctorID;
    string specialty;
    double consultationFee;
    string availableDays;   // e.g. "Mon,Wed,Fri"

public:
    Doctor();
    Doctor(string name, string id, string phone, int age,
           string doctorID, string specialty, double fee, string days);

    // Getters
    string getDoctorID()        const;
    string getSpecialty()       const;
    double getConsultationFee() const;
    string getAvailableDays()   const;

    // Setters
    void setDoctorID(const string& did);
    void setSpecialty(const string& s);
    void setConsultationFee(double fee);
    void setAvailableDays(const string& days);

    bool isAvailableOn(const string& day) const;

    void displayInfo() const override;
};

#endif
