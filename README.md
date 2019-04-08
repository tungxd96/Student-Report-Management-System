# Student-Report-Management-System

Instruction:
  * If you're familar with gcc/g++ compiler, please go straight to step 4.
  1. After downloading all the attached files, put them in a separate folder where you use to compile on Linux with gcc/g++.
  2. Open your local gcc/g++ compiler. If you don't have one, follow this instruction on how to install the latest gcc on Windows:
     + https://preshing.com/20141108/how-to-install-the-latest-gcc-on-windows/
  3. Once you open your gcc/g++ compiler, change your current directory to the directory that includes these files.
  4. When you're in your file's directory, to run the program:
     * ./a.exe: execute the program on gcc compiler on Windows platform.
     * ./a.out: execute the program on gcc compiler on Linux platform.
     + For c++98 or c++03, type in g++ -std=c++11 *.cpp, then ./a.exe or ./a.out.
     + For c++11 or c++ higher version, type in g++ *.cpp, then ./a.exe or ./a.out.
    
Description: 
  + Student Report Management System is the program that allows college/university facilities to manage all enrolled students information. 
  + Functionalities: add a new student profile, create student records, modify student record, delete student record, view GPA scale, view 300-500 level courses, view a student transcript, and view all student records.
  + With the use of hash tables to store student ID, (insert, search and delete) runtime complexity is O(1) for average case and O(n) for worst case.
  + Currently, all databases are saved in .txt files.
