#include <iostream>
#include <fstream>
#include <vector>
#include <string>


int main() {
    std::string filename = "../inputs/day6.txt";
    std::ifstream inputFile(filename);

    if (!inputFile.is_open()) {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        return 1;
    }

    std::string line;
    std::vector<std::vector<char>> content;
    while (std::getline(inputFile, line)) {
        content.emplace_back(line.begin(), line.end());
    }

    inputFile.close();

    int row = 0;
    int col = 0;

    //find the guy
    while(true){
        if(content[row][col] == '^'){
           break;
        }
        if(col >= content[row].size()){
            row++;
            col = 0;
        } else {
            col++;
        }
    }

    //play the little game
    int direction = 0;
    while(row < content.size() && col < content[0].size()){
        if(content[row][col] == '#'){
            if(direction == 0){
                row++;
            } else if(direction == 1){
                col--;
            } else if(direction == 2){
                row--;
            } else if(direction == 3){
                col++;
            }
            direction = (direction + 1) % 4;
        } else {
            content[row][col] = 'X';
            if(direction == 0){
                row--;
            } else if(direction == 1){
                col++;
            } else if(direction == 2){
                row++;
            } else if(direction == 3){
                col--;
            }
        }
    }

    // //count where we have been
    int count = 0;
    for(row = 0; row < content.size(); row++){
        for(col = 0; col < content[0].size(); col++){
            if(content[row][col] == 'X'){
                count++;
            }
        }
    }

    std::cout << count << std::endl;

    return 0;
}
