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
    int direction;

    Point(int _row, int _col, int _direction)
    {
        row = _row;
        col = _col;
        direction = _direction;
    }

    bool operator<(const Point &other) const
    {
        return (row < other.row) || (row == other.row && col < other.col);
    }

    bool horizontalComparator(const Point &other)
    {
        return row < other.row || row == other.row && direction < other.direction || row == other.row && direction == other.direction && col < other.col;
    }

    bool verticalComparator(const Point &other)
    {
        return col < other.col || col == other.col && direction < other.direction || col == other.col && direction == other.direction && row < other.row;
    }
};

class Plot
{
public:
    int area;
    std::vector<Point> horizontalSides;
    std::vector<Point> verticalSides;

    Plot()
    {
        area = 0;
    }

    bool addToBorders(Point p, bool horizontal)
    {
        if (horizontal)
        {
            for (int i = 0; i < horizontalSides.size(); i++)
            {
                if (p.horizontalComparator(horizontalSides[i]))
                {
                    horizontalSides.insert(horizontalSides.begin() + i, p);
                    return true;
                }
            }
            horizontalSides.push_back(p);
        }
        else
        {
            for (int i = 0; i < verticalSides.size(); i++)
            {
                if (p.verticalComparator(verticalSides[i]))
                {
                    verticalSides.insert(verticalSides.begin() + i, p);
                    return true;
                }
            }
            verticalSides.push_back(p);
        }
        return true;
    }

    int getNumSides()
    {
        int sides = 2;
        int prevRow = horizontalSides[0].row;
        int prevCol = horizontalSides[0].col;
        int prevDir = horizontalSides[0].direction;
        for (auto border : horizontalSides)
        {
            if (prevRow != border.row || prevDir != border.direction || abs(prevCol - border.col) > 1)
            {
                sides++;
            }
            prevRow = border.row;
            prevCol = border.col;
            prevDir = border.direction;
        }

        prevRow = verticalSides[0].row;
        prevCol = verticalSides[0].col;
        prevDir = verticalSides[0].direction;
        for (auto border : verticalSides)
        {
            if (prevCol != border.col || prevDir != border.direction || abs(prevRow - border.row) > 1)
            {
                sides += 1;
            }
            prevRow = border.row;
            prevCol = border.col;
            prevDir = border.direction;
        }
        return sides;
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
        plot->addToBorders(right, false);
    }
    else if (!(*exploredLand)[right])
    {
        handlePlotPoint(right, plot, exploredLand, content);
    }

    Point down(point.row + 1, point.col, 1);
    if (point.row == (*content).size() - 1 || (*content)[point.row + 1][point.col] != value)
    {
        plot->addToBorders(down, true);
    }
    else if (!(*exploredLand)[down])
    {
        handlePlotPoint(down, plot, exploredLand, content);
    }

    Point left(point.row, point.col - 1, 2);
    if (point.col == 0 || (*content)[point.row][point.col - 1] != value)
    {
        plot->addToBorders(left, false);
    }
    else if (!(*exploredLand)[left])
    {
        handlePlotPoint(left, plot, exploredLand, content);
    }

    Point up(point.row - 1, point.col, 3);
    if (point.row == 0 || (*content)[point.row - 1][point.col] != value)
    {
        plot->addToBorders(up, true);
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
            result += plot->area * plot->getNumSides();
            delete plot;
        }
    }

    cout << result << endl;

    inputFile.close();

    return 0;
}