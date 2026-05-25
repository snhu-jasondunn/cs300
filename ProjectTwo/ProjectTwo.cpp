//============================================================================
// Name        : ProjectTwo.cpp
// Author      : Jason Dunn
// Description : CS 300 Project Two - ABCU Course Planner using a Hash Table
//============================================================================

#include <algorithm>
#include <cctype>
#include <fstream>
#include <iostream>
#include <limits>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

const string COURSE_FILE_NAME = "CS 300 ABCU_Advising_Program_Input.csv";
const unsigned int DEFAULT_TABLE_SIZE = 101;

// Course object stored in the hash table.
struct Course {
    string courseNumber;
    string title;
    vector<string> prerequisites;
};

/**
 * Remove leading and trailing whitespace from a string.
 */
string trim(const string& value) {
    size_t first = value.find_first_not_of(" \t\r\n");
    if (first == string::npos) {
        return "";
    }

    size_t last = value.find_last_not_of(" \t\r\n");
    return value.substr(first, last - first + 1);
}

/**
 * Convert a string to uppercase so user course searches are case-insensitive.
 */
string toUpperCase(string value) {
    transform(value.begin(), value.end(), value.begin(), [](unsigned char ch) {
        return static_cast<char>(toupper(ch));
        });

    return value;
}

/**
 * Split a CSV line into fields. This supports quoted fields and does not need
 * an external CSVParser header or source file.
 */
vector<string> parseCsvLine(const string& line) {
    vector<string> fields;
    string currentField;
    bool insideQuotes = false;

    for (size_t i = 0; i < line.length(); ++i) {
        char ch = line[i];

        if (ch == '"') {
            // Handle escaped quotes inside quoted fields.
            if (insideQuotes && i + 1 < line.length() && line[i + 1] == '"') {
                currentField += '"';
                ++i;
            }
            else {
                insideQuotes = !insideQuotes;
            }
        }
        else if (ch == ',' && !insideQuotes) {
            fields.push_back(trim(currentField));
            currentField.clear();
        }
        else {
            currentField += ch;
        }
    }

    fields.push_back(trim(currentField));
    return fields;
}

/**
 * Hash table using separate chaining. Courses are hashed by course number.
 */
class CourseHashTable {
private:
    struct Node {
        Course course;
        Node* next;

        Node(const Course& aCourse) {
            course = aCourse;
            next = nullptr;
        }
    };

    vector<Node*> table;
    unsigned int tableSize;
    unsigned int courseCount;

    unsigned int hash(const string& courseNumber) const {
        unsigned int hashValue = 0;

        for (char ch : courseNumber) {
            hashValue = (hashValue * 31 + static_cast<unsigned char>(ch)) % tableSize;
        }

        return hashValue;
    }

public:
    CourseHashTable(unsigned int size = DEFAULT_TABLE_SIZE) {
        tableSize = size;
        courseCount = 0;
        table.resize(tableSize, nullptr);
    }

    ~CourseHashTable() {
        clear();
    }

    void clear() {
        for (Node*& bucket : table) {
            Node* current = bucket;

            while (current != nullptr) {
                Node* temp = current;
                current = current->next;
                delete temp;
            }

            bucket = nullptr;
        }

        courseCount = 0;
    }

    void insert(const Course& course) {
        unsigned int index = hash(course.courseNumber);
        Node* current = table[index];

        // Update an existing course if the course number is already present.
        while (current != nullptr) {
            if (current->course.courseNumber == course.courseNumber) {
                current->course = course;
                return;
            }
            current = current->next;
        }

        Node* newNode = new Node(course);
        newNode->next = table[index];
        table[index] = newNode;
        ++courseCount;
    }

    const Course* search(const string& courseNumber) const {
        unsigned int index = hash(courseNumber);
        Node* current = table[index];

        while (current != nullptr) {
            if (current->course.courseNumber == courseNumber) {
                return &(current->course);
            }
            current = current->next;
        }

        return nullptr;
    }

    bool contains(const string& courseNumber) const {
        return search(courseNumber) != nullptr;
    }

    bool empty() const {
        return courseCount == 0;
    }

    vector<Course> getAllCourses() const {
        vector<Course> courses;
        courses.reserve(courseCount);

        for (Node* bucket : table) {
            Node* current = bucket;
            while (current != nullptr) {
                courses.push_back(current->course);
                current = current->next;
            }
        }

        return courses;
    }
};

/**
 * Load course data from the hardcoded CSV file into the hash table.
 * Expected format per row: courseNumber, title, prerequisite1, prerequisite2, ...
 */
bool loadCourses(CourseHashTable& courses) {
    ifstream inputFile(COURSE_FILE_NAME);

    if (!inputFile.is_open()) {
        cout << "Error: Could not open file " << COURSE_FILE_NAME << "." << endl;
        return false;
    }

    CourseHashTable loadedCourses;
    string line;
    int lineNumber = 0;

    while (getline(inputFile, line)) {
        ++lineNumber;

        if (trim(line).empty()) {
            continue;
        }

        vector<string> fields = parseCsvLine(line);

        if (fields.size() < 2 || fields[0].empty() || fields[1].empty()) {
            cout << "Error: Invalid course data on line " << lineNumber << "." << endl;
            return false;
        }

        Course course;
        course.courseNumber = toUpperCase(fields[0]);
        course.title = fields[1];

        for (size_t i = 2; i < fields.size(); ++i) {
            string prerequisite = toUpperCase(fields[i]);
            if (!prerequisite.empty()) {
                course.prerequisites.push_back(prerequisite);
            }
        }

        loadedCourses.insert(course);
    }

    // Validate that every prerequisite listed in the file exists as a course.
    vector<Course> loadedCourseList = loadedCourses.getAllCourses();
    for (const Course& course : loadedCourseList) {
        for (const string& prerequisite : course.prerequisites) {
            if (!loadedCourses.contains(prerequisite)) {
                cout << "Error: Course " << course.courseNumber
                    << " lists missing prerequisite " << prerequisite << "." << endl;
                return false;
            }
        }
    }

    courses.clear();
    for (const Course& course : loadedCourseList) {
        courses.insert(course);
    }

    cout << "Data loaded successfully." << endl;
    return true;
}

/**
 * Print all courses in alphanumeric order.
 */
void printCourseList(const CourseHashTable& courses) {
    vector<Course> sortedCourses = courses.getAllCourses();

    sort(sortedCourses.begin(), sortedCourses.end(), [](const Course& left, const Course& right) {
        return left.courseNumber < right.courseNumber;
        });

    cout << "Here is a sample schedule:" << endl;

    for (const Course& course : sortedCourses) {
        cout << course.courseNumber << ", " << course.title << endl;
    }
}

/**
 * Print one course and its prerequisites.
 */
void printCourseInformation(const CourseHashTable& courses) {
    string courseNumber;

    cout << "What course do you want to know about? ";
    cin >> courseNumber;
    courseNumber = toUpperCase(trim(courseNumber));

    const Course* course = courses.search(courseNumber);
    if (course == nullptr) {
        cout << "Course " << courseNumber << " was not found." << endl;
        return;
    }

    cout << course->courseNumber << ", " << course->title << endl;

    if (course->prerequisites.empty()) {
        cout << "Prerequisites: None" << endl;
        return;
    }

    cout << "Prerequisites: ";
    for (size_t i = 0; i < course->prerequisites.size(); ++i) {
        const string& prerequisiteNumber = course->prerequisites[i];
        const Course* prerequisiteCourse = courses.search(prerequisiteNumber);

        cout << prerequisiteNumber;
        if (prerequisiteCourse != nullptr) {
            cout << " (" << prerequisiteCourse->title << ")";
        }

        if (i + 1 < course->prerequisites.size()) {
            cout << ", ";
        }
    }
    cout << endl;
}

/**
 * Display the program menu.
 */
void displayMenu() {
    cout << "1. Load Data Structure." << endl;
    cout << "2. Print Course List." << endl;
    cout << "3. Print Course." << endl;
    cout << "9. Exit" << endl;
    cout << "What would you like to do? ";
}

int main() {
    CourseHashTable courses;
    bool dataLoaded = false;
    int choice = 0;

    cout << "Welcome to the course planner." << endl;

    while (choice != 9) {
        displayMenu();

        if (!(cin >> choice)) {
            cout << "Invalid input. Please enter a number from the menu." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        switch (choice) {
        case 1:
            dataLoaded = loadCourses(courses);
            break;
        case 2:
            if (!dataLoaded) {
                cout << "Please load the course data first." << endl;
            }
            else {
                printCourseList(courses);
            }
            break;
        case 3:
            if (!dataLoaded) {
                cout << "Please load the course data first." << endl;
            }
            else {
                printCourseInformation(courses);
            }
            break;
        case 9:
            cout << "Thank you for using the course planner!" << endl;
            break;
        default:
            cout << choice << " is not a valid option." << endl;
            break;
        }
    }

    return 0;
}
