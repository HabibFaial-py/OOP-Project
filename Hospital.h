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
void clearScreen();

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

    // ── ID generators ──────────────────────────────
    string generatePatientID();
    string generateDoctorID();
    string generateApptID();
    string generateBillID();

    // ── Lookup helpers ─────────────────────────────
    int findPatientIndex(const string& pid) const;
    int findDoctorIndex(const string& did)  const;
    int findRoomIndex(int roomNo)            const;
    int findApptIndex(const string& aid)    const;
    int findBillIndex(const string& bid)    const;

    bool patientIDExists(const string& pid) const;
    bool doctorIDExists(const string& did)  const;

    // ── Validation helpers ─────────────────────────
    int    inputInt(const string& prompt);
    double inputDouble(const string& prompt);
    string inputNonEmpty(const string& prompt);

    // ── Sub-menus ──────────────────────────────────
    void menuPatient();
    void menuDoctor();
    void menuAppointment();
    void menuRoom();
    void menuBilling();

    // ── Patient operations ─────────────────────────
    void addPatient();
    void viewAllPatients()    const;
    void searchPatient();
    void updatePatient();
    void dischargePatient();

    // ── Doctor operations ──────────────────────────
    void addDoctor();
    void viewAllDoctors();
    void searchBySpecialty();
    void updateDoctorSchedule();

    // ── Appointment operations ─────────────────────
    void bookAppointment();
    void viewAppointments();
    void cancelAppointment();

    // ── Room operations ────────────────────────────
    void viewAllRooms();
    void assignRoom();
    void releaseRoom();

    // ── Billing operations ─────────────────────────
    void generateBill(const string& patientID = "");
    void viewBillByPatient();
    void markBillPaid();

    // ── Persistence ───────────────────────────────
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

    // ── UI helpers ─────────────────────────────────
    void printHeader(const string& title) const;
    void printSeparator()                 const;
    void pause()                          const;

public:
    Hospital();
    ~Hospital();

    void loadData();
    void saveData() const;
    void run();
};

#endif
