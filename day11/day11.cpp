//credit to https://github.com/houseofmackee. I snooped on their solution while optimizing
//lesson learned is to look at what is being computed, and notice that I am doing a lot of unneccesary recomputations.

#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <map>

using namespace std;

int numDigits(long long number)
{
    return floor(log10(number) + 1);
}

map<long long, long long> stones;
map<long long, long long> delta;

long long count;

void blink(long long value, long long freq)
{
    if (value == 0)
    {
        delta[0] -= freq;
        delta[1] += freq;
        return;
    }
    long long nd = numDigits(value);
    if (nd % 2 == 0)
    {
        count += freq;
        delta[value] -= freq;
        long long power = pow(10, nd / 2);
        long long left = value / power;
        long long right = value - left * power;
        delta[left] += freq;
        delta[right] += freq;
    }
    else
    {
        delta[value] -= freq;
        delta[value * 2024] += freq;
    }
}

void processStones(int numBlinks)
{
    map<long long, long long>::iterator it = stones.begin();

    std::vector<long long> keys;
    while (it != stones.end())
    {
        keys.push_back(it->first);
        it++;
    }

    for (auto &key : keys)
    {
        if (stones[key] > 0)
        {
            blink(key, stones[key]);
        }
    }

    it = delta.begin();
    while (it != delta.end())
    {
        stones[it->first] += it->second;
        it++;
    }
    delta.clear();

    if (numBlinks > 1)
    {
        processStones(numBlinks - 1);
    }
    return;
}

int main(int argc, char *argv[])
{
    int n;
    if(argc != 2){
        cout << "Usage: ./day11 numBlinks" << endl;
        return 1;
    }

    n = atoi(argv[1]);

    if(n > 75){
        cout << "Higher than neccesary" << endl;
        return 1;
    }

    std::ifstream inputFile("../inputs/day11.txt");
    if (!inputFile)
    {
        std::cerr << "Error: Could not open the file." << std::endl;
        return 1;
    }

    long long number;
    while (inputFile >> number)
    {
        stones[number] ++;
        count++;
    }

    processStones(n);

    cout << count << endl;

    inputFile.close();

    return 0;
}