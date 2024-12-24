#include "guestmanagement.cpp"


int main() {
    loadGuestProfiles("guestprofile.csv");
    loadReservations("Reservation.csv");
    loadRooms("Room.csv");
    displayGuestMenu();
    return 0;
}
