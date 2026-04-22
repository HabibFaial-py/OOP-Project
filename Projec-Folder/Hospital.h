#ifndef HOSPITAL_H
#define HOSPITAL_H

#include "Patient.h"
#include "Doctor.h"
#include "Room.h"
#include "Appointment.h"
#include "Bill.h"

const int MAX_PATIENTS     = 100;
const int MAX_DOCTORS      = 50;
const int MAX_ROOMS        = 30;
const int MAX_APPOINTMENTS = 200;
const int MAX_BILLS        = 200;

class Hospital {
private:
    Patient**     patients;
    Doctor**      doctors;
    Room**        rooms;
    Appointment** appointments;
    Bill**        bills;

    int patientCount;
    int doctorCount;
    int roomCount;
    int appointmentCount;
    int billCount;


    string generatePatientID();
    string generateDoctorID();
    string generateApptID();
    string generateBillID();

    int findPatientIndex(const string& pid) const;
    int findDoctorIndex(const string& did)  const;
    int findRoomIndex(int roomNo)            const;
    int findApptIndex(const string& aid)    const;
    int findBillIndex(const string& bid)    const;

    bool patientIDExists(const string& pid) const;
    bool doctorIDExists(const string& did)  const;


    int    inputInt(const string& prompt);
    double inputDouble(const string& prompt);
    string inputNonEmpty(const string& prompt);


    void menuPatient();
    void menuDoctor();
    void menuAppointment();
    void menuRoom();
    void menuBilling();


    void addPatient();
    void viewAllPatients()    const;
    void searchPatient();
    void updatePatient();
    void dischargePatient();


    void addDoctor();
    void viewAllDoctors();
    void searchBySpecialty();
    void updateDoctorSchedule();


    void bookAppointment();
    void viewAppointments();
    void cancelAppointment();


    void viewAllRooms();
    void assignRoom();
    void releaseRoom();


    void generateBill(const string& patientID = "");
    void viewBillByPatient();
    void markBillPaid();


    void savePatients()      const;
    void saveDoctors()       const;
    void saveRooms()         const;
    void saveAppointments()  const;
    void saveBills()         const;

    void loadPatients();
    void loadDoctors();
    void loadRooms();
    void loadAppointments();
    void loadBills();

    // UI funcions
    void printHeader(const string& title) const;
    void printSeparator()     const;
    void pause()    const;
    void clearScreen() const;

public:
    Hospital();
    ~Hospital();

    void loadData();
    void saveData() const;
    void run();
};

#endif
