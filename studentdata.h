#ifndef STUDENTDATA_H
#define STUDENTDATA_H
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "studentrecord.h"
using namespace std;

class StudentData {

public:
	StudentRecord* record;
	StudentData();	// Constructor
	~StudentData();	// Destructor
	void setKey(int);
	void setSid(int);
	void setFirstname(string);
	void setLastname(string);
	void setMajor(string);
	void setNext(StudentData*);
	int getKey() const;
	int getSid() const;
	string getFirstname() const;
	string getLastname() const;
	string getFullname() const;
	string getMajor() const;
	StudentData* getNext() const;

private:
	int key;
	int sid;
	string firstname;
	string lastname;
	string major;
	StudentData *next;
};
#endif