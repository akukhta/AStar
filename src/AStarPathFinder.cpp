#include "pch.h"
#include <set>
#include <queue>
#include <array>
#include "../include/AStarPathFinder.h"

std::forward_list<std::pair<int, int>> AStarPathFinder::findPath(std::vector<std::vector<char>> const& matrix, std::vector<char> const& nonMovableChars, std::pair<int, int> const& startingPoint, std::pair<int, int> const& targetPoint,
    bool enableDiagonalsMoves)
{
    std::forward_list<std::pair<int, int>> paths;

    std::unordered_map<int, std::unordered_map<int, int>> open;
    std::unordered_map<int, std::set<int>> closed;

    std::priority_queue<std::shared_ptr<cell>, std::vector<std::shared_ptr<cell>>, decltype(cell::compareShared)*> sorted(cell::compareShared);

    auto startPoint = std::make_shared<cell>(std::make_pair(startingPoint.first, startingPoint.second));

    open[startingPoint.first][startingPoint.second] = 0;

    sorted.push(startPoint);


    while (true)
    {
        if (sorted.empty())
        {
            break;
        }

        auto curr = sorted.top();
        sorted.pop();

        open[curr->currentCell.first].erase(curr->currentCell.second);
        closed[curr->currentCell.first].insert(curr->currentCell.second);

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
                if (std::find(nonMovableChars.begin(), nonMovableChars.end(), matrix[nbI][nbJ]) != nonMovableChars.end() || checkIfPresent(nbI, nbJ, closed))
                {
                    continue;
                }

                auto neighborCell = std::make_shared<cell>(curr, std::make_pair(nbI, nbJ), targetPoint, off);

                auto cellIsPresent = checkIfPresent(nbI, nbJ, open);

                if (checkIfPresent(nbI, nbJ, open) == false || open[nbI][nbJ] > neighborCell->totalCost)
                {
                    open[nbI][nbJ] = neighborCell->totalCost;
                    sorted.push(neighborCell);
                }
            }
        }
    }

    return paths;
}
