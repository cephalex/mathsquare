/* Ross Trimble
 to solve a math square, the numbers 1-9 go once each into the 9 spaces (_)
 the numbers and operators must equal the number to the right or bottom of row
 see http://mentalfloss.com/article/53721/brain-game-math-square-192
 	___________
 	|_ * _ / _|= 6
 	|+   +   *|
 	|_ + _ - _|= 5
 	|-   +   -|
 	|_ + _ + _|= 13
	-----------
	 =   =   =
	 2   13  13
*/
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <set>
#include "square.hpp"

int readFile(char* filename, int numbers[][4], char rowOps[][2], char colOps[][2]);


int main(int argc, char* argv[])
{

	std::set<int> digits;
	int problemNumbers[4][4] = {{0,0,0,0}, {0,0,0,0}, {0,0,0,0}, {0,0,0,0}};
	char problemRowOperations[3][2] = {{'+','+'}, {'+','+'}, {'+','+'}};
	char problemColOperations[3][2] = {{'+','+'}, {'+','+'}, {'+','+'}};


    readFile(argv[1], problemNumbers, problemRowOperations, problemColOperations);

	Square data(problemNumbers, problemRowOperations, problemColOperations);
		
	std::cout << "Problem Set:\n";	    
	data.displaySquare();
	data.solve();

	std::cout << std::endl;
} // end of main


//-------------------------------readFile---------------------------------------
int readFile(char* filename, int numbers[][4], char rowOps[][2], char colOps[][2])
{
    char noErrors = 1;
    std::ifstream inputFile(filename);
    std::string inputLine;

    if (inputFile.is_open())
    {
        for (int row = 0; row <=4; row++)
        {
            std::getline (inputFile, inputLine); 
//            std::cout << inputLine << std::endl;	//debug
            std::istringstream inputLineStream (inputLine);


            if (row%2 == 0)     //on even lines
            {
                inputLineStream >> rowOps[row / 2][0];
                inputLineStream >> rowOps[row / 2][1];
                inputLineStream >> numbers[row / 2][3];
            }
            else                //on odd lines
            {
                for (int col = 0; col <=2; col++)
                    inputLineStream >> colOps[col][(row-1) / 2];
            }
        }

        //sixth line outside loop
        std::getline (inputFile, inputLine); 
//        std::cout << inputLine << std::endl; //debug
        std::istringstream inputLineStream (inputLine);

        for (int col = 0; col <=2; col++)
            inputLineStream >> numbers[3][col];

    }
    else
        noErrors = 0;

    inputFile.close();
    
    return (noErrors);

} //end of readFile
