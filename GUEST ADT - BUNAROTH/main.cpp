#include "guestmanagement.h"

int main() {
    // Load all necessary data from files
    loadRooms("room.csv");
    loadReservations("Reservation.csv");
    loadGuestProfiles("guestprofile.csv");

    int choice;
    
    while (true) {
        clearScreen();
        
        // Display menu in a neat and structured format
        cout << "\n" << string(40, '=') << endl;
        cout << "        Hotel Management System         " << endl;
        cout << string(40, '=') << endl;
        cout << "1. Create Account" << endl;
        cout << "2. Update Account" << endl;
        cout << "3. View Account" << endl;
        cout << "4. Check Available Rooms" << endl;
        cout << "5. Book Room" << endl;
        cout << "6. View Booking History" << endl;
        cout << "7. Exit" << endl;
        cout << string(40, '=') << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                createAccount();
                break;
            case 2:
                updateAccount();
                break;
            case 3:
                viewAccount();
                break;
            case 4:
                checkAvailableRooms();
                break;
            case 5:
                bookRoom();
                break;
            case 6: {
                string userID;
                cout << "Enter User ID to view booking history: ";
                cin >> userID;
                viewBookingHistory(userID); // Show only the user's booking history
                break;
            }
            case 7:
                // Save data before exiting
                saveRooms("room.csv");
                saveGuestProfiles("guestprofile.csv");
                saveBookingHistory("Reservation.csv");
                cout << "Exiting... Goodbye!" << endl;
                return 0;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }

        // Pause for user to review before continuing
        cout << "\nPress Enter to continue...";
        cin.ignore();
        cin.get();
    }

    return 0;
}
