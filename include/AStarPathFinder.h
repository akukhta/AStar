#pragma once
#include <forward_list>
#include <memory>
#include <unordered_map>

template <typename T>
concept HasFind = requires (T x) { x.find(T::key_type()); };


class AStarPathFinder
{
public:
    AStarPathFinder() = delete;
    void* operator new(size_t) = delete;

    static std::forward_list<std::pair<int, int>> findPath(std::vector<std::vector<char>> const& matrix,
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

            totalCost += (prevCell != nullptr ? prevCell->moveCost : 0) + moveCost;
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
            return a->totalCost < b->totalCost;
        }
    };

    template<class HasFind>
    static bool checkIfPresent(int i, int j, std::unordered_map<int, HasFind>& map)
    {
        if (map.find(i) != map.end())
        {
            if (map[i].find(j) != map[i].end())
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        else
        {
            return false;
        }
    }
};

