#include "guestprofile.h"
#include <iostream>
#include <fstream>
#include <sstream>

void GuestProfile::createProfile(const std::string& guestID, const std::string& name, const std::string& contactInfo) {
    std::ofstream outFile("guest_profiles.csv", std::ios::app); // Open in append mode
    outFile << guestID << "," << name << "," << contactInfo << std::endl;
    outFile.close();
    std::cout << "Guest Profile Created!" << std::endl;
}

void GuestProfile::getProfile(const std::string& guestID) {
    std::ifstream inFile("guest_profiles.csv");
    std::string line;
    while (std::getline(inFile, line)) {
        std::istringstream stream(line);
        std::string id, name, contact;
        std::getline(stream, id, ',');
        std::getline(stream, name, ',');
        std::getline(stream, contact, ',');
        
        if (id == guestID) {
            std::cout << "Guest ID: " << id << ", Name: " << name << ", Contact Info: " << contact << std::endl;
            return;
        }
    }
    std::cout << "Guest ID not found!" << std::endl;
}

void GuestProfile::updateProfile(const std::string& guestID, const std::string& name, const std::string& contactInfo) {
    // Implement functionality to update a guest's profile in the CSV file
}

void GuestProfile::deleteProfile(const std::string& guestID) {
    std::ifstream inFile("guest_profiles.csv");
    std::ofstream tempFile("temp.csv");
    std::string line;
    
    while (std::getline(inFile, line)) {
        std::istringstream stream(line);
        std::string id, name, contact;
        std::getline(stream, id, ',');
        std::getline(stream, name, ',');
        std::getline(stream, contact, ',');
        
        if (id != guestID) {
            tempFile << line << std::endl;
        }
    }
    
    inFile.close();
    tempFile.close();
    
    remove("guest_profiles.csv");
    rename("temp.csv", "guest_profiles.csv");
    
    std::cout << "Guest Profile Deleted!" << std::endl;
}
