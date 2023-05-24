// tests.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#define BOOST_TEST_MODULE PathfindingTest
#include <boost/test/unit_test.hpp>
#include <vector>
#include "AStarPathFinder.h"

std::vector<char> obstacles = { 'X' };

BOOST_AUTO_TEST_CASE(Unreachable1)
{
    std::vector<std::vector<char>> matrix{ {'.', '.', 'X', '.'} };
    auto startingPoint = std::make_pair(0, 0);
    auto endPoint = std::make_pair(0, 3);

    BOOST_CHECK(AStarPathFinder::findPath(matrix, obstacles, startingPoint, endPoint).empty() == true);
}

BOOST_AUTO_TEST_CASE(Reachable1)
{
    std::vector<std::vector<char>> matrix{ {'X', '.', '.', '.'} };
    auto startingPoint = std::make_pair(0, 1);
    auto endPoint = std::make_pair(0, 3);

    BOOST_CHECK(AStarPathFinder::findPath(matrix, obstacles, startingPoint, endPoint).empty() == false);
}

BOOST_AUTO_TEST_CASE(Unreachable2)
{
    std::vector<std::vector<char>> matrix{ 
        {'.', '.', 'X', '.'},
        {'X', 'X', 'X', 'X'},
        {'.', '.', 'X', '.'},
    };

    auto startingPoint = std::make_pair(0, 0);
    auto endPoint = std::make_pair(2, 1);

    BOOST_CHECK(AStarPathFinder::findPath(matrix, obstacles, startingPoint, endPoint).empty() == true);
}

BOOST_AUTO_TEST_CASE(Reachable2)
{
    std::vector<std::vector<char>> matrix{
        {'.', '.', 'X', '.'},
        {'X', 'X', '.', 'X'},
        {'.', '.', 'X', '.'},
    };
    auto startingPoint = std::make_pair(0, 0);
    auto endPoint = std::make_pair(2, 1);

    BOOST_CHECK(AStarPathFinder::findPath(matrix, obstacles, startingPoint, endPoint).empty() == false);
}

BOOST_AUTO_TEST_CASE(Unreachable3)
{
    std::vector<std::vector<char>> matrix{
        {'.', '.', 'X', '.'},
        {'.', '.', 'X', '.'},
        {'.', '.', 'X', '.'},
        {'.', '.', 'X', 'X'},
        {'X', 'X', 'X', 'X'},
        {'X', '.', 'X', '.'},
    };

    auto startingPoint = std::make_pair(0, 0);
    auto endPoint = std::make_pair(5, 1);

    BOOST_CHECK(AStarPathFinder::findPath(matrix, obstacles, startingPoint, endPoint).empty() == true);
}

BOOST_AUTO_TEST_CASE(Reachable3)
{
    std::vector<std::vector<char>> matrix{
        {'.', '.', 'X', '.'},
        {'.', '.', 'X', '.'},
        {'.', '.', 'X', '.'},
        {'.', '.', 'X', 'X'},
        {'.', 'X', 'X', 'X'},
        {'X', '.', 'X', '.'},
    };

    auto startingPoint = std::make_pair(0, 0);
    auto endPoint = std::make_pair(5, 1);

    BOOST_CHECK(AStarPathFinder::findPath(matrix, obstacles, startingPoint, endPoint).empty() == false);
}

BOOST_AUTO_TEST_CASE(UnreachableByForwardMoving)
{
    std::vector<std::vector<char>> matrix{
        {'.', '.', 'X', '.'},
        {'.', '.', 'X', '.'},
        {'.', '.', 'X', '.'},
        {'.', '.', 'X', 'X'},
        {'.', 'X', 'X', 'X'},
        {'X', '.', 'X', '.'},
    };

    auto startingPoint = std::make_pair(0, 0);
    auto endPoint = std::make_pair(5, 1);

    BOOST_CHECK(AStarPathFinder::findPath(matrix, obstacles, startingPoint, endPoint, false).empty() == true);
}

BOOST_AUTO_TEST_CASE(ReachableByDiagonalMoving)
{
    std::vector<std::vector<char>> matrix{
        {'.', '.', 'X', '.'},
        {'.', '.', 'X', '.'},
        {'.', '.', 'X', '.'},
        {'.', '.', 'X', 'X'},
        {'.', 'X', 'X', 'X'},
        {'X', '.', 'X', '.'},
    };

    auto startingPoint = std::make_pair(0, 0);
    auto endPoint = std::make_pair(5, 1);

    BOOST_CHECK(AStarPathFinder::findPath(matrix, obstacles, startingPoint, endPoint).empty() == false);
}

BOOST_AUTO_TEST_CASE(Reachable10x10)
{
    std::vector<std::vector<char>> matrix = {
        {'X', 'X', 'X', '.', 'X', '.', '.', 'X', '.', '.'},
        {'.', 'X', '.', 'X', 'X', 'X', '.', 'X', '.', '.'},
        {'.', '.', '.', 'X', '.', '.', '.', 'X', '.', '.'},
        {'X', '.', '.', 'X', '.', '.', '.', 'X', '.', '.'},
        {'.', '.', 'X', 'X', '.', '.', '.', '.', 'X', '.'},
        {'.', 'X', '.', '.', 'X', 'X', 'X', 'X', '.', '.'},
        {'X', '.', '.', 'X', '.', '.', 'X', '.', 'X', '.'},
        {'.', 'X', 'X', 'X', 'X', 'X', 'X', 'X', '.', '.'},
        {'.', '.', '.', 'X', '.', '.', 'X', '.', 'X', '.'},
        {'.', '.', '.', 'X', '.', 'X', '.', '.', '.', '.'}
    };

    auto startingPoint = std::make_pair(0, 3);
    auto endPoint = std::make_pair(9, 4);

    BOOST_CHECK(AStarPathFinder::findPath(matrix, obstacles, startingPoint, endPoint).empty() == false);
}
// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
