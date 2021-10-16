#include <iostream>
#include <vector>

struct Point
{
	float x;
	float y;

	bool operator==(const Point& p2) const
	{
		return p2.x == this->x && p2.y == this->y;
	}
	bool operator!=(const Point& p2) const
	{
		return !(*this == p2);
	}
};

static bool lines_intersect(Point a, Point b, Point c, Point d)
{
	if (a == c && b == d)
		return true;

	float denominator = ((b.x - a.x) * (d.y - c.y)) - ((b.y - a.y) * (d.x - c.x));
	float numerator1 = ((a.y - c.y) * (d.x - c.x)) - ((a.x - c.x) * (d.y - c.y));
	float numerator2 = ((a.y - c.y) * (b.x - a.x)) - ((a.x - c.x) * (b.y - a.y));

	// Detect coincident lines (has a problem, read below)
	if (denominator == 0) return numerator1 == 0 && numerator2 == 0;

	float r = numerator1 / denominator;
	float s = numerator2 / denominator;

	return (r >= 0 && r <= 1) && (s >= 0 && s <= 1);
}

static bool polygon_self_intersect(const std::vector<Point>& points)
{
	int j = 2, i = 0;
	while (j != 0)
	{
		int ii = i + 1;
		for (size_t x = 0; x < points.size() - 3; x++)
		{
			int jj = (j + 1) % points.size();

			if (lines_intersect(points[i], points[ii], points[j], points[jj]))
				return true;

			if(x != points.size() - 4)
				j = (j + 1) % points.size();
		}

		if(points.size() <= 4)
			j = (j + 1) % points.size();

		i++;
	}

	return false;
}


static bool polygon_contains_identical_corners(const std::vector<Point>& points)
{
	for (size_t i = 0; i < points.size(); i++)
	{
		for (size_t j = i + 1; j < points.size(); j++)
		{
			if (points[i] == points[j])
				return true;
		}
	}
	return false;
}

int main()
{
	int n;
	std::vector<Point> points;
	
	// number of points input
	std::cout << "Number of verticies: \n>>";
	std::cin >> n;

	// check if polygon is correctly defined #1
	if (n < 3)
	{
		std::cout << "ERROR: Polygon has to have more than 2 verticies!\n";
		return 0;
	}

	// points input
	for (size_t i = 0; i < n; i++)
	{
		Point point;

		std::cout << "Vertex[" << i + 1 << "]: \n>>";
		std::cin >> point.x;
		std::cin >> point.y;

		points.push_back(point);
	}

	// check if polygon is correctly defined #2
	if (polygon_contains_identical_corners(points))
	{
		std::cout << "ERROR: Polygon has identical corners!\n";
		return 0;
	}

	if (polygon_self_intersect(points))
	{
		std::cout << "ERROR: Polygon edges can't intersect with each other!\n";
		return 0;
	}

	// count field of the polygon
	float field = 0;
	for (size_t i = 0; i < points.size(); i++)
	{
		int j = (i + 1) % points.size();
		field += (points[i].x * points[j].y - points[i].y * points[j].x);
	}

	field /= 2;
	field = std::abs(field);

	// output
	std::cout << "\nField of the polygon: " << field << std::endl;

	return 0;
}