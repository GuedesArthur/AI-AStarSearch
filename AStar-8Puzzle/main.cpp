#include "Puzzle.h"
#include <array>
#include <iostream>


int main(int argc, char* argv[])
{
	Puzzle<3, 3> puzzle({{
		{1,8,2},
		{0,4,3},
		{7,6,5}
	}});

	auto moves = puzzle.Solve();

	if (moves == -1)
		std::cout << "Could not be solved!";
	else
		std::cout << "Solved in" << moves << " moves!";

	return 0;
}

