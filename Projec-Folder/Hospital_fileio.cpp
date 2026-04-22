#include "Hospital.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
using namespace std;

//  SAVE

void Hospital::savePatients() const {
    ofstream f("patients.txt");
    if (!f) { cerr << "  [!] Cannot write patients.txt\n"; return; }
    for (int i = 0; i < patientCount; ++i) {
        Patient* p = patients[i];
        f << p->getPatientID()        << "|"
          << p->getName()             << "|"
          << p->getId()               << "|"
          << p->getPhone()            << "|"
          << p->getAge()              << "|"
          << p->getDiagnosis()        << "|"
          << p->getAdmitDate()        << "|"
          << p->getAssignedRoomNo()   << "|"
          << p->getAssignedDoctorID() << "|"
          << (p->getIsPaid() ? "1" : "0") << "\n";
    }
}

void Hospital::saveDoctors() const {
    ofstream f("doctors.txt");
    if (!f) { cerr << "  [!] Cannot write doctors.txt\n"; return; }
    for (int i = 0; i < doctorCount; ++i) {
        Doctor* d = doctors[i];
        f << d->getDoctorID()        << "|"
          << d->getName()            << "|"
          << d->getId()              << "|"
          << d->getPhone()           << "|"
          << d->getAge()             << "|"
          << d->getSpecialty()       << "|"
          << d->getConsultationFee() << "|"
          << d->getAvailableDays()   << "\n";
    }
}

void Hospital::saveRooms() const {
    ofstream f("rooms.txt");
    if (!f) { cerr << "  [!] Cannot write rooms.txt\n"; return; }
    for (int i = 0; i < roomCount; ++i) {
        Room* r = rooms[i];
        f << r->getRoomNo()              << "|"
          << r->getTypeString()          << "|"
          << (r->getIsOccupied() ? "1" : "0") << "|"
          << r->getOccupiedByPatientID() << "\n";
    }
}

void Hospital::saveAppointments() const {
    ofstream f("appointments.txt");
    if (!f) { cerr << "  [!] Cannot write appointments.txt\n"; return; }
    for (int i = 0; i < appointmentCount; ++i) {
        Appointment* a = appointments[i];
        f << a->getApptID()    << "|"
          << a->getPatientID() << "|"
          << a->getDoctorID()  << "|"
          << a->getDate()      << "|"
          << a->getTime()      << "|"
          << a->getStatusStr() << "\n";
    }
}

void Hospital::saveBills() const {
    ofstream f("bills.txt");
    if (!f) { cerr << "  [!] Cannot write bills.txt\n"; return; }
    for (int i = 0; i < billCount; ++i) {
        Bill* b = bills[i];
        f << b->getBillID()      << "|"
          << b->getPatientID()   << "|"
          << b->getDaysStayed()  << "|"
          << b->getRoomRate()    << "|"
          << b->getDoctorFee()   << "|"
          << b->getMedCharges()  << "|"
          << (b->getIsPaid() ? "1" : "0") << "\n";
    }
}

void Hospital::saveData() const {
    savePatients();
    saveDoctors();
    saveRooms();
    saveAppointments();
    saveBills();
    cout << "  [✓] All data saved successfully.\n";
}


//  LOAD

static vector<string> splitLine(const string& line, char delim = '|') {
    vector<string> tokens;
    stringstream ss(line);
    string tok;
    while (getline(ss, tok, delim)) tokens.push_back(tok);
    return tokens;
}

void Hospital::loadPatients() {
    ifstream f("patients.txt");
    if (!f) return;
    string line;
    while (getline(f, line)) {
        if (line.empty()) continue;
        auto t = splitLine(line);
        if (t.size() < 10) continue;
        if (patientCount >= MAX_PATIENTS) break;
        try {
            Patient* p = new Patient(
                t[1], t[2], t[3], stoi(t[4]),
                t[0], t[5], t[6], stoi(t[7]), t[8]
            );
            p->setIsPaid(t[9] == "1");
            patients[patientCount++] = p;
        } catch (...) {
            cerr << "  [!] Skipping corrupt patient record.\n";
        }
    }
}

void Hospital::loadDoctors() {
    ifstream f("doctors.txt");
    if (!f) return;
    string line;
    while (getline(f, line)) {
        if (line.empty()) continue;
        auto t = splitLine(line);
        if (t.size() < 8) continue;
        if (doctorCount >= MAX_DOCTORS) break;
        try {
            doctors[doctorCount++] = new Doctor(
                t[1], t[2], t[3], stoi(t[4]),
                t[0], t[5], stod(t[6]), t[7]
            );
        } catch (...) {
            cerr << "  [!] Skipping corrupt doctor record.\n";
        }
    }
}

void Hospital::loadRooms() {
    ifstream f("rooms.txt");
    if (!f) return;   // keep default rooms if no file
    string line;

    // Clear pre-populated rooms first
    for (int i = 0; i < roomCount; ++i) delete rooms[i];
    roomCount = 0;

    while (getline(f, line)) {
        if (line.empty()) continue;
        auto t = splitLine(line);
        if (t.size() < 3) continue;
        if (roomCount >= MAX_ROOMS) break;
        try {
            Room::RoomType rt = Room::stringToType(t[1]);
            Room* r = new Room(stoi(t[0]), rt);
            if (t[2] == "1") {
                r->setOccupied(true);
                r->setOccupiedByPatientID(t.size() > 3 ? t[3] : "");
            }
            rooms[roomCount++] = r;
        } catch (...) {
            cerr << "  [!] Skipping corrupt room record.\n";
        }
    }
}

void Hospital::loadAppointments() {
    ifstream f("appointments.txt");
    if (!f) return;
    string line;
    while (getline(f, line)) {
        if (line.empty()) continue;
        auto t = splitLine(line);
        if (t.size() < 6) continue;
        if (appointmentCount >= MAX_APPOINTMENTS) break;
        try {
            Appointment* a = new Appointment(t[0], t[1], t[2], t[3], t[4]);
            a->setStatus(Appointment::stringToStatus(t[5]));
            appointments[appointmentCount++] = a;
        } catch (...) {
            cerr << "  [!] Skipping corrupt appointment record.\n";
        }
    }
}

void Hospital::loadBills() {
    ifstream f("bills.txt");
    if (!f) return;
    string line;
    while (getline(f, line)) {
        if (line.empty()) continue;
        auto t = splitLine(line);
        if (t.size() < 7) continue;
        if (billCount >= MAX_BILLS) break;
        try {
            Bill* b = new Bill(t[0], t[1], stoi(t[2]),
                               stod(t[3]), stod(t[4]), stod(t[5]));
            b->setIsPaid(t[6] == "1");
            bills[billCount++] = b;
        } catch (...) {
            cerr << "  [!] Skipping corrupt bill record.\n";
        }
    }
}

void Hospital::loadData() {
    loadPatients();
    loadDoctors();
    loadRooms();
    loadAppointments();
    loadBills();
    cout << "  [✓] Data loaded: "
         << patientCount     << " patient(s), "
         << doctorCount      << " doctor(s), "
         << roomCount        << " room(s), "
         << appointmentCount << " appointment(s), "
         << billCount        << " bill(s).\n";
}
