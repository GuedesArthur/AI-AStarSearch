#include "Puzzle.h"
#include <algorithm>
#include <array>
#include <vector>
#include <set>

using namespace std;

template<int width, int height>
Puzzle<width, height>::Puzzle(Matrix m) : _matrix(m) {}

template<int width, int height>
Puzzle<width, height>::Puzzle(const Puzzle& puzzle) : _matrix(puzzle._matrix) { }

template<int width, int height>
inline Point2D Puzzle<width, height>::FinalPos(int index)
{
    return Point2D(index % width, index /width);
}

template<int width, int height>
int Puzzle<width, height>::Solve(int moveCount, set<Puzzle>* set)
{
    vector<Puzzle> vec = PossibleMovements();
    sort(vec.begin(), vec.end(), Puzzle::Comparer());

    if (vec[0].Evaluate() == 0) // Only verifies the puzzle with the least value (closest to solution)
        return moveCount; 

    for (Puzzle puz : vec)
    {
        auto result = (*set).insert(puz);
        if (!result.second) continue; // If has already checked that state, ignores it
        return puz.Solve(moveCount + 1, set);
    }

    return -1;
}

template<int width, int height>
int Puzzle<width, height>::Solve()
{
    set<Puzzle> puzzleSet;
    return Solve(0, &puzzleSet);
}

template<int width, int height>
Point2D Puzzle<width, height>::Find(int num) const
{
    for (int i = 0; i < width; i++)
        for (int j = 0; j < height; j++)
            if (this->_matrix[i][j] == num)
                return Point2D(j, i);
    throw "Could not find number " + num;
}

template<int width, int height>
optional<Puzzle<width, height>> Puzzle<width, height>::Move(Point2D dir) const
{
    auto point = Find(0);

    if (!IsInsideBoard(point + dir)) return std::nullopt; // If that direction is a wall, returns null
    Puzzle copy = *this;
    copy.Swap(point, point + dir);

    return { copy }; // Else, returns the new puzzle state
}

template<int width, int height>
void Puzzle<width, height>::Swap(Point2D a, Point2D b)
{
    auto temp = _matrix[a.x][a.y];
    _matrix[a.x][a.y] = _matrix[b.x][b.y];
    _matrix[b.x][b.y] = temp;
}

template<int width, int height>
vector<Puzzle<width, height>> Puzzle<width, height>::PossibleMovements() const
{
    vector<Puzzle> vec(4);

    auto point = Find(0);

    for (Point2D dir : Point2D::Directions) // All possible movements (up, down, left, right)
    {
        optional<Puzzle> result = Move(dir);
        if (result.has_value())
            vec.emplace_back(result);
    }

    return vec;
}

/*
The value of each puzzle corresponds to the sum of each piece's distance to the final position
*/
template<int width, int height>
int Puzzle<width, height>::Evaluate() const
{
    int sum = 0;
    for (int i = 0; i < width * height; i++)
        sum += Find(i).ManehattanDist(&FinalPos(i));

    return sum;
}

template<int width, int height>
array<int, width> Puzzle<width, height>::operator[](int i)
{
    return _matrix[i];
}

template<int width, int height>
int Puzzle<width, height>::operator[](Point2D p)
{
    return _matrix[p.x][p.y];
}

template<int width, int height>
inline bool Puzzle<width, height>::IsInsideBoard(Point2D point) const
{
    return point.x >= 0 && point.y > 0 && point.x < width && point.y < height;
}

template<int width, int height>
inline bool Puzzle<width, height>::Comparer::Compare(Puzzle& lhs, Puzzle& rhs) const
{
    return lhs.Evaluate() < rhs.Evaluate();
}
