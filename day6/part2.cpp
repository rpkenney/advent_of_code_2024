#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>

int main()
{
    std::string filename = "../inputs/day6.txt";
    std::ifstream inputFile(filename);

    if (!inputFile.is_open())
    {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        return 1;
    }

    std::string line;
    std::vector<std::vector<char>> content;
    while (std::getline(inputFile, line))
    {
        content.emplace_back(line.begin(), line.end() - 1);
    }

    inputFile.close();

    int row = 0;
    int col = 0;

    // find the guy
    while (true)
    {
        if (content[row][col] == '^')
        {
            break;
        }
        if (col >= content[row].size())
        {
            row++;
            col = 0;
        }
        else
        {
            col++;
        }
    }
    int direction = 0;
    int count = 0;

        int startRow = row;
    int startCol = col;
    

    //play the little game
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

    row = startRow;
    col = startCol;
    direction = 0;

    for (int testRow = 0; testRow < content.size(); testRow++)
    {
        for (int testCol = 0; testCol < content[0].size(); testCol++)
        {
            if(content[testRow][testCol] != 'X'){
                continue;
            }

            content[testRow][testCol] = '#';

            int moveCount = 0;

            while (row < content.size() && col < content[0].size())
            {

                if(moveCount > content.size() * content[0].size()){
                    count++;
                    row = startRow;
                    col = startCol;
                    content[testRow][testCol] = '.';
                    direction = 0;
                    break;
                }
                moveCount++;
                if (content[row][col] == '#')
                {
                    if (direction == 0)
                    {
                        row++;
                        col++;
                    }
                    else if (direction == 1)
                    {
                        col--;
                        row++;
                    }
                    else if (direction == 2)
                    {
                        row--;
                        col--;
                    }
                    else if (direction == 3)
                    {
                        col++;
                        row--;
                    }
                    direction = (direction + 1) % 4;
                }
                else
                {
                    if (direction == 0)
                    {
                        row--;
                    }
                    else if (direction == 1)
                    {
                        col++;
                    }
                    else if (direction == 2)
                    {
                        row++;
                    }
                    else if (direction == 3)
                    {
                        col--;
                    }
                }
            }

            row = startRow;
            col = startCol;
            content[testRow][testCol] = '.';
            direction = 0;

        }
    }

    std::cout << count << std::endl;

    return 0;
}
