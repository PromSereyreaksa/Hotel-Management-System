#include <iostream>
#include <unordered_map>
#include <string>
#include <fstream>
#include <sstream>
#include <list>

using namespace std;

// Guest Profile structure
struct GuestProfile {
    int id;
    string name;
    string phone;
    string email;

    // Constructor for guest profile
    GuestProfile(int id, const string& n, const string& p, const string& e)
        : id(id), name(n), phone(p), email(e) {}

    // Function to display guest profile
    void displayProfile() const {
        cout << "ID: " << id << endl;
        cout << "Name: " << name << endl;
        cout << "Phone: " << phone << endl;
        cout << "Email: " << email << endl;
    }
};

// Reservation structure
struct Reservation {
    int guestId;
    string roomType;
    string checkInDate;
    string checkOutDate;
    bool isConfirmed;

    // Constructor for reservation
    Reservation(int id, const string& room, const string& checkIn, const string& checkOut)
        : guestId(id), roomType(room), checkInDate(checkIn), checkOutDate(checkOut), isConfirmed(false) {}

    // Function to display reservation details
    void displayReservation() const {
        cout << "Guest ID: " << guestId << endl;
        cout << "Room Type: " << roomType << endl;
        cout << "Check-in: " << checkInDate << endl;
        cout << "Check-out: " << checkOutDate << endl;
        cout << "Confirmed: " << (isConfirmed ? "Yes" : "No") << endl;
    }
};

// Function to add reservation to linked list
void addReservation(list<Reservation>& reservations, int guestId, const string& roomType, const string& checkInDate, const string& checkOutDate) {
    reservations.push_back(Reservation(guestId, roomType, checkInDate, checkOutDate));
    cout << "Reservation added. Awaiting confirmation by staff." << endl;
}

// Function to load guest profiles from a file
void loadGuestProfiles(unordered_map<int, GuestProfile>& guestMap, const string& filename) {
    ifstream file(filename);
    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        int id;
        string name, phone, email;
        ss >> id >> name >> phone >> email;
        guestMap[id] = GuestProfile(id, name, phone, email);
    }
}

// Function to save guest profiles to a file
void saveGuestProfiles(const unordered_map<int, GuestProfile>& guestMap, const string& filename) {
    ofstream file(filename);
    for (const auto& entry : guestMap) {
        const GuestProfile& profile = entry.second;
        file << profile.id << " " << profile.name << " " << profile.phone << " " << profile.email << endl;
    }
}

// Function to display available rooms
void displayAvailableRooms() {
    cout << "=== Available Room Types ===" << endl;
    cout << "1. Single Room" << endl;
    cout << "2. Double Room" << endl;
    cout << "3. Suite" << endl;
    cout << "Please choose a room type (1-3): ";
}

// Function to display the guest profile menu
void displayMenu() {
    cout << "=== CADT Hotel - Guest Management ===" << endl;
    cout << "1. Create Guest Profile" << endl;
    cout << "2. Update Guest Profile" << endl;
    cout << "3. View Guest Profile" << endl;
    cout << "4. Book a Room" << endl;
    cout << "5. View Booking History" << endl;
    cout << "6. Exit" << endl;
    cout << "Please select an option: ";
}

int main() {
    unordered_map<int, GuestProfile> guestMap;  // Store guest profiles in hash map
    list<Reservation> reservations;             // Store reservations in a linked list
    loadGuestProfiles(guestMap, "guest_profiles.csv");  // Load existing profiles from a file

    int choice;
    while (true) {
        displayMenu();
        cin >> choice;

        if (choice == 1) {
            // Create new guest profile
            int id;
            string name, phone, email;
            cout << "Enter Guest ID: ";
            cin >> id;
            cin.ignore();  // to ignore the newline character
            cout << "Enter Name: ";
            getline(cin, name);
            cout << "Enter Phone: ";
            getline(cin, phone);
            cout << "Enter Email: ";
            getline(cin, email);

            guestMap[id] = GuestProfile(id, name, phone, email);
            cout << "Guest Profile Created!" << endl;

        } else if (choice == 2) {
            // Update existing guest profile
            int id;
            cout << "Enter Guest ID to update: ";
            cin >> id;
            if (guestMap.find(id) != guestMap.end()) {
                string name, phone, email;
                cout << "Enter New Name: ";
                cin.ignore();
                getline(cin, name);
                cout << "Enter New Phone: ";
                getline(cin, phone);
                cout << "Enter New Email: ";
                getline(cin, email);
                guestMap[id].name = name;
                guestMap[id].phone = phone;
                guestMap[id].email = email;
                cout << "Guest Profile Updated!" << endl;
            } else {
                cout << "Guest not found!" << endl;
            }

        } else if (choice == 3) {
            // View guest profile
            int id;
            cout << "Enter Guest ID to view profile: ";
            cin >> id;
            if (guestMap.find(id) != guestMap.end()) {
                cout << "Guest Profile Details:" << endl;
                guestMap[id].displayProfile();
            } else {
                cout << "Guest not found!" << endl;
            }

        } else if (choice == 4) {
            // Book a room
            int guestId;
            cout << "Enter your Guest ID: ";
            cin >> guestId;
            if (guestMap.find(guestId) != guestMap.end()) {
                displayAvailableRooms();
                int roomChoice;
                cin >> roomChoice;
                string roomType;
                switch (roomChoice) {
                    case 1: roomType = "Single Room"; break;
                    case 2: roomType = "Double Room"; break;
                    case 3: roomType = "Suite"; break;
                    default: cout << "Invalid choice, try again." << endl; continue;
                }

                string checkInDate, checkOutDate;
                cout << "Enter Check-in Date (YYYY-MM-DD): ";
                cin >> checkInDate;
                cout << "Enter Check-out Date (YYYY-MM-DD): ";
                cin >> checkOutDate;

                addReservation(reservations, guestId, roomType, checkInDate, checkOutDate);
            } else {
                cout << "Guest not found!" << endl;
            }

        } else if (choice == 5) {
            // View booking history
            int guestId;
            cout << "Enter Guest ID to view booking history: ";
            cin >> guestId;
            bool found = false;
            for (const auto& res : reservations) {
                if (res.guestId == guestId) {
                    res.displayReservation();
                    found = true;
                }
            }
            if (!found) {
                cout << "No bookings found!" << endl;
            }

        } else if (choice == 6) {
            // Exit the application
            saveGuestProfiles(guestMap, "guest_profiles.csv");  // Save profiles to file
            cout << "Thank you for using the CADT Hotel Management System!" << endl;
            break;
        } else {
            cout << "Invalid option, please try again." << endl;
        }
    }

    return 0;
}
