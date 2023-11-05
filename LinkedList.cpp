/*************************************************HEADER***************************************************/
/*
Name: Carlos Gross-Martinez                              Z:23226341
Due Date: 9/19/2019                                      Course: COP3530
Assignment: Homework 2                                   Professor: Dr. K. Weiss

Description: This program will create a link list and perform different types of actions to the list.
The actions include to add or delete nodes to the list, calculate the size of the link list, and provide 
information contained in the list.
*/
/***********************************************************************************************************/
#include <new>
#include <iostream>
#include "LinkedList.h"

//--- Definition of class constructor
// Construct a List object.
// Precondition:  None.
// Postcondition : An empty List object is constructed; first == nullptr
LinkedList::LinkedList()
{	
	//initialization of poiter first to nullptr
	first = nullptr;	
}//end constructor

//--- Definition of class destructor
// Destroys a List object.
// Precondition : The life of a List object is over.
// Postcondition : The memory dynamically allocated to the linked list is now deallocated
LinkedList::~LinkedList()
{
	//deallocation of pointer dynamic memory
	delete first;	
}//end destructor

//--- Definition of copy constructor
// Construct a copy of a List object.
// Precondition:  A copy of origList is needed; origList is a const
// reference parameter.
// Postcondition: A copy of origList has been constructed.
LinkedList::LinkedList(const LinkedList& origList)
{
	//pointer declaration and initialization. ptrCopyFrom is a pointer
	//pointing to the beggining of the list that we are copying from
	Node* ptrCopyFrom = origList.first;
	
	//pointer declaration. Pointer will be used to point to the new node 
	//where the information is going to be copied to
	Node* ptrNewNode;	

	//pointer initialization of first to a null pointer
	this->first = nullptr;

	//condition that checks to ensure that list to be copied from is not empty
	if (ptrCopyFrom != nullptr)
		{
			//code that creates a new node and assigns the address of node
			//to the newNode pointer
			Node* newNode = new(std::nothrow) Node();
			
			//code that assigns the integer value from the list we are copying from
			//to the first node
			newNode->data = ptrCopyFrom->data;

			//code that assigns the address of the new node to first pointer
			this->first = newNode;

			//code that assigns the address of the new node to ptrNewNode
			ptrNewNode = newNode;
			
			//code that loads the address of the next node to process/copy
			//to the pointer ptrCopyFrom
			ptrCopyFrom = ptrCopyFrom->next;
			
			//condition loops through the list until it gets to end of the list to copy
			while (ptrCopyFrom != nullptr)
				{
					//code that creates a new node and assigns the address of node
					//to the newNode pointer
					Node* newNode = new(std::nothrow) Node();

					//code that assigns the address of the new node to ptrNewNode
					ptrNewNode->next = newNode;

					//code that assigns the integer value from the list we are copying from
					//to the next node
					newNode->data = ptrCopyFrom->data;

					//code that copies to ptrNewNode pointer the address of the next node
					ptrNewNode = ptrNewNode->next;

					//code that places the address of the next node to be copied in the pointer
					//ptrCopyFrom
					ptrCopyFrom = ptrCopyFrom->next;
				}//end while
		}//end if
}//end copy constructor

//--- Definition of assignment operator
// Assign a copy of a List object to the current object.
// Precondition: rightHandSide List is required.
// Postcondition : A copy of rightHandSide has been assigned to this
// object. A const reference to this list is returned.
const LinkedList& LinkedList::operator = (const LinkedList& rightHandSide)
{
	//code that checks for no self-assignment
	if (this != &rightHandSide)
		{
			//pointer declaration and initialization. ptrCopyFrom is a pointer
			//pointing to the beggining of the list that we are copying from
			Node* ptrCopyFrom = rightHandSide.first;

			//pointer declaration. Pointer will be used to point to the new node 
			//where the information is going to be copied to
			Node* ptrNewNode;

			//pointer initialization of first to a null pointer
			this->first = nullptr;
			
			//condition that checks to ensure that list to be copied from is not empty
			if (ptrCopyFrom != nullptr)
				{
					//code that creates a new node and assigns the address of node
					//to the newNode pointer
					Node* newNode = new(std::nothrow) Node();

					//code that assigns the integer value from the list we are copying from
					//to the first node
					newNode->data = ptrCopyFrom->data;

					//code that assigns the address of the new node to first pointer
					this->first = newNode;

					//code that assigns the address of the new node to ptrNewNode
					ptrNewNode = newNode;

					//code that loads the address of the next node to process/copy
					//to the pointer ptrCopyFrom
					ptrCopyFrom = ptrCopyFrom->next;

					//condition loops through the list until it gets to end of the list to copy
					while (ptrCopyFrom != nullptr)
						{
							//code that creates a new node and assigns the address of node
							//to the newNode pointer
							Node* newNode = new(std::nothrow) Node();

							//code that assigns the integer value from the list we are copying from
							//to the first node
							newNode->data = ptrCopyFrom->data;

							//code that copies to ptrNewNode next node pointer the address of the next node
							ptrNewNode->next = newNode;

							//code that copies to ptrNewNode pointer the address of the next node
							ptrNewNode = ptrNewNode->next;

							//code that places the address of the next node to be copied in the pointer
							//ptrCopyFrom
							ptrCopyFrom = ptrCopyFrom->next;
						}//end while
				}//end if
		}//end if

	//code that returns reference to the object
	return *this;
}//end operator =

//--- Definition of insert()
// Insert item at pos position.pos 0 is the first element position in the list
// Precondition : A constructed list, either empty or with elements
// Postcondition : inserted item into list at pos position
// Returns ILLEGAL_LIST_POSITION for insert that is out of range of the current list,
// Otherwise return a NO_ERROR.
int LinkedList::insert(ListElement item, int pos)
{
	//code that checks to ensure that the position where the new node will created
	//is valis
	if (pos < 0 || pos > getListSize())
		{
			//value that is return to main is the insertion position is invalid
			return ILLEGAL_LIST_POSITION;
		}//end if
	
	//condition that needs to be met to insert new node at begining of list 
	if (pos == 0)
		{
			//code that creates a new node and assigns the address of node
			//to the newPtr pointer
			Node* newPtr = new(std::nothrow) Node();
			
			//code that enters the integer value to new node
			newPtr->data = item;
			
			//code sets the adrress of the prior first node to the new node next pointer
			newPtr->next = first;

			//code that sets the address of the new pointer to the pointer first.
			first = newPtr;
		}//end if
	
	//condition that needs to be met to insert new node at the end of the list
	else if (pos == getListSize())
		{
			//code that creates a new pointer and assigns its value to the address of the beggining 
			//of the list
			Node* predPtr = first;

			//code that transverse throught the list until it gets to the last node
			for (int i = 0; i < pos - 1; i++)
				{
					//code that assigns the address of the last node to predPtr pointer
					predPtr = predPtr->next;
				}//end for

			//code that creates a new node and assigns the address of node
			//to the newPtr pointer
			Node* newPtr = new(std::nothrow) Node();

			//code that assings the integer value to the data variable of new node
			newPtr->data = item;

			//code that sets the address of the next pointer to null
			newPtr->next = nullptr;

			//code that assings the address of the new node to predPtr pointer
			predPtr->next = newPtr;
		}//end else if
	
	//condition that is met to insert new node in the anywhere else in the list
	else
		{
			//code that creates a new pointer and assigns its value to the address of the beggining 
			//of the list
			Node* predPtr = first; 

			//code that transverse throught the list until it gets to the specifed position
			for (int i = 0; i < pos - 1; i++)
				{
					//code that assigns the address of the node to predPtr pointer
					predPtr = predPtr->next;
				}//end for

			//code that creates a new node and assigns the address of node
			//to the newPtr pointer
			Node* newPtr = new(std::nothrow) Node();

			//code that assings the integer value to the data variable of new node
			newPtr->data = item;

			//code that assigns the address of the next node to the newPtr next pointer
			//from new node
			newPtr->next = predPtr->next;

			//code that assigns the address of the new node to the predPtr pointer
			predPtr->next = newPtr;
		}//end else

	//return statements if the code runs with no errors
	return NO_ERROR;
}//end insert

//--- Definition of erase()
// Erase item at pos position.pos 0 is the first element position in the list.
// Precondition: A constructed list, either empty or with elements
// Postcondition : erased item at pos position
// Returns ILLEGAL_LIST_POSITION for erase that is out of range of the current list,
// Otherwise return a NO_ERROR.
int LinkedList::erase(int pos)
{
	//code that checks to ensure that the position where the new node will be deleted
	//is valid
	if (pos < 0 || pos >= getListSize())
		{
		//value that is return to main is the deletion position is invalid
			return ILLEGAL_LIST_POSITION;
		}//end if

	//condition that needs to be met to delete node at begining of list
	if (pos == 0)
		{
			//code that creates a new pointer ptr and assings the address of the first
			//node in the list
			Node* ptr = first;

			//code that assings to first pointer the address of the second node in the list
			first = ptr->next;

			//code that deletes the dynamically allocated pointer
			delete ptr;		
		}//end if

	//condition that needs to be met to delete node at the end of the list
	else if (pos == getListSize())
		{
			//code that creates a new pointer predPtr and assings the address of the first
			//node in the list
			Node* predPtr = first; 

			//code that transverse throught the list until it gets to the specifed position
			for (int i = 0; i < pos - 1; i++)
				{
					//code that assigns the address of the last node to predPtr pointer
					predPtr = predPtr->next;
				}//end for

			//code that creates a new pointer ptr and assings the address of the node before last 
			Node* ptr = predPtr->next;

			//code that sets the value of the pointer next of the node before the last to null
			predPtr -> next = nullptr;

			//code that deletes the dynamically allocated pointer
			delete ptr;		
		}//end if-else
	else
		{
			//code that creates a new pointer predPtr and assings the address of the first
			//node in the list
			Node* predPtr = first;  

			//code that transverse throught the list until it gets to the specifed position
			for (int i = 0; i < pos - 1; i++)
				{
				//code that assigns the address of the specified node to predPtr pointer
					predPtr = predPtr->next;
				}//end for

			//code that creates a new pointer ptr and assings the address of the next node
			//by passing the node that will be deleted
			Node* ptr = predPtr->next;

			//code that assings the address of the next node on the list bypassing the one that 
			//will be deleted to the pointer next of the prior node
			predPtr->next = ptr->next;

			//code that deletes the dynamically allocated pointer
			delete ptr;
		}//end else

	//return statements if the code runs with no errors
	return NO_ERROR;
}//end erase

//--- Definition of getListElement()
// Returns list values
// Precondition : A constructed list, either empty or with elements.
// The rv[] array must be large enough to hold the returned contents.
// Postcondition : Fills array rv with the list elements specified
// Returns ILLEGAL_LIST_POSITION for move that is out of range of the current list,
// Otherwise return a NO_ERROR. Both posStart and posEnd must be valid positions
// and posStart <= posEnd.posStart is an index to the start of the data and
// posEnd is an index to the end of the data.To retieve one element
// posStart and posEnd will be the same value.
int LinkedList::getListElement(int posStart, int posEnd, ListElement rv[]) const
{
	if (posStart < 0 || posStart >= getListSize() || posEnd < 0 || posEnd >= getListSize() || posStart > posEnd)
		{ // check for valid paramenters
			return ILLEGAL_LIST_POSITION;
		}
	Node* current = first;   // point to zero node
	for (int i = 0; i < posStart; i++)
		{ // loop to find the node
			current = current->next;
		}
	for (int i = 0; i < ((posEnd - posStart) + 1); i++)
		{ // put returned elements in the beginning of the list
			rv[i] = current->data;
			current = current->next;
		}
	return NO_ERROR;
}

//--- Definition of getSize()
// returns the size of the list. Do not change this.
int LinkedList::getListSize() const
{
	int rv = 0;
	Node* current = first;
	for (; current != nullptr;)
		{
			rv++;
			current = current->next;
		}
	return rv;
}

