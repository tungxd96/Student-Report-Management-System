#include "course.h"

//--------------- Constructor ----------------
Course::Course() {}

//--------------- Destructor -----------------
Course::~Course() {}

//--------------- setCourse ------------------
void Course::setCourse(ifstream &infile) {
	string line, semicolon = "; ", element;
	int pos = 0, cur = 0;
	vector<string> major, courseId, courseTitle;
	vector<int> courseCredit;
	for (;;) {
		getline(infile, line);
		if (line != "") {
			while ((pos = line.find(semicolon)) != -1) {
				cur++;
				element = line.substr(0, pos);
				if (cur == 1) major.push_back(element);
				else if (cur == 2) courseId.push_back(element);
				else if (cur == 3) courseTitle.push_back(element);
				line.erase(0, pos + semicolon.length());
			}
			courseCredit.push_back(stoi(line));
			cur = 0;
		}
		if (infile.eof()) break;
	}
	for (int i = 0; i < courseTitle.size(); i++) {
			Course* report = new Course();
			course.push_back(*report);
			course[i].setMajor(major[i]);
			course[i].setCourseId(courseId[i]);
			course[i].setCourseTitle(courseTitle[i]);
			course[i].setCourseCredit(courseCredit[i]);
	}
}

void Course::display300() {
	for (int i = 0; i < course.size(); i++) {
		if (course[i].getCourseId() >= "300" && course[i].getCourseId() < "400") {
			cout << "    " << course[i].getMajor() << " " << course[i].getCourseId() << ": " << course[i].getCourseTitle() << " (Credit: " << course[i].getCourseCredit() << ")" << endl;
		}
	}
}

void Course::display400() {
	for (int i = 0; i < course.size(); i++) {
		if (course[i].getCourseId() >= "400" && course[i].getCourseId() < "500") {
			cout << "    " << course[i].getMajor() << " " << course[i].getCourseId() << ": " << course[i].getCourseTitle() << " (Credit: " << course[i].getCourseCredit() << ")" << endl;
		}
	}
}

int Course::getIndex(string courseId) {
	for (int i = 0; i < course.size(); i++) {
		if (course[i].getCourseId() == courseId) return i;
	}
	return -1;
}

string Course::getMajor(string courseId) {
	int index = getIndex(courseId);
	if (index != -1) {
		return course[index].getMajor();
	}
	return "";
}

string Course::getTitle(int index) {
	return course[index].getCourseTitle();
}

double Course::getCredit(int index) {
	return course[index].getCourseCredit();
}

void Course::setMajor(string major) {
	this->major = major;
}

void Course::setCourseId(string id) {
	this->courseId = id;
}

void Course::setCourseTitle(string title) {
	this->courseTitle = title;
}

void Course::setCourseCredit(double credit) {
	this->courseCredit = credit;
}

bool Course::checkTerm(string term) {
	if (term == "AUT" || term == "WIN" || term == "SPR" || term == "SUM") {
		return true;
	}
	return false;
}

string Course::getMajor() {
	return this->major;
}

string Course::getCourseId() {
	return this->courseId;
}

string Course::getCourseTitle() {
	return this->courseTitle;
}

double Course::getCourseCredit() {
	return this->courseCredit;
}