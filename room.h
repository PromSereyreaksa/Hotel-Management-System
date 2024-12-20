// room.h
#ifndef ROOM_H
#define ROOM_H

#include <string>

class Room {
private:
    std::string roomID;
    std::string roomType;
    float price;
    bool isAvailable;

public:
    Room(const std::string &id, const std::string &type, float p, bool available);
    // Other member functions if needed
};

#endif
