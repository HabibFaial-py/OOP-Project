#include "Hospital.h"
#include <iostream>
#include <iomanip>
using namespace std;
//  Billing sub-menu
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

// ── Generate Bill 
void Hospital::generateBill(const string& presetPID) {
    if (billCount >= MAX_BILLS) {
        cout << "  [!] Bill capacity reached.\n"; pause(); return;
    }
    printHeader("GENERATE BILL");

    string pid = presetPID.empty() ? inputNonEmpty("  Patient ID : ") : presetPID;
    int pi = findPatientIndex(pid);
    if (pi == -1) { cout << "  [!] Patient not found.\n"; pause(); return; }

    Patient* p = patients[pi];

    // ── Step 1: Room rate (auto from assigned room) 
    double roomRate  = 0.0;
    int    rno       = p->getAssignedRoomNo();
    string roomLabel = "None";

    if (rno != -1) {
        int ri = findRoomIndex(rno);
        if (ri != -1) {
            roomRate  = rooms[ri]->getDailyCharge();
            roomLabel = "Room " + to_string(rno) + " [" + rooms[ri]->getTypeString() + "]"
                        + "  PKR " + to_string((int)roomRate) + "/day";
        }
    }
    cout << "  Assigned Room  : " << roomLabel << "\n";

    // ── Step 2: Days stayed (user enters) 
    int days = inputInt("  Days Stayed   : ");
    while (days < 0) {
        cout << "  [!] Days cannot be negative.\n";
        days = inputInt("  Days Stayed   : ");
    }
    double roomCost = roomRate * days;   // <-- auto calculated

    // ── Step 3: Doctor fee (auto from assigned doctor)
    double docFee   = 0.0;
    string docLabel = "None";
    string did      = p->getAssignedDoctorID();
    if (!did.empty()) {
        int di = findDoctorIndex(did);
        if (di != -1) {
            docFee   = doctors[di]->getConsultationFee();
            docLabel = did + " - " + doctors[di]->getName();
        }
    }
    cout << "  Doctor         : " << docLabel << "\n";

    // ── Step 4: Medication charges (user enters) 
    double meds = inputDouble("  Medication Charges (PKR): ");
    while (meds < 0) {
        cout << "  [!] Cannot be negative.\n";
        meds = inputDouble("  Medication Charges (PKR): ");
    }

    // ── Step 5: Create bill (total = roomCost + docFee + meds) ──
    string bid = generateBillID();
    // Pass roomRate (per day); Bill::recalculate() does roomRate * daysStayed internally
    bills[billCount++] = new Bill(bid, pid, days, roomRate, docFee, meds);
    Bill* b = bills[billCount - 1];

    // ── Step 6: Print itemized receipt 
    cout << "\n";
    printSeparator();
    cout << "  BILL RECEIPT\n";
    printSeparator();
    cout << "  Bill ID        : " << bid                    << "\n"
         << "  Patient ID     : " << pid                    << "\n"
         << "  Patient Name   : " << p->getName()           << "\n"
         << "  Admit Date     : " << p->getAdmitDate()      << "\n";
    printSeparator();
    cout << fixed << setprecision(2);
    cout << "  Room Cost      : PKR " << setw(8) << roomRate
         << "  x  " << days << " day(s)  =  PKR " << roomCost << "\n"
         << "  Doctor Fee     : PKR " << setw(8) << docFee    << "\n"
         << "  Medication     : PKR " << setw(8) << meds      << "\n";
    printSeparator();
    cout << "  TOTAL AMOUNT   : PKR " << b->getTotalAmount() << "\n"
         << "  Status         : UNPAID\n";
    printSeparator();
    cout << "  [OK] Bill " << bid << " saved.\n";
    saveData();
    pause();
}

// ── View Bill 
void Hospital::viewBillByPatient() {
    printHeader("VIEW BILL");
    string pid = inputNonEmpty("  Enter Patient ID: ");
    bool found = false;
    for (int i = 0; i < billCount; ++i) {
        if (bills[i]->getPatientID() == pid) {
            Bill* b = bills[i];
            double roomCost = b->getRoomRate() * b->getDaysStayed();
            printSeparator();
            cout << "  Bill ID        : " << b->getBillID()    << "\n"
                 << "  Patient ID     : " << b->getPatientID() << "\n";
            printSeparator();
            cout << fixed << setprecision(2);
            cout << "  Room Cost      : PKR " << setw(8) << b->getRoomRate()
                 << "  x  " << b->getDaysStayed() << " day(s)  =  PKR " << roomCost << "\n"
                 << "  Doctor Fee     : PKR " << setw(8) << b->getDoctorFee()  << "\n"
                 << "  Medication     : PKR " << setw(8) << b->getMedCharges() << "\n";
            printSeparator();
            cout << "  TOTAL AMOUNT   : PKR " << b->getTotalAmount() << "\n"
                 << "  Status         : " << (b->getIsPaid() ? "PAID" : "UNPAID") << "\n";
            printSeparator();
            found = true;
        }
    }
    if (!found) cout << "  [!] No bills found for patient " << pid << ".\n";
    pause();
}

// ── Mark as Paid 
void Hospital::markBillPaid() {
    printHeader("MARK BILL AS PAID");
    string bid = inputNonEmpty("  Enter Bill ID: ");
    int idx = findBillIndex(bid);
    if (idx == -1) { cout << "  [!] Bill not found.\n"; pause(); return; }

    if (bills[idx]->getIsPaid()) {
        cout << "  [!] Bill already marked as paid.\n"; pause(); return;
    }
    bills[idx]->setIsPaid(true);

    string pid = bills[idx]->getPatientID();
    int pi = findPatientIndex(pid);
    if (pi != -1) patients[pi]->setIsPaid(true);

    cout << "  [OK] Bill " << bid << " marked as PAID.\n";
    saveData();
    pause();
}
