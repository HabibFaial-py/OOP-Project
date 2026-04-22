#include "Hospital.h"
#include <iostream>
#include <algorithm>
using namespace std;
//  Doctor sub-menu
void Hospital::menuDoctor() {
    int choice;
    do {
    	clearScreen();
        printHeader("DOCTOR MANAGEMENT");
        cout << "  1. Add New Doctor\n"
             << "  2. View All Doctors\n"
             << "  3. Search by Specialty\n"
             << "  4. Update Schedule / Details\n"
             << "  0. Back\n";
        printSeparator();
        choice = inputInt("  Choice: ");
        switch (choice) {
            case 1: addDoctor();            break;
            case 2: viewAllDoctors();       break;
            case 3: searchBySpecialty();    break;
            case 4: updateDoctorSchedule(); break;
            case 0: break;
            default: cout << "  [!] Invalid option.\n";
        }
    } while (choice != 0);
}

// ── Add Doctor
void Hospital::addDoctor() {
    if (doctorCount >= MAX_DOCTORS) {
        cout << "  [!] Doctor capacity reached.\n"; pause(); return;
    }
    printHeader("ADD NEW DOCTOR");

    string name  = inputNonEmpty("  Full Name       : ");
    string phone = inputNonEmpty("  Phone Number    : ");
    int    age   = inputInt     ("  Age             : ");
    while (age <= 0 || age > 100) {
        cout << "  [!] Enter a realistic age.\n";
        age = inputInt("  Age             : ");
    }
    string spec  = inputNonEmpty("  Specialty        : ");
    double fee   = inputDouble  ("  Consultation Fee: ");
    while (fee < 0) {
        cout << "  [!] Fee cannot be negative.\n";
        fee = inputDouble("  Consultation Fee: ");
    }
    cout << "  Available Days (e.g. Mon,Wed,Fri): ";
    string days; getline(cin, days);
    if (days.empty()) days = "Mon,Tue,Wed,Thu,Fri";

    string did = generateDoctorID();
    doctors[doctorCount++] = new Doctor(name, did, phone, age, did, spec, fee, days);
    cout << "\n  [✓] Doctor added. ID: " << did << "\n";
    pause();
}

// ── View All 
void Hospital::viewAllDoctors() {
    printHeader("ALL DOCTORS");
    if (doctorCount == 0) { cout << "  No doctors on record.\n"; pause(); return; }
    for (int i = 0; i < doctorCount; ++i) {
        printSeparator();
        doctors[i]->displayInfo();
    }
    printSeparator();
    pause();
}

// ── Search by Specialty 
void Hospital::searchBySpecialty() {
    printHeader("SEARCH BY SPECIALTY");
    string spec = inputNonEmpty("  Enter Specialty (partial ok): ");
    string specLow = spec;
    transform(specLow.begin(), specLow.end(), specLow.begin(), ::tolower);

    bool found = false;
    for (int i = 0; i < doctorCount; ++i) {
        string sLow = doctors[i]->getSpecialty();
        transform(sLow.begin(), sLow.end(), sLow.begin(), ::tolower);
        if (sLow.find(specLow) != string::npos) {
            printSeparator(); doctors[i]->displayInfo(); found = true;
        }
    }
    if (!found) cout << "  [!] No doctors found for that specialty.\n";
    pause();
}

// ── Update Schedule 
void Hospital::updateDoctorSchedule() {
    printHeader("UPDATE DOCTOR");
    string did = inputNonEmpty("  Enter Doctor ID: ");
    int idx = findDoctorIndex(did);
    if (idx == -1) { cout << "  [!] Doctor not found.\n"; pause(); return; }

    Doctor* d = doctors[idx];
    cout << "  Leave blank to keep current value.\n\n";

    auto upd = [](const string& prompt, const string& cur) {
        cout << prompt << " [" << cur << "]: ";
        string v; getline(cin, v);
        return v.empty() ? cur : v;
    };

    d->setName         (upd("  Name",           d->getName()));
    d->setPhone        (upd("  Phone",          d->getPhone()));
    d->setSpecialty    (upd("  Specialty",      d->getSpecialty()));
    d->setAvailableDays(upd("  Available Days", d->getAvailableDays()));

    cout << "  Fee [" << d->getConsultationFee() << "] (0=keep): ";
    string fs; getline(cin, fs);
    if (!fs.empty() && fs != "0") {
        try { double f = stod(fs); if (f >= 0) d->setConsultationFee(f); }
        catch(...) {}
    }
    cout << "  [✓] Doctor record updated.\n";
    pause();
}
