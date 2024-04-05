#include "pch.h"
#include "CppUnitTest.h"
#include "mapping_r.h" // Include the C header

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace MappingTests
{
    TEST_CLASS(UnitTest1)
    {
    public:

        TEST_METHOD(TestPopulateMap)
        {
            // Test populateMap function
            Map map = populateMap();

            // Assert statements to verify the properties of the map
            Assert::AreEqual(MAP_ROWS, getNumRows(&map));
            Assert::AreEqual(MAP_COLS, getNumCols(&map));

            // Add more assertions based on the expected properties of the map
            Assert::AreEqual(0, map.squares[0][0]);
            Assert::AreEqual(1, map.squares[1][1]);
            Assert::AreEqual(2, map.squares[2][2]);
            Assert::AreEqual(3, map.squares[3][3]);
        }

        TEST_METHOD(TestAddRoute)
        {
            // Test addRoute function
            Map map = populateMap();
            Route route = getBlueRoute();

            // Add the route to the map
            Map mapWithRoute = addRoute(&map, &route);

            // Assert statements to verify the properties of the map with the added route
            Assert::AreEqual(2, mapWithRoute.squares[0][0]);
            Assert::AreEqual(2, mapWithRoute.squares[1][0]);
            Assert::AreEqual(2, mapWithRoute.squares[15][0]);
            Assert::AreEqual(2, mapWithRoute.squares[32][0]);
        }

        TEST_METHOD(TestShortestPath)
        {
            // Test shortestPath function
            Map map = populateMap();
            Point start = { 0, 0 };
            Point dest = { 5, 5 };

            // Calculate the shortest path from start to dest
            Route shortest = shortestPath(&map, start, dest);

            // Assert statements to verify properties of the shortest path
            Assert::AreEqual(5, shortest.numPoints);

            // Check specific points in the path to ensure correctness
            Assert::IsTrue(eqPt(start, shortest.points[0]));
            Assert::IsTrue(eqPt(dest, shortest.points[shortest.numPoints - 1]));
            Assert::IsTrue(eqPt(dest, shortest.points[shortest.numPoints + 1]));
            Assert::IsTrue(eqPt(dest, shortest.points[shortest.numPoints + 1000]));
        }

        TEST_METHOD(TestGetPossibleMoves)
        {
            // Test getPossibleMoves function
            Map map = populateMap();
            Point p1 = { 0, 0 };
            Point backpath = { 0, 1 };

            // Get possible moves from p1 while excluding backpath
            Route possibleMoves = getPossibleMoves(&map, p1, backpath);

            // Add assertions to check if the possible moves are correct based on expectations
            Assert::AreEqual(2, possibleMoves.numPoints);

            // Check specific points in the possible moves
            Assert::IsTrue(eqPt(Point{ 1, 0 }, possibleMoves.points[0]));
            Assert::IsTrue(eqPt(Point{ 0, 1 }, possibleMoves.points[1]));
            Assert::IsTrue(eqPt(Point{ 0, 0 }, possibleMoves.points[0]));
            Assert::IsTrue(eqPt(Point{ -1, -1 }, possibleMoves.points[-1]));
        }
    };
}
