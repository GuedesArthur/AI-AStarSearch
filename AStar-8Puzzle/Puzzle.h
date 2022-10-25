#pragma once
#include "Point2D.h"
#include <iterator>
#include <vector>
#include <optional>
#include <set>

using namespace std;

template<int width, int height>
struct Puzzle
{
public:
	typedef array<array<int, width>, height> Matrix;

private:
	Matrix _matrix; // Stores the current puzzle pieces' position
	static inline Point2D FinalPos(int index); // Get's that number's solution position
	int Solve(int moveCount, set<Puzzle>* set);

public:
	Puzzle(Matrix m); // Constructor
	Puzzle(const Puzzle& puzzle);
	int Solve();
	Point2D Find(int num) const; // Finds the num's piece position
	optional<Puzzle> Move(Point2D dir) const; // Moves the empty(0) piece in that specific direction
	void Swap(Point2D a, Point2D b);
	vector<Puzzle> PossibleMovements() const; // Gets all possible states after each possible movement
	int Evaluate() const; // Measures the Puzzle's correctness
	array<int, width> operator[](int i);
	int operator[](Point2D p);
	inline bool IsInsideBoard(Point2D point) const; // Is this point inside the board coordinates? 

	struct Comparer
	{
		bool Compare(Puzzle& lhs, Puzzle& rhs) const;
	};
};