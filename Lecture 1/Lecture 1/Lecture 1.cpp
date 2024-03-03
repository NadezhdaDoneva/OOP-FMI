// Lecture 1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
using namespace std;

//Namespace Points includes:
//1) struct Point
//2) void readPoint
//3) double getDistance
//4) printPoint
namespace Points {
	struct Point
	{
		int x;
		int y;
	};

	void readPoint(Point& point) {
		cin >> point.x;
		cin >> point.y;
	}

	double getDistance(const Point& p1, const Point& p2) {
		int dx = p2.x - p1.x;
		int dy = p2.y - p1.y;
		
		return sqrt(dx * dx + dy * dy);
	}

	void printPoint(const Point& point)
	{
		std::cout << "( " << point.x << " " << point.y << ") ";
	}
}


//Namespace Figures includes:
//0) using namespace Points 
//1) struct Triangle
//2) void readTriangle
//3) double getArea with Heron
//4) void sortTriangles by area
//5) print triangle
namespace Figures {
	using namespace Points;
	
	struct Triangle {
		Point p1;
		Point p2;
		Point p3;
	};

	void readTriangle(Triangle& tr) {
		readPoint(tr.p1);
		readPoint(tr.p2);
		readPoint(tr.p3);
	}

	double getArea(const Triangle& tr) {
		double sideA = getDistance(tr.p1, tr.p2);
		double sideB = getDistance(tr.p1, tr.p3);
		double sideC = getDistance(tr.p2, tr.p3);

		double halfPer = (sideA + sideB + sideC) / 2;
		return sqrt(halfPer * (halfPer - sideA) * (halfPer - sideB) * (halfPer - sideC));
	}

	//1) create array for the areas dynamically
	//2) fill it using the getArea Method
	//3) do selection sort and swap in both arrays - the trianlge and the area ones
	//4) allocate memory!!!
	void sortTrianglesByArea(Triangle* trianglesArr, size_t N) {
		double* areas = new double[N];
		for (size_t i = 0; i < N; i++)
		{
			areas[i] = getArea(trianglesArr[i]);
		}

		for (size_t i = 0; i < N - 1; i++)
		{
			size_t minIdx = i;
			for (size_t j = i + 1; j < N; j++)
			{
				if (areas[j] < areas[minIdx]) {
					minIdx = j;
				}
			}
			if (minIdx != i)
			{
				swap(trianglesArr[minIdx], trianglesArr[i]);
				swap(areas[minIdx], areas[i]);
			}
		}
		delete[] areas;
	}

	void printTriangle(const Triangle& triangle) {
		printPoint(triangle.p1);
		printPoint(triangle.p2);
		printPoint(triangle.p3);
		std::cout << std::endl;
	}
}

//cin >> N
//1) dynamically create triangle array
//2) read triangles
//3) sort, print
//4) allocate memory!!!
int main()
{
	size_t N;
	cin >> N;

	Figures::Triangle* triangleArr = new Figures::Triangle[N];

	for (size_t i = 0; i < N; i++)
	{
		Figures::readTriangle(triangleArr[i]);
	}

	Figures::sortTrianglesByArea(triangleArr, N);

	for (size_t i = 0; i < N; i++)
	{
		Figures::printTriangle(triangleArr[i]);
	}

	delete[] triangleArr;
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
