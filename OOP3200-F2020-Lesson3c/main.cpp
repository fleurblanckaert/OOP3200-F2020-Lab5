/* Name: Fleur Blanckaert (100747083), Gabriel Dietrich (100764733)
Date: Oct 24 2020
Program: OOP 3200 - Lab 5 - Standard Template Library
Description: This page reads the the data of another file, count how many
points there are and the distance between them. Then, it prompts
the user to enter a specific point and it calculates the distance
between the first point until the point entered
*/


#include <fstream>
#include <iomanip>
#include <iostream>
#include <map>
#include "Vector2D.h"

int main()
{
	try
	{
		/************************
		* DECLARATIONS
		************************/
		int count = -1;

		float totalDistance = 0;
		float x = 0;
		float y = 0;

		std::map<std::string, Vector2D<float>*> vectorObj;
		std::ifstream inClientFile;
		std::string fileName = "PointData.dat";
		std::string userInput;
		std::string key = "";

		/******************************************************************************
	   * Reading Labels/Points into the Map:
	   * Attempt to open the data file. If the data file opens, read a label,
	   * followed by a point and insert them into the map using the label as the key.
	   * Repeat until all the data is read and close the file. If the data file did
	   * not open, tell the user and remind them to check that the file exists. If
	   * the file opened but the map is empty after the input loop, report that to
	   * the user and remind them to check that the file contains valid data in
	   * the correct format. Only continue processing if the file was opened and the
	   * map is not empty.
	   ******************************************************************************/

	   // Opens file
		inClientFile.open(fileName.c_str());
		//If the data file did not open, tell the user and remind them to check that the file exists.
		if (!inClientFile.is_open())
		{
			throw std::invalid_argument("File could not be opened for input. Please check if the file exists.\n");
		}
		//If the file opened, then...
		else
		{
			//Attempts to open the data file. If the data file opens, reads a label, followed by a point
			while (!inClientFile.fail())
			{
				// Ignores brackets and comma
				inClientFile >> key;
				inClientFile.ignore(1, ' ');
				inClientFile.ignore(1, '(');
				inClientFile >> x;
				inClientFile.ignore(1, ',');
				inClientFile.ignore(1, ' ');
				inClientFile >> y;
				inClientFile.ignore(1, ')');

				// Counts points
				count++;

				// Creates object that will store points
				auto* tempObj = new Vector2D<float>(x, y);

				//Inserts points into the map using the label as the key.
				vectorObj[key] = tempObj;

				/******************************************************************************
			   * Determine the Total Distance Between All Points in Order:
			   * Use an iterator and a loop to traverse each label/point in the map. For
			   * each label/point, determine the distance from that point to the previous
			   * point (or next point depending on how you implement this) and add that
			   * distance to a total. Note that the Vector2D class includes a static
			   * distance function to determine the distance between two Vector2D
			   * objects, so you should not need to use any complicated math here. Report
			   * to the user how many points the map contains and what the total distance is.
			   ******************************************************************************/

			   // Starts the points at (0, 0)
				auto* startObj = new Vector2D<float>(0, 0);

				// Calls Distance functionality
				auto distance = Vector2D<float>::Distance(*startObj, *tempObj);

				// Adds distances
				totalDistance += distance;
			}
			// Closes file
			inClientFile.close();
			// If map is empty
			if (vectorObj.empty())
			{
				throw std::invalid_argument("The map is empty. Check that the file contains valid data in the correct format\n");
			}

			//Reports to the user all points
			for (auto tempObj : vectorObj)
			{
				std::cout << tempObj.first;
				std::cout << tempObj.second->ToString() << std::endl;
			}
			//Reports totals to user
			std::cout << "\nThe map contains a total of " << count << " points for a total distance of "
				<< std::to_string(totalDistance) << std::endl << std::endl;

			/******************************************************************************
			* Determine the Distance Between the Start Point and a User Selected Point:
			* Prompt the user to enter a label or to enter "quit" to end. If the user
			* entered anything other than "quit", attempt to find the label they entered
			* in the map. If it was found, report the distance between the point for the
			* label they entered and the start point (i.e. the point labeled "AA").
			* Otherwise, tell the user that the label they entered is not in the map.
			* Repeat these steps until the user enters "quit".
			******************************************************************************/

			// Ends application if user types quit
			while (userInput != "quit")
			{
				//Variable declarations
				int findTotalDistance = 0;
				
				std::cout << "Enter the label of the point you wish to go to ('quit' to end): ";
				std::cin >> userInput;

				// Searches for userInput within map
				auto it = vectorObj.find(userInput);

				// If userInput is found in the map
				if (it != vectorObj.end())
				{
					//Point for userInput 
					auto it = vectorObj[userInput];

					//inital Point
					auto* userTemp = new Vector2D<float>();

					//Calculates distance between AA and userInput
					auto findDistance = Vector2D<float>::Distance(*userTemp, *it);
					findTotalDistance += findDistance;

					std::cout << "\tThe distance between AA (0, 0)" << " and " << userInput << " (" <<
						it->GetX() << ", " << it->GetY() << ") is " << std::to_string(findTotalDistance) << std::endl << std::endl;

				}

				//If userInput is not found in the map
				else if (userInput != "quit")
				{
					std::cerr << "\tThere is no point labelled (" <<  userInput <<  ") in the map \n\n";
				}
			}

		}
	}
	/******************************************************************************
	* Exception Handling:
	* Catch any std::exception thrown. Report to the user that a run-time error
	* occurred and show what exception was thrown.
	******************************************************************************/
	catch (const std::invalid_argument& ex)
	{
		std::cerr << "\nException occurred: " << ex.what() << std::endl << std::endl;
	}

	// END-OF-PROGRAM

	return 0;
}