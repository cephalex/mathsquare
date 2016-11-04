//square.cpp

#include <iostream>
#include <set>
#include <list>
#include <algorithm>
#include "square.hpp"

// Square constructor
Square::Square(int localNumbers[4][4], char localRowOps[3][2], char localColOps[3][2])
{
	for(int i=0; i<=3; i++)
	{
		for(int j=0; j<=3; j++)
		{
			numbers[i][j] = localNumbers[i][j];
		}
	}
	
	for(int i=0; i<=2; i++)
	{
		for(int j=0; j<=1; j++)
		{
			rowOperations[i][j] = localRowOps[i][j];
		}
	}

	for(int i=0; i<=2; i++)
	{
		for(int j=0; j<=1; j++)
		{
			columnOperations[i][j] = localColOps[i][j];
		}
	}

} //end of Square constructor



//--------------------------Square.solve---------------------------------------
void Square::solve()
{
//	std::cout << "Entering Square.Solve2\n";	//debug
	
	std::set<int> digits, remainingDigits;
	Triplet currentTriplet;
	std::list<Triplet> rowTriplets[3];
	std::list<Triplet> colTriplets[3];
	std::list<Triplet> tempTriplets;
	int formula[4];
	float answer, answerA, answerB, answerC;
	bool found = false;
	
	for (int i=1; i<=9; ++i) // fill digits set with digits 1 - 9
	{
		digits.insert(i);    // set := 1 2 3 4 5 6 7 8 9
	}
	remainingDigits = digits;
	
	// Fill row triplets with all possible solutions for each formula
	for (int i=0; i<=2; i++)
	{
		for (int j=0; j<=3; j++)
		{
			formula[j] = numbers[i][j];
		}
		
		for (int firstDigit=1; firstDigit<=9; firstDigit++)
		{
			for (int secondDigit=1; secondDigit<=9; secondDigit++)
			{
				if (secondDigit != firstDigit) // no duplicate digits
				{
					for (int thirdDigit=1; thirdDigit<=9; thirdDigit++)
					{
						if ((thirdDigit != firstDigit) && (thirdDigit != secondDigit)) // no duplicate digits
						{
//							std::cout << firstDigit << rowOperations[i][0] << 
//								secondDigit << rowOperations[i][1]<< thirdDigit;	/debug
							answer = doOperation(rowOperations[i][1], 
								doOperation(rowOperations[i][0], firstDigit, secondDigit), thirdDigit);
//							std::cout << "=" << answer << " ";	//debug
							if (answer == numbers[i][3])
							{
								currentTriplet.member[0] = firstDigit;
								currentTriplet.member[1] = secondDigit;
								currentTriplet.member[2] = thirdDigit;
								rowTriplets[i].push_back(currentTriplet);							
							}
						}
					}
				}			
			}
			
		}
    	
//    	displayTriplets(rowTriplets[i]);	//debug
	}
	
	// This phase compares the sets of triplets and only uses the ones that fit

	for (std::list<Triplet>::iterator itRow0=rowTriplets[0].begin(); itRow0 !=rowTriplets[0].end(); ++itRow0)
    {
	    for (std::list<Triplet>::iterator itRow1=rowTriplets[1].begin(); itRow1 !=rowTriplets[1].end(); ++itRow1)
        {
            if ((itRow0->member[0] != itRow1->member[0]) && (itRow0->member[1] != itRow1->member[1]) && (itRow0->member[2] != itRow1->member[2]))
            {
                for (std::list<Triplet>::iterator itRow2=rowTriplets[2].begin(); itRow2 !=rowTriplets[2].end(); ++itRow2)
                {
                    if ((itRow1->member[0] != itRow2->member[0]) && (itRow1->member[1] != itRow2->member[1]) && (itRow1->member[2] != itRow2->member[2]))
                    {
                    answerA = doOperation(columnOperations[0][1], doOperation(columnOperations[0][0], itRow0->member[0], itRow1->member[0]), itRow2->member[0]);
                        if (answerA == numbers[3][0]) // first column correct
                        {
        //                    std::cout << "First Column Correct\n";
                            answerB = doOperation(columnOperations[1][1], doOperation(columnOperations[1][0], itRow0->member[1], itRow1->member[1]), itRow2->member[1]);
                            if (answerB == numbers[3][1]) // first and second columns correct
                            {
        //                        std::cout << "Second Column Correct\n";
                                answerC = doOperation(columnOperations[2][1], doOperation(columnOperations[2][0], itRow0->member[2], itRow1->member[2]), itRow2->member[2]);
                                if (answerC == numbers[3][2]) // all columns correct
                                {
                                    std::cout << "Solution:\n";
                                    for (int i = 0; i <= 2; i++)
                                    {
                                        numbers[0][i] = itRow0->member[i];
                                        numbers[1][i] = itRow1->member[i];
                                        numbers[2][i] = itRow2->member[i];
                                    }
                                    displaySquare();
                                 //   return; //uncomment if you only want one solution
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    
} //end of Square.solve



//--------------------------Square.displaySquare--------------------------------
void Square::displaySquare()
{
//	std::cout << "Entering displaySquare\n";	//debug
	for (int i=0; i<=2; i++)
	{
		std::cout << numbers[i][0] << ' ' << rowOperations[i][0] << ' ' << 
					 numbers[i][1] << ' ' << rowOperations[i][1] << ' ' << 
					 numbers[i][2] << " = " << numbers[i][3]<< std::endl;
		
		if (i <=1)
		{			 
			std::cout << columnOperations[0][i] << "   " << columnOperations[1][i]
					  << "   " << columnOperations[2][i]<< std::endl;
		}
	}
	
	std::cout << "=   =   =" << std::endl;
	std::cout << numbers[3][0] << "   " << numbers[3][1] << "  " << numbers[3][2] << std::endl;	
	std::cout << std::endl;
	
} //end of Square.displaySquare()



//--------------------------Square.displayTriplets------------------------------
void Square::displayTriplets(std::list<Triplet> displayList)
{
	std::cout << "Entering displayTriplets\n";
	
	for(std::list<Triplet>::iterator it=displayList.begin(); it !=displayList.end(); ++it)
	{
		std::cout << it->member[0] << " " << it->member[1] << " " << it->member[2] << std::endl;
	}
} //end of Square.displayTriplets



//--------------------------Square.doOperation------------------------------
float Square::doOperation(char op, float a, float b)
{
    switch(op)
    {
		case '+':
		   return a+b;
			break;
		case '-':
		   return a-b;
			break;
		case '*':
		   return a*b;
			break;
		case '/':
		   return a/b;
			break;
		default:
		    std::cerr << "unknown op" << std::endl;
		    return 0;
		    break;
    }
 } //end of Square.doOperation
