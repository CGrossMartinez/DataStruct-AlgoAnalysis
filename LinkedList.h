/*************************************************HEADER***************************************************/
/*
Name: Carlos Gross-Martinez                              Z:23226341
Due Date: 10/15/2019                                     Course: COP3530
Assignment: Homework 4                                   Professor: Dr. K. Weiss

Description: This program creates a template of the list assignment
*/
/***********************************************************************************************************/

/*-- LinkedList.h --------------------------------------------------------------

This header file defines the data type List for processing lists.
Operations are:
Constructor
Destructor
Copy constructor
Assignment operator
insert:   Insert an item
erase:    Remove an item
getListElement: get a range of list elements

-------------------------------------------------------------------------*/

//header file declaration
#ifndef LINKED_LIST_H
#define LINKED_LIST_H

//template declaration
template <typename ListElement>


//LinkedList class declaration
class LinkedList
{
public:	
private:
	/******** Data Members ********/
	class Node
		{
			public:
				ListElement data;

				Node* next;
		};
	Node* first;         // pointer to first element in linked list
	int getListSize() const;

public:
	/******** Error Codes ********/
	static const int ILLEGAL_LIST_POSITION = -1;
	static const int NO_ERROR = 0;


	//member functions
	LinkedList();
	~LinkedList();
	LinkedList(const LinkedList<ListElement>& origList);
	const LinkedList<ListElement>& operator=(const LinkedList<ListElement>& rightHandSide);
	int insert(ListElement item, int pos);
	int erase(int pos);
	int getListElement(int posStart, int posEnd, ListElement rv[]) const;
}; //--- end of LinkedList class

//--- Definition of class constructor
// Construct a List object.
// Precondition:  None.
// Postcondition : An empty List object is constructed; first == nullptr
template<typename ListElement>
LinkedList<ListElement>::LinkedList() : first(nullptr) // initialize to empty list
{	
}//end constructor

//--- Definition of class destructor
// Destroys a List object.
// Precondition : The life of a List object is over.
// Postcondition : The memory dynamically allocated by the linked list is now deallocated
template<typename ListElement>
inline LinkedList<ListElement>::~LinkedList()
{
	//creates a Node pointer named current and initializes it to first
	Node* current = first;
	//creates a Node pointer named temp
	Node* temp;
	//variable declaration and initialization
	int k = getListSize();
	// traverse through the list and deallocate nodes
	for (int i = 0; i < k; i++)
		{ 
			//get the next node in the linked list
			temp = current->next;  
			//deletes node
			delete current;
			//sets pointer to the next node
			current = temp;
		}//end for
}//end destructor

//--- Definition of copy constructor
// Construct a copy of a List object.
// Precondition:  A copy of origList is needed; origList is a const
// reference parameter.
// Postcondition: A copy of origList has been constructed.
template<typename ListElement>
LinkedList<ListElement>::LinkedList(const LinkedList<ListElement>& origList)
{
	Node* temp;					  // stores the new node pointer
	Node* prevNode = nullptr;     // store the previous node pointer
	Node* orgPrevNode = nullptr;  // stores the previous node pointer from the original list
	for (int i = 0; i < origList.getListSize(); i++)
		{
			temp = new(std::nothrow) Node();
			if (temp == nullptr)
				{ // if there was an error in the allocation then
					std::cerr << "*** Inadequate memory to allocate storage for new node ***\n";
					exit(1);
				}//end if 
			else if (i == 0)
				{ // if this is the first node then
					first = temp;  // set the pointer in the previous node
					first->data = origList.first->data;  // set the data in the node
					first->next = nullptr;  // set next pointer to null
					prevNode = temp;        // set the previous node for the next loop
					orgPrevNode = origList.first;   // set the org list previous node for the next loop
				}//end else if
			else
				{
					prevNode->next = temp;  // set the pointer in the previous node
					prevNode->next->data = orgPrevNode->next->data;  // set the data in the node
					prevNode->next->next = nullptr;  // set next pointer to null
					prevNode = temp;    // set the previous node for the next loop
					orgPrevNode = orgPrevNode->next;  // set the org list previous node for the next loop
				}//end else
		}//end for
}//end copy constructor

//--- Definition of assignment operator
// Assign a copy of a List object to the current object.
// Precondition: rightHandSide List is required.
// Postcondition : A copy of rightHandSide has been assigned to this
// object. A const reference to this list is returned.
template<typename ListElement>
const LinkedList<ListElement>& LinkedList<ListElement>::operator=(const LinkedList<ListElement>& rightHandSide)
{
	if (this != &rightHandSide)  // check that not self-assignment
		{
			// deallocate current linked list, same as the destructor code
			Node* current = first;
			//creates a Node pointer named temp
			Node* temp;
			//variable declaration and initialization
			int k = getListSize();
			// traverse through the list and deallocate nodes
			for (int i = 0; i < k; i++)
				{
					temp = current->next;  // get the next node in the linked list
					delete current;
					current = temp;
				}//end for 
			// now start to copy from the rightHandSide
			first = nullptr;
			// similar to copy constructor
			Node* prevNode = nullptr;     // store the previous node pointer
			Node* orgPrevNode = nullptr;  // stores the previous node pointer from the original list
			for (int i = 0; i < rightHandSide.getListSize(); i++)
				{
					temp = new(std::nothrow) Node();
					if (temp == nullptr)
							{ // if there was an error in the allocation then
								std::cerr << "*** Inadequate memory to allocate storage for new node ***\n";
								exit(1);
							}//end if
					else if (i == 0)
						{ // if this is the first node then
							first = temp;  // set the pointer in the previous node
							first->data = rightHandSide.first->data;  // set the data in the node
							first->next = nullptr;  // set next pointer to null
							prevNode = temp;        // set the previous node for the next loop
							orgPrevNode = rightHandSide.first;   // set the org list previous node for the next loop
						}//end else if
					else
						{
							prevNode->next = temp;  // set the pointer in the previous node
							prevNode->next->data = orgPrevNode->next->data;  // set the data in the node
							prevNode->next->next = nullptr;  // set next pointer to null
							prevNode = temp;    // set the previous node for the next loop
							orgPrevNode = orgPrevNode->next;  // set the org list previous node for the next loop
						}//end else
				}//end for 
		}//end if
	//return pointer
	return *this;
}//end assignment operator

//--- Definition of insert()
// Insert item at pos position.pos 0 is the first element position in the list
// Precondition : A constructed list, either empty or with elements
// Postcondition : inserted item into list at pos position
// Returns ILLEGAL_LIST_POSITION for insert that is out of range of the current list,
// Otherwise return a NO_ERROR.
template<typename ListElement>
int LinkedList<ListElement>::insert(ListElement item, int pos)
{
	// note pos goes from 0 to n
	if (pos < 0 || pos > getListSize())
		{ // perform error checking on the input
			return ILLEGAL_LIST_POSITION;
		}//end if
	// get the new node to insert
	Node* temp = new(std::nothrow) Node();
	if (temp == nullptr)
		{ // if there was an error in the allocation then
			std::cerr << "*** Inadequate memory to allocate storage for new node ***\n";
			exit(1);
		}//end if 
	//data value and pointer assignment to temp
	temp->data = item;
	temp->next = nullptr; // if at the end of the list

	if (pos == 0)
		{ // process insertion at the beginning of the list  
			temp->next = first;
			first = temp;
		}//end if
	else
		{ // process insertion after the beginning of the list
			// find the node before the insertion point
			Node* current = first;
			for (int i = 1; i < pos; i++)
				{
					current = current->next;
				}//end for
			temp->next = current->next; // set the next pointer in the new node
			current->next = temp;  // set the next pointer in the previous node
		}//end else
	//returned value if no error encountered
	return NO_ERROR;
}//end insert

//--- Definition of erase()
// Erase item at pos position.pos 0 is the first element position in the list.
// Precondition: A constructed list, either empty or with elements
// Postcondition : erased item at pos position
// Returns ILLEGAL_LIST_POSITION for erase that is out of range of the current list,
// Otherwise return a NO_ERROR.
template<typename ListElement>
int LinkedList<ListElement>::erase(int pos)
{
	if (getListSize() == 0)
		{ // perform error checking on the input
			return ILLEGAL_LIST_POSITION;
		}//end if
	if (pos < 0 || pos >= getListSize())
		{ // perform error checking on the input
			return ILLEGAL_LIST_POSITION;
		}//end if 
	//creates a Node pointer named temp
	Node* temp;
	if (pos == 0)
		{ // if the deletion is the zero node then
			temp = first;   // save pointer to be deleted
			first = first->next;   // bypass node
			delete temp;  // delete node
		}//end if 
	else
		{
			// find the node before the deletion point
			Node* current = first;
			for (int i = 1; i < pos; i++)
				{
					current = current->next;
				}//end for
			temp = current->next;  // save pointer to be deleted
			if (pos == (getListSize() - 1))
				{ // if the deleted node is at the end of the list then
					current->next = nullptr;
				}//end if 
			else
				{ // else there is another node to link with
					current->next = current->next->next;
				}//end else
			delete temp; // delete the node
		}//end else
	//returned value if no error encountered
	return NO_ERROR;
}//end erase

//--- Definition of getListElement()
// Returns list values
// Precondition : A constructed list, either empty or with elements.
// The rv[] array must be large enough to hold the returned contents.
// Postcondition : Fills array rv with the list elements specified
// Returns ILLEGAL_LIST_POSITION for move that is out of range of the current list,
// Otherwise return a NO_ERROR.Both posStart and posEnd must be valid positions
// and posStart <= posEnd.posStart is an index to the start of the data and
// posEnd is an index to the end of the data.To retieve one element
// posStart and posEnd will be the same value.
template<typename ListElement>
int LinkedList<ListElement>::getListElement(int posStart, int posEnd, ListElement rv[]) const
{
	if (posStart < 0 || posStart >= getListSize() || posEnd < 0 || posEnd >= getListSize() || posStart > posEnd)
		{ // check for valid paramenters
			return ILLEGAL_LIST_POSITION;
		}//end if
	Node* current = first;   // point to zero node
	for (int i = 0; i < posStart; i++)
		{ // loop to find the node
			current = current->next;
		}//end for
	for (int i = 0; i < ((posEnd - posStart) + 1); i++)
		{ // put returned elements in the beginning of the list
			rv[i] = current->data;
			current = current->next;
		}//end for
	//returned value if no error encountered
	return NO_ERROR;
}//end getListElement

//--- Definition of getSize()
// Precondition : None
// Postcondition : returns the the size of the linked list
template<typename ListElement>
int LinkedList<ListElement>::getListSize() const
{
	//variable declaration and initialization
	int rv = 0;
	//new Node pointer named current declaration and initialization	
	Node* current = first;
	//loop that will tranverse through list until last node
	for (; current != nullptr;)
		{
			//counter that adds 1 everytime current != nullptr
			rv++;
			//current is assigned the list pointer value
			current = current->next;
		}//end for
	//size of list returned to main
	return rv;
}//end getSize
#endif