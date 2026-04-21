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

## 🛠️ How to Compile and Run

Make sure you have **g++/mingw32** (GCC) installed.

### Windows (MinGW)
```bash
mingw32-make //compiles all files
./hospital //Runs
```

> Requires C++11 or later. Add `-std=c++11` flag if needed.

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
## Test Cases

### TC1 — Add a New Patient
**Module:** Patient Management  
**Steps:**
1. Main menu → `1` (Patient Management) → `1` (Add New Patient)
2. Enter: Name = `Ali Hassan`, Phone = `03001234567`, Age = `35`, Diagnosis = `Typhoid`, Admit Date = `20/04/2026`

**Expected:** Patient added with auto-generated ID (e.g. `P001`). Confirmation message displayed.

---

### TC2 — Add Patient with Invalid Age (Validation)
**Module:** Patient Management  
**Steps:**
1. Main menu → `1` → `1` (Add New Patient)
2. Enter age as `0` → rejected. Enter `200` → rejected. Enter `25` → accepted.

**Expected:** System rejects `0` and `200` with an error message. Accepts `25` and proceeds normally.

---

### TC3 — Add a New Doctor
**Module:** Doctor Management  
**Steps:**
1. Main menu → `2` (Doctor Management) → `1` (Add Doctor)
2. Enter: Name = `Dr. Ayesha Raza`, Phone = `03211234567`, Age = `42`, Specialty = `Cardiology`, Fee = `2500`, Available Days = `Mon,Wed,Fri`

**Expected:** Doctor added with auto-generated ID (e.g. `D001`). Visible under View All Doctors.

---

### TC4 — Book Appointment on Available Day
**Module:** Appointment Management  
**Pre-condition:** TC1 patient (`P001`) and TC3 doctor (`D001`) must exist.  
**Steps:**
1. Main menu → `3` (Appointment Management) → `1` (Book Appointment)
2. Enter: Patient ID = `P001`, Doctor ID = `D001`, Date = `22/04/2026`, Day = `Wed`

**Expected:** Appointment booked (e.g. `A001`). Status set to `SCHEDULED`. No warning shown.

---

### TC5 — Book Appointment on Unavailable Day (Validation)
**Module:** Appointment Management  
**Pre-condition:** TC3 doctor (`D001`) available only on `Mon,Wed,Fri`.  
**Steps:**
1. Main menu → `3` → `1` (Book Appointment)
2. Enter valid Patient ID and Doctor ID, set Day = `Tue`
3. When prompted to book anyway, enter `n`

**Expected:** Warning shown with doctor's available days listed. Booking cancelled — no record added.

---

### TC6 — Assign Room and Generate Bill (Integration)
**Module:** Room Management + Billing  
**Pre-condition:** TC1 patient (`P001`) and TC3 doctor (`D001`) must exist.  
**Steps:**
1. Main menu → `4` (Room Management) → Assign Room → enter `P001`, assign room `101` (General, Rs. 1500/day)
2. Main menu → `5` (Billing) → Generate Bill → enter `P001`
3. Enter: Days Stayed = `3`, Med Charges = `500`

**Expected:** Bill generated correctly.
| Component | Calculation | Amount |
|---|---|---|
| Room charges | 1500 × 3 | Rs. 4500 |
| Doctor fee | — | Rs. 2500 |
| Medicine charges | — | Rs. 500 |
| **Total** | | **Rs. 7500** |

Bill status = `Unpaid`.

---

### TC7 — Cancel Appointment (+ Duplicate Cancel Guard)
**Module:** Appointment Management  
**Pre-condition:** TC4 appointment (`A001`) must exist with status `SCHEDULED`.  
**Steps:**
1. Main menu → `3` → `3` (Cancel Appointment) → enter `A001`
2. Attempt to cancel `A001` a second time

**Expected:** First cancel → status changes to `CANCELLED`. Second attempt → error: `Already cancelled.`

---

### TC8 — Save, Exit and Reload Data (Persistence)
**Module:** File I/O  
**Pre-condition:** Run TC1–TC7 in the same session first.  
**Steps:**
1. Main menu → `6` (Save & Exit)
2. Verify the following files are created in the project folder: `patients.txt`, `doctors.txt`, `rooms.txt`, `appointments.txt`, `bills.txt`
3. Relaunch the program: `./hospital`
4. View All Patients and View All Doctors to confirm records loaded

**Expected:** All records from the previous session are fully restored. Data counts match. No corrupt record warnings shown on startup.

## 📁 Project Structure

```
HospitalMS/
.
├── Appointment.cpp
├── Appointment.h
├── Bill.cpp
├── Bill.h
├── Doctor.cpp
├── Doctor.h
├── Hospital.h
├── Hospital_appointment.cpp
├── Hospital_billing.cpp
├── Hospital_core.cpp
├── Hospital_doctor.cpp
├── Hospital_fileio.cpp
├── Hospital_patient.cpp
├── Hospital_room.cpp
├── Hospital_run.cpp
├── Makefile
├── Patient.cpp
├── Patient.h
├── Person.cpp
├── Person.h
├── Room.cpp
├── Room.h
└── main.cpp
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
