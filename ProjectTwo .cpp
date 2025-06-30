/*
    ProjectTwo.cpp — CS 300 Advising Assistance Program
    Author : Rukhsar Amin
    Date   : 29 June 2025

    Description
    -----------
      A tiny console tool to help academic advisors:

        1.  Load a CSV file of Computer-Science courses
        2.  Print every course in alphanumeric order
        3.  Look up one course (title + prerequisites)
        9.  Exit gracefully

      •  Everything sits in ONE .cpp file, just as the rubric asks.
      •  Standard Library only—no external headers, no fancy tricks.
      •  Clear, human comments so my future self can follow along.
*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <cctype>

using namespace std;

/* -----------------------------  DATA TYPES  ----------------------------- */

struct Course
{
    string number;            // e.g.  CSCI200
    string title;             // e.g.  Data Structures
    vector<string> prereqs;   // zero or more prerequisite course numbers
};

/* ---------------------------  HELPER UTILITIES  ------------------------- */

// Trim whitespace from both ends of a string
static string trim(const string& s)
{
    const string WS = " \t\n\r\f\v";

    size_t start = s.find_first_not_of(WS);
    size_t end   = s.find_last_not_of(WS);
    return (start == string::npos) ? "" : s.substr(start, end - start + 1);
}

// Convert a string to upper-case (handy for case-insensitive look-ups)
static string toUpper(string s)
{
    transform(s.begin(), s.end(), s.begin(),
              [](unsigned char c){ return static_cast<char>(toupper(c)); });
    return s;
}

/* ----------------------------  GLOBAL STATE  --------------------------- */

map<string, Course> courseTable;   // Key = course number

/* ----------------------------  CORE FUNCTIONS  ------------------------- */

void loadDataStructure(const string& fileName)
{
    ifstream file(fileName);
    if (!file.is_open())
    {
        cout << "Couldn’t open "" << fileName << "" — check the path and try again.\n";
        return;
    }

    courseTable.clear();   // start fresh each time we load

    string line;
    while (getline(file, line))
    {
        line = trim(line);
        if (line.empty()) continue;     // skip empty lines

        stringstream ss(line);
        string cell;

        // Column 1 : course number
        getline(ss, cell, ',');
        string num = trim(cell);
        if (num.empty())
        {
            cout << "Skipping a row with no course number.\n";
            continue;
        }

        // Column 2 : course title
        if (!getline(ss, cell, ','))
        {
            cout << "Skipping " << num << " (no title found).\n";
            continue;
        }
        string title = trim(cell);

        // Build Course object
        Course c;
        c.number = num;
        c.title  = title;

        // Remaining columns : prerequisites (optional)
        while (getline(ss, cell, ','))
        {
            string pre = trim(cell);
            if (!pre.empty()) c.prereqs.push_back(pre);
        }

        courseTable[num] = c;
    }

    cout << "Loaded " << courseTable.size() << " courses from "" << fileName << "".\n\n";
}

void printCourseList()
{
    if (courseTable.empty())
    {
        cout << "→ Please load data first (menu option 1).\n\n";
        return;
    }

    vector<string> keys;
    for (const auto& pair : courseTable) keys.push_back(pair.first);
    sort(keys.begin(), keys.end());

    cout << "\nCourse List (A-Z)\n-----------------\n";
    for (const string& key : keys)
    {
        const Course& c = courseTable[key];
        cout << c.number << "  |  " << c.title << '\n';
    }
    cout << '\n';
}

void printCourse()
{
    if (courseTable.empty())
    {
        cout << "→ Load the data first (menu option 1).\n\n";
        return;
    }

    cout << "Enter a course number (e.g. CSCI400): ";
    string query;
    cin  >> query;
    query = toUpper(query);

    auto it = courseTable.find(query);
    if (it == courseTable.end())
    {
        cout << "Course not found — double-check the code and try again.\n\n";
        return;
    }

    const Course& c = it->second;

    cout << "\n" << c.number << "  |  " << c.title << '\n';
    cout << "Prerequisites: ";
    if (c.prereqs.empty())
    {
        cout << "None";
    }
    else
    {
        for (size_t i = 0; i < c.prereqs.size(); ++i)
        {
            cout << c.prereqs[i];
            if (i < c.prereqs.size() - 1) cout << ", ";
        }
    }
    cout << "\n\n";
}

/* -------------------------------  MAIN  -------------------------------- */

int main()
{
    cout << "Welcome to the Course Planner!\n\n";

    int choice = 0;
    while (choice != 9)
    {
        cout << "1. Load Data Structure\n"
                "2. Print Course List\n"
                "3. Print Course\n"
                "9. Exit\n\n"
                "What would you like to do? ";

        if (!(cin >> choice))
        {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Please enter a number from the menu.\n\n";
            continue;
        }

        switch (choice)
        {
            case 1:
            {
                cout << "CSV file name: ";
                string fileName;
                cin.ignore();               // flush leftover newline
                getline(cin, fileName);
                loadDataStructure(fileName);
                break;
            }
            case 2:
                printCourseList();
                break;
            case 3:
                printCourse();
                break;
            case 9:
                cout << "Goodbye — have a fabulous day!\n";
                break;
            default:
                cout << choice << " isn’t on the menu. Try again.\n\n";
        }
    }

    return 0;
}
