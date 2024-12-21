#include "guestmanagement.cpp"


int main() {
    // Load data from CSV files into memory
    loadRooms("room.csv");
    loadReservations("Reservation.csv");
    loadGuestProfiles("guestprofile.csv");

    int choice;
    do {
        clearScreen();
        cout << "\n" << string(40, '=') << endl;
        cout << "Hotel Management System:\n";
        cout << string(40, '=') << endl;
        cout << "1. Create Account" << endl;
        cout << "2. Update Account" << endl;
        cout << "3. View Account" << endl;
        cout << "4. Check Available Rooms" << endl;
        cout << "5. Book Room" << endl;
        cout << "6. View Booking History" << endl;
        cout << "7. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: createAccount(); break;
            case 2: updateAccount(); break;
            case 3: viewAccount(); break;
            case 4: checkAvailableRooms(); break;
            case 5: bookRoom(); break;
            case 6: {
                string userID;
                cout << "Enter User ID: ";
                cin >> userID;
                viewBookingHistory(userID);
                break;
            }
            case 7: cout << "Exiting...\n"; break;
            default: cout << "Invalid choice! Please try again.\n";
        }

    } while (choice != 7);

    return 0;
}
