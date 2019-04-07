#include "course.h"
#include "student.h"
#include "studentdata.h"
#include "studentrecord.h"
#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <sstream>

const string CLEAR = "\033[2J\033[1;1H";
const string EXIT = "-1";
void setGpa(ifstream &, Student*, Course*, ofstream &);
void intro();
void main_menu(Student*, Course*, ofstream &);
void displayAll(Student*);
void display(Student*, int);
void modify(Student*, Course*, ofstream &);
void modify_term(string &, int &);
void create(Student*, Course*, ofstream &);
void returnMain(Student*, Course*, ofstream &);
void modify_course(string &, bool &, Course*);
void modify_gpa(Student*, double &, bool &);
void savingRequest();
string editOption();

int main() {
	
	ofstream out("temp.txt");
	ifstream coursefile("coursedata.txt");
	if(!coursefile) {
		cout << "File could not be opened." << endl;
		return 1;
	}
	Course* course = new Course();
	course->setCourse(coursefile);
	
	ifstream studentfile("studentdata.txt");
	if(!studentfile) {
		cout << "File could not be opened." << endl;
		return 1;
	}
	Student* student = new Student(course);
	student->setStudent(studentfile);
	studentfile.clear();
	
	ifstream gpafile("gpadata.txt");
	if(!gpafile) {
		cout << "File could not be opened." << endl;
		return 1;
	}
	setGpa(gpafile, student, course, out);
	gpafile.clear();
	
	intro();
	main_menu(student, course, out);

}

void setGpa(ifstream &infile, Student* student, Course* course, ofstream &out) {
	string space = " ", line, element;
	int pos = 0, cur = 0, year;
	string sid, term, courseId;
	double grade;
	for(;;) {
		getline(infile, line);
		out << line << endl;
		if (line != "") {
			while ((pos = line.find(space)) != -1) {
				cur++;
				element = line.substr(0, pos);
				if (cur == 1) sid = element;
				else if (cur == 2) term = element;
				else if (cur == 3) year = stoi(element);
				else if (cur == 4) courseId = element;
				line.erase(0, pos + space.length());
			}
			cur = 0;
			grade = stod(line);
			if (student->find(stoi(sid)) != -1 && course->getIndex(courseId) != -1 && course->checkTerm(term)) {
				student->setTranscript(stoi(sid), term, year, courseId, grade);
			}
		}
		if(infile.eof()) break;
	}
}

void intro() {
	cout << CLEAR;
	cout << "\n" << '\t' << "   " << "STUDENT" << endl;
	cout << '\t' << " " << "REPORT CARD" << endl;
	cout << '\t' << "   " << "PROJECT" << endl;
	cout << "     " << "MADE BY : Tung Dinh" << endl;
}

//***************************************************************
//      MAIN / EDIT MENU FUNCTION
//****************************************************************
void main_menu(Student* student, Course* course, ofstream &out) {
	string ch;
	cout<<"\n------------------------------" << endl;
	cout<<"          MAIN MENU           " << endl;
	cout<<"------------------------------" << endl;
	cout<<"\n1. Create new student";
	cout<<"\n2. Display all student records";
	cout<<"\n3. Search student record";
	cout<<"\n4. Modify student record";
	cout<<"\n5. Exit";
	cout<<"\n-> Enter option (1-5): ";
	cin >> ch;
	cout << endl;
	if (ch == "1") {
		cout << CLEAR;
		create(student, course, out);
	} else if (ch == "2") {
		displayAll(student);
		returnMain(student, course, out);
	} else if (ch == "3") {
		int sid;
		cout << CLEAR;
		cout<<"\n(*) Enter SID (Student ID): ";
		cin >> sid;
		display(student, sid);
		returnMain(student, course, out);
	} else if (ch == "4") {
		modify(student, course, out);
	} else if (ch == "5") {
		cout << CLEAR;
		exit(EXIT_SUCCESS);
	} else {
		main_menu(student, course, out);
    }
}

void returnMain(Student* student, Course* course, ofstream &out) {
	string option;
	cout << "\n1: Return to main menu" << endl;
	cout << "0: Exit" << endl;
	cout << "-> Enter option (0-1): ";
	cin >> option;
	if (option == "1") {
		cout << CLEAR;
		main_menu(student, course, out);
	} else if (option == "0") {
		cout << CLEAR;
		exit(EXIT_SUCCESS);
	}
}

void displayAll(Student* student) {
	student->displayTranscriptAll();
}

void display(Student* student, int sid) {
	student->displayTranscript(sid);
}

void modify_term(string &term, int &year) {
	string termCh;
	cout << "    1. Autumn" << endl;
	cout << "    2. Winter" << endl;
	cout << "    3. Spring" << endl;
	cout << "    4. Summer" << endl;
	cout << "    -> Enter option (1-4): ";
	cin >> termCh;
	if (termCh == EXIT) exit(EXIT_SUCCESS);
	if (termCh == "1") {
		term = "AUT";
	} else if (termCh == "2") {
		term = "WIN";
	} else if (termCh == "3") {
		term = "SPR";
	} else if (termCh == "4") {
		term = "SUM";
	} else {
		cout << "\n* Your input is invalid, please re-enter option from 1 to 4" << endl;
		modify_term(term, year);
	}
	cout << "    -> Enter term year: ";
	cin >> year;
}

void modify_course(string &courseId, bool &courseValid, Course* course) {
	cout << "\n    * To view 300-level courses available, enter \"view300\" at course ID input" << endl;
	cout << "    * To view 400-level courses available, enter \"view400\" at course ID input" << endl << endl;
	cout << "    -> Enter course ID (Ex: 301,342,...): ";
	cin >> courseId;
	if (courseId == EXIT) exit(EXIT_SUCCESS);
	if (courseId == "view300") {
		cout << endl;
		course->display300();
		cout << endl;
		modify_course(courseId, courseValid, course);
	} else if (courseId == "view400") {
		cout << endl;
		course->display400();
		cout << endl;
		modify_course(courseId, courseValid, course);
	} else {
		if (course->getIndex(courseId) == -1) {
			courseValid = false;
			cout << "\n    * Course entered is not found in our system, please re-enter different course" << endl;
			modify_course(courseId, courseValid, course);
		} else {
			courseValid = true;
		}
	}
}

void modify_gpa(Student* student, double &gpa, bool &gpaValid) {
	cout << "\n    * To view GPA scale, enter \"viewScale\"" << endl << endl;
	enterGpa:
	cout << "    -> Enter GPA (out of 4.0): ";
	string grade;
	cin >> grade;
	int dot = 0;
	bool isDouble;
	if (grade == EXIT) exit(EXIT_SUCCESS);
	if (grade == "viewScale") {
		cout << endl;
		student->displayGpaScale();
		cout << endl;
		goto enterGpa;
	} else {
		for (int i = 0; i < grade.length(); i++) {
			int dec = grade[i];
			if (dec == 46) {
				dot++;
				if (dot > 1) {
					isDouble = false;
					break;
				}
			} else if (dec >= 48 && dec <= 57) {
				isDouble = true;
			} else {
				isDouble = false;
				break;
			}
		}
		if (isDouble) {
			gpa = stod(grade);
		} else {
			cout << "\n    * GPA entered is invalid, your GPA must be from 0.0 to 4.0" << endl;
			cout << "    * Please re-enter your GPA" << endl;
			modify_gpa(student, gpa, gpaValid);
		}
	}
	if (gpa < 0 || gpa > 4) {
		gpaValid = false;
		cout << "\n    * GPA entered is invalid, your GPA must be from 0.0 to 4.0" << endl;
		cout << "    * Please re-enter your GPA" << endl;
		modify_gpa(student, gpa, gpaValid);
	} else {
		gpaValid = true;
	}
}

void savingRequest() {
	cout << "\n(*) What do you want to do next?" << endl;
	cout << "    1. Save and return to main menu" << endl;
	cout << "    2. Save and exit" << endl;
	cout << "    3. Cancel and return to main menu" << endl;
	cout << "    4. Cancel and exit" << endl;
	cout << "    -> Enter option (1-4): ";
}

void modify(Student* student, Course* course, ofstream &out) {
	int sid, year;
	double gpa;
	string term, courseId, choice;
	bool courseValid = false, gpaValid = false, added = false;
	cout << CLEAR;
	cout << "\n(*) Enter SID (Student ID): ";
	cin >> sid;
	if (student->find(sid) != -1) {
		reenter_modify:
		cout << "    1. Add a new record" << endl;
		cout << "    2. Edit student record" << endl;
		cout << "    -> Enter option (1-2): ";
		cin >> choice;
		if(choice == "1") {
			cout << CLEAR;
			cout << "\n--> Enter -1 to exit the program" << endl;
			cout << "\n********* ADD **********" << endl;
			add:
			cout << "\n(*) Term" << endl;
			modify_term(term, year);
			cout << "\n(*) Course" << endl;
			modify_course(courseId, courseValid, course);
			cout << "\n(*) GPA" << endl;
			modify_gpa(student, gpa, gpaValid);
			cout << "\n(*) Review" << endl;
			cout << "    Enrolled term: " << term << " " << year << endl;
			cout << "    Course: " << course->getMajor(courseId) << " " << courseId << endl;
			cout << "    GPA: " << gpa << endl;
			reenter_continue:
			cout << "\n(*) Do you still want to edit? (Y/N) ";
			string ch0;
			cin >> ch0;
			if (ch0 == EXIT) exit(EXIT_SUCCESS);
			if (ch0 == "Y" || ch0 == "y" || ch0 == "Yes" || ch0 == "YES" || ch0 == "YeS" || ch0 == "yEs" || ch0 == "yes" || ch0 == "yES" || ch0 == "YEs" || ch0 == "yeS") {
				cout << CLEAR;
				cout << "\n(*) Current process" << endl;
				cout << "    Enrolled term: " << term << " " << year << endl;
				cout << "    Course: " << course->getMajor(courseId) << " " << courseId << endl;
				cout << "    GPA: " << gpa << endl;
				goto add; 
			} else if (ch0 == "N" || ch0 == "n" || ch0 == "No" || ch0 == "NO" || ch0 == "no" || ch0 == "nO") {
				string ch1;
				if (gpaValid && courseValid) {
					next_modify:
					savingRequest();
					cin >> ch1;
					if (ch1 == EXIT) exit(EXIT_SUCCESS);
					if (ch1 == "1") {
						added = true;
						out << sid << " " << term << " " << year << " " << courseId << " " << gpa << endl;
						student->setTranscript(sid, term, year, courseId, gpa);
						cout << CLEAR;
						main_menu(student, course, out);
					} else if (ch1 == "2") {
						added = true;
						out << sid << " " << term << " " << year << " " << courseId << " " << gpa << endl;
						student->setTranscript(sid, term, year, courseId, gpa);
						cout << CLEAR;
						exit(EXIT_SUCCESS);
					} else if (ch1 == "3") {
						added = false;
						cout << CLEAR;
						main_menu(student, course, out);
					} else if (ch1 == "4") {
						added = false;
						cout << CLEAR;
						exit(EXIT_SUCCESS);
					} else {
						added = false;
						cout << "\n* Your input is invalid, please re-enter option from 1 to 4" << endl;
						goto next_modify;
					}
				}
			} else {
				cout << "\n* Your input is invalid, please re-enter" << endl;
				cout << "* If answer is \"Yes\", enter \"Y\" or \"y\" or \"Yes\"" << endl;
				cout << "* If answer is \"No\", enter \"N\" or \"n\" or \"No\"" << endl;
				goto reenter_continue;
			}
		} else if (choice == "2") {
			cout << CLEAR;
			cout << "\n********* EDIT *********\n" << endl;
			edit:
			student->displayCourse(sid);
			cout << "(*) Which record do you want to edit? (1-" << student->getCourseTotal(sid) << ") ";
			string option_course;
			cin >> option_course;
			string option_edit;
			string oldLine, oldGrade, updatedLine;
			for (int i = 1; i <= student->getCourseTotal(sid); i++) {
				if (stoi(option_course) == i) {
					ostringstream str;
					str << student->getGpa(sid, i);
					oldGrade = str.str();
					oldLine = to_string(sid) + " " + student->getTerm(sid, i) + " " + to_string(student->getYear(sid, i)) + " " + student->getCourse(sid, i) + " " + oldGrade;
					term = student->getTerm(sid, i);
					year = student->getYear(sid, i);
					courseId = student->getCourse(sid, i);
					gpa = student->getGpa(sid, i);
					editOpt:
					option_edit = editOption();
					if (option_edit == "1") {
						cout << "\n------- EDIT TERM ------" << endl;
						modify_term(term, year);
						cout << "--> Term updated" << endl;
						goto editOpt;
					} else if (option_edit == "2") {
						cout << "\n------ EDIT COURSE -----" << endl;
						modify_course(courseId, courseValid, course);
						cout << "--> Course updated" << endl;
						goto editOpt;
					} else if (option_edit == "3") {
						cout << "\n------- EDIT GPA -------" << endl;
						modify_gpa(student, gpa, gpaValid);
						cout << "--> GPA updated" << endl;
						goto editOpt;
					} else if (option_edit == "4") {
						deleteConfirm:
						string ch;
						cout << "\n(*) Are you sure you want to delete this record? (Y/N) ";
						cin >> ch;
						if (ch == "Y" || ch == "y" || ch == "Yes" || ch == "YES" || ch == "YeS" || ch == "yEs" || ch == "yes" || ch == "yES" || ch == "YEs" || ch == "yeS") {
							student->deleteRecord(sid, i);
							ifstream editFile("temp.txt");
							ofstream mainFile("gpadata.txt");
							string l;
							for	(;;) {
								getline(editFile, l);
								if (l.find(oldLine) == -1) {
									mainFile << l << endl;
								}
								if (editFile.eof()) break;
							}
							editFile.clear();
							cout << "--> Record no." << i << " has been removed" << endl;
							goto edit;
						} else if (ch == "N" || ch == "n" || ch == "No" || ch == "NO" || ch == "no" || ch == "nO") {
							goto editOpt;
						} else {
							cout << "\n* Your input is invalid, please re-enter" << endl;
							cout << "* If answer is \"Yes\", enter \"Y\" or \"y\" or \"Yes\"" << endl;
							cout << "* If answer is \"No\", enter \"N\" or \"n\" or \"No\"" << endl;
							goto deleteConfirm;
						}
					} else if (option_edit == "5") {
						student->editTerm(sid, i, term);
						student->editYear(sid, i, year);
						student->editCourse(sid, i, courseId);
						student->editGpa(sid, i, gpa);
						ostringstream strs;
						strs << student->getGpa(sid, i);
						string grade = strs.str();
						updatedLine = to_string(sid) + " " + student->getTerm(sid, i) + " " + to_string(student->getYear(sid, i)) + " " + student->getCourse(sid, i) + " " + grade;
						ifstream editFile("temp.txt");
						ofstream mainFile("gpadata.txt");
						string l;
						for	(;;) {
							getline(editFile, l);
							if (l.find(oldLine) != -1) {
								mainFile << updatedLine << endl;
							} else {
								mainFile << l << endl;
							}
							if (editFile.eof()) break;
						}
						editFile.clear();
						cout << "--> Successfully saved" << endl;
						returnMain(student, course, out);
					} else if (option_edit == "6") {
						cancelConfirm:
						string ch;
						cout << "\n(*) Are you sure you want to cancel all changes? (Y/N) ";
						cin >> ch;
						if (ch == "Y" || ch == "y" || ch == "Yes" || ch == "YES" || ch == "YeS" || ch == "yEs" || ch == "yes" || ch == "yES" || ch == "YEs" || ch == "yeS") {
							cout << "--> No changes was made" << endl;
							returnMain(student, course, out);
						} else if (ch == "N" || ch == "n" || ch == "No" || ch == "NO" || ch == "no" || ch == "nO") {
							goto editOpt;
						} else {
							cout << "\n* Your input is invalid, please re-enter" << endl;
							cout << "* If answer is \"Yes\", enter \"Y\" or \"y\" or \"Yes\"" << endl;
							cout << "* If answer is \"No\", enter \"N\" or \"n\" or \"No\"" << endl;
							goto cancelConfirm;
						}
						returnMain(student, course, out);
					} else {
						cout << "Your input is invalid. Please re-enter option from 1 to 5" << endl;
						goto editOpt;
					}
				}
			}
		} else {
			cout << "Your input is invalid. Please re-enter option from 1 to 2" << endl;
			goto reenter_modify;
		}
	} else {
		added = false;
		cout << "* Student ID entered is not found in our system. Please re-enter different Student ID" << endl;	
		modify(student, course, out);
	}
	string line;
	if (added) {
		ifstream infile("temp.txt");
		ofstream outfile("gpadata.txt");
		cout << "true" << endl;
		for (;;) {
			getline(infile, line);
			outfile << line << endl;
			if(infile.eof()) break;
		}
		infile.clear();
	}
}

string editOption() {
	string option_edit;
	cout << "\n(*) What do you want to edit?" << endl;
	cout << "    1. Edit term" << endl; 
	cout << "    2. Edit course" << endl; 
	cout << "    3. Edit gpa" << endl;
	cout << "    4. Delete record" << endl;
	cout << "    5. Save" << endl;
	cout << "    6. Cancel" << endl;
	cout << "    -> Enter option (1-4): ";
	cin >> option_edit;
	return option_edit;
}

void create(Student* student, Course* course, ofstream &out) {
	string firstname, lastname, major, option, sid;
	bool majorError, sidError;
	cout << "\n--> Enter -1 to exit the program" << endl;
	cout << "\n****** CREATE STUDENT PROFILE ******" << endl;
	cout << "\n(*) First name: ";
	cin.ignore();
	getline(cin, firstname);
	if (firstname == EXIT) exit(EXIT_SUCCESS);
	cout << "\n(*) Last name: ";
	getline(cin, lastname);
	if (lastname == EXIT) exit(EXIT_SUCCESS);
	reenter_sid:
	cout << "\n(*) Student ID: ";
	cin >> sid;
	if (sid == EXIT) {
		exit(EXIT_SUCCESS);
	} else {
		for (int i = 0; i < sid.length(); i++) {
			int dec = sid[i];
			if (dec >= 48 && dec <= 57) {
				int check = student->find(stoi(sid));
				if (check != -1) {
					sidError = true;
					cout << "* The student number entered is already existed, please re-enter with another Student ID" << endl;
					goto reenter_sid;
				} else {
					cout << "--> Student ID is valid" << endl;
					sidError = false;
				}
			} else {
				sidError = true;
				cout << "\n* Student ID entered is invalid, please re-enter your student ID using only numeric characters" << endl;
				goto reenter_sid;
			}
		}
	}
	cout << "\n(*) Major:" << endl;
	cout << "    1. Computer Science & Software Engineer" << endl;
	cout << "    2. Computing & Software Systems" << endl;
	reenter_major:
	cout << "    -> Enter option (1-2): ";
	cin >> option;
	if (option == "1") {
		major = "CSSE";
		majorError = false;
	} else if (option == "2") {
		major = "CSS";
		majorError = false;
	} else if (option == EXIT) {
		exit(EXIT_SUCCESS);
	} else {
		majorError = true;
		cout << "\n* Your input is invalid, please re-enter major option from 1 to 2" << endl;
		cout << "* If your major is Computer Science & Software Engineer, enter \"1\"" << endl;
		cout << "* If your major is Computing & Software Systems, enter \"2\"" << endl << endl;
		goto reenter_major;
	}
	if (!sidError && !majorError) {
		next_create:
		savingRequest();
		string choice;
		cin >> choice;
		if (choice == "1") {
			// Copy old & new data to temp file
			ofstream copy("temp_student.txt");
			ifstream infile("studentdata.txt");
			string line;
			for(;;) {
				getline(infile, line);
				copy << line << endl;
				if (infile.eof()) break;
			}
			copy << sid << " " << major << " " << firstname << " " << lastname << flush;
			student->setStudent(stoi(sid), firstname, lastname, major);
			// Update new data from temp file to old file
			ofstream update("studentdata.txt");
			ifstream updatedFile("temp_student.txt");
			for (;;) {
				getline(updatedFile, line);
				update << line << endl;
				if(updatedFile.eof()) break;
			}
			cout << CLEAR;
			main_menu(student, course, out);
		} else if (choice == "2") {
			// Copy old & new data to temp file
			ofstream copy("temp_student.txt");
			ifstream infile("studentdata.txt");
			string line;
			for(;;) {
				getline(infile, line);
				copy << line << endl;
				if (infile.eof()) break;
			}
			copy << sid << " " << major << " " << firstname << " " << lastname << flush;
			student->setStudent(stoi(sid), firstname, lastname, major);
			// Update new data from temp file to old file
			ofstream update("studentdata.txt");
			ifstream updatedFile("temp_student.txt");
			for (;;) {
				getline(updatedFile, line);
				update << line << endl;
				if(updatedFile.eof()) break;
			}
			exit(EXIT_SUCCESS);
		} else if (choice == "3") {
			cout << CLEAR;
			main_menu(student, course, out);
		} else if (choice == "4") {
			cout << CLEAR;
			exit(EXIT_SUCCESS);
		} else if (choice == EXIT) {
			exit(EXIT_SUCCESS);
		} else {
			cout << "\n* Your input is invalid, please re-enter option from 1 to 4" << endl;
			goto next_create;
		}
	}
}