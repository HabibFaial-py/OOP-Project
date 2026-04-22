#include "Hospital.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <algorithm>
#include <limits>
using namespace std;


//  Constructor / Destructor
// ════════════════════════════════════════════════════════════
Hospital::Hospital()
    : patientCount(0), doctorCount(0), roomCount(0),
      appointmentCount(0), billCount(0)
{
    patients     = new Patient*[MAX_PATIENTS];
    doctors      = new Doctor*[MAX_DOCTORS];
    rooms        = new Room*[MAX_ROOMS];
    appointments = new Appointment*[MAX_APPOINTMENTS];
    bills        = new Bill*[MAX_BILLS];


    for (int i = 0; i < 10; ++i)
        rooms[roomCount++] = new Room(100 + i, Room::GENERAL);
    for (int i = 0; i < 10; ++i)
        rooms[roomCount++] = new Room(200 + i, Room::SEMI_PRIVATE);
    for (int i = 0; i < 10; ++i)
        rooms[roomCount++] = new Room(300 + i, Room::PRIVATE);
}

Hospital::~Hospital() {
    for (int i = 0; i < patientCount; ++i) delete patients[i];
    for (int i = 0; i < doctorCount;    ++i) delete doctors[i];
    for (int i = 0; i < roomCount;    ++i) delete rooms[i];
    for (int i = 0; i < appointmentCount; ++i) delete appointments[i];
    for (int i = 0; i < billCount;    ++i) delete bills[i];

    delete[] patients;
    delete[] doctors;
    delete[] rooms;
    delete[] appointments;
    delete[] bills;
}


//  ID Generators

string Hospital::generatePatientID() {
    return "P" + to_string(1000 + patientCount + 1);
}
string Hospital::generateDoctorID() {
    return "D" + to_string(2000 + doctorCount + 1);
}
string Hospital::generateApptID() {
    return "A" + to_string(3000 + appointmentCount + 1);
}
string Hospital::generateBillID() {
    return "B" + to_string(4000 + billCount + 1);
}

//  Lookup helpers

int Hospital::findPatientIndex(const string& pid) const {
    for (int i = 0; i < patientCount; ++i)
        if (patients[i]->getPatientID() == pid) return i;
    return -1;
}
int Hospital::findDoctorIndex(const string& did) const {
    for (int i = 0; i < doctorCount; ++i)
        if (doctors[i]->getDoctorID() == did) return i;
    return -1;
}
int Hospital::findRoomIndex(int roomNo) const {
    for (int i = 0; i < roomCount; ++i)
        if (rooms[i]->getRoomNo() == roomNo) return i;
    return -1;
}
int Hospital::findApptIndex(const string& aid) const {
    for (int i = 0; i < appointmentCount; ++i)
        if (appointments[i]->getApptID() == aid) return i;
    return -1;
}
int Hospital::findBillIndex(const string& bid) const {
    for (int i = 0; i < billCount; ++i)
        if (bills[i]->getBillID() == bid) return i;
    return -1;
}
bool Hospital::patientIDExists(const string& pid) const {
    return findPatientIndex(pid) != -1;
}
bool Hospital::doctorIDExists(const string& did) const {
    return findDoctorIndex(did) != -1;
}


//  Validated input helpers

int Hospital::inputInt(const string& prompt) {
    while (true) {
        cout << prompt;
        string line;
        if (!getline(cin, line)) {
            // EOF — just return 0 to break loops
            return 0;
        }
        if (line.empty()) continue;
        try {
            size_t pos;
            int val = stoi(line, &pos);
            // allow trailing spaces
            while (pos < line.size() && isspace(line[pos])) pos++;
            if (pos == line.size()) return val;
        } catch (...) {}
        cout << "  [!] Invalid input. Please enter a whole number.\n";
    }
}

double Hospital::inputDouble(const string& prompt) {
    while (true) {
        cout << prompt;
        string line;
        if (!getline(cin, line)) return 0.0;
        if (line.empty()) continue;
        try {
            size_t pos;
            double val = stod(line, &pos);
            while (pos < line.size() && isspace(line[pos])) pos++;
            if (pos == line.size()) return val;
        } catch (...) {}
        cout << "  [!] Invalid input. Please enter a numeric value.\n";
    }
}

string Hospital::inputNonEmpty(const string& prompt) {
    string val;
    while (val.empty()) {
        cout << prompt;
        if (!getline(cin, val)) return "N/A";  // EOF fallback
        if (val.empty()) cout << "  [!] Input cannot be empty.\n";
    }
    return val;
}


void Hospital::printSeparator() const {
    cout << "  " << string(56, '=') << "\n";
}
void Hospital::printHeader(const string& title) const {
    cout << "\n";
    printSeparator();
    int pad = (56 - (int)title.size()) / 2;
    cout << "  " << string(pad, ' ') << title << "\n";
    printSeparator();
}
void Hospital::pause() const {
    cout << "\n  Press ENTER to continue...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}
void Hospital::clearScreen() const {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}
