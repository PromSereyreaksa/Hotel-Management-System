#include "guestmanagement.h"

map<string, GuestProfile> guestProfiles;
map<string, Reservation> editReservationHistory;
list<Reservation> reservationHistory;
map<string, Room> roomDatabase;


void loadUserCounters(int &userCounter) {
    ifstream file("DataBasefiles/usercounters.txt");
    if (file.is_open()) {
        file >>userCounter;
        file.close();
    } else {
        userCounter = 1; // Default value if file doesn't exist
    }
}

void loadBookCounters(int &bookingCounter) {
    ifstream file("DataBasefiles/bookingcounters.txt");
    if (file.is_open()) {
        file >>bookingCounter;
        file.close();
    } else {
        bookingCounter = 1; // Default value if file doesn't exist
    }
}

void saveUserCounters(int userCounter) {
    ofstream file("DataBasefiles/usercounters.txt");
    if (file.is_open()) {
        file << userCounter;
        file.close();
    } else {
        cerr << "Error: Could not save counters." << endl;
    }
}

void saveBookCounters(int bookingCounter) {
    ofstream file("DataBasefiles/bookingcounters.txt");
    if (file.is_open()) {
        file <<bookingCounter;
        file.close();
    } else {
        cerr << "Error: Could not save counters." << endl;
    }
}

void loadGuestProfiles(const string &filename) {
    ifstream file("DataBasefiles/" + filename);  // Corrected path
    if (!file.is_open()) {
        cerr << "Error: Could not open " << filename << endl;
        return;
    }
    string line;
    getline(file, line);
    while (getline(file, line)) {
        stringstream ss(line);
        GuestProfile profile;
        getline(ss, profile.userID, ',');
        getline(ss, profile.name, ',');
        getline(ss, profile.password, ',');
        getline(ss, profile.email, ',');
        getline(ss, profile.phoneNumber);
        guestProfiles[profile.userID] = profile;
    }
    file.close();
}

void loadRooms(const string &filename) {
    ifstream file("DataBasefiles/" + filename);  // Corrected path
    if (!file.is_open()) {
        cerr << "Error: Could not open " << filename << endl;
        return;
    }
    string line;
    getline(file, line);
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

void loadReservations(const string &filename) {
    ifstream file("DataBasefiles/" + filename);  // Corrected path
    if (!file.is_open()) {
        cerr << "Error: Could not open " << filename << endl;
        return;
    }
    string line;
    getline(file, line);
    while (getline(file, line)) {
        stringstream ss(line);
        Reservation res;
        getline(ss, res.bookingID, ',');
        getline(ss, res.name, ',');
        getline(ss, res.userID, ',');
        getline(ss, res.roomID, ',');
        getline(ss, res.roomType, ',');
        getline(ss, res.checkInDate, ',');
        getline(ss, res.checkOutDate, ',');
        ss >> res.totalPrice;
        reservationHistory.push_back(res);

        editReservationHistory [res.bookingID] = res;
    }
    file.close();
}

void saveRooms(const string &filename) {
    ofstream file("DataBasefiles/" + filename, ios::trunc);  // Corrected path
    if (!file.is_open()) {
        cerr << "Error: Could not open " << filename << endl;
        return;
    }
    file <<"RoomID,RoomType,Price,RoomStatus"<< endl;
    for (const auto &room : roomDatabase) {
        if (!room.second.roomID.empty() && !room.second.roomType.empty() && !room.second.status.empty()) {
            file << room.second.roomID << "," << room.second.roomType << "," << room.second.price << "," << room.second.status << endl;
        }
    }
    file.close();
}

void saveReservation(const string &filename, const Reservation &res) {
    ofstream file("DataBasefiles/" + filename, ios::app);  // Corrected path
    if (!file.is_open()) {
        cerr << "Error: Could not open " << filename << endl;
        return;
    }
    file << res.bookingID << "," << res.name << "," << res.userID << "," << res.roomID << "," << res.roomType << "," 
         << res.checkInDate << "," << res.checkOutDate << "," << res.totalPrice << endl;
    file.close();
}

void saveGuestProfiles(const string &filename) {
    ofstream file("DataBasefiles/" + filename, ios::trunc);  // Corrected path
    if (!file.is_open()) {
        cerr << "Error: Could not open " << filename << endl;
        return;
    }

    file <<"UserID,UserName,Password,Gmail,PhoneNumber"<< endl;
    for (const auto &entry : guestProfiles) {
        const GuestProfile &profile = entry.second;
        if (!profile.userID.empty() && !profile.name.empty() && !profile.password.empty() && !profile.email.empty() && !profile.phoneNumber.empty()) {
            file << profile.userID << "," << profile.name << "," << profile.password << "," 
                << profile.email << "," << profile.phoneNumber << endl;
        }
    }
    file.close();
}

void saveBookingHistory(const string &filename) {
    ofstream file("DataBasefiles/" + filename, ios::trunc);  // Corrected path
    if (!file.is_open()) {
        cerr << "Error: Could not open " << filename << endl;
        return;
    }

    file <<"BookingID,UserName,UserID,RoomID,RoomType,CheckinDate,CheckoutDate,TotalPrice"<< endl;
    for (const auto &entry : editReservationHistory) {
        const Reservation &res = entry.second;
        if (!res.bookingID.empty() && !res.name.empty() && !res.userID.empty() && !res.roomID.empty() && !res.roomType.empty() && !res.checkInDate.empty() && !res.checkOutDate.empty()) {
            file << res.bookingID << "," << res.name << "," << res.userID << "," << res.roomID << "," << res.roomType << "," 
                << res.checkInDate << "," << res.checkOutDate << "," << res.totalPrice << endl;
        }
    }
    file.close();
}


int calculateDays(const string &checkIn, const string &checkOut) {
    struct tm tmIn = {}, tmOut = {};
    istringstream ssIn(checkIn), ssOut(checkOut);

    // Parse the input dates into tm structures
    ssIn >> get_time(&tmIn, "%d-%m-%Y");
    ssOut >> get_time(&tmOut, "%d-%m-%Y");

    // Convert tm structures to time_t (which is in seconds since the epoch)
    time_t timeIn = mktime(&tmIn);
    time_t timeOut = mktime(&tmOut);

    // Calculate the difference in seconds and convert to days
    double secondsDiff = difftime(timeOut, timeIn);
    int daysDiff = secondsDiff / (60 * 60 * 24);  // Convert seconds to days

    // Include the check-in day as part of the total (adding 1)
    return daysDiff;
}

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

template <typename T>
string generateID(const string &prefix, T counter) {
    stringstream ss;
    ss << prefix << setw(3) << setfill('0') << counter;
    return ss.str();
}

void createAccount() {
    static int userCounter = 1;
    loadUserCounters(userCounter);

    GuestProfile profile;
    profile.userID = generateID("AID", userCounter++);

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

    saveGuestProfiles("guestprofile.csv");
    saveUserCounters(userCounter);
    system("pause");
}

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

            saveGuestProfiles("guestprofile.csv");
        } else {
            cout << "Incorrect Password!" << endl;
        }
    } else {
        cout << "User ID not found!" << endl;
    }
    system("pause");
}

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
    system("pause");
}

void checkAvailableRooms() {
    cout << "\n" << string(40, '-') << endl;
    cout << "Available Rooms:\n";
    cout << "Room ID\tType\tPrice\n";
    cout << string(40, '-') << endl;
    bool hasAvailableRooms = false;

    for (const auto &room : roomDatabase) {
        if (room.second.status == "available") {
            cout << room.second.roomID << "\t" << room.second.roomType << "\t" << room.second.price << endl;
            hasAvailableRooms = false;
        }
    }

    if (!hasAvailableRooms) {
        // If no rooms are available, output the message and skip to the next loop iteration
        cout << "There's no available room!" << endl;
        system("pause");
        return; // Exit the function to skip to the next iteration of the calling loop
    }

    cout << string(40, '-') << endl;
    system("pause");
}

void bookRoom() {
    static int bookingCounter = 1;
    loadBookCounters(bookingCounter);
    Reservation res;

    cout << "Enter UserID: ";
    cin >> res.userID;

    if (guestProfiles.find(res.userID) != guestProfiles.end()) {
        res.name = guestProfiles[res.userID].name;
        cout << "User Name: " << res.name << endl;
    } else {
        cout << "UserID not found! Please make sure the UserID is correct." << endl;
        system("pause");
        return;
    }

    cout << "Enter Check-In Date (dd-mm-yyyy):"<< endl;
    res.checkInDate = getDateInput();
    cout << "Enter Check-Out Date (dd-mm-yyyy):"<< endl;
    res.checkOutDate = getDateInput();

    clearScreen();
    cout << "Available Rooms:\n";
    checkAvailableRooms();

    cout << "Enter Room ID to book: ";
    cin >> res.roomID;

    if (roomDatabase.find(res.roomID) != roomDatabase.end() && roomDatabase[res.roomID].status == "available") {
        res.roomType = roomDatabase[res.roomID].roomType;

        // Calculate the total price based on days
        int totalDays = calculateDays(res.checkInDate, res.checkOutDate);
        res.totalPrice = roomDatabase[res.roomID].price * totalDays;
        res.bookingID = generateID("BID", bookingCounter++);

        roomDatabase[res.roomID].status = "unavailable";
        editReservationHistory[res.bookingID] = res;

        reservationHistory.push_back(res);
        saveReservation("Reservation.csv", res);

        saveRooms("room.csv");
        saveBookCounters(bookingCounter);

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
        cout << "Total Days: " << totalDays << endl;
        cout << "Total Price: $" << fixed << setprecision(2) << res.totalPrice << endl;
        cout << string(40, '-') << endl;
    } else {
        cout << "Room not available or invalid Room ID!" << endl;
    }
    system("pause");
}

// Function to edit a booking from reservationHistory
void editBooking() {
    string bookingID;
    cout << "Enter Booking ID to edit: ";
    cin >> bookingID;

    // Search for the booking in reservationHistory using unordered_map
  // Use unordered_map for faster lookup
    auto it = editReservationHistory.find(bookingID);
    if (it != editReservationHistory.end()) {
        Reservation &res = it->second;  // Get the reservation from the map

        cout << "Booking found!\n";
        cout << "Current Details:\n";
        cout << "Booking ID: " << res.bookingID << endl;
        cout << "Name: " << res.name << endl;
        cout << "Room ID: " << res.roomID << endl;
        cout << "Room Type: " << res.roomType << endl;
        cout << "Check-In Date: " << res.checkInDate << endl;
        cout << "Check-Out Date: " << res.checkOutDate << endl;
        cout << "Total Price: $" << fixed << setprecision(2) << res.totalPrice << endl;

        cout << "\nWhat would you like to edit?\n";
        cout << "1. Check-In Date\n2. Check-Out Date\n3. Room\n4. Cancel\n";
        int choice;
        cin >> choice;

        switch (choice) {
            case 1: {
                cout << "Enter new Check-In Date (dd-mm-yyyy):"<< endl;
                res.checkInDate = getDateInput();
                break;
            }
            case 2: {
                cout << "Enter new Check-Out Date (dd-mm-yyyy):"<< endl;
                res.checkOutDate = getDateInput();
                break;
            }
            case 3: {
                cout << "Available Rooms:\n";
                checkAvailableRooms();
                cout << "Enter new Room ID: ";
                string newRoomID;
                cin >> newRoomID;

                // Check if room exists in roomDatabase and is available using unordered_map
                auto roomIt = roomDatabase.find(newRoomID);
                if (roomIt != roomDatabase.end() && roomIt->second.status == "available") {
                    // Free the old room
                    roomDatabase[res.roomID].status = "available";

                    // Update to the new room
                    res.roomID = newRoomID;
                    res.roomType = roomIt->second.roomType;
                    roomDatabase[newRoomID].status = "unavailable";
                } else {
                    cout << "Invalid Room ID or Room not available!" << endl;
                    return;
                }
                break;
            }
            case 4: {
                cout << "Edit canceled.\n";
                return;
            }
            default:
                cout << "Invalid choice.\n";
                return;
        }

        // Recalculate total price based on number of days
        int totalDays = calculateDays(res.checkInDate, res.checkOutDate);
        res.totalPrice = roomDatabase[res.roomID].price * totalDays;

        // Save updated data
        saveRooms("room.csv");
        saveBookingHistory("Reservation.csv");

        cout << "Booking updated successfully!\n";
        cout << "Updated Details:\n";
        cout << "Booking ID: " << res.bookingID << endl;
        cout << "Name: " << res.name << endl;
        cout << "Room ID: " << res.roomID << endl;
        cout << "Room Type: " << res.roomType << endl;
        cout << "Check-In Date: " << res.checkInDate << endl;
        cout << "Check-Out Date: " << res.checkOutDate << endl;
        cout << "Total Price: $" << fixed << setprecision(2) << res.totalPrice << endl;
    } else {
        cout << "Booking ID not found!" << endl;
    }

    system("pause");
}


void viewBookingHistory(const string &userID) {
    cout << "\n" << string(40, '-') << endl;
    cout << "Booking History for User: " << userID << endl;
    cout << "Booking ID\tRoom ID\tRoom Type\tPrice\n";
    cout << string(40, '-') << endl;
    for (const auto &res : reservationHistory) {
        if (res.userID == userID) {
            cout << res.bookingID << "\t" << res.roomID << "\t" << res.roomType << "\t$" 
                 << fixed << setprecision(2) << res.totalPrice << endl;
        }
    }
    cout << string(40, '-') << endl;
    system("pause");
}

void displayGuestMenu() {
    
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
        cout << "6. Edit Book" << endl;
        cout << "7. View Booking History" << endl;
        cout << "8. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: createAccount(); break;
            case 2: updateAccount(); break;
            case 3: viewAccount(); break;
            case 4: checkAvailableRooms(); break;
            case 5: bookRoom(); break;
            case 6: editBooking(); break;
            case 7: {
                string userID;
                cout << "Enter User ID: ";
                cin >> userID;
                viewBookingHistory(userID);
                break;
            }
            case 8: cout << "Exiting...\n"; break;
            default: cout << "Invalid choice! Please try again.\n";
        }

    } while (choice != 8);
}
