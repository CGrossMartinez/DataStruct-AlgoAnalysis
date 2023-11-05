/*************************************************HEADER***************************************************/
/*
Name: Carlos Gross-Martinez                              Z:23226341
Due Date: 8/29/2019                                      Course: COP3530
Assignment: Homework 1                                   Professor: Dr. K. Weiss

Description: This program processes student grades based on homework and exams
			 information. Moreover, it calculates the final grade based in the data
			 entered, and provides the grade that a student will require on the final
			 to successfully pass the course with a given desired grade
*/
/***********************************************************************************************************/

// Pre-processor directives, library/header declaration
#include "MyGrades.h"
using namespace std;

/*
Name: default constructor
Precondition:  no formal parameters are passed to the function because all variables are private
			   members of class, and the state of the class is known to all members functions
			   of class
Postcondition: function will initialize finalExam, midtermExam, numberOfOHomeworks variables
			   to 0. It will also initialize maxNumberOfOHomeworks variable to DEFAULT_NUM_HW,
			   and initialize dynamic array to DEFAULT_NUM_HW as default size.
Description:   The default constructor MyGrades() initialize test scores to 0 and allocate any
			   memory necessary to dynamic array hw
*/
MyGrades::MyGrades()
{
	//variable and dynamic array initialization
	finalExam = 0;
	midtermExam = 0;
	numberOfOHomeworks = 0;
	maxNumberOfOHomeworks = DEFAULT_NUM_HW;
	hw = new int[DEFAULT_NUM_HW];
}//end default constructor

/*
Name: copy constructor
Precondition:  function will have one parameters. A constant array called "org"
Postcondition: function will perform a deep copy of specified class objects
Description:   performs a deep copy of org.hw to hw
*/
MyGrades::MyGrades(const MyGrades& org)
{
	//variable initialization to values of org.hw
	finalExam = org.finalExam;
	midtermExam = org.midtermExam;
	numberOfOHomeworks = org.numberOfOHomeworks;
	maxNumberOfOHomeworks = org.maxNumberOfOHomeworks;

	//new dynamic array named hw declaration
	hw = new int[numberOfOHomeworks];

	//loop that will copy all information from org.hw to hw
	for (int i = 0; i < numberOfOHomeworks; i++)
		{
			hw[i] = org.hw[i];
		}//end for
}//end copy constructor

/*
Name: destructor
Precondition:  no formal parameters are passed to the function because all variables are private
			   members of class, and the state of the class is known to all members functions
			   of class
Postcondition: function removes all memory allocated to hw array and resets numberOfOHomeworks and
			   maxNumberOfOHomeworks variables to 0
Description:   de-allocates all memory allocated to hr and resets dynamic array tracking variables
*/
MyGrades::~MyGrades()
{
	//code that deallocates memory from hw
	//and reset variables to '0'
	delete[] hw;
	numberOfOHomeworks = 0;
	maxNumberOfOHomeworks = 0;
}//end destructor

/*
Name: setFinalExam
Precondition:  function will have one parameter. An int variable grade that will be passed by value
Postcondition: function will initilize the finalExam variable in the class with the value stored in
			   the grade variable that was passed to the function
Description:   The setFinalExam member function sets the final exam grade
*/
void MyGrades::setFinalExam(int grade)
{
	//code that initiliazes variable finalExam
	finalExam = grade;
}//end setFinalExam

/*
Name: setMidtermExam
Precondition:  function will have one parameter. An int variable grade that will be passed by value
Postcondition: function will initilize the midtermExam variable in the class with the value stored
			   in the grade variable that was passed to the function
Description:   The setMidtermExam member function sets the midterm grade
*/
void MyGrades::setMidtermExam(int grade)
{
	//code that initiliazes variable midtermExam
	midtermExam = grade;
}//end setMidtermExam

/*
Name: setHomework
Precondition:  function will have one parameter. An int variable grade that will be passed by value
Postcondition: function will add homework grade to hw array. If hw array is full, function will
			   increase size of array
Description:   The setHomework member function adds a homework grade to the hw array
*/
void MyGrades::setHomework(int grade)
{
	//condition that will test if the hw array is full
	if (numberOfOHomeworks == maxNumberOfOHomeworks)
		{
			//code that will increase value of maxNumberOfOHomeworks
			// variable by 1
			maxNumberOfOHomeworks++;

			//new dynamic array name temp declaration
			int* temp = new int[maxNumberOfOHomeworks];

			//loop that will copy all information from hw to temp
			//with the increased size
			for (int i = 0; i < maxNumberOfOHomeworks; i++)
				{
					temp[i] = hw[i];
				}//end for

			//code that deletes hw dynamic array	
			delete[] hw;

			//code that will set the pointer from hw to point to the
			//temp array
			hw = temp;
		}//end if

	//code that will save the homework grade in an empty slot
	//in the dynamic array
	hw[numberOfOHomeworks] = grade;

	//code that will increase value of numberOfOHomeworks
	// variable by 1
	numberOfOHomeworks++;
}//end setHomework

/*
Name: getFinalGrade
Precondition:  no formal parameters are passed to the function because all variables are private
			   members of class, and the state of the class is known to all members functions
			   of class
Postcondition: function will calculate the average of all homeworks and calculate the final grade
			   based on the information gathered from all the grades
Description:   The getFinalGrade member function returns the weighted average grade
*/
double MyGrades::getFinalGrade() const
{
	//local variable declaration and initialization
	double finalGrade(0), hwTotal(0);

	//loop that will add all the grades from all homeworks and save it in hwTotal variable
	for (int i = 0; i < numberOfOHomeworks; i++)
		{
			//code that adds all grades from all homeworks into variable
			hwTotal += hw[i];
		}//end for

	//condition that needs to be met to use the first formula to calculate grade. if 
	//numberOfOHomeworks = 0 there will be an error because the variable is in the denominator.  
	//Hence, a separate formula was used to calculate finalGrade whenever numberOfOHomeworks = 0
	if (numberOfOHomeworks == 0)
		{
			//code that calculates the final grade when numberOfOHomeworks = 0
			finalGrade = (midtermExam * midtermExamWeight) + (finalExam * finalExamWeight);
		}//end if
	else
		{
			//code that calculates the final grade when numberOfOHomeworks != 0
			finalGrade = ((hwTotal / numberOfOHomeworks) * HWWeight) + (midtermExam * midtermExamWeight) + (finalExam * finalExamWeight);
		}//end if-else	

	//code that returns value for final grade to main
	return finalGrade;
}//end getFinalGrade

/*
Name: getGradeNeededOnFinal
Precondition:  function will have one parameter. A double variable desireGrade that will be passed by value
Postcondition: function will return the grade to main that is required in order to obatain the desireGrade
Description:   The getGradeNeededOnFinal member function returns the grade needed on the final exam to achieve
			   the final desired grade
*/
double MyGrades::getGradeNeededOnFinal(double desiredGrade) const
{
	//local variable declaration and initialization
	double neededGrade(0), hwTotal(0);

	//loop that will add all the grades from all homeworks and save it in hwTotal variable
	for (int i = 0; i < numberOfOHomeworks; i++)
		{
			//code that adds all grades from all homeworks
			hwTotal += hw[i];
		}//end for

	//code that calculated the needed grade in the finalExam to pass with the desired grade
	neededGrade = (desiredGrade - (midtermExam * midtermExamWeight) - ((hwTotal / numberOfOHomeworks) * HWWeight)) / finalExamWeight;

	//code that returns value for the needed grade to main
	return neededGrade;
}//end getGradeNeededOnFinal

/*
Name: operator =
Precondition:  function will have one parameters. A constant array called "rightSide"
Postcondition: function will perform a copy of rightSide.hw to hw
Description:   performs a copy of rightSide.hw to hw
*/
const MyGrades& MyGrades::operator = (const MyGrades& rightSide)
{
	//code that checks for no self-assignment
	if (this != &rightSide)
		{
			//code that deletes hw dynamic array
			delete[] hw;

			//variable initialization to values of rightSide.hw
			finalExam = rightSide.finalExam;
			midtermExam = rightSide.midtermExam;
			numberOfOHomeworks = rightSide.numberOfOHomeworks;
			maxNumberOfOHomeworks = rightSide.maxNumberOfOHomeworks;

			//new dynamic array name hw declaration
			hw = new int[numberOfOHomeworks];

			//loop that will copy all information from rightSide.hw to hw
			for (int i = 0; i < numberOfOHomeworks; i++)
				{
					hw[i] = rightSide.hw[i];
				}//end for
		}//end if

	//code that returns reference to the object
	return *this;
}//end operator =

/*
Name: operator ==
Precondition:  function will have one parameters. A constant array called "g"
Postcondition: function will compare the values of the all the variables from g.hw and hw
			   and return 1 or 0 depeding if the values of the variables are the same
Description:   function will return 1 or 0 depending if the objects are equal
*/
int MyGrades::operator == (const MyGrades& g) const
{
	//local variable declaration and initialization
	int returnNumber, gradeChecker(0);

	//loop that will check all grades in the arrays to ensure that they are the same
	for (int i = 0; i < numberOfOHomeworks; i++)
		{
			//condition that needs to be met in order for the grades to be the same
			if (hw[i] == g.hw[i])
				{
					//if the condition is true and all the grades are the same, gradeChecker
					//will be equal to 1
					gradeChecker += 1;
				}//end if
		}//end for

	//condition that needs to be met to return returnNumber back to main with the value of 1
	if (finalExam == g.finalExam && midtermExam == g.midtermExam && numberOfOHomeworks == g.numberOfOHomeworks && gradeChecker == numberOfOHomeworks)
		{
			//code the returns returnNumber back to main
			return returnNumber = 1;
		}//end if		
	else
		{
			//code the returns returnNumber back to main
			return returnNumber = 0;
		}//end if-else	
}//end operator ==


