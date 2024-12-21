#include "guestmanagement.h"

// Data structures
unordered_map<string, GuestProfile> guestProfiles;
list<Reservation> reservationHistory;
map<string, Room> roomDatabase;

// Function definitions

void loadGuestProfiles(const string &filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Could not open " << filename << endl;
        return;
    }
    string line;
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

void loadReservations(const string &filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Could not open " << filename << endl;
        return;
    }
    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        Reservation res;
        getline(ss, res.bookingID, ',');
        getline(ss, res.name, ',');
        getline(ss, res.roomID, ',');
        getline(ss, res.roomType, ',');
        getline(ss, res.checkInDate, ',');
        getline(ss, res.checkOutDate, ',');
        ss >> res.totalPrice;
        reservationHistory.push_back(res);
    }
    file.close();
}

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

void saveGuestProfiles(const string &filename) {
    ofstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Could not open " << filename << endl;
        return;
    }
    for (const auto &entry : guestProfiles) {
        const GuestProfile &profile = entry.second;
        file << profile.userID << "," << profile.name << "," << profile.password << ","
             << profile.email << "," << profile.phoneNumber << endl;
    }
    file.close();
}

void saveBookingHistory(const string &filename) {
    ofstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Could not open " << filename << endl;
        return;
    }
    for (const auto &res : reservationHistory) {
        file << res.bookingID << "," << res.name << "," << res.roomID << "," << res.roomType << "," 
             << res.checkInDate << "," << res.checkOutDate << "," << res.totalPrice << endl;
    }
    file.close();
}

int calculateDays(const string &checkIn, const string &checkOut) {
    struct tm tmIn = {}, tmOut = {};
    istringstream ssIn(checkIn), ssOut(checkOut);
    ssIn >> get_time(&tmIn, "%d-%m-%Y");
    ssOut >> get_time(&tmOut, "%d-%m-%Y");
    time_t timeIn = mktime(&tmIn);
    time_t timeOut = mktime(&tmOut);
    return difftime(timeOut, timeIn) / (60 * 60 * 24);
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

    // Save the new account to guestprofile.csv
    saveGuestProfiles("guestprofile.csv");
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
        } else {
            cout << "Incorrect Password!" << endl;
        }
    } else {
        cout << "User ID not found!" << endl;
    }
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
}

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

void viewBookingHistory(const string &userID) {
    cout << "\n" << string(40, '-') << endl;
    cout << "Booking History for User ID: " << userID << endl;
    for (const auto &res : reservationHistory) {
        if (res.name == userID) {
            cout << "Booking ID: " << res.bookingID << "\nName: " << res.name << "\nRoom ID: " << res.roomID
                 << "\nCheck-In: " << res.checkInDate << "\nCheck-Out: " << res.checkOutDate
                 << "\nTotal Price: $" << fixed << setprecision(2) << res.totalPrice << endl;
            cout << string(40, '-') << endl;
        }
    }
}
