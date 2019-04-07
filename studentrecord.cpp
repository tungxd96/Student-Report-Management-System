#include "studentrecord.h"

//--------------- Constructor ----------------
StudentRecord::StudentRecord() {}

//--------------- Destructor -----------------
StudentRecord::~StudentRecord() {}

void StudentRecord::setTerm(string term) {
	this->term.push_back(term);
}

void StudentRecord::setYear(int year) {
	this->year.push_back(year);
}

void StudentRecord::setCourseId(string courseId) {
	this->courseId.push_back(courseId);
}

void StudentRecord::setGpa(double gpa) {
	this->gpa.push_back(gpa);
}

void StudentRecord::setCredit(double cre) {
	this->credit += cre;
}

void StudentRecord::editTerm(int index, string term) {
	this->term[index] = term;
}

void StudentRecord::editYear(int index, int year) {
	this->year[index] = year;
}

void StudentRecord::editCourse(int index, string courseId) {
	this->courseId[index] = courseId;
}

void StudentRecord::editGpa(int index, double gpa) {
	this->gpa[index] = gpa;
}

void StudentRecord::deleteRecord(int index) {
	this->term.erase(this->term.begin() + index);
	this->year.erase(this->year.begin() + index);
	this->courseId.erase(this->courseId.begin() + index);
	this->gpa.erase(this->gpa.begin() + index);
}

vector<string> StudentRecord::getTerm() const {
	return this->term;
}

vector<int> StudentRecord::getYear() const {
	return this->year;
}

vector<string> StudentRecord::getCourseId() const {
	return this->courseId;
}

vector<double> StudentRecord::getGpa() const {
	return this->gpa;
}

double StudentRecord::getCum() {
	double total = 0;
	for (int i = 0; i < gpa.size(); i++) {
		total += gpa[i];
	}
	if (gpa.size() > 0) {
		cum = total/(double) gpa.size();
	} else {
		cum = 0;
	}
	return cum;
}

double StudentRecord::getCredit() {
	return this->credit;
}