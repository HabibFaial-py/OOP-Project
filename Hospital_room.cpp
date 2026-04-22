#include "Hospital.h"
#include <iostream>
using namespace std;

//  Room sub-menu

void Hospital::menuRoom() {
    int choice;
    do {
    	clearScreen();
        printHeader("ROOM MANAGEMENT");
        cout << "  1. View All Rooms\n"
             << "  2. Assign Room to Patient\n"
             << "  3. Release Room\n"
             << "  0. Back\n";
        printSeparator();
        choice = inputInt("  Choice: ");
        switch (choice) {
            case 1: viewAllRooms(); break;
            case 2: assignRoom();   break;
            case 3: releaseRoom();  break;
            case 0: break;
            default: cout << "  [!] Invalid option.\n";
        }
    } while (choice != 0);
}

// ── View All Rooms ─
void Hospital::viewAllRooms() {
    printHeader("ROOM STATUS");

    cout << "  Available Rates:\n"
         << "    General      : PKR 2,000 / day\n"
         << "    Semi-Private : PKR 4,000 / day\n"
         << "    Private      : PKR 7,000 / day\n\n";

    for (int i = 0; i < roomCount; ++i) {
        printSeparator();
        rooms[i]->displayInfo();
    }
    printSeparator();
    pause();
}

// ── Assign Room ─
void Hospital::assignRoom() {
    printHeader("ASSIGN ROOM");
    string pid = inputNonEmpty("  Patient ID : ");
    int pi = findPatientIndex(pid);
    if (pi == -1) { cout << "  [!] Patient not found.\n"; pause(); return; }

    if (patients[pi]->getAssignedRoomNo() != -1) {
        cout << "  [!] Patient already in Room " << patients[pi]->getAssignedRoomNo() << ".\n";
        pause(); return;
    }

    cout << "  Room Types: 1=General (100-109)  2=Semi-Private (200-209)  3=Private (300-309)\n";
    int rno = inputInt("  Enter Room Number: ");
    int ri  = findRoomIndex(rno);

    if (ri == -1) { cout << "  [!] Room not found.\n"; pause(); return; }
    if (rooms[ri]->getIsOccupied()) {
        cout << "  [!] Room " << rno << " is already occupied.\n"; pause(); return;
    }

    rooms[ri]->setOccupied(true);
    rooms[ri]->setOccupiedByPatientID(pid);
    patients[pi]->setAssignedRoomNo(rno);

    cout << "  [✓] Room " << rno << " (" << rooms[ri]->getTypeString()
         << ") assigned to " << pid << ".\n";
    pause();
}

// ── Release Room ──
void Hospital::releaseRoom() {
    printHeader("RELEASE ROOM");
    int rno = inputInt("  Enter Room Number: ");
    int ri  = findRoomIndex(rno);
    if (ri == -1) { cout << "  [!] Room not found.\n"; pause(); return; }

    if (!rooms[ri]->getIsOccupied()) {
        cout << "  [!] Room is already vacant.\n"; pause(); return;
    }

    string pid = rooms[ri]->getOccupiedByPatientID();
    rooms[ri]->setOccupied(false);
    rooms[ri]->setOccupiedByPatientID("");

    int pi = findPatientIndex(pid);
    if (pi != -1) patients[pi]->setAssignedRoomNo(-1);

    cout << "  [✓] Room " << rno << " released.\n";
    pause();
}
