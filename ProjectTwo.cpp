#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

// Structure to represent a course
struct Course {
    std::string courseNumber;
    std::string title;
    std::vector<std::string> prerequisites;
};

// Vector to hold course data
std::vector<Course> courseData;

// Function to load course data from a CSV file
void loadDataStructure(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        Course course;
        std::getline(iss, course.courseNumber, ',');
        std::getline(iss, course.title, ',');

        std::string prereq;
        while (std::getline(iss, prereq, ',')) {
            course.prerequisites.push_back(prereq);
        }

        courseData.push_back(course);
    }

    file.close();
    std::cout << "Data loaded successfully." << std::endl;
}

// Function to print course information based on course number
void printCourseInfo(const std::string& courseNumber) {
    for (const Course& course : courseData) {
        if (course.courseNumber == courseNumber) {
            std::cout << course.courseNumber << ", " << course.title << std::endl;
            if (!course.prerequisites.empty()) {
                std::cout << "Prerequisites: ";
                for (const std::string& prereq : course.prerequisites) {
                    std::cout << prereq << ", ";
                }
                std::cout << "\b\b" << std::endl; // Remove trailing comma and space
            }
            return;
        }
    }
    std::cout << "Course not found." << std::endl;
}

// Function to print an alphanumeric course list
void printCourseList() {
    // Sort course data based on courseNumber
    std::sort(courseData.begin(), courseData.end(),
        [](const Course& a, const Course& b) {
            return a.courseNumber < b.courseNumber;
        });

    std::cout << "Here is a sample schedule:" << std::endl;
    for (const Course& course : courseData) {
        std::cout << course.courseNumber << ", " << course.title << std::endl;
    }
}

// Main program
int main() {
    int choice;
    std::string courseNumber;
    std::string filename = "ABCU_Advising_Program_Input.csv"; // CSV file containing course data

    std::cout << "Welcome to the course planner." << std::endl;

    do {
        // Display menu options
        std::cout << "1. Load Data Structure." << std::endl;
        std::cout << "2. Print Course List." << std::endl;
        std::cout << "3. Print Course." << std::endl;
        std::cout << "9. Exit" << std::endl;
        std::cout << "What would you like to do? ";
        std::cin >> choice;

        // Process user's choice
        switch (choice) {
        case 1:
            loadDataStructure(filename);
            break;
        case 2:
            printCourseList();
            break;
        case 3:
            std::cout << "What course do you want to know about? ";
            std::cin >> courseNumber;
            printCourseInfo(courseNumber);
            break;
        case 9:
            std::cout << "Thank you for using the course planner!" << std::endl;
            break;
        default:
            std::cout << choice << " is not a valid option." << std::endl;
        }

    } while (choice != 9);

    return 0;
}
