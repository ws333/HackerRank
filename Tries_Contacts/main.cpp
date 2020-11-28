#include <iostream>
#include <vector>
#include <map>
#include <limits>

using std::cout;
using std::cin;
using std::string;
using std::vector;

// Challenge details: https://www.hackerrank.com/challenges/ctci-contacts/problem

class TrieNode
{
    std::map<char, TrieNode*> charMap;
    int count{};
public:
    void add(TrieNode* node, const string &s) {
        for (const auto& c : s)
        {
            if (!node->charMap.count(c)) { node->charMap[c] = new TrieNode; }
            node = node->charMap[c];
            ++node->count;
        }
    }
    int find(TrieNode* node, const string &s) {
        for (size_t i{0}; i < s.size(); ++i)
        {
            if (node->charMap.count(s.at(i))) { node = node->charMap[s.at(i)]; }
            else { return 0; }
        }
        return node->count;
    }
};

vector<int> contacts(const vector<vector<string>> &queries)
{
    TrieNode trie;
    TrieNode trie2;
    vector<int> result;

    for (const auto& vec : queries) {
        if (vec.at(0) == "add")
        {
            trie.add(&trie, vec.at(1));
        }
        else if (vec.at(0) == "find")
        {
            auto count = trie.find(&trie, vec.at(1));
            result.push_back(count);
        }
    }

    return result;
}

// Modified from challenge template to display to terminal instead of writing to file
int main()
{
    int queries_rows;
    cin >> queries_rows;
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    vector<vector<string>> queries(queries_rows);
    for (int queries_row_itr = 0; queries_row_itr < queries_rows; queries_row_itr++) {
        queries[queries_row_itr].resize(2);

        for (int queries_column_itr = 0; queries_column_itr < 2; queries_column_itr++) {
            cin >> queries[queries_row_itr][queries_column_itr];
        }

        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    vector<int> result = contacts(queries);

    for (size_t result_itr = 0; result_itr < result.size(); result_itr++) {
        cout << result[result_itr];

        if (result_itr != result.size() - 1) {
            cout << "\n";
        }
    }
    cout << "\n";

    return 0;
}
