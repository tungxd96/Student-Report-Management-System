#include "student.h"

//--------------- Constructor ----------------
Student::Student(Course* course) {
	this->course = course; 
	size = 50;
	student = new StudentData*[size];
	for (int i = 0; i < size; i++) {
		student[i] = new StudentData();
		student[i]->setKey(i);
		student[i]->setSid(-1);
		student[i]->setFirstname("");
		student[i]->setLastname("");
		student[i]->setMajor("");
		student[i]->setNext(nullptr);
	}
}

//--------------- Destructor -----------------
Student::~Student() {}

//--------------- setStudent -----------------
void Student::setStudent(ifstream &infile) {
	string space = " ", line, element;
	int pos = 0, index = 0;
	vector<string> sid, firstname, lastname, major;
	for(;;) {
		getline(infile, line);
		if (line != "") {
			while ((pos = line.find(space)) != -1) {
				index++;
				element = line.substr(0, pos);
				if (index == 1) sid.push_back(element);
				else if (index == 2) major.push_back(element);
				else if (index == 3) firstname.push_back(element);
				else if (index > 3) firstname[firstname.size()-1] += " " + element;
				line.erase(0, pos + space.length());
			}
			index = 0;
			lastname.push_back(line);
		}
		if (infile.eof()) break;
	}
	lastSid = sid[sid.size() - 1];
	for (int i = 0; i < sid.size(); i++) {
		int key = stoi(sid[i]) % size;
		if (student[key]->getSid() == -1) {
			student[key]->setKey(key);
			student[key]->setSid(stoi(sid[i]));
			student[key]->setFirstname(firstname[i]);
			student[key]->setLastname(lastname[i]);
			student[key]->setMajor(major[i]);
		} else {
			if (student[key]->getSid() != stoi(sid[i])) {
				StudentData *cur = student[key];
				while (cur->getNext() != nullptr) {
					cur = cur->getNext();
				}
				StudentData *entry = new StudentData();
				cur->setNext(entry);
				cur = cur->getNext();
				cur->setKey(key);
				cur->setSid(stoi(sid[i]));
				cur->setFirstname(firstname[i]);
				cur->setLastname(lastname[i]);
				cur->setMajor(major[i]);
				cur->setNext(nullptr);
			}
		}
	}
}

void Student::setStudent(int sid, string firstname, string lastname, string major) {
	int key = sid % size;
	if (student[key]->getSid() == -1) {
		student[key]->setKey(key);
		student[key]->setSid(sid);
		student[key]->setFirstname(firstname);
		student[key]->setLastname(lastname);
		student[key]->setMajor(major);
	} else {
		if (student[key]->getSid() != sid) {
			StudentData *cur = student[key];
			while (cur->getNext() != nullptr) {
				cur = cur->getNext();
			}
			StudentData *entry = new StudentData();
			cur->setNext(entry);
			cur = cur->getNext();
			cur->setKey(key);
			cur->setSid(sid);
			cur->setFirstname(firstname);
			cur->setLastname(lastname);
			cur->setMajor(major);
			cur->setNext(nullptr);
		}
	}
}

int Student::find(int sid) {
	int key = sid % size;
	StudentData* cur = student[key];
	if (cur->getSid() != -1) {
		while (cur->getSid() != sid && cur->getNext() != nullptr) {
			cur = cur->getNext();
		}
		return key;
	} 
	return -1;
}

string Student::getFirstname(int sid) {
	StudentData* cur = getPos(sid);
	if (cur != nullptr) {			
		return cur->getFirstname();
	}
	return "";
}

string Student::getLastname(int sid) {
	StudentData* cur = getPos(sid);
	if (cur != nullptr) {			
		return cur->getLastname();
	}
	return "";
}

//-------------------------- getFullname ----------------------------
string Student::getFullname(int sid) {
	StudentData* cur = getPos(sid);
	if (cur != nullptr) {
		return cur->getFirstname() + " " + cur->getLastname();
	}
	return "";
}

//-------------------------- setTranscript ---------------------------
void Student::setTranscript(int sid, string term, int year, string courseId, double grade) {
	StudentData* cur = getPos(sid);
	if (cur != nullptr) {
		int courseIndex = course->getIndex(courseId);
		cur->record->setTerm(term);
		cur->record->setYear(year);
		cur->record->setCourseId(courseId);
		cur->record->setGpa(grade);
		cur->record->setCredit(course->getCredit(courseIndex));
	}
}

//----------------------- displayTranscript --------------------------
void Student::displayTranscript(int sid) {
	StudentData* cur = getPos(sid);
	if (cur != nullptr) {
		cout << "\n------------------------------------------------- Unofficial Transcript ------------------------------------------------" << endl;
		cout << "UNIVERSITY OF WASHINGTON BOTHELL CAMPUS" << endl;
		cout << "Student No." << '\t' << "Name" << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << "Major" << endl;
		if (cur->getSid() != stoi(lastSid)) {
			if (cur->getMajor() == "CSSE") {
				cout << sid << '\t' << '\t' << cur->getFullname() << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << "Computer Science & Software Engineer" << endl;
			} else if (cur->getMajor() == "CSS") {
				cout << sid << '\t' << '\t' << cur->getFullname() << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << "Computing & Software Systems" << endl;
			}
		} else {
			if (cur->getMajor() == "CSSE") {
				cout << sid << '\t' << '\t' << cur->getFullname() << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << "Computer Science & Software Engineer" << endl;
			} else if (cur->getMajor() == "CSS") {
				cout << sid << '\t' << '\t' << cur->getFullname() << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << "Computing & Software Systems" << endl;
			}
		}
		
		cout << "Course" << '\t' << '\t' << "Title" << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << "Credits" << '\t' << '\t' << "Grade" << '\t' << '\t' << "Term" << endl;
		for (int i = 0; i < cur->record->getCourseId().size(); i++) {
			int courseIndex = course->getIndex(cur->record->getCourseId()[i]);
			string courseTitle = course->getTitle(courseIndex);
			if (cur->getMajor() == "CSSE" || cur->getMajor() == "CSS") {
				cout << "CSS " << cur->record->getCourseId()[i] << '\t' << '\t' << courseTitle; 
				for (int j = 0; j < 8 - courseTitle.length()/8; j++) cout << '\t';
				cout.precision(1);
				cout << fixed << course->getCredit(courseIndex) << '\t' << '\t' << fixed << cur->record->getGpa()[i] << '\t' << '\t' << cur->record->getTerm()[i] << " " << cur->record->getYear()[i] << endl;
			}
		}
		cout.precision(1);
		cout << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << "EARNED: " << fixed << cur->record->getCredit();
		cout.precision(2);
		cout << '\t' << "CUM GPA: " << fixed << cur->record->getCum() << endl;
		cout << endl;
	} else {
		cout << "Student ID Not Found." << endl;
	}
}

void Student::displayTranscriptAll() {
	for (int i = 0; i < size; i++) {
		StudentData* cur = student[i];
		if (cur->getSid() != -1) {
			displayTranscript(cur->getSid());
			while (cur->getNext() != nullptr) {
				cur = cur->getNext();
				displayTranscript(cur->getSid());
			}
		}
	}
}

void Student::displayCourse(int sid) {
	StudentData* cur = getPos(sid);
	if (cur != nullptr) {
		cout << "    No. | Course | GPA | Term " << endl;
		for (int i = 0; i < cur->record->getCourseId().size(); i++) {
			if (cur->getMajor() == "CSSE" || cur->getMajor() == "CSS") {
				if (cur->record->getCourseId()[i] != "") {
					cout << "    " << i+1;
					for (int j = 0; j < 4 - to_string(i+1).length(); j++) {
						cout << " ";
					}
					cout.precision(1);
					cout << "| CSS" << cur->record->getCourseId()[i] << " | " << fixed << cur->record->getGpa()[i] << " | " << cur->record->getTerm()[i] << cur->record->getYear()[i] << endl;
				}
			}
		}
		cout << endl;
	}
}

void Student::displayGpaScale() {
	cout << "    Achievements|Approximately Corresponding Numeric Grade" << endl;
	cout << "    60s         |0.7-1.4" << endl;
	cout << "    70s         |1.5-2.4" << endl;
	cout << "    80s         |2.5-3.4" << endl;
	cout << "    90s         |3.5-4.0" << endl;
}

void Student::deleteRecord(int sid, int index) {
	StudentData* cur = getPos(sid);
	if (cur != nullptr) {
		cur->record->editTerm(index-1, "");
		cur->record->editYear(index-1, -1);
		cur->record->editCourse(index-1, "");
		cur->record->editGpa(index-1, -1);
		cur->record->deleteRecord(index-1);
	}
}

int Student::getCourseTotal(int sid) {
	StudentData* cur = getPos(sid);
	if (cur != nullptr) {
		return cur->record->getCourseId().size();
	}
	return -1;
}

void Student::editTerm(int sid, int index, string term) {
	StudentData* cur = getPos(sid);
	if (cur != nullptr) {
		cur->record->editTerm(index-1, term);
	}
}

void Student::editYear(int sid, int index, int year) {
	StudentData* cur = getPos(sid);
	if (cur != nullptr) {
		cur->record->editYear(index-1, year);
	}
}

void Student::editCourse(int sid, int index, string courseId) {
	StudentData* cur = getPos(sid);
	if (cur != nullptr) {
		cur->record->editCourse(index-1, courseId);
	}
}

void Student::editGpa(int sid, int index, double gpa) {
	StudentData* cur = getPos(sid);
	if (cur != nullptr) {
		cur->record->editGpa(index-1, gpa);
	}
}

string Student::getTerm(int sid, int index) {
	StudentData* cur = getPos(sid);
	if (cur != nullptr) {
		return cur->record->getTerm()[index-1];
	}
	return "";
}

int Student::getYear(int sid, int index) {
	StudentData* cur = getPos(sid);
	if (cur != nullptr) {
		return cur->record->getYear()[index-1];
	}
	return -1;
}

string Student::getCourse(int sid, int index) {
	StudentData* cur = getPos(sid);
	if (cur != nullptr) {
		return cur->record->getCourseId()[index-1];
	}
	return "";
}

double Student::getGpa(int sid, int index) {
	StudentData* cur = getPos(sid);
	if (cur != nullptr) {
		return cur->record->getGpa()[index-1];
	}
	return -1;
}

StudentData* Student::getPos(int sid) {
	int key = find(sid);
	StudentData* cur = student[key];
	if (key != -1) {
		while (cur->getSid() != sid && cur->getNext() != nullptr) {
			cur = cur->getNext();
		}
		return cur;
	}
	return nullptr;
}








