#include "pch.h"
#include <set>
#include <unordered_set>
#include <queue>
#include <array>
#include "../include/AStarPathFinder.h"

std::forward_list<std::pair<int, int>> AStarPathFinder::findPath(std::vector<std::vector<char>> const& matrix, std::vector<char> const& nonMovableChars, std::pair<int, int> const& startingPoint, std::pair<int, int> const& targetPoint,
    bool enableDiagonalsMoves)
{
    std::forward_list<std::pair<int, int>> paths;

    std::unordered_map<size_t, int> open;
    std::unordered_set<size_t> closed;

    std::priority_queue<std::shared_ptr<cell>, std::vector<std::shared_ptr<cell>>, decltype(cell::compareShared)*> sorted(cell::compareShared);

    auto startPoint = std::make_shared<cell>(std::make_pair(startingPoint.first, startingPoint.second));

    open[hashPair(matrix.size(), startingPoint.first, startingPoint.second)] = 0;

    sorted.push(startPoint);


    while (true)
    {
        if (sorted.empty())
        {
            break;
        }

        auto curr = sorted.top();
        sorted.pop();

        open.erase(hashPair(matrix.size(), curr->currentCell.first, curr->currentCell.second));

        closed.insert(hashPair(matrix.size(), curr->currentCell.first, curr->currentCell.second));
        
        if (curr->currentCell.first == targetPoint.first && curr->currentCell.second == targetPoint.second)
        {
            auto it = curr;

            while (it)
            {
                paths.push_front(it->currentCell);
                it = it->prevCell;
            }

            break;
        }

        // Iterate through all neighboors
        std::vector<std::pair<int, int>> offsets = {
            {-1, 0}, {1, 0}, {0, -1}, {0, 1}  // Up, Down, Left, Right
        };

        if (enableDiagonalsMoves)
        {
            for (auto off : std::array<std::pair<int, int>, 4>{ std::make_pair(-1, -1), std::make_pair(-1, 1),
                std::make_pair(1, -1), std::make_pair(1, 1) })
            {
                offsets.push_back(off);
            }
        }

        // Iterate through the offsets to access the neighbors
        for (auto& off : offsets)
        {
            int nbI = curr->currentCell.first + off.first;
            int nbJ = curr->currentCell.second + off.second;

            // Check if the neighbor is within the matrix bounds
            if (nbI >= 0 && nbI < matrix.size() && nbJ >= 0 && nbJ < matrix[0].size())
            {
                if (std::find(nonMovableChars.begin(), nonMovableChars.end(), matrix[nbI][nbJ]) != nonMovableChars.end() || checkIfPresent(hashPair(matrix.size(), nbI, nbJ), closed))
                {
                    continue;
                }

                auto neighborCell = std::make_shared<cell>(curr, std::make_pair(nbI, nbJ), targetPoint, off);

                auto cellKey = hashPair(matrix.size(), nbI, nbJ);

                if (checkIfPresent(cellKey, open) == false || open[cellKey] > neighborCell->totalCost)
                {
                    open[cellKey] = neighborCell->totalCost;
                    sorted.push(neighborCell);
                }
            }
        }
    }

    return paths;
}
