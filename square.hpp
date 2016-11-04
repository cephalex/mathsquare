//square.hpp
#ifndef SQUARE_HPP
#define SQUARE_HPP

#include <list>

struct Triplet
{
	 	int member[3];
};
	
class Square
{
	public:
		Square(int[4][4], char[3][2], char[3][2]); //constructor
		void solve();	
		void displaySquare();
		void displayTriplets(std::list<Triplet>);
	
	private:
		int numbers[4][4]; 
		char rowOperations[3][2];
		char columnOperations[3][2];
		float doOperation(char op, float a, float b);
};


#endif //SQUARE_HPP
