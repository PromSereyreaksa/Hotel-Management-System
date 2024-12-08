#include <algorithm>
#include <cctype>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
using namespace std;

// CREATE ACCOUNT
inline void createAdminAccount(const string &filename) {
  fstream file;
  file.open(filename, ios::out);
  string username, passwd, passwd_1, email;

  cout << "Enter your username: ";
  cin >> username;
  file << "Username: " << username << "\n";
  do {
    if ((passwd.compare(passwd_1)) != 0) {
      cout << "Password doesn't match. Please re-enter your password.\n";
    }
    cout << "Enter your password: ";
    cin >> passwd;
    cout << "Confirm your password: ";
    cin >> passwd_1;
    // comparing password 1 and password 2
    if ((passwd.compare(passwd_1)) ==
        0) { // if passwd and passwd_1 is same it returns 0 if not it returns
             // positive / negative integer
      file << "Password: " << passwd << "\n";
    }
  } while ((passwd.compare(passwd_1)) != 0);
  do {
    cout << "Email: ";
    cin >> email;

    // Check if email is valid to avoid any error when handling password in
    // login
    //  checks correctly if @ is missing.
    // string::npos is a special constant that indicates "not found" when using
    // functions like find.
    if (email.find('@') == string::npos) {
      cout << "Invalid email format. Please re-enter your email.\n";
    } else {
      file << "Email: " << email << endl;
    }

  } while (email.find('@') == string::npos);

  file.close();
  cout << "Succesfully register! - Data saved." << endl;
  exit(0);
}

// LOGIN
inline void login() {
  fstream file;
  string username, passwd, userData, passwdData;
  bool foundUser,
      foundPasswd; // boolean to check if user exists / if passwd is correct
  int choice;
  file.open("adminAccount.csv", ios::in);

  // file >> userData prints out every single word in the .csv file to compare
  // one by one

  cout << "Enter your username: ";
  cin >> username;
  while (file >> userData) {
    if (userData.compare(username) == 0) {
      foundUser = true;
      break;
    }
  }
  if (foundUser != true) {
    cout << "Username not found" << endl;
    cout << "Would you like to create an account?" << endl;
    cout << "1.Yes\n2.No" << endl;
    cout << "Select an option: ";
    cin >> choice;
    switch (choice) {
    case 1:
      createAdminAccount("adminAccount.csv");
      break;
    case 2:
      exit(0);
      break;
    default:
      cout << "Invalid option. Exiting the program..";
      exit(0);
    }
  }
  cout << "Enter your password: ";
  cin >> passwd;
  while (file >> passwdData) {
    if (passwdData.compare(passwd) == 0) {
      cout << "Login Success!";
      foundPasswd = true;
      break;
    }
  }
  if (foundPasswd != true) {
    cout << "Incorrect Password" << endl;
    cout << "Would you like to reset your password?" << endl;
    cout << "1.Yes\n2.No" << endl;
    cout << "Select an option: ";
    cin >> choice;
    switch (choice) {
    case 1:
      cout << "hi";
      break;
    case 2:
      cout << "hi";
      break;
    default:
      cout << "Invalid option. Exiting the program..";
      exit(0);
    }
  }
  file.close();
  exit(0);
}