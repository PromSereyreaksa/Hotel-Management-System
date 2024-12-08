#include "adminAccount.h"
#include <iostream>
#include <stdlib.h>
using namespace std;

int main() {
  system("clear");
  int choice;
  cout << "Welcome to the admin dashboard" << endl;
  cout << "Please select an option." << endl;
  cout << "1.Register" << endl;
  cout << "2.Login" << endl;
  cout << "3.Reset your password" << endl;
  cout << "4.Exit" << endl;
  cout << "Select an option: ";
  cin >> choice;
  switch (choice) {
  case 1:
    system("clear");
    cout << "Welcome to the registration." << endl;
    createAdminAccount("adminAccount.csv");
    break;
  case 2:
    system("clear");
    cout << "Welcome back!" << endl;
    login();
  case 3:
    system("clear");
    break;
  case 4:
    system("clear");
    cout << "Exiting program....." << endl;
    break;
  default:
    cout << "Invalid option. Exiting the program..";
    exit(0);
  }
}
