/*************************************************HEADER***************************************************/
/*
Name: Carlos Gross-Martinez                              Z:23226341
Due Date: 9/29/2019                                      Course: COP3530
Assignment: Homework 3                                   Professor: Dr. K. Weiss

Description: This program uses a queue as a buffer between a data transmission source and
			 and a data receiver. The data transmission conducted will be asynchronous
*/
/***********************************************************************************************************/

#include <iostream>
#include <string>
#include "Sender.h"
#include "Receiver.h"
#include "Queue.h"
#include <ctime>

int main()
{
	Sender tx;
	Receiver rx;
	Queue q;
	std::cout << "Code written by Carlos Gross-Martinez" << std::endl;
	std::clock_t start = std::clock();

	// put your code here (below)

	//Variable and array declaration and initialization
	char myArr[200];
	int sendCount(0), queueTracker(0);

	//Loop that ensures the sender is active sending information
	//and queue is not empty. Loop will check for conditions until  
	//all data has been transmitted.
	while (tx.isSenderStreamOpen() || !q.empty())
	{
		//code that will read data to be transmitted from the
		//sender and save it in myArr variable. The amount of data
		//transmitted will be saved in variable sendCount
		sendCount = tx.readFromSender(200, myArr);

		//loop that will iterate until all the data that was copied to
		//myArr has been sent to the quue
		for (int i = 0; i < sendCount; i++)
		{
			//code that transfer the data contained in myArr
			//to the queue's array
			q.enqueue(myArr[i]);
		}//end for

	//code that saves how much data that receiver is able to receive
	//and updates variable sendCount with the information
		sendCount = rx.howManyCharCanRx();

		//Condition that ensures that receiver has space to process data
		//from sender
		if (sendCount > 0)
		{
			//variable queueTracker initialization
			queueTracker = 0;

			//loop that will iterate until all data that the
			//receiver is able to process is received
			for (int i = 0; i < sendCount; i++)
			{
				//condition that checks to ensure that there
				//is data to be transmitted from the queue
				if (!q.empty())
				{
					//code that takes the data from the 
					//front of the queue and saves it to myArr
					myArr[i] = q.front();

					//code that deletes the data that was 
					//transfered to myArr from the queue
					q.dequeue();

					//counter that keeps track of how many
					//items were transfered from the queue
					queueTracker++;
				}//end if							
			}//end for

		//code that transfers all the data contained in myArr
		//to the receiver
			rx.sendCharsToRx(queueTracker, myArr);
		}//end if					
	}//end while


// put your code here (above)

	double duration = ((std::clock() - start) / (double)CLOCKS_PER_SEC);
	std::cout << "The time to transfer the data was " << duration << " milliseconds" << std::endl;
	std::cout << rx.getRxedMsg() << std::endl;
	std::cout << "The maximum queue depth = " << q.getMaxSize() << std::endl;

	return 0;
}