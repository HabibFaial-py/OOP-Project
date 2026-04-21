#ifndef PATIENT_H
#define PATIENT_H

#include "Person.h"
#include <string>
using namespace std;

class Patient : public Person {
private:
    string patientID;
    string diagnosis;
    string admitDate;
    int    assignedRoomNo;
    string assignedDoctorID;
    bool   isPaid;

public:
    Patient();
    Patient(string name, string id, string phone, int age,
            string patientID, string diagnosis, string admitDate,
            int roomNo, string doctorID);

    // Getters
    string getPatientID()       const;
    string getDiagnosis()       const;
    string getAdmitDate()       const;
    int    getAssignedRoomNo()  const;
    string getAssignedDoctorID() const;
    bool   getIsPaid()          const;

    // Setters
    void setPatientID(const string& pid);
    void setDiagnosis(const string& d);
    void setAdmitDate(const string& date);
    void setAssignedRoomNo(int roomNo);
    void setAssignedDoctorID(const string& docID);
    void setIsPaid(bool paid);

    void displayInfo() const override;
};

#endif
