/*************************************************HEADER***************************************************/
/*
Name: Carlos Gross-Martinez                              Z:23226341
Due Date: 10/15/2019                                     Course: COP3530
Assignment: Homework 4 Task 2                            Professor: Dr. K. Weiss

Description: This program is a recursive function that will perform mathematical operations
			 based on the arguments that are passed to it through a vector. Function will
			 save operands to a stack and perform the operation based on the information provided 
			 in the vector
*/
/***********************************************************************************************************/

//--- Definition of recursive funtion 
// conducs mathematical operations based on information contained in vector
// Precondition:   function recives a vector with string values, an empty stack
//                 and a variable of type doubles named result which in passed by
//                 reference
// Postcondition : all mathematical operations will be conducted with all operands
//                 and operator provided in the vector. Result will be saved to 
//                 variable result in main. Funtion will return the bool value of 
//                 if all computations are performed with no issues or false if there 
//                 are any issues
bool evalPostfix(std::vector<std::string>& v, std::stack<double>& s, double& result)
{
	//variable declaration and initialization
	bool returnResult = false;
	double temp1(0), temp2(0);

	//Anchor condition that needs to be met to make program stop recursion
	if (v.empty() && s.size() == 1)
	{
		//code that places the result from all calculations from stack to result
		result = s.top();
		//code that empties stack after result has been updated
		s.pop();
		//code that sets variable to true to return to main
		returnResult = true;
		//code that returns bool result to calling function
		return returnResult;
	}//end if 	
	//contion that checks to ensure vector has information to process
	else if (!v.empty())
	{
		//condition that checks the contents in v[0] to see if it is an operator
		if (v[0] == "+" || v[0] == "-" || v[0] == "*" || v[0] == "/")
		{
			//condition that checks the size of stack to ensure it has two variables
			//or more in it to be able to do mathematical operation
			if (s.size() < 2)
			{
				//if stack does not have two variables, resturnResult will be set to false
				//because it does not have the necessary operands to make calculation
				returnResult = false;
				//code that returns bool result to calling function
				return returnResult;
			}//end if
			//code that will execute if we have enough operands to do mathematical operation
			else
			{
				//code that sets variable temp1 to operand on top of stack
				temp1 = s.top();
				//code that removes operand from top of stack after saving it to vairable
				s.pop();
				//code that sets variable temp2 to operand on top of stack
				temp2 = s.top();
				//code that removes operand from top of stack after saving it to vairable
				s.pop();
			}//end else									

			//condition that needs to be met to perform addition
			if (v[0] == "+")
			{
				//code that deletes operator from vector
				v.erase(v.begin());
				//code that pushes to the stack the addition of operands
				s.push(temp1 + temp2);
			}//end if
			//condition that needs to be met to perform substraction
			else if (v[0] == "-")
			{
				//code that deletes operator from vector
				v.erase(v.begin());
				//code that pushes to the stack the substraction of operands
				s.push(temp2 - temp1);

			}//end if/else
			//condition that needs to be met to perform multiplication
			else if (v[0] == "*")
			{
				//code that deletes operator from vector
				v.erase(v.begin());
				//code that pushes to the stack the multiplication of operands
				s.push(temp1 * temp2);

			}//end if/else
			//condition that needs to be met to perform division
			else if (v[0] == "/")
			{
				//code that deletes operator from vector
				v.erase(v.begin());
				//code that pushes to the stack the division of operands
				s.push(temp2 / temp1);
			}//end if/else
		}//end if
		//condition that is met when the contents in v[0] are not an operator
		else
		{
			//code that pushes to the stack the string contained in v[0] as a double
			s.push(atof(v[0].c_str()));
			//code that deletes the string from v[0]
			v.erase(v.begin());
		}//end else
		//code that sets the value of returnResult based on results from recursion
		returnResult = evalPostfix(v, s, result);
	}//end if/else
	//code that returns returnResult to main	
	return returnResult;
}//end  evalPostfix