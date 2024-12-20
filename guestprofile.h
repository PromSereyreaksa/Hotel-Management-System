#ifndef GUESTPROFILE_H
#define GUESTPROFILE_H

#include <string>

class GuestProfile {
public:
    std::string guestID;
    std::string name;
    std::string contactInfo;
    
    GuestProfile(const std::string& guestID, const std::string& name, const std::string& contactInfo)
        : guestID(guestID), name(name), contactInfo(contactInfo) {}
    
    void createProfile(const std::string& guestID, const std::string& name, const std::string& contactInfo);
    void getProfile(const std::string& guestID);
    void updateProfile(const std::string& guestID, const std::string& name, const std::string& contactInfo);
    void deleteProfile(const std::string& guestID);
};

#endif
