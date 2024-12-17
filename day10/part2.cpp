#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <set>

using namespace std;

class Point
{
public:
    int row;
    int col;

    Point(int _row, int _col)
    {
        row = _row;
        col = _col;
    }
    friend std::ostream &operator<<(std::ostream &os, const Point &obj)
    {
        os << "(" << obj.row << ", " << obj.col << ")";
        return os;
    }

    bool operator<(const Point& other) const {
        return (row < other.row) || (row == other.row && col < other.col);    
    }
};

std::vector<std::vector<char>> content;

int numTrails(Point start)
{
    int elevation = content[start.row][start.col] - '0';
    if (elevation == 9)
    {
        return 1;
    }
    int sum = 0;
    if (start.row + 1 < content.size() && content[start.row + 1][start.col] - '0' == elevation + 1)
    {
        Point p(start.row + 1, start.col);
        sum += numTrails(p);
    }
    if (start.row - 1 >= 0 && content[start.row - 1][start.col] - '0' == elevation + 1)
    {
        Point p(start.row - 1, start.col);
        sum += numTrails(p);
    }
    if (start.col - 1 >= 0 && content[start.row][start.col - 1] - '0' == elevation + 1)
    {
        Point p(start.row, start.col - 1);
        sum += numTrails(p);
    }
    if (start.col + 1 < content[0].size() && content[start.row][start.col + 1] - '0' == elevation + 1)
    {
        Point p(start.row, start.col + 1);
        sum += numTrails(p);
    }
    return sum;
}

int main()
{
    std::string filename = "../inputs/day10.txt";
    std::ifstream inputFile(filename);

    if (!inputFile.is_open())
    {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        return 1;
    }

    std::string line;
    while (std::getline(inputFile, line))
    {
        content.emplace_back(line.begin(), line.end() - 1);
    }

    int result = 0;
    for (int i = 0; i < content.size(); i++)
    {
        for (int j = 0; j < content[0].size(); j++)
        {
            if (content[i][j] == '0')
            {
                Point p(i, j);
                int score = numTrails(p);
                result += score;
            }
        }
    }

    cout << result << endl;

    inputFile.close();

    return 0;
}
