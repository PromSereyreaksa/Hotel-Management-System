#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <unordered_map>

// Structure for a Report
struct Report {
    int reportID;
    std::string type;
    std::string date;
    std::string data;
};

// Function to parse a line of CSV into a Report object
Report parseReport(const std::string& line) {
    std::istringstream stream(line);
    std::string field;
    Report report;

    // Parse the fields
    std::getline(stream, field, ',');
    report.reportID = std::stoi(field);

    std::getline(stream, report.type, ',');

    std::getline(stream, report.date, ',');

    std::getline(stream, report.data, ',');

    return report;
}

// Function to split date into components (year, month, day)
std::vector<int> splitDate(const std::string& date) {
    std::istringstream stream(date);
    std::string part;
    std::vector<int> components;

    while (std::getline(stream, part, '-')) {
        components.push_back(std::stoi(part));
    }
    return components;
}

// Sequential Access: List all reports
void listAllReports(const std::string& filename) {
    std::ifstream file(filename);
    std::string line;

    // Skip the header
    std::getline(file, line);

    // Read and display all reports
    while (std::getline(file, line)) {
        Report report = parseReport(line);
        std::cout << "ReportID: " << report.reportID
                  << ", Type: " << report.type
                  << ", Date: " << report.date
                  << ", Data: " << report.data << "\n";
    }
    file.close();
}

// Filter by Day
void filterReportsByDay(const std::string& filename, const std::string& targetDate) {
    std::ifstream file(filename);
    std::string line;

    // Skip the header
    std::getline(file, line);

    // Filter reports by date
    while (std::getline(file, line)) {
        Report report = parseReport(line);
        if (report.date == targetDate) {
            std::cout << "ReportID: " << report.reportID
                      << ", Type: " << report.type
                      << ", Data: " << report.data << "\n";
        }
    }
    file.close();
}

// Filter by Month
void filterReportsByMonth(const std::string& filename, int year, int month) {
    std::ifstream file(filename);
    std::string line;

    // Skip the header
    std::getline(file, line);

    // Filter reports by month
    while (std::getline(file, line)) {
        Report report = parseReport(line);
        std::vector<int> dateComponents = splitDate(report.date);

        if (dateComponents[0] == year && dateComponents[1] == month) {
            std::cout << "ReportID: " << report.reportID
                      << ", Type: " << report.type
                      << ", Date: " << report.date
                      << ", Data: " << report.data << "\n";
        }
    }
    file.close();
}

// Filter by Year
void filterReportsByYear(const std::string& filename, int year) {
    std::ifstream file(filename);
    std::string line;

    // Skip the header
    std::getline(file, line);

    // Filter reports by year
    while (std::getline(file, line)) {
        Report report = parseReport(line);
        std::vector<int> dateComponents = splitDate(report.date);

        if (dateComponents[0] == year) {
            std::cout << "ReportID: " << report.reportID
                      << ", Type: " << report.type
                      << ", Date: " << report.date
                      << ", Data: " << report.data << "\n";
        }
    }
    file.close();
}

// Main function demonstrating usage
int main() {
    std::string filename = "reports.csv";

    // List all reports
    std::cout << "1. List All Reports\n";
    listAllReports(filename);

    // Filter reports by a specific day
    std::cout << "\n2. Reports for a Specific Day (2023-12-01):\n";
    filterReportsByDay(filename, "2023-08-17");

    // Filter reports by a specific month
    std::cout << "\n3. Reports for a Specific Month (December 2023):\n";
    filterReportsByMonth(filename, 2023, 12);

    // Filter reports by a specific year
    std::cout << "\n4. Reports for a Specific Year (2023):\n";
    filterReportsByYear(filename, 2023);

    return 0;
}
