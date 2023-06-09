#pragma once
#include <deque>
#include <memory>
#include <unordered_map>

template <typename T>
concept HasFind = requires (T x) { std::same_as<decltype(x.find(T::key_type())), typename T::iterator>; };


class AStarPathFinder
{
public:
    AStarPathFinder() = delete;
    void* operator new(size_t) = delete;

    static std::deque<std::pair<int, int>> findPath(std::vector<std::vector<char>> const& matrix,
        std::vector<char> const& nonMovableChars, std::pair<int, int> const& startingPoint, std::pair<int, int> const& targetPoint, bool enableDiagonalsMoves = true);

private:

    struct cell
    {
        cell(std::shared_ptr<cell> prevCell, std::pair<int, int> currentCell, std::pair<int, int> const& target,
            std::pair<int, int> const& direction) : currentCell(currentCell), prevCell(prevCell)
        {
            totalCost = fabs(target.first - currentCell.first) * 10 + fabs(target.second - currentCell.second) * 10;

            // diagonal direction
            if (direction.first != 0 && direction.second != 0)
            {
                moveCost = 14;
            }
            // straight direciton
            else
            {
                moveCost = 10;
            }

            totalCost += (prevCell != nullptr ? this->prevCell->moveCost : 0) + moveCost;
        }

        cell(std::pair<int, int> currentCell)
            : totalCost(0), moveCost(0), prevCell(nullptr), currentCell(currentCell) {
            ;
        }

        int totalCost;
        int moveCost;
        std::shared_ptr<cell> prevCell;
        std::pair<int, int> currentCell;

        static bool compareShared(std::shared_ptr<cell> const& a, std::shared_ptr<cell> const& b)
        {
            return a->totalCost > b->totalCost;
        }
    };

    template <class T, class HasFind>
    static bool checkIfPresent(T key, HasFind & map)
    {
        return map.find(key) != map.end();
    }

    static inline size_t hashPair(size_t maxSize, int a, int b)
    {
        return std::hash<int>()(a * maxSize + b);
    }

    static std::vector<std::pair<int, int>> const forwardOffsets;
    static std::vector<std::pair<int, int>> const diagonalsOffsets;
};

