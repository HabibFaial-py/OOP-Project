#include "Hospital.h"
#include <iostream>
using namespace std;

void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void Hospital::run() {
    clearScreen();
    printHeader("HOSPITAL MANAGEMENT SYSTEM");
    cout << "  Welcome! Data loaded from previous session.\n";
    int choice;
    do {
        clearScreen();
        printHeader("MAIN MENU");
        cout << "  1. Patient Management\n"
             << "  2. Doctor Management\n"
             << "  3. Appointment Management\n"
             << "  4. Room Management\n"
             << "  5. Billing\n"
             << "  6. Save & Exit\n";
        printSeparator();
        choice = inputInt("  Choice: ");
        switch (choice) {
            case 1: menuPatient();     break;
            case 2: menuDoctor();      break;
            case 3: menuAppointment(); break;
            case 4: menuRoom();        break;
            case 5: menuBilling();     break;
            case 6:
                clearScreen();
                saveData();
                printHeader("GOODBYE");
                cout << "  All records saved. Goodbye!\n";
                printSeparator();
                break;
            default:
                cout << "  [!] Invalid option. Please choose 1-6.\n";
        }
    } while (choice != 6);
}
