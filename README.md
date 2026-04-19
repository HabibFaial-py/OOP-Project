# 🏥 Hospital Management System

A console-based C++ application to manage core hospital operations including patient registration, doctor records, appointment scheduling, room allocation, and billing. Built entirely on Object-Oriented Programming principles with persistent file-based storage.

---

## 👥 Group Members

| Name | Student ID |
|------|------------|
| Habib Faisal | 25K-0690 |
| Muhammad Arif | 25K-0866 |

---

## 📋 Use Cases

1. **Patient Registration** — A receptionist registers a new patient by entering their name, age, contact details, and diagnosis. The patient is assigned a unique ID and optionally allocated an available room.

2. **Doctor Lookup** — Staff can search for a doctor by specialty (e.g. Cardiology, Orthopedics) to check availability, consultation fee, and working days before scheduling.

3. **Appointment Booking** — An appointment is booked between a specific patient and doctor for a given date and time. The system prevents double-booking the same doctor at the same slot.

4. **Patient Discharge** — When a patient is discharged, their record is updated and their assigned room is automatically released and marked available for the next patient.

5. **Billing & Invoice** — A bill is generated for a patient by combining room charges, doctor consultation fee, and any additional charges. The bill can be marked as paid and saved to file.

6. **Record Search** — Staff can search for any patient by name or ID, or filter doctors by specialty, to quickly retrieve and update records.

7. **Data Persistence** — All records (patients, doctors, appointments, rooms, bills) are saved to text files on exit and automatically reloaded when the program is restarted — no data is lost between sessions.

8. **Room Management** — Staff can view all rooms with their type (General / ICU / Private), current occupancy status, and daily charge rate, and manually assign or release rooms as needed.

---

## 🛠️ How to Compile

Make sure you have **g++** (GCC) installed.

### Linux / macOS
```bash
g++ -o HospitalMS main.cpp Person.cpp Patient.cpp Doctor.cpp Appointment.cpp Room.cpp Bill.cpp HospitalSystem.cpp
```

### Windows (MinGW)
```bash
g++ -o HospitalMS.exe main.cpp Person.cpp Patient.cpp Doctor.cpp Appointment.cpp Room.cpp Bill.cpp HospitalSystem.cpp
```

> Requires C++11 or later. Add `-std=c++11` flag if needed.

---

## ▶️ How to Run

### Linux / macOS
```bash
./HospitalMS
```

### Windows
```bash
HospitalMS.exe
```

The program will automatically load existing data from the text files (`patients.txt`, `doctors.txt`, `appointments.txt`, `rooms.txt`, `bills.txt`) if they exist.

---

## 📖 How to Use the System

Once launched, you will see the main menu:

```
===== HOSPITAL MANAGEMENT SYSTEM =====
1. Patient Management
2. Doctor Management
3. Appointment Management
4. Room Management
5. Billing
6. Save & Exit
```

Navigate by entering the number corresponding to your choice and pressing **Enter**. Each sub-menu provides further options.

### Quick Guide

| Module | What You Can Do |
|--------|----------------|
| Patient Management | Add, view, search, update, discharge patients |
| Doctor Management | Add, view, search by specialty, update doctor info |
| Appointment Management | Book, view, cancel appointments; view by patient |
| Room Management | View rooms, assign to patient, release room |
| Billing | Generate bill, view bill, mark as paid, view all bills |
| Save & Exit | Saves all data to files before exiting |

> Always use **option 6 (Save & Exit)** to quit — this ensures all records are saved properly.

---

## 📁 Project Structure

```
HospitalMS/
├── main.cpp
├── Person.h            Person.cpp          ← abstract base class
├── Patient.h           Patient.cpp         ← derived from Person
├── Doctor.h            Doctor.cpp          ← derived from Person
├── Appointment.h       Appointment.cpp
├── Room.h              Room.cpp
├── Bill.h              Bill.cpp            ← billing module
├── HospitalSystem.h    HospitalSystem.cpp  ← main controller
├── patients.txt
├── doctors.txt
├── appointments.txt
├── rooms.txt
└── bills.txt
```

---

## ⚙️ OOP Concepts Used

| Concept | Implementation |
|---------|---------------|
| Classes & Objects | `Person`, `Patient`, `Doctor`, `Appointment`, `Room`, `Bill`, `HospitalSystem` |
| Encapsulation | All data members are `private`; accessed via public getters/setters |
| Inheritance | `Patient` and `Doctor` both inherit from abstract base class `Person` |
| Polymorphism | `displayInfo()` is `virtual` in `Person` and overridden in `Patient` and `Doctor` |
| Abstraction | `Person` has a pure virtual function (`displayInfo() = 0`) — cannot be instantiated |

---

## ⚠️ Assumptions & Limitations

- The system is **console-based only** — no GUI.
- Data is stored in **plain text files**; no database is used.
- A maximum number of patients, doctors, rooms, and appointments may be defined using fixed-size arrays (or vectors if STL is permitted).
- Room numbers are assumed to be **pre-initialized** at program startup (e.g. 10 rooms of different types).
- The billing module calculates totals based on **room daily charge × days admitted** plus the doctor's consultation fee; no pharmacy/medicine charges are tracked.
- Input validation covers empty fields and type mismatches but does **not** handle all edge cases.
- The program does not support **concurrent access** (single-user only).
- Date and time are stored as **strings** — no calendar validation is performed.
