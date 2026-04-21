#ifndef ROOM_H
#define ROOM_H

#include <string>
using namespace std;

class Room {
public:
    enum RoomType { GENERAL, SEMI_PRIVATE, PRIVATE };

private:
    int      roomNo;
    bool     isOccupied;
    double   dailyCharge;
    RoomType type;
    string   occupiedByPatientID;

public:
    Room();
    Room(int roomNo, RoomType type);

    // Getters
    int       getRoomNo()               const;
    bool      getIsOccupied()           const;
    double    getDailyCharge()          const;
    RoomType  getType()                 const;
    string    getTypeString()           const;
    string    getOccupiedByPatientID()  const;

    // Setters
    void setOccupied(bool occ);
    void setOccupiedByPatientID(const string& pid);

    void displayInfo() const;

    // Static charge lookup
    static double chargeForType(RoomType t);
    static string typeToString(RoomType t);
    static RoomType stringToType(const string& s);
};

#endif
