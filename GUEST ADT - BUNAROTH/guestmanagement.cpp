#include "guestmanagement.h"

map<string, GuestProfile> guestProfiles;
map<string, Reservation> reservationHistory;
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
<<<<<<< Updated upstream
        // guestProfiles[profile.userID] = profile;
=======
>>>>>>> Stashed changes
        guestProfiles[profile.name] = profile;
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
        reservationHistory [res.bookingID] = res;
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
    for (const auto &entry : reservationHistory) {
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

<<<<<<< Updated upstream
string loginUserName;
=======
>>>>>>> Stashed changes
void loginAccount() {
    string userName;
    string password;
    cout << "Enter UserName: ";
    cin >> userName;

    if (guestProfiles.find(userName) != guestProfiles.end()) {
        cout << "Enter Password: ";
        cin >> password;
        if (guestProfiles[userName].password == password) {
<<<<<<< Updated upstream
            loginUserName = guestProfiles[userName].name;
=======
>>>>>>> Stashed changes
            int choice;
            
            do {
                clearScreen();
                cout << "\n" << string(40, '=') << endl;
<<<<<<< Updated upstream
                cout << "Welcome To CADT HOTEL\n";
                cout << string(40, '=') << endl;
                cout << "1. View Account" << endl;
                cout << "2. Update Account" << endl;
                cout << "3. Check Available Rooms" << endl;
                cout << "4. Book Room" << endl;
                cout << "5. Edit Book" << endl;
                cout << "6. View Booking History" << endl;
                cout << "7. Exit" << endl;
=======
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
>>>>>>> Stashed changes
                cout << "Enter your choice: ";
                cin >> choice;

                switch (choice) {
<<<<<<< Updated upstream
                    case 1: viewAccount(); break;
                    case 2: updateAccount(); break;
                    case 3: checkAvailableRooms(); break;
                    case 4: bookRoom(); break;
                    case 5: editBooking(); break;
                    case 6: {
=======
                    case 1: createAccount(); break;
                    case 2: updateAccount(); break;
                    case 3: viewAccount(); break;
                    case 4: checkAvailableRooms(); break;
                    case 5: bookRoom(); break;
                    case 6: editBooking(); break;
                    case 7: {
>>>>>>> Stashed changes
                        string userID;
                        cout << "Enter User ID: ";
                        cin >> userID;
                        viewBookingHistory(userID);
                        break;
                    }
<<<<<<< Updated upstream
                    case 7: cout << "Exiting...\n"; break;
                    default: cout << "Invalid choice! Please try again.\n";
                }

            } while (choice != 7);
=======
                    case 8: cout << "Exiting...\n"; break;
                    default: cout << "Invalid choice! Please try again.\n";
                }

            } while (choice != 8);
>>>>>>> Stashed changes
        } else {
            cout << "Incorrect Password!" << endl;
        }
    } else {
        cout << "User ID not found!" << endl;
    }
    system("pause");
}

void createAccount() {
    static int userCounter = 1;
    loadUserCounters(userCounter);

    GuestProfile profile;
    profile.userID = generateID("AID", userCounter++);

    do {
        cout << "Enter Name: ";
        cin >> profile.name;    
        if (guestProfiles.find(profile.name) != guestProfiles.end()){
            cout<<"Username Has Already Existed! Please try again."<< endl;
        } else{
          break;  
        }
    } while (true);
    
    
    cout << "Enter Password: ";
    cin >> profile.password;
    cout << "Enter Email: ";
    cin >> profile.email;
    cout << "Enter Phone Number: ";
    cin >> profile.phoneNumber;

    // guestProfiles[profile.userID] = profile;
    guestProfiles[profile.name] = profile;
    cout << "Account created successfully! User ID: " << profile.userID << endl;

    saveGuestProfiles("guestprofile.csv");
    saveUserCounters(userCounter);
    system("pause");
}

void updateAccount() {
    string userName;
    string password;
    cout << "Enter Username to update: ";
    cin >> userName;

    if (guestProfiles.find(userName) != guestProfiles.end()) {
        cout << "Enter Password: ";
        cin >> password;
        if (guestProfiles[userName].password == password) {
            cout << "Enter New Name: ";
            cin >> guestProfiles[userName].name;
            cout << "Enter New Password: ";
            cin >> guestProfiles[userName].password;
            cout << "Enter New Email: ";
            cin >> guestProfiles[userName].email;
            cout << "Enter New Phone Number: ";
            cin >> guestProfiles[userName].phoneNumber;
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

    if (guestProfiles.find(loginUserName) != guestProfiles.end()) {
            GuestProfile &profile = guestProfiles[loginUserName];
            cout << "User ID: " << profile.userID << endl;
            cout << "Name: " << profile.name << endl;
            cout << "Email: " << profile.email << endl;
            cout << "Phone Number: " << profile.phoneNumber << endl;
    };
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
            hasAvailableRooms = true;
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
    Reservation ress;

    cout << "Enter Username: ";
    cin >> ress.name;

    if (guestProfiles.find(ress.name) != guestProfiles.end()) {
        ress.name = guestProfiles[ress.name].name;
        cout << "User Name: " << ress.name << endl;
    } else {
        cout << "UserID not found! Please make sure the UserID is correct." << endl;
        system("pause");
        return;
    }

    cout << "Enter Check-In Date (dd-mm-yyyy):"<< endl;
    ress.checkInDate = getDateInput();
    cout << "Enter Check-Out Date (dd-mm-yyyy):"<< endl;
    ress.checkOutDate = getDateInput();

    clearScreen();
    cout << "Available Rooms:\n";
    checkAvailableRooms();

    cout << "Enter Room ID to book: ";
    cin >> ress.roomID;

    if (roomDatabase.find(ress.roomID) != roomDatabase.end() && roomDatabase[ress.roomID].status == "available") {
        ress.roomType = roomDatabase[ress.roomID].roomType;

        // Calculate the total price based on days
        int totalDays = calculateDays(ress.checkInDate, ress.checkOutDate);
        ress.totalPrice = roomDatabase[ress.roomID].price * totalDays;
        ress.bookingID = generateID("BID", bookingCounter++);

        roomDatabase[ress.roomID].status = "unavailable";

        clearScreen();
        cout << "Booking Successful!\n";
        cout << string(40, '-') << endl;
        cout << "Invoice:\n";
        cout << "Booking ID: " << ress.bookingID << endl;
        cout << "Name: " << ress.name << endl;
        cout << "Room ID: " << ress.roomID << endl;
        cout << "Room Type: " << ress.roomType << endl;
        cout << "Check-In Date: " << ress.checkInDate << endl;
        cout << "Check-Out Date: " << ress.checkOutDate << endl;
        cout << "Total Days: " << totalDays << endl;
        cout << "Total Price: $" << fixed << setprecision(2) << ress.totalPrice << endl;
        // saving
        reservationHistory[ress.bookingID] = ress;
        cout << "Added reservation with ID: " << ress.bookingID << endl;
        cout << "Current number of reservations: " << reservationHistory.size() << endl;
        // Save updated data
        saveRooms("Room.csv");
        saveBookingHistory("Reservation.csv");
        saveBookCounters(bookingCounter);
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

    auto it = reservationHistory.find(bookingID);
    if (it != reservationHistory.end()) {
        Reservation &res = it->second; 

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
        saveRooms("Room.csv");
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
        if (res.second.userID == userID) {
            cout << res.second.bookingID << "\t" << res.second.roomID << "\t" << res.second.roomType << "\t$" 
                 << fixed << setprecision(2) << res.second.totalPrice << endl;
        }
    }
    cout << string(40, '-') << endl;
    system("pause");
}

void displayGuestMenu() {
<<<<<<< Updated upstream
    int choice1;

    do
    {
        system("cls");
        cout << "\n" << string(40, '=') << endl;
        cout << "Welcome To CADT HOTEL\n";
        cout << string(40, '=') << endl;
        cout<< "1. Login Account\n2. Create New Account"<< endl;
        cout<< "Choose Menu: ";
        cin >> choice1;

        switch (choice1){
            case 1: loginAccount(); break;
            case 2: createAccount(); break;
            case 3: cout << "Exiting...\n"; break;
            default: cout << "Invalid choice! Please try again.\n";
        }
    } while (choice1 != 3);
    
    
        
}
=======
    
    

    int choice1;
    cout << "\n" << string(40, '=') << endl;
    cout<< "1. Login Profile\n  2 ";
    cout<< "Choose Menu: ";
    cin >> choice1;

    switch (choice1){
        case 1:
            loginAccount();
            break;
        case 2:
            createAccount();
            break;
        default:
            break;
    }
        
}
>>>>>>> Stashed changes
