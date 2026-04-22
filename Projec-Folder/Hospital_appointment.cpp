#include "Hospital.h"
#include <iostream>
using namespace std;

void Hospital::menuAppointment() {
    int choice;
    do {
    	clearScreen();
        printHeader("APPOINTMENT MANAGEMENT");
        cout << "  1. Book Appointment\n"
             << "  2. View All Appointments\n"
             << "  3. Cancel Appointment\n"
             << "  0. Back\n";
        printSeparator();
        choice = inputInt("  Choice: ");
        switch (choice) {
            case 1: bookAppointment();  break;
            case 2: viewAppointments(); break;
            case 3: cancelAppointment(); break;
            case 0: break;
            default: cout << "  [!] Invalid option.\n";
        }
    } while (choice != 0);
}

// ── Book Appointment 
void Hospital::bookAppointment() {
    if (appointmentCount >= MAX_APPOINTMENTS) {
        cout << "  [!] Appointment capacity reached.\n"; pause(); return;
    }
    printHeader("BOOK APPOINTMENT");

    string pid = inputNonEmpty("  Patient ID : ");
    if (findPatientIndex(pid) == -1) {
        cout << "  [!] Patient not found.\n"; pause(); return;
    }

    string did = inputNonEmpty("  Doctor ID  : ");
    int di = findDoctorIndex(did);
    if (di == -1) {
        cout << "  [!] Doctor not found.\n"; pause(); return;
    }

    string date = inputNonEmpty("  Date (DD/MM/YYYY): ");

    // Extract day-of-week name from user or ask separately
    cout << "  Day of week (e.g. Mon): ";
    string day; getline(cin, day);

    // Check availability
    if (!doctors[di]->isAvailableOn(day)) {
        cout << "  [!] Doctor " << did << " is NOT available on " << day << ".\n"
             << "      Available: " << doctors[di]->getAvailableDays() << "\n";
        cout << "  Book anyway? (y/n): ";
        string yn; getline(cin, yn);
        if (yn != "y" && yn != "Y") { pause(); return; }
    }

    string time = inputNonEmpty("  Time (HH:MM): ");
    string aid  = generateApptID();

    appointments[appointmentCount++] = new Appointment(aid, pid, did, date, time);

    // Update patient's assigned doctor if not set
    int pi = findPatientIndex(pid);
    if (pi != -1 && patients[pi]->getAssignedDoctorID().empty())
        patients[pi]->setAssignedDoctorID(did);

    cout << "  [✓] Appointment booked. ID: " << aid << "\n";
    pause();
}

// ── View All 
void Hospital::viewAppointments() {
    printHeader("APPOINTMENT SCHEDULE");
    if (appointmentCount == 0) { cout << "  No appointments on record.\n"; pause(); return; }

    cout << "  Filter by Patient ID (blank = all): ";
    string filter; getline(cin, filter);

    bool found = false;
    for (int i = 0; i < appointmentCount; ++i) {
        if (filter.empty() || appointments[i]->getPatientID() == filter) {
            printSeparator();
            appointments[i]->displayInfo();
            found = true;
        }
    }
    if (!found) cout << "  [!] No matching appointments.\n";
    printSeparator();
    pause();
}

// ── Cancel Appointment
void Hospital::cancelAppointment() {
    printHeader("CANCEL APPOINTMENT");
    string aid = inputNonEmpty("  Enter Appointment ID: ");
    int idx = findApptIndex(aid);
    if (idx == -1) { cout << "  [!] Appointment not found.\n"; pause(); return; }

    if (appointments[idx]->getStatus() == Appointment::CANCELLED) {
        cout << "  [!] Already cancelled.\n"; pause(); return;
    }
    appointments[idx]->setStatus(Appointment::CANCELLED);
    cout << "  [✓] Appointment " << aid << " cancelled.\n";
    pause();
}
