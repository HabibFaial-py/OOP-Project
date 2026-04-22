#include "Room.h"
#include <iostream>
#include <iomanip>
using namespace std;

// Static charge lookup
double Room::chargeForType(RoomType t) {
    switch (t) {
        case GENERAL:      return 1500.0;
        case SEMI_PRIVATE: return 3000.0;
        case PRIVATE:      return 5000.0;
    }
    return 1500.0;
}

string Room::typeToString(RoomType t) {
    switch (t) {
        case GENERAL:      return "GENERAL";
        case SEMI_PRIVATE: return "SEMI_PRIVATE";
        case PRIVATE:      return "PRIVATE";
    }
    return "GENERAL";
}

Room::RoomType Room::stringToType(const string& s) {
    if (s == "SEMI_PRIVATE") return SEMI_PRIVATE;
    if (s == "PRIVATE")      return PRIVATE;
    return GENERAL;
}

Room::Room()
    : roomNo(0), isOccupied(false), dailyCharge(0.0),
      type(GENERAL), occupiedByPatientID("") {}

Room::Room(int roomNo, RoomType type)
    : roomNo(roomNo), isOccupied(false),
      dailyCharge(chargeForType(type)), type(type),
      occupiedByPatientID("") {}

int          Room::getRoomNo()              const { return roomNo; }
bool         Room::getIsOccupied()          const { return isOccupied; }
double       Room::getDailyCharge()         const { return dailyCharge; }
Room::RoomType Room::getType()              const { return type; }
string       Room::getTypeString()          const { return typeToString(type); }
string       Room::getOccupiedByPatientID() const { return occupiedByPatientID; }

void Room::setOccupied(bool occ)                        { isOccupied          = occ; }
void Room::setOccupiedByPatientID(const string& pid)    { occupiedByPatientID = pid; }

void Room::displayInfo() const {
    cout << left
         << setw(8)  << roomNo
         << setw(14) << typeToString(type)
         << setw(12) << fixed << setprecision(2) << dailyCharge
         << setw(10) << (isOccupied ? "Occupied" : "Free")
         << occupiedByPatientID << "\n";
}
