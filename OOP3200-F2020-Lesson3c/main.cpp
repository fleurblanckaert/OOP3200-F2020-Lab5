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
		 *	DECLARATIONS
		 ************************/
		std::map<std::string, Vector2D<float>*> vectorObj;
		std::ifstream inClientFile;
		const std::string fileName = "MockDataForTesting.txt";

		/******************************************************************************
		 *	Reading Labels/Points into the Map:
		 *	Attempt to open the data file.  If the data file opens, read a label,
		 *	followed by a point and insert them into the map using the label as the key.
		 *	Repeat until all the data is read and close the file. If the data file did
		 *	not open, tell the user and remind them to check that the file exists. If
		 *	the file opened but the map is empty after the input loop, report that to
		 *	the user and remind them to check that the file contains valid data in
		 *	the correct format. Only continue processing if the file was opened and the
		 *	map is not empty.
		 ******************************************************************************/

		 //Opens file
		inClientFile.open(fileName.c_str());

		// If file doesn't open, display error message
		if (!inClientFile.is_open())
		{
			std::cerr << "File could not be opened for input. Please check if the file exists.\n";
			std::cout << "---------------------------------\n";
		}
		else
		{
			int count = 0;
			std::string key;
			int x, y;

			// Reads every line of file until the end
			while (!inClientFile.fail())
			{

				inClientFile >> key;
				inClientFile.ignore(1, ' ');
				inClientFile.ignore(1, '(');
				inClientFile >> x;
				inClientFile.ignore(1, ',');
				inClientFile.ignore(1, ' ');
				inClientFile >> y;
				inClientFile.ignore(1, ')');

				count++;

			}

			/******************************************************************************
			 *	Determine the Total Distance Between All Points in Order:
			 *	Use an iterator and a loop to traverse each label/point in the map. For
			 *	each label/point, determine the distance from that point to the previous
			 *	point (or next point depending on how you implement this) and add that
			 *	distance to a total.  Note that the Vector2D class includes a static
			 *	distance function to determine the distance between two Vector2D
			 *	objects, so you should not need to use any complicated math here.  Report
			 *	to the user how many points the map contains and what the total distance is.
			 ******************************************************************************/

			auto* temp_object1 = new Vector2D<float>;
			auto* temp_object2 = new Vector2D<float>(x, y);

			auto distance = Vector2D<float>::Distance(*temp_object1, *temp_object2);

			std::cout << "The map contains a total of " << count << " points for a total distance of " << std::to_string(distance) << std::endl;

			inClientFile.close(); 

			//inClientFile.close();
			/*if (vectorObj.empty())
			{
			std::cerr << "File is empty. Please check the file contains valid data and in the correct format\n";
			std::cout << "---------------------------------\n";*/
			//}
		}



		//// Used this part for testing purposes, gonna come out of file later
		//char str[255];

		//while(inClientFile)
		//{
		//	inClientFile.getline(str, 255);
		//	if (inClientFile) std::cout << str << std::endl;
		//}



		/******************************************************************************
		 *	Determine the Distance Between the Start Point and a User Selected Point:
		 *	Prompt the user to enter a label or to enter "quit" to end.  If the user
		 *	entered anything other than "quit", attempt to find the label they entered
		 *	in the map. If it was found, report the distance between the point for the
		 *	label they entered and the start point (i.e. the point labeled "AA").
		 *	Otherwise, tell the user that the label they entered is not in the map.
		 *	Repeat these steps until the user enters "quit".
		 ******************************************************************************/



	}
	/******************************************************************************
	 *	Exception Handling:
	 *	Catch any std::exception thrown. Report to the user that a run-time error
	 *	occurred and show what exception was thrown.
	 ******************************************************************************/
	catch (...)  // an exception was thrown
	{
		std::cerr << "\nException occurred: " << std::endl;
		//return false;
	}

	// END-OF-PROGRAM

	return 0;
}

void outputLine(int, int)
{
}
