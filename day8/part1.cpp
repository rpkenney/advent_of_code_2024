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

    std::vector<Point> getAntinodes(const Point p2){
        std::vector<Point> antinodes;

        int deltaX = p2.x - x;
        int deltaY = p2.y - y;

        Point antinode1(p2.x + deltaX, p2.y + deltaY);
        antinodes.push_back(antinode1);

        Point antinode2(x - deltaX, y - deltaY);
        antinodes.push_back(antinode2);
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
                std::vector<Point> antinodes = p1.getAntinodes(p2);
                for( const auto& antinode : antinodes){
                    if(antinode.x < content.size() && antinode.y < content[0].size()){
                        content[antinode.x][antinode.y] = '#';
                    }
                }

            }
        }
    }

    int count = 0;
    for(int row = 0; row < content.size(); row++){
        for(int col = 0; col < content[0].size(); col++){
            if(content[row][col] == '#'){
                count++;
            }
        }
    }

    std::cout << count << std::endl;

    return 0;
}
