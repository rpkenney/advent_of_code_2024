#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>
#include <map>


class Point {
public:
    int x;
    int y;

    Point(int _x, int _y) {
        x = _x;
        y = _y;
    }

    std::vector<Point> getAntinodes(const Point p2, int xMax, int yMax){
        std::vector<Point> antinodes;

        int deltaX = p2.x - x;
        int deltaY = p2.y - y;

        int i = 1;
        while(p2.x + deltaX * i < xMax && p2.x + deltaX * i >= 0 && p2.y + deltaY * i < yMax && p2.y + deltaY * i >= 0){
            Point antinode(p2.x + deltaX * i, p2.y + deltaY * i );
            antinodes.push_back(antinode);
            i++;
        }

        i = 1;
        while(x - deltaX * i < xMax && x - deltaX * i >= 0 && y - deltaY * i < yMax && y - deltaY * i >= 0){
            Point antinode(x - deltaX * i, y - deltaY * i );
            antinodes.push_back(antinode);
            i++;
        }
        return antinodes;
    }

    // Overload the << operator
    friend std::ostream& operator<<(std::ostream& os, const Point& obj) {
        os << "(" << obj.x << ", " << obj.y << ")"; // Access x and y through obj
        return os;
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
        content.emplace_back(line.begin(), line.end() - 1);
    }

    inputFile.close();

    std::map<char, std::vector<Point>> antennaMap;

    for(int row = 0; row < content.size(); row++){
        for(int col = 0; col < content[0].size(); col++){
            if(content[row][col] != '.' && content[row][col] != 0){
                Point p(row, col);
                antennaMap[content[row][col]].push_back(p);
            }
        }
    }

    for (const auto& kv : antennaMap) {

        for(int i = 0; i < kv.second.size(); i++){
            Point p1 = kv.second[i];
            for(int j = i + 1; j < kv.second.size(); j++){
                Point p2 = kv.second[j];
                std::vector<Point> antinodes = p1.getAntinodes(p2, content.size(), content[0].size());
                for( const auto& antinode : antinodes){
                    if(content[antinode.x][antinode.y] == '.'){
                        content[antinode.x][antinode.y] = '#';
                    }
                }

            }
        }
    }

    int count = 0;
    for(int row = 0; row < content.size(); row++){
        for(int col = 0; col < content[0].size(); col++){
            std::cout << content[row][col];
            if(content[row][col] != '.'){
                count++;
            }
        }
        std::cout << std::endl;
    }

    std::cout << count << std::endl;

    return 0;
}
