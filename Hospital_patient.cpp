#include "Hospital.h"
#include <iostream>
#include <algorithm>
using namespace std;
//  Patient sub-menu
void Hospital::menuPatient() {
    int choice;
    do {
    	clearScreen();
        printHeader("PATIENT MANAGEMENT");
        cout << "  1. Add New Patient\n"
             << "  2. View All Patients\n"
             << "  3. Search Patient\n"
             << "  4. Update Patient Record\n"
             << "  5. Discharge Patient\n"
             << "  0. Back\n";
        printSeparator();
        choice = inputInt("  Choice: ");
        switch (choice) {
            case 1: addPatient();      break;
            case 2: viewAllPatients(); break;
            case 3: searchPatient();   break;
            case 4: updatePatient();   break;
            case 5: dischargePatient(); break;
            case 0: break;
            default: cout << "  [!] Invalid option.\n";
        }
    } while (choice != 0);
}

// ── Add Patient 
void Hospital::addPatient() {
    if (patientCount >= MAX_PATIENTS) {
        cout << "  [!] Patient capacity reached.\n"; pause(); return;
    }
    printHeader("ADD NEW PATIENT");

    string name  = inputNonEmpty("  Full Name      : ");
    string phone = inputNonEmpty("  Phone Number   : ");
    int    age   = inputInt     ("  Age            : ");
    while (age <= 0 || age > 150) {
        cout << "  [!] Enter a realistic age (1-150).\n";
        age = inputInt("  Age            : ");
    }
    string diag  = inputNonEmpty("  Diagnosis      : ");
    string date  = inputNonEmpty("  Admit Date (DD/MM/YYYY): ");

    string pid = generatePatientID();
    string sid = pid; // Person id == patientID for simplicity

    patients[patientCount++] = new Patient(name, sid, phone, age,
                                            pid, diag, date, -1, "");
    cout << "\n  [✓] Patient added successfully. ID: " << pid << "\n";
    pause();
}

// ── View All 
void Hospital::viewAllPatients() const {
    printHeader("ALL PATIENTS");
    if (patientCount == 0) { cout << "  No patients on record.\n"; pause(); return; }
    for (int i = 0; i < patientCount; ++i) {
        printSeparator();
        patients[i]->displayInfo();
    }
    printSeparator();
    pause();
}

// ── Search 
void Hospital::searchPatient() {
    printHeader("SEARCH PATIENT");
    cout << "  1. Search by Patient ID\n"
         << "  2. Search by Name\n";
    int c = inputInt("  Choice: ");

    if (c == 1) {
        string pid = inputNonEmpty("  Enter Patient ID: ");
        int idx = findPatientIndex(pid);
        if (idx == -1) { cout << "  [!] Not found.\n"; }
        else { printSeparator(); patients[idx]->displayInfo(); }
    } else if (c == 2) {
        string nm = inputNonEmpty("  Enter Name (partial ok): ");
        // lowercase comparison
        string nmLow = nm;
        transform(nmLow.begin(), nmLow.end(), nmLow.begin(), ::tolower);
        bool found = false;
        for (int i = 0; i < patientCount; ++i) {
            string pnLow = patients[i]->getName();
            transform(pnLow.begin(), pnLow.end(), pnLow.begin(), ::tolower);
            if (pnLow.find(nmLow) != string::npos) {
                printSeparator(); patients[i]->displayInfo(); found = true;
            }
        }
        if (!found) cout << "  [!] No match found.\n";
    } else {
        cout << "  [!] Invalid option.\n";
    }
    pause();
}

// ── Update
void Hospital::updatePatient() {
    printHeader("UPDATE PATIENT RECORD");
    string pid = inputNonEmpty("  Enter Patient ID: ");
    int idx = findPatientIndex(pid);
    if (idx == -1) { cout << "  [!] Patient not found.\n"; pause(); return; }

    Patient* p = patients[idx];
    cout << "  Leave blank to keep current value.\n\n";

    auto updateField = [](const string& prompt, const string& cur) {
        cout << prompt << " [" << cur << "]: ";
        string v; getline(cin, v);
        return v.empty() ? cur : v;
    };

    p->setName     (updateField("  Name",      p->getName()));
    p->setPhone    (updateField("  Phone",     p->getPhone()));
    p->setDiagnosis(updateField("  Diagnosis", p->getDiagnosis()));

    cout << "  Age [" << p->getAge() << "] (0=keep): ";
    string ageStr; getline(cin, ageStr);
    if (!ageStr.empty() && ageStr != "0") {
        try { int a = stoi(ageStr); if (a>0&&a<=150) p->setAge(a); }
        catch(...) {}
    }
    p->setAssignedDoctorID(updateField("  Doctor ID", p->getAssignedDoctorID()));
    cout << "  [✓] Record updated.\n";
    pause();
}

// ── Discharge 
void Hospital::dischargePatient() {
    printHeader("DISCHARGE PATIENT");
    string pid = inputNonEmpty("  Enter Patient ID: ");
    int idx = findPatientIndex(pid);
    if (idx == -1) { cout << "  [!] Patient not found.\n"; pause(); return; }

    Patient* p = patients[idx];

    // Release room
    int rno = p->getAssignedRoomNo();
    if (rno != -1) {
        int ri = findRoomIndex(rno);
        if (ri != -1) {
            rooms[ri]->setOccupied(false);
            rooms[ri]->setOccupiedByPatientID("");
            cout << "  [✓] Room " << rno << " released.\n";
        }
        p->setAssignedRoomNo(-1);
    }

    // Prompt bill generation
    cout << "  Generate bill for this patient? (y/n): ";
    string yn; getline(cin, yn);
    if (yn == "y" || yn == "Y") {
        generateBill(pid);
    }

    // Remove patient from array
    delete patients[idx];
    for (int i = idx; i < patientCount - 1; ++i)
        patients[i] = patients[i+1];
    --patientCount;
    cout << "  [✓] Patient discharged and removed from system.\n";
    pause();
}
