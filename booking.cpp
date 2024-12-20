#include "booking.h"
#include "room.h"
#include <iostream>
#include <fstream>
#include <sstream>

Booking::Booking(const std::string& bookingID, const std::string& guestID, Room bookedRoom, 
                 const std::string& checkInDate, const std::string& checkOutDate, bool paymentStatus)
    : bookingID(bookingID), guestID(guestID), bookedRoom(bookedRoom), checkInDate(checkInDate), 
      checkOutDate(checkOutDate), paymentStatus(paymentStatus) {}

void Booking::bookRoom(const std::string& bookingID, const std::string& guestID, Room& bookedRoom, 
                       const std::string& checkInDate, const std::string& checkOutDate, bool paymentStatus) {
    std::ofstream outFile("reservations.csv", std::ios::app);  // Open the file in append mode
    outFile << bookingID << "," << guestID << "," << bookedRoom.roomID << "," 
            << bookedRoom.roomType << "," << bookedRoom.price << "," << checkInDate << "," 
            << checkOutDate << "," << paymentStatus << std::endl;
    outFile.close();
    std::cout << "Room booked successfully!" << std::endl;
}

void Booking::getBookingDetails(const std::string& bookingID) {
    std::ifstream inFile("reservations.csv");
    std::string line;
    while (std::getline(inFile, line)) {
        std::istringstream stream(line);
        std::string id, guestID, roomID, roomType, price, checkInDate, checkOutDate, paymentStatus;
        if (!std::getline(stream, id, ',') || 
            !std::getline(stream, guestID, ',') || 
            !std::getline(stream, roomID, ',') || 
            !std::getline(stream, roomType, ',') || 
            !std::getline(stream, price, ',') || 
            !std::getline(stream, checkInDate, ',') || 
            !std::getline(stream, checkOutDate, ',') || 
            !std::getline(stream, paymentStatus, ',')) {
            std::cerr << "Error reading line in file, skipping line." << std::endl;
            continue;  // Skip the malformed line
        }

        if (id == bookingID) {
            std::cout << "Booking ID: " << id << ", Guest ID: " << guestID << ", Room: " << roomType 
                      << ", Price: " << price << ", Check-in: " << checkInDate << ", Check-out: " 
                      << checkOutDate << ", Payment Status: " << paymentStatus << std::endl;
            return;
        }
    }
    std::cout << "Booking not found!" << std::endl;
}

void Booking::cancelBooking(const std::string& bookingID) {
    std::ifstream inFile("reservations.csv");
    std::ofstream tempFile("temp.csv");
    std::string line;
    
    while (std::getline(inFile, line)) {
        std::istringstream stream(line);
        std::string id, guestID, roomID, roomType, price, checkInDate, checkOutDate, paymentStatus;
        if (!std::getline(stream, id, ',') || 
            !std::getline(stream, guestID, ',') || 
            !std::getline(stream, roomID, ',') || 
            !std::getline(stream, roomType, ',') || 
            !std::getline(stream, price, ',') || 
            !std::getline(stream, checkInDate, ',') || 
            !std::getline(stream, checkOutDate, ',') || 
            !std::getline(stream, paymentStatus, ',')) {
            std::cerr << "Error reading line in file, skipping line." << std::endl;
            continue;  // Skip the malformed line
        }

        if (id != bookingID) {
            tempFile << line << std::endl;
        }
    }

    inFile.close();
    tempFile.close();

    remove("reservations.csv");
    rename("temp.csv", "reservations.csv");

    std::cout << "Booking canceled!" << std::endl;
}
