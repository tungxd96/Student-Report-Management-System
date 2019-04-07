#include "studentdata.h"

//--------------- Constructor ----------------
StudentData::StudentData() {
	next = nullptr;
	record = new StudentRecord();
}

//--------------- Destructor -----------------
StudentData::~StudentData() {}

void StudentData::setKey(int key) {
	this->key = key;
}

void StudentData::setSid(int sid) {
	this->sid = sid;
}

void StudentData::setFirstname(string firstname) {
	this->firstname = firstname;
}

void StudentData::setLastname(string lastname) {
	this->lastname = lastname;
}

void StudentData::setMajor(string major) {
	this->major = major;
}

void StudentData::setNext(StudentData *next) {
	this->next = next;
}

int StudentData::getKey() const {
	return this->key;
}

int StudentData::getSid() const {
	return this->sid;
}

string StudentData::getFirstname() const {
	return this->firstname;	
}

string StudentData::getLastname() const {
	return this->lastname;
}

string StudentData::getFullname() const {
	return this->firstname + ' ' + this->lastname;
}

string StudentData::getMajor() const {
	return this->major;
}

StudentData* StudentData::getNext() const {
	return next;
}
