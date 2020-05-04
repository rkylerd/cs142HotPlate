#include <iostream>
#include <string>
#include <math.h>
#include <iomanip>
#include <fstream>
#define WIDTH 20
#define HEIGHT 20
using namespace std;

/*the purpose of this program is to create a hot plate, distributing heat toward the middle of the plate by averaging the surrounding values.
The program further creates a file readable and viewable by microsoft excel.*/


void Average(double initialPLATE[][HEIGHT], double average[][HEIGHT])
{// this function takes the average of the values directly above, below, to the left, and to the right of a location on the plate.
	for (int j = 1; j < HEIGHT - 1; j++) {
			for (int i = 1; i < WIDTH - 1; i++) {
				int surrounding = 4;
				average[i][j] = (initialPLATE[i - 1][j] + initialPLATE[i + 1][j] + initialPLATE[i][j-1] + initialPLATE[i][j + 1]) / surrounding;
			}
		}
}


void untilStable(double average[][HEIGHT], double initialPLATE[][HEIGHT], double stable) 
{//This function will continue to average each row until the difference in the average temperatures is less than or equal to .1
	bool check = true;
	while (check) {
		
		double largest = 0;
		double difference = 1;
		Average(initialPLATE, average);
		for (int i = 0; i<WIDTH; i++) {//if there is a greater number encountered through the loop, it becomes the new geatest value.
			for (int j = 0; j<HEIGHT; j++) {	
				difference = abs(average[j][i] - initialPLATE[j][i]);
				if (difference > largest) {
					largest = difference;
				}				
			}
		}
		for (int i = 0; i < WIDTH; i++) {
			for (int j = 0; j < HEIGHT; j++) {
				initialPLATE[j][i] = average[j][i];
			}
		}
		if (largest < stable) {
			check = false;
		}
	}
}
void firstIteration(double average[][HEIGHT], double initialPLATE[][HEIGHT])
{
	Average(initialPLATE, average);
	for (int i = 1; i < WIDTH-1; i++) {
		for (int j = 0; j < HEIGHT; j++) {
			initialPLATE[j][i] = average[j][i];
		}
	}
}
void initializer(int firstRow, int lastRow, double initialPLATE[][HEIGHT], double _100degrees, double _0degrees)
{//This function initializes the hot plate to zero, with 100s on the top and bottom rows
	for (int j = 0; j < WIDTH; j++) {
		for (int i = 0; i < HEIGHT; i++) {
			if (i > firstRow && i < lastRow && (j == firstRow || j == lastRow)) {
				initialPLATE[i][j] = _100degrees;
			}
			else {
				initialPLATE[i][j] = _0degrees;
			}
		}
	}
}
void print(int firstRow, int lastRow, double initialPLATE[][HEIGHT]) 
{//The purpose of this function is to simply print out both the initial, and final heated plate.
	for (int j = 0; j < WIDTH; j++) {
		for (int i = 0; i < HEIGHT; i++) {
			
			cout << fixed << setprecision(1) << initialPLATE[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}

void SendToCSV(double initialPLATE[][HEIGHT])// this function turns it into a file readable by microsoft excel
{// find the file by the source code
	ofstream outFile("lab6output.csv");
	for (int i = 0; i < HEIGHT; i++) {
		for (int j = 0; j < WIDTH; j++) {
			outFile << fixed << setprecision(4) << initialPLATE[j][i] << ",";
		}
		outFile << endl;
	}
	outFile.close();
}

int main()
{
	int lastRow = 19;
	int firstRow = 0;
	int surrounding = 4;
	int corners = 3;
	double _100degrees = 100;
	double _0degrees = 0;
	double stable = .1;
	 
	
	double initialPLATE[WIDTH][HEIGHT];
	double average[WIDTH][HEIGHT];
	
	//Initialize the plate with 0s and 100s
	initializer(firstRow, lastRow, initialPLATE, _100degrees, _0degrees);
	print(firstRow, lastRow, initialPLATE);
	initializer(firstRow, lastRow, average, _100degrees, _0degrees);

	// Prints the first iteration.
	firstIteration(average, initialPLATE);
	print(firstRow, lastRow, initialPLATE);

	//Average each plate position until stable 
	untilStable(average, initialPLATE, stable);
	print(firstRow, lastRow, initialPLATE);
	
	//Export the Hot PLate to a csv file
	SendToCSV(initialPLATE);
	system("pause");
	return 0;
}