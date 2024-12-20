#ifndef BOOKING_H
#define BOOKING_H

#include <string>
#include "room.h"

class Booking {
public:
    std::string bookingID;
    std::string guestID;
    Room bookedRoom;
    std::string checkInDate;
    std::string checkOutDate;
    bool paymentStatus;

    Booking(const std::string& bookingID, const std::string& guestID, Room bookedRoom, 
            const std::string& checkInDate, const std::string& checkOutDate, bool paymentStatus);

    void bookRoom(const std::string& bookingID, const std::string& guestID, Room& bookedRoom, 
                  const std::string& checkInDate, const std::string& checkOutDate, bool paymentStatus);
    void getBookingDetails(const std::string& bookingID);
    void cancelBooking(const std::string& bookingID);
};

#endif
