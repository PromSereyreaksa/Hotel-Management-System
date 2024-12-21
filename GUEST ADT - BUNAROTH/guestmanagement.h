#ifndef GUESTMANAGEMENT_H
#define GUESTMANAGEMENT_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <list>
#include <queue>
#include <map>
#include <iomanip>
#include <ctime>

using namespace std;

struct GuestProfile {
    string userID;
    string name;
    string password;
    string email;
    string phoneNumber;
};

struct Room {
    string roomID;
    string roomType;
    double price;
    string status; // available or unavailable
};

struct Reservation {
    string bookingID;
    string userID;
    string name;
    string roomID;
    string roomType;
    string checkInDate;
    string checkOutDate;
    double totalPrice;
};

extern unordered_map<string, GuestProfile> guestProfiles;
extern list<Reservation> reservationHistory;
extern queue<Reservation> bookingQueue;
extern map<string, Room> roomDatabase;

void loadRooms(const string &filename);
void loadReservations(const string &filename);
void loadGuestProfiles(const string &filename);
void saveRooms(const string &filename);
void saveReservation(const string &filename, const Reservation &res);
void saveGuestProfiles(const string &filename);
void saveBookingHistory(const string &filename);
int calculateDays(const string &checkIn, const string &checkOut);
string getDateInput();
void clearScreen();
template <typename T> string generateID(const string &prefix, T counter);
void createAccount();
void updateAccount();
void viewAccount();
void checkAvailableRooms();
void bookRoom();
void viewBookingHistory(const string &userID);

#endif // GUESTMANAGEMENT_H
