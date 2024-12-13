#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>
#include <map>


class Point {
private:
    int x, y;

public:
    Point(float x = 0.0, float y = 0.0) : x(x), y(y) {}

    int getX() const { return x; }
    int getY() const { return y; }

    float distanceTo(const Point& other) const {
        return std::sqrt(std::pow(other.x - x, 2) + std::pow(other.y - y, 2));
    }

    void print() const {
        std::cout << "(" << x << ", " << y << ")";
    }
};

int main() {
    std::string filename = "../inputs/day8.txt";
    std::ifstream inputFile(filename);

    if (!inputFile.is_open()) {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        return 1;
    }

    std::string line;
    std::vector<std::vector<char>> content;
    while (std::getline(inputFile, line)) {
        std::cout << line;
        content.emplace_back(line.begin(), line.end());
    }

    inputFile.close();

    std::map<char, std::vector<Point>> antenna;

    for(int row = 0; row < content.size(); row++){
        for(int col = 0; col < content[0].size(); col++){
            if(content[row][col] != '.'){
                Point p(row, col);
                antenna[content[row][col]].push_back(p);
            }
        }
    }
    for (auto it = antenna.begin(); it != antenna.end(); ++it) {
        std::cout << it->first << ": ";

        for(auto it2 = it->second.begin(); it2 != it->second.end(); ++it2){
            it2->print();
            std::cout << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}
