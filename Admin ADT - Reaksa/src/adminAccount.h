#include <algorithm>
#include <cctype>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
using namespace std;

string username, email, passwd,
    passwd_1; // declare global variable for other functions to check username;
// CREATE ACCOUNT
inline void createAdminAccount() {
  fstream file;
  string u;
  file.open("adminAccount.csv", ios::out);
  cout << "Enter your username: ";
  cin >> u;
  file << "Username: " << u << "\n";

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

inline void forgotPassword();

// LOGIN
inline void login() {
  cout << username;
  fstream file;
  string userData, passwdData;
  int choice;
  file.open("adminAccount.csv", ios::in);

  // handling no file case
  if (!file.is_open()) {
    cout << "Error: no user datafound. Please create an account";
    exit(0);
  }
  bool foundUser,
      foundPasswd; // boolean to check if user exists / if passwd is correct

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
  if (!foundUser) {
    cout << "Username not found" << endl;
    cout << "Would you like to create an account?" << endl;
    cout << "1.Yes\n2.No" << endl;
    cout << "Select an option: ";
    cin >> choice;
    switch (choice) {
    case 1:
      createAdminAccount();
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
  if (!foundPasswd) {
    cout << "Incorrect Password" << endl;
    cout << "Would you like to reset your password?" << endl;
    cout << "1.Yes\n2.No" << endl;
    cout << "Select an option: ";
    cin >> choice;
    switch (choice) {
    case 1:
      forgotPassword();
      break;
    case 2:
      exit(0);
      break;
    default:
      cout << "Invalid option. Exiting the program..";
      return;
    }
  }
  file.close();
  exit(0);
}

inline void forgotPassword() {
    fstream file;
    string newPasswd, newPasswd_1, oTPv;
    
    // Generate OTP
    srand(static_cast<unsigned int>(time(0)));
    int OTP = rand() % 1000000;
    cout << "Your OTP has been sent. Please check your file for the OTP." << endl;

    // Write OTP to a file
    file.open("OTP.csv", ios::out);
    file << OTP; // Save the OTP in the file
    file.close();

    // Prompt user to enter OTP
    cout << "Enter your OTP: ";
    cin >> oTPv;

    // Read the OTP from the file for verification
    string storedOTP;
    file.open("OTP.csv", ios::in);
    if (file.is_open()) {
        getline(file, storedOTP); // Read the OTP from the file
        file.close();
    } else {
        cout << "Error: Unable to open OTP file." << endl;
        return; // Exit if file can't be opened
    }

    // Check if the entered OTP matches the stored OTP
    if (to_string(OTP) == oTPv) {
        cout << "OTP verified successfully!" << endl;
    } else {
        cout << "Wrong OTP. Please try again later.";
        return; // Exit if OTP is incorrect
    }

    // Update password
    do {
        cout << "Enter your new password: ";
        cin >> newPasswd;
        cout << "Confirm your new password: ";
        cin >> newPasswd_1;

        if (newPasswd == newPasswd_1) {
            // Open the account file to read existing data
            fstream readFile("adminAccount.csv", ios::in);
            string line;
            string updatedData;
            bool usernameFound = false;

            while (getline(readFile, line)) {
                if (line.find("Username: " + username) != string::npos) {
                    usernameFound = true; // Username found
                    updatedData += line + "\n"; // Keep username line
                    getline(readFile, line); // Read the next line (password)
                    updatedData += "Password: " + newPasswd + "\n"; // Update password
                } else {
                    updatedData += line + "\n"; // Keep other lines unchanged
                }
            }
            readFile.close();

            // If the username was not found, handle accordingly (optional)
            if (!usernameFound) {
                cout << "Username not found. Unable to update password." << endl;
                return;
            }

            // Write the updated data back to the file
            fstream writeFile("adminAccount.csv", ios::out | ios::trunc);
            writeFile << updatedData;
            writeFile.close();

            cout << "Password updated successfully!" << endl;
        } else {
            cout << "Passwords do not match. Please try again.\n";
        }
    } while (newPasswd != newPasswd_1);
    exit(0);
}
inline void changePassword() {
    fstream file;
    int choice;
    string newPasswd, newPasswd_1, passwdData;
    bool foundPasswd;
    file.open("adminAccount.csv", ios::in);
    // Update password
    retry:
  cout << "Enter your current password: ";
  cin >> passwd;
  while (file >> passwdData) {
    if (passwdData.compare(passwd) == 0) {
      foundPasswd = true;
      break;
    }
  }
  if (!foundPasswd) {
    cout << "Incorrect Password" << endl;
    cout << "Would you like to reset your password?" << endl;
    cout << "1.Yes\n2.Return to login" << endl;
    cout << "Select an option: ";
    cin >> choice;
    switch (choice) {
    case 1:
      forgotPassword();
      break;
    case 2:
      goto retry;
      break;
    default:
      cout << "Invalid option. Exiting the program..";
      exit(0);
    }
  }
  file.close();
    do {
        cout << "Enter your new password: ";
        cin >> newPasswd;
        cout << "Confirm your new password: ";
        cin >> newPasswd_1;

        if (newPasswd == newPasswd_1) {
            // Open the account file to read existing data
            fstream readFile("adminAccount.csv", ios::in);
            string line;
            string updatedData;
            bool usernameFound = false;

            while (getline(readFile, line)) {
                if (line.find("Username: " + username) != string::npos) {
                    usernameFound = true; // Username found
                    updatedData += line + "\n"; // Keep username line
                    getline(readFile, line); // Read the next line (password)
                    updatedData += "Password: " + newPasswd + "\n"; // Update password
                } else {
                    updatedData += line + "\n"; // Keep other lines unchanged
                }
            }
            readFile.close();

            // If the username was not found, handle accordingly (optional)
            if (!usernameFound) {
                cout << "Username not found. Unable to update password." << endl;
                return;
            }

            // Write the updated data back to the file
            fstream writeFile("adminAccount.csv", ios::out | ios::trunc);
            writeFile << updatedData;
            writeFile.close();

            cout << "Password updated successfully!" << endl;
        } else {
            cout << "Passwords do not match. Please try again.\n";
        }
    } while (newPasswd != newPasswd_1);
    exit(0);
}