#include "room.h"
#include <iostream>

Room::Room(const std::string& roomID, const std::string& roomType, float price, bool isAvailable)
    : roomID(roomID), roomType(roomType), price(price), isAvailable(isAvailable) {}

void Room::setRoomStatus(bool status) {
    isAvailable = status;
    std::cout << "Room availability status updated!" << std::endl;
}
