/**
Michael Berry
CS300 - DSA Analysis & Design
SNHU
4/23/2023
Project 2
**/

#ifndef COURSE_H
#define COURSE_H

#include <vector>
#include <string>

using namespace std;

class Course {
	// private fields
private:
	vector<string> coursePrerequisites;
	string courseName;
	string courseId;

	// public methods
public:
	Course() = default;
	Course(string id, string name, vector<string> prerequisites);
	string courseToString();
	string getName();
	vector<string> getPrereqs();
	string getId();
};

#endif
