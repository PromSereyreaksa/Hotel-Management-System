#include "adminAccount.h"
#include <cstdlib>
#include <iostream>
#include <stdlib.h>
using namespace std;

int main() {
  system("clear");
  int choice;
  cout << "Please select an option." << endl;
  cout << "1.Register" << endl;
  cout << "2.Login" << endl;
  cout << "3.Forgot password" << endl;
  cout << "4.Change Password" << endl;
  cout << "5.Exit" << endl;
  cout << "Select an option: ";
  cin >> choice;
  switch (choice) {
  case 1:
    system("clear");
    cout << "Welcome to the registration." << endl;
    createAdminAccount();
    break;
  case 2:
    system("clear");
    cout << "Welcome back!" << endl;
    login();
    goto adminDashboard;
  case 3:
    system("clear");
  forgotPassword();
    break;
    case 4:
    system("clear");
    changePassword();
    break;
  case 5:
    system("clear");
    cout << "Exiting program....." << endl;
    break;
  default:
    cout << "Invalid option. Exiting the program..";
    exit(0);
  }
  adminDashboard:
  cout << "Welcome to the admin dashboard" << endl;
}
