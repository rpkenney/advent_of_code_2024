#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main() {
    ifstream file("../inputs/day9.txt");
    string content((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
    file.close();

    long long result  = 0;

    int pos = 0;
    int end = content.length() - 1;
    int id;
    for(int i = 0; i <= end; i++){    
        if(i % 2 == 0){
            id = i / 2;
            for(int j = 0; j < content[i] - '0'; j++){
                result += pos * id;
                pos++;
            }
        } else {
            for(int j = 0; j < content[i] - '0'; j++){
                while(content[end] - '0' <= 0){
                    end -=2;
                }
                if(end <= i){
                    break;
                }
                content[end]--;
                id = end / 2;
                result += pos * id;
                pos++;
            }
        }
    }
    cout << result << endl;

    return 0;
}