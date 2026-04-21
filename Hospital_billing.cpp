#include "Hospital.h"
#include <iostream>
#include <iomanip>
using namespace std;

// ════════════════════════════════════════════════════════════
//  Billing sub-menu
// ════════════════════════════════════════════════════════════
void Hospital::menuBilling() {
    int choice;
    do {
        clearScreen();
        printHeader("BILLING MANAGEMENT");
        cout << "  1. Generate Bill\n"
             << "  2. View Bill by Patient ID\n"
             << "  3. Mark Bill as Paid\n"
             << "  0. Back\n";
        printSeparator();
        choice = inputInt("  Choice: ");
        switch (choice) {
            case 1: generateBill();      break;
            case 2: viewBillByPatient(); break;
            case 3: markBillPaid();      break;
            case 0: break;
            default: cout << "  [!] Invalid option.\n";
        }
    } while (choice != 0);
}

// ── Generate Bill ─────────────────────────────────────────
void Hospital::generateBill(const string& presetPID) {
    if (billCount >= MAX_BILLS) {
        cout << "  [!] Bill capacity reached.\n"; pause(); return;
    }
    printHeader("GENERATE BILL");

    string pid = presetPID.empty() ? inputNonEmpty("  Patient ID : ") : presetPID;
    int pi = findPatientIndex(pid);
    if (pi == -1) { cout << "  [!] Patient not found.\n"; pause(); return; }

    Patient* p = patients[pi];

    // Room rate
    double roomRate = 0;
    int    rno = p->getAssignedRoomNo();
    if (rno != -1) {
        int ri = findRoomIndex(rno);
        if (ri != -1) roomRate = rooms[ri]->getDailyCharge();
    }
    int days = inputInt("  Days Stayed  : ");
    while (days < 0) {
        cout << "  [!] Days cannot be negative.\n";
        days = inputInt("  Days Stayed  : ");
    }

    // Doctor fee
    double docFee = 0;
    string did = p->getAssignedDoctorID();
    if (!did.empty()) {
        int di = findDoctorIndex(did);
        if (di != -1) docFee = doctors[di]->getConsultationFee();
    }

    double meds = inputDouble("  Medication Charges (PKR): ");
    while (meds < 0) {
        cout << "  [!] Cannot be negative.\n";
        meds = inputDouble("  Medication Charges (PKR): ");
    }

    string bid = generateBillID();
    bills[billCount++] = new Bill(bid, pid, days, roomRate, docFee, meds);

    cout << "\n";
    printSeparator();
    bills[billCount - 1]->displayInfo();
    printSeparator();
    cout << "  [✓] Bill generated. ID: " << bid << "\n";
    pause();
}

// ── View Bill ─────────────────────────────────────────────
void Hospital::viewBillByPatient() {
    printHeader("VIEW BILL");
    string pid = inputNonEmpty("  Enter Patient ID: ");
    bool found = false;
    for (int i = 0; i < billCount; ++i) {
        if (bills[i]->getPatientID() == pid) {
            printSeparator();
            bills[i]->displayInfo();
            found = true;
        }
    }
    if (!found) cout << "  [!] No bills found for patient " << pid << ".\n";
    pause();
}

// ── Mark as Paid ──────────────────────────────────────────
void Hospital::markBillPaid() {
    printHeader("MARK BILL AS PAID");
    string bid = inputNonEmpty("  Enter Bill ID: ");
    int idx = findBillIndex(bid);
    if (idx == -1) { cout << "  [!] Bill not found.\n"; pause(); return; }

    if (bills[idx]->getIsPaid()) {
        cout << "  [!] Bill already marked as paid.\n"; pause(); return;
    }
    bills[idx]->setIsPaid(true);

    // Also update patient isPaid flag
    string pid = bills[idx]->getPatientID();
    int pi = findPatientIndex(pid);
    if (pi != -1) patients[pi]->setIsPaid(true);

    cout << "  [✓] Bill " << bid << " marked as PAID.\n";
    pause();
}
