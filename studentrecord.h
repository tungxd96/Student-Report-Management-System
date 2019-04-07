#ifndef STUDENTRECORD_H
#define STUDENTRECORD_H
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "course.h"
using namespace std;

class StudentRecord {
	
public:
	StudentRecord();	// Constructor
	~StudentRecord();	// Destructor
	void setTerm(string);
	void setYear(int);
	void setCourseId(string);
	void setGpa(double);
	void setCredit(double);
	void editTerm(int, string);
	void editYear(int, int);
	void editCourse(int, string);
	void editGpa(int, double);
	void deleteRecord(int);
	vector<string> getTerm() const;
	vector<int> getYear() const;
	vector<string> getCourseId() const;
	vector<double> getGpa() const;
	double getCum();
	double getCredit();
	void displayTranscript();
	
private:
	double cum;
	double credit;
	vector<string> term;
	vector<int> year;
	vector<string> courseId;
	vector<double> gpa;
	
};
#endif