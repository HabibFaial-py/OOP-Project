#ifndef APPOINTMENT_H
#define APPOINTMENT_H

#include <string>
using namespace std;

class Appointment {
public:
    enum Status { SCHEDULED, COMPLETED, CANCELLED };

private:
    string apptID;
    string patientID;
    string doctorID;
    string date;
    string time;
    Status status;

public:
    Appointment();
    Appointment(string apptID, string patientID, string doctorID,
                string date, string time);

    // Getters
    string getApptID()    const;
    string getPatientID() const;
    string getDoctorID()  const;
    string getDate()      const;
    string getTime()      const;
    Status getStatus()    const;
    string getStatusStr() const;

    // Setters
    void setStatus(Status s);

    void displayInfo() const;

    static string statusToString(Status s);
    static Status stringToStatus(const string& s);
};

#endif
