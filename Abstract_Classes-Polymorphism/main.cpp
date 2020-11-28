#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include <set>
#include <cassert>
using namespace std;

struct Node {
    Node* next;
    Node* prev;
    int value;
    int key;
    Node(Node* p, Node* n, int k, int val) :prev(p), next(n), key(k), value(val) {};
    Node(int k, int val) :prev(NULL), next(NULL), key(k), value(val) {};
};

class Cache {

protected:
    map<int, Node*> mp; //map the key to the node in the linked list
    int cp;  //capacity
    Node* tail; // double linked list tail pointer
    Node* head; // double linked list head pointer
    virtual void set(int, int) = 0; //set function
    virtual int get(int) = 0; //get function

};

// Code above this line is locked in HackerRank online editor

// Challenge details: https://www.hackerrank.com/challenges/abstract-classes-polymorphism/problem
// This challenge is somewhat contrived since a cache miss doesn't retrieve fresh data.
// Cleanup with virtual dstor, but no copy or move cstors/assignment operators defined since not needed for this challenge.

class LRUCache : public Cache {
public:
    LRUCache(const int c);
    virtual ~LRUCache();
    void set(int key, int value) override;
    int get(int key) override;
    void updateLRU_byKey(const int key);
    void updateLRU_byTail(const int key, const int value);
};

LRUCache::LRUCache(const int c)
{
    cp = c;
}

LRUCache::~LRUCache()
{
    Node* current = head;
    while (current != nullptr)
    {
        Node* tmpNode = current->next;
        delete current;
        current = tmpNode;
    }
}

void LRUCache::set(int key, int value)
{
    const auto mpSize = static_cast<int>(mp.size());
    if (mpSize >= cp)
    {
        const auto keyToErase = tail->key;
        mp.erase(keyToErase);

        if (head == tail)
        {
            head->key = key;
            head->value = value;
        }
        else
        {
            if (mp.count(key) == 0)
            {
                updateLRU_byTail(key, value);
            }
            else
            {
                updateLRU_byKey(key);
                head->value = value;
            }
        }
        mp[key] = head;
    }
    else
    {
        Node* newNode = new Node(nullptr, head, key, value);
        if (head == nullptr)
        {
            head = newNode;
            tail = newNode;
        }
        else
        {
            head->prev = newNode;
            head = newNode;
        }
        mp[key] = head;
    }
}

int LRUCache::get(int key)
{
    if (mp.count(key) == 0)
    {
        set(key, -1);
        return -1;
    }
    updateLRU_byKey(key);
    return mp[key]->value;
}

void LRUCache::updateLRU_byKey(const int key)
{
    Node* currentNode = mp[key];
    if (currentNode == head) { return; }
    if (currentNode == tail)
    {
        updateLRU_byTail(key, tail->value);
        return;
    }
    Node* prevNode = currentNode->prev;
    Node* nextNode = currentNode->next;
    prevNode->next = nextNode;
    nextNode->prev = prevNode;
    head->prev = currentNode;
    currentNode->next = head;
    head = currentNode;
}

void LRUCache::updateLRU_byTail(const int key, const int value)
{
    Node* newTail = tail->prev;
    newTail->next = nullptr;
    Node* newHead = tail;
    tail = newTail;
    head->prev = newHead;
    newHead->next = head;
    head = newHead;
    head->key = key;
    head->value = value;
}

// Code below this line is locked in HackerRank online editor
int main() {
    int n, capacity, i;
    cin >> n >> capacity;
    LRUCache l(capacity);
    for (i = 0; i < n; i++) {
        string command;
        cin >> command;
        if (command == "get") {
            int key;
            cin >> key;
            cout << l.get(key) << endl;
        }
        else if (command == "set") {
            int key, value;
            cin >> key >> value;
            l.set(key, value);
        }
    }
    return 0;
}
