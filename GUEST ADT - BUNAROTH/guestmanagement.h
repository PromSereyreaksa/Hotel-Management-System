#ifndef GUESTMANAGEMENT_H
#define GUESTMANAGEMENT_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <list>
#include <map>
#include <iomanip>
#include <ctime>
#include <cstdlib>
#include <limits>

void clearScreen() {
#ifdef _WIN32
    system("cls");  // Windows
#else
    system("clear");  // Unix-based (Linux, MacOS)
#endif
}

using namespace std;

// Data structures
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
    string userID;
    string roomID;
    string roomType;
    string checkInDate;
    string checkOutDate;
    double totalPrice;
};

struct Room {
    string roomID;
    string roomType;
    double price;
    string status;
};

// Function declarations
void loadBookCounters(int &bookingCounter);
void saveBookCounters(int bookingCounter);
void loadUserCounters(int &userCounter);
void saveUserCounters(int userCounter);
void loadGuestProfiles(const string &filename);
void loadRooms(const string &filename);
void loadReservations(const string &filename);
void saveRooms(const string &filename);
void saveGuestProfiles(const string &filename);
void saveBookingHistory(const string &filename);
void checkAvailableRooms();
void bookRoom();
void viewBookingHistory(const string &userID);
int calculateDays(const string &checkIn, const string &checkOut);
string getDateInput();
template <typename T>
string generateID(const string &prefix, T counter);
void loginAccount();
void createAccount();
void updateAccount();
void viewAccount();
void editBooking();
void clearScreen();
void displayGuestMenu();

extern map<string, GuestProfile> guestProfiles;
extern map<string, Reservation> reservationHistory;
extern map<string, Room> roomDatabase;

#endif // GUESTMANAGEMENT_H
