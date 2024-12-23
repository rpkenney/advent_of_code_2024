#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>

using namespace std;

class Point
{
public:
    int row;
    int col;

    Point(int _row, int _col, int _direction)
    {
        row = _row;
        col = _col;
    }

    bool operator<(const Point &other) const
    {
        return (row < other.row) || (row == other.row && col < other.col);
    }
};

class Plot
{
public:
    int area;
    int perimeter;

    Plot()
    {
        area = 0;
        perimeter = 0;
    }
};

void handlePlotPoint(Point point, Plot *plot, map<Point, bool> *exploredLand, std::vector<std::vector<char>> *content)
{
    (*exploredLand)[point] = true;
    plot->area++;

    char value = (*content)[point.row][point.col];

    Point right(point.row, point.col + 1, 0);
    if (point.col == (*content)[0].size() - 1 || (*content)[point.row][point.col + 1] != value)
    {
        plot->perimeter++;
    }
    else if (!(*exploredLand)[right])
    {
        handlePlotPoint(right, plot, exploredLand, content);
    }

    Point down(point.row + 1, point.col, 1);
    if (point.row == (*content).size() - 1 || (*content)[point.row + 1][point.col] != value)
    {
        plot->perimeter++;
    }
    else if (!(*exploredLand)[down])
    {
        handlePlotPoint(down, plot, exploredLand, content);
    }

    Point left(point.row, point.col - 1, 2);
    if (point.col == 0 || (*content)[point.row][point.col - 1] != value)
    {
        plot->perimeter++;
    }
    else if (!(*exploredLand)[left])
    {
        handlePlotPoint(left, plot, exploredLand, content);
    }

    Point up(point.row - 1, point.col, 3);
    if (point.row == 0 || (*content)[point.row - 1][point.col] != value)
    {
        plot->perimeter++;
    }
    else if (!(*exploredLand)[up])
    {
        handlePlotPoint(up, plot, exploredLand, content);
    }
}

Plot *findPlot(Point point, map<Point, bool> *exploredLand, std::vector<std::vector<char>> *content)
{
    Plot *plot = new Plot();

    handlePlotPoint(point, plot, exploredLand, content);
    return plot;
}

int main()
{
    std::string filename = "../inputs/day12.txt";
    std::ifstream inputFile(filename);

    if (!inputFile.is_open())
    {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        return 1;
    }

    std::vector<std::vector<char>> content;
    std::string line;
    while (std::getline(inputFile, line))
    {
        content.emplace_back(line.begin(), line.end() - 1);
    }

    long long result = 0;
    map<Point, bool> exploredLand;

    for (int row = 0; row < content.size(); row++)
    {
        for (int col = 0; col < content[0].size(); col++)
        {
            Point point(row, col, -1);
            if (exploredLand[point])
            {
                continue;
            }

            Plot *plot = findPlot(point, &exploredLand, &content);
            result += plot->area * plot->perimeter;
            delete plot;
        }
    }

    cout << result << endl;

    inputFile.close();

    return 0;
}