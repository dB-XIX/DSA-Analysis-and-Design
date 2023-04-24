/**
Michael Berry
CS300 - DSA Analysis & Design
SNHU
4/23/2023
Project 2
**/

#include <sstream>
#include <fstream>
#include <regex>
#include <iostream>
#include "Courses.h"

using namespace std;



void displayCourse(Course course) {
	vector<string> coursePrereqs = course.getPrereqs();
	string prerequisites;
	// formats prerequisites
	if (coursePrereqs.size() == 1) {
		prerequisites = course.getPrereqs()[0];
	}
	else if (coursePrereqs.size() > 1) {
		for (int i = 0; i < coursePrereqs.size() - 1; i++) {
			prerequisites += coursePrereqs[i] + ", ";
		}
		prerequisites += coursePrereqs.back();
	}
	else {
		prerequisites = "N/A";
	}

	// prints course information
	cout << course.getId() << ", "
		<< course.getName() << endl;
	cout << "Prerequisites: " << prerequisites << endl;
}

//Load an input file into data structure
void loadCourses(const string inputFile, Courses* coursesBst) {
	cout << "Loading input file " << inputFile << endl;

	ifstream file(inputFile);
	string currentLine;
	try {
		while (getline(file, currentLine)) {
			stringstream stream(currentLine);
			string word, id, name;
			vector<string> prerequisites;
			int index = 0;
			while (!stream.eof()) {
				getline(stream, word, ',');
				word = regex_replace(word, regex(R"(\r\n|\r|\n)"), "");
				if (index == 0) {
					id = word;
				}
				else if (index == 1) {
					name = word;
				}
				else {
					prerequisites.push_back(word);
				}
				index++;
			}
			// create a data structure
			Course course = Course(id, name, prerequisites);
			// add to tree
			coursesBst->Insert(course);
		}
	}
	catch (ifstream::failure e) {
		cerr << e.what() << endl;
	}

	file.close();
}

int main() {
	// Initialize binary search tree
	Courses* coursesBst;
	coursesBst = new Courses();
	Course course;
	string inputPath, courseKey;

	cout << "Welcome to the course planner." << endl << endl;

	int choice = 0;
	while (choice != 9) {
		cout << "  1. Load Data Structure" << endl;
		cout << "  2. Print Course List" << endl;
		cout << "  3. Print Course" << endl;
		cout << "  9. Exit" << endl << endl;
		cout << "What would you like to do? ";
		cin >> choice;

		switch (choice) {

		case 1:
			cout << "Enter the path for the input file: ";
			cin >> inputPath;

			// call to load courses
			loadCourses(inputPath, coursesBst);
			break;

		case 2:
			cout << "Here is a sample schedule: " << endl << endl;
			coursesBst->InOrder();
			break;

		case 3:
			cout << "What course do you want to learn about? ";
			cin >> courseKey;
			course = coursesBst->Search(courseKey);

			if (!course.getId().empty()) {
				displayCourse(course);
			}
			else {
				cout << "Course Id " << courseKey << " was not found." << endl;
			}
			break;

		case 9:
			cout << "Goodbye." << endl;
			break;

		default:
			cout << "Option " << choice << " is invalid." << endl;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			break;
		}
	}
	return 0;
}