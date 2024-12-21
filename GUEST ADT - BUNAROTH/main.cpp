#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <list>
#include <queue>
#include <vector>
#include <sstream>
#include <iomanip>
#include <ctime>
#include <map>
#ifdef _WIN32
#include <windows.h>
#else
#include <cstdlib>
#endif

using namespace std;

struct Room {
    string roomID;
    string roomType;
    double price;
    string status; // "available" or "unavailable"
};

struct GuestProfile {
    string userID;
    string name;
    string password;
    string email;
    string phoneNumber;
};

struct Reservation {
    string bookingID;
    string name;
    string roomID;
    string roomType;
    string checkInDate; // Stored as dd-mm-yyyy
    string checkOutDate; // Stored as dd-mm-yyyy
    double totalPrice;
};

// Data structures
unordered_map<string, GuestProfile> guestProfiles; // Hash map for guest profiles
list<Reservation> reservationHistory;             // Linked list for reservation history
queue<Reservation> bookingQueue;                  // Queue for booking requests
map<string, Room> roomDatabase;                   // Map for rooms

// Helper function to clear the console
void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// Helper function to generate unique IDs
template <typename T>
string generateID(const string &prefix, T counter) {
    stringstream ss;
    ss << prefix << setw(3) << setfill('0') << counter;
    return ss.str();
}

// Helper function to read room data from file
void loadRooms(const string &filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Could not open " << filename << endl;
        return;
    }
    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        Room room;
        getline(ss, room.roomID, ',');
        getline(ss, room.roomType, ',');
        ss >> room.price;
        ss.ignore();
        getline(ss, room.status);
        roomDatabase[room.roomID] = room;
    }
    file.close();
}

// Helper function to save room data to file
void saveRooms(const string &filename) {
    ofstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Could not open " << filename << endl;
        return;
    }
    for (const auto &room : roomDatabase) {
        file << room.second.roomID << "," << room.second.roomType << "," << room.second.price << "," << room.second.status << endl;
    }
    file.close();
}

// Helper function to save reservation data to file
void saveReservation(const string &filename, const Reservation &res) {
    ofstream file(filename, ios::app);
    if (!file.is_open()) {
        cerr << "Error: Could not open " << filename << endl;
        return;
    }
    file << res.bookingID << "," << res.name << "," << res.roomID << "," << res.roomType << "," 
         << res.checkInDate << "," << res.checkOutDate << "," << res.totalPrice << endl;
    file.close();
}

// Helper function to calculate the number of days between two dates
int calculateDays(const string &checkIn, const string &checkOut) {
    struct tm tmIn = {}, tmOut = {};
    istringstream ssIn(checkIn), ssOut(checkOut);
    ssIn >> get_time(&tmIn, "%d-%m-%Y");
    ssOut >> get_time(&tmOut, "%d-%m-%Y");
    time_t timeIn = mktime(&tmIn);
    time_t timeOut = mktime(&tmOut);
    return difftime(timeOut, timeIn) / (60 * 60 * 24);
}

// Helper function to get date input from the user
string getDateInput() {
    int day, month, year;
    cout << "Enter day: ";
    cin >> day;
    cout << "Enter month: ";
    cin >> month;
    cout << "Enter year: ";
    cin >> year;
    stringstream ss;
    ss << setw(2) << setfill('0') << day << "-" << setw(2) << setfill('0') << month << "-" << year;
    return ss.str();
}

// Create a new account
void createAccount() {
    static int userCounter = 1;
    GuestProfile profile;
    profile.userID = generateID("aid", userCounter++);

    cout << "Enter Name: ";
    cin >> profile.name;
    cout << "Enter Password: ";
    cin >> profile.password;
    cout << "Enter Email: ";
    cin >> profile.email;
    cout << "Enter Phone Number: ";
    cin >> profile.phoneNumber;

    guestProfiles[profile.userID] = profile;
    cout << "Account created successfully! User ID: " << profile.userID << endl;
}

// Update an account
void updateAccount() {
    string userID;
    string password;
    cout << "Enter User ID to update: ";
    cin >> userID;

    if (guestProfiles.find(userID) != guestProfiles.end()) {
        cout << "Enter Password: ";
        cin >> password;
        if (guestProfiles[userID].password == password) {
            cout << "Enter New Name: ";
            cin >> guestProfiles[userID].name;
            cout << "Enter New Password: ";
            cin >> guestProfiles[userID].password;
            cout << "Enter New Email: ";
            cin >> guestProfiles[userID].email;
            cout << "Enter New Phone Number: ";
            cin >> guestProfiles[userID].phoneNumber;
            cout << "Account updated successfully!" << endl;
        } else {
            cout << "Incorrect Password!" << endl;
        }
    } else {
        cout << "User ID not found!" << endl;
    }
}

// View account
void viewAccount() {
    string userID;
    string password;
    cout << "Enter User ID to view: ";
    cin >> userID;

    if (guestProfiles.find(userID) != guestProfiles.end()) {
        cout << "Enter Password: ";
        cin >> password;
        if (guestProfiles[userID].password == password) {
            GuestProfile &profile = guestProfiles[userID];
            cout << "User ID: " << profile.userID << endl;
            cout << "Name: " << profile.name << endl;
            cout << "Email: " << profile.email << endl;
            cout << "Phone Number: " << profile.phoneNumber << endl;
        } else {
            cout << "Incorrect Password!" << endl;
        }
    } else {
        cout << "User ID not found!" << endl;
    }
}

// Check available rooms
void checkAvailableRooms() {
    cout << "\n" << string(40, '-') << endl;
    cout << "Available Rooms:\n";
    cout << "Room ID\tType\tPrice\n";
    cout << string(40, '-') << endl;
    for (const auto &room : roomDatabase) {
        if (room.second.status == "available") {
            cout << room.second.roomID << "\t" << room.second.roomType << "\t" << room.second.price << endl;
        }
    }
    cout << string(40, '-') << endl;
}

// Book a room
void bookRoom() {
    static int bookingCounter = 1;
    Reservation res;

    cout << "Enter Name: ";
    cin >> res.name;
    cout << "Enter Check-In Date:" << endl;
    res.checkInDate = getDateInput();
    cout << "Enter Check-Out Date:" << endl;
    res.checkOutDate = getDateInput();

    clearScreen();
    cout << "Available Rooms:\n";
    checkAvailableRooms();

    cout << "Enter Room ID to book: ";
    cin >> res.roomID;

    if (roomDatabase.find(res.roomID) != roomDatabase.end() && roomDatabase[res.roomID].status == "available") {
        res.roomType = roomDatabase[res.roomID].roomType;
        res.totalPrice = roomDatabase[res.roomID].price * calculateDays(res.checkInDate, res.checkOutDate);
        res.bookingID = generateID("bid", bookingCounter++);

        // Mark the room as unavailable
        roomDatabase[res.roomID].status = "unavailable";

        // Save reservation
        reservationHistory.push_back(res);
        saveReservation("Reservation.csv", res);

        // Update room data in file
        saveRooms("room.csv");

        clearScreen();
        cout << "Booking Successful!\n";
        cout << string(40, '-') << endl;
        cout << "Invoice:\n";
        cout << "Booking ID: " << res.bookingID << endl;
        cout << "Name: " << res.name << endl;
        cout << "Room ID: " << res.roomID << endl;
        cout << "Room Type: " << res.roomType << endl;
        cout << "Check-In Date: " << res.checkInDate << endl;
        cout << "Check-Out Date: " << res.checkOutDate << endl;
        cout << "Total Price: $" << fixed << setprecision(2) << res.totalPrice << endl;
        cout << string(40, '-') << endl;
    } else {
        cout << "Room not available or invalid Room ID!" << endl;
    }
}

// View booking history
void viewBookingHistory() {
    cout << "\n" << string(40, '-') << endl;
    cout << "Booking History:\n";
    for (const auto &res : reservationHistory) {
        cout << "Booking ID: " << res.bookingID << "\nName: " << res.name << "\nRoom ID: " << res.roomID
             << "\nCheck-In: " << res.checkInDate << "\nCheck-Out: " << res.checkOutDate
             << "\nTotal Price: $" << fixed << setprecision(2) << res.totalPrice << endl;
        cout << string(40, '-') << endl;
    }
}

int main() {
    loadRooms("room.csv");
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
        cout << "5. Book a Room" << endl;
        cout << "6. View Booking History" << endl;
        cout << "7. Exit" << endl;
        cout << string(40, '=') << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                clearScreen();
                createAccount();
                break;
            case 2:
                clearScreen();
                updateAccount();
                break;
            case 3:
                clearScreen();
                viewAccount();
                break;
            case 4:
                clearScreen();
                checkAvailableRooms();
                break;
            case 5:
                clearScreen();
                bookRoom();
                break;
            case 6:
                clearScreen();
                viewBookingHistory();
                break;
            case 7:
                cout << "Exiting... Goodbye!" << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
        if (choice != 7) {
            cout << "\nPress Enter to continue...";
            cin.ignore();
            cin.get();
        }
    } while (choice != 7);

    return 0;
}

