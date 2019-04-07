#ifndef COURSE_H
#define COURSE_H
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

class Course {
	
public:
	Course();	// Constructor
	~Course();	// Destructor
	void setMajor(string);
	void setCourseId(string);
	void setCourseTitle(string);
	void setCourseCredit(double);
	void display300();
	void display400();
	string getMajor();
	string getMajor(string);
	string getCourseId();
	string getCourseTitle();
	double getCourseCredit();
	void setCourse(ifstream &);
	int getIndex(string);
	string getTitle(int);
	double getCredit(int);
	bool checkTerm(string);
	
private:
	vector<Course> course;
	string major;
	string courseId;
	string courseTitle;
	double courseCredit;
	
};
#endif