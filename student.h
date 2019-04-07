#ifndef STUDENT_H
#define STUDENT_H
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "studentdata.h"
#include "studentrecord.h"
#include "course.h" 
using namespace std;

class Student : StudentData {
	
public:
	Course* course;
	Student(Course*);	// Constructor
	~Student();	// Destructor
	void setStudent(ifstream &);
	int find(int);
	string getFirstname(int);
	string getLastname(int);
	string getFullname(int);
	string getTerm(int, int);
	string getCourse(int, int);
	double getGpa(int, int);
	int getYear(int, int);
	int getCourseTotal(int);
	StudentData* getPos(int);
	void setTranscript(int, string, int, string, double);
	void setStudent(int, string, string, string);
	void displayTranscript(int);
	void displayTranscriptAll();
	void displayCourse(int);
	void editTerm(int, int, string);
	void editYear(int, int, int);
	void editCourse(int, int, string);
	void editGpa(int, int, double);
	void deleteRecord(int, int);
	void displayGpaScale();
	
private:
	StudentData** student;
	int size;
	string lastSid;
};
#endif