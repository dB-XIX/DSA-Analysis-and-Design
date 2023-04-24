/**
Michael Berry
CS300 - DSA Analysis & Design
SNHU
4/23/2023
Project 2
**/

#include "Course.h"

using namespace std;

// Constructor
Course::Course(string id, string name, vector<string> prerequisites) {
	this->courseName = name;
	this->courseId = id;
	this->coursePrerequisites = prerequisites;
}

// Get course prerequisites
vector<string> Course::getPrereqs() {
	return this->coursePrerequisites;
}

// Get course name
string Course::getName() {
	return this->courseName;
}

// Get course id
string Course::getId() {
	return this->courseId;
}

// String of course values
string Course::courseToString() {
	return this->courseId + ", " + this->courseName;
}