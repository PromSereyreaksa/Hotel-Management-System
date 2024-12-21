#include "guestmanagement.h"

unordered_map<string, GuestProfile> guestProfiles;
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
    }
    file.close();
}

void saveRooms(const string &filename) {
    ofstream file("DataBasefiles/" + filename, ios::trunc);  // Corrected path
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
    ofstream file("DataBasefiles/" + filename, ios::app);  // Corrected path
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
    ofstream file("DataBasefiles/" + filename, ios::trunc);  // Corrected path
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

    // Parse the input dates into tm structures
    ssIn >> get_time(&tmIn, "%d-%m-%Y");
    ssOut >> get_time(&tmOut, "%d-%m-%Y");

    // Convert tm structures to time_t (which is in seconds since the epoch)
    time_t timeIn = mktime(&tmIn);
    time_t timeOut = mktime(&tmOut);

    // Calculate the difference in seconds and convert to days
    double secondsDiff = difftime(timeOut, timeIn);
    int daysDiff = secondsDiff / (60 * 60 * 24);  // Convert seconds to days

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
    for (const auto &room : roomDatabase) {
        if (room.second.status == "available") {
            cout << room.second.roomID << "\t" << room.second.roomType << "\t" << room.second.price << endl;
        }
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
        res.bookingID = generateID("BID", bookingCounter++);

        roomDatabase[res.roomID].status = "unavailable";

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
        cout << "Total Price: $" << fixed << setprecision(2) << res.totalPrice << endl;
        cout << string(40, '-') << endl;
    } else {
        cout << "Room not available or invalid Room ID!" << endl;
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
