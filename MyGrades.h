/****************************************************HEADER******************************************************/
/*
Name: Carlos Gross-Martinez                              Z:23226341
Due Date: 8/29/2019                                      Course: COP3530
Assignment: Homework 1                                   Professor: Dr. K. Weiss

Description: This program processes student grades based on homework and exam grades
			 information. Moreover, it calculates the final grade based in the data
			 input and provides the grade that a student will require on the final to
			 successfully pass the course with a given desired grade
*/
/****************************************************************************************************************/

// Pre-processor directives, library declaration
#include <iostream>//standard library for i/o
using namespace std;

//header file declaration
#ifndef MYGRADES_H
#define MYGRADES_H

//MyGrades class declaration
class MyGrades
{
	public:
		// Constructor
		MyGrades();

		// copy constructor
		MyGrades(const MyGrades& org);

		// Destructor
		~MyGrades();

		// mutators
		void setFinalExam(int grade);
		void setMidtermExam(int grade);
		void setHomework(int grade);

		// accessors
		double getFinalGrade() const;
		double getGradeNeededOnFinal(double desiredGrade) const;

		// overloaded operators
		const MyGrades& operator=(const MyGrades& rightSide);
		int operator==(const MyGrades& g) const;

	private:
		// member variables
		const int DEFAULT_NUM_HW = 3;
		int* hw;   //  pointer for array that holds the homework grades
		int finalExam;  // final exam grade
		int midtermExam;  // midterm exam grade
		int numberOfOHomeworks; // holds the number of homework assignments entered in the hw array
		int maxNumberOfOHomeworks;  // holds the capacipty of the hw array
		const double finalExamWeight = .4;  // the weighted value of the final exam
		const double midtermExamWeight = .3;  // the weighted value of the midterm exam
		const double HWWeight = .3;  // the weighted value of the homework assignments
};

//code that will end the definition of the class in the header file 
#endif
