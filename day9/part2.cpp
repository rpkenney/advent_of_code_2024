#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class Node{
public:
    int id;
    int size;
    Node* next;
    Node* prev;

    friend std::ostream& operator<<(std::ostream& os, const Node& obj) {
        os << "id: " << obj.id << " size: " << obj.size;
        return os;
    }
};

int main() {
    ifstream file("../inputs/day9.txt");
    string content((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
    file.close();

    Node* head = new Node();
    head->id = 0;
    head->size = content[0] - '0';
    head->prev = NULL;

    Node* curr = head;
    for(int i = 1; i < content.length(); i++){    
        Node *node = new Node();
        node->size = content[i] - '0';
        if(i % 2 == 0){
            node->id = i / 2;
        } else {
            node->id = -1;
        }
        
        node->prev = curr;
        curr->next = node;
        curr = node;
    }
    curr->next = NULL;

    Node* tail = curr;

    while(curr != NULL){

        Node* prev = curr->prev;
        if(curr->id == -1){
            curr = prev;
            continue;
        }

        Node* freeBlock = head;

        while(freeBlock != NULL && freeBlock != curr && (freeBlock->id != -1 || freeBlock->size < curr->size || freeBlock->size == 0)){
            freeBlock = freeBlock->next;
        }
        
        if(freeBlock == NULL || freeBlock == curr){
            curr = prev;
            continue;
        }

        if(freeBlock->size > 0){
            freeBlock->size -= curr->size;
            Node* temp = freeBlock->prev;

            freeBlock->prev = curr;
            temp->next = curr;

            Node* newFreeSpace = new Node();
            newFreeSpace->size = curr->size;
            newFreeSpace->id = -1;

            newFreeSpace->prev = curr->prev;
            curr->prev->next = newFreeSpace;

            newFreeSpace->next = curr->next;
            if(curr->next != NULL){
                curr->next->prev = newFreeSpace;
            }

            curr->next = freeBlock;
            curr->prev = temp;
        } else {
            freeBlock->id = curr->id;
            curr->id = -1;
        }
        curr = prev;
    }

    long long result  = 0;

    curr = head;

    int pos = 0;
    while(curr != NULL){
        for(int i = 0; i < curr->size; i++){
            if(curr->id != -1){
                result += pos * curr->id;
            }
            pos++;
        }
        curr = curr->next;
    }


    cout << result << endl;

    return 0;
}