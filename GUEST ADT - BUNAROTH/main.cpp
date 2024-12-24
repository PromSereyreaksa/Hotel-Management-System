#include "guestmanagement.cpp"


int main() {
<<<<<<< Updated upstream
    loadGuestProfiles("guestprofile.csv");
    loadReservations("Reservation.csv");
    loadRooms("Room.csv");
=======
    // Load data from CSV files into memory
    loadRooms("Room.csv");
    loadReservations("Reservation.csv");
    loadGuestProfiles("guestprofile.csv");
>>>>>>> Stashed changes
    displayGuestMenu();
    return 0;
}
