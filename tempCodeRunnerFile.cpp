#include <iostream>
#include <string>
#include "guestprofile.h"
#include "booking.h"
#include "room.h"

int main() {
    int choice;
    std::string guestID, name, contactInfo, roomID, roomType, checkInDate, checkOutDate, bookingID;
    float price;
    bool isAvailable, paymentStatus;

    // Create Room Object for testing
    Room room1("101", "Single", 100.0f, true);  // Example room data

    while (true) {
        std::cout << "Hotel Management System Menu\n";
        std::cout << "1. Create Guest Profile\n";
        std::cout << "2. View Guest Profile\n";
        std::cout << "3. Book Room\n";
        std::cout << "4. Cancel Reservation\n";
        std::cout << "0. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1: {
                // Declare the guest profile object within the case block
                std::cout << "Enter Guest ID: ";
                std::cin >> guestID;
                std::cout << "Enter Name: ";
                std::cin >> name;
                std::cout << "Enter Contact Info: ";
                std::cin >> contactInfo;

                GuestProfile guest(guestID, name, contactInfo);
                guest.createProfile(guestID, name, contactInfo);  // From guestprofile.cpp
                break;
            }

            case 2: {
                // Declare the guest profile object within the case block
                std::cout << "Enter Guest ID to view profile: ";
                std::cin >> guestID;

                GuestProfile guestProfile("", "", "");
                guestProfile.getProfile(guestID);  // From guestprofile.cpp
                break;
            }

            case 3: {
                // Declare the room and booking objects within the case block
                std::cout << "Enter Room ID to Book: ";
                std::cin >> roomID;
                std::cout << "Enter Room Type: ";
                std::cin >> roomType;
                std::cout << "Enter Price: ";
                std::cin >> price;
                std::cout << "Enter Availability (1 for available, 0 for not): ";
                std::cin >> isAvailable;

                Room bookedRoom(roomID, roomType, price, isAvailable);

                std::cout << "Enter Check-in Date (yyyy-mm-dd): ";
                std::cin >> checkInDate;
                std::cout << "Enter Check-out Date (yyyy-mm-dd): ";
                std::cin >> checkOutDate;
                std::cout << "Enter Payment Status (1 for paid, 0 for not): ";
                std::cin >> paymentStatus;

                // Generate bookingID for new booking (for example purposes, use simple random number)
                bookingID = std::to_string(rand());  // Replace with proper ID generation logic

                Booking booking(bookingID, guestID, bookedRoom, checkInDate, checkOutDate, paymentStatus);
                booking.bookRoom(bookingID, guestID, bookedRoom, checkInDate, checkOutDate, paymentStatus);  // From booking.cpp
                break;
            }

            case 4: {
                // Declare the cancelBooking object within the case block
                std::cout << "Enter Reservation ID to cancel: ";
                std::cin >> bookingID;

                Booking cancelBookingObj("", "", room1, "", "", false);
                cancelBookingObj.cancelBooking(bookingID);  // From booking.cpp
                break;
            }

            case 0:
                std::cout << "Exiting program...\n";
                return 0;

            default:
                std::cout << "Invalid choice! Please try again.\n";
                break;
        }
    }

    return 0;
}
