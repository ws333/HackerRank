#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using std::cout;
using std::cin;
using std::vector;
using std::string;

vector<string> split_string(string);

// Challenge details: https://www.hackerrank.com/challenges/insertion-sort/problem
// This solution use a BIT/Fenwick tree to count inversions to calculate the number of shifts an insertion sort performs when sorting an array
// Time complexity for BIT::update and BIT::sum is O(log m) where m = max input array value
// Time complexity for BIT::countInversions is O(n log m) where n = size of input array
// Space complexity for BIT::bitArray is O(m)
// For details on BIT and counting inversions see https://www.youtube.com/watch?v=kPaJfAUwViY&feature=youtu.be&t=1485

class BIT {
    uint32_t size;
    uint32_t* bitArray;
public:
    BIT(const uint32_t sizeArg) : size{sizeArg} {
        bitArray = new uint32_t[sizeArg] {0};
    }

    ~BIT() {
        delete bitArray;
    }

    void update(uint32_t idx, const uint32_t delta) const {
        while (idx < size) {
            bitArray[idx] += delta;
            idx += idx & -idx;
        }
    }

    uint32_t sum(uint32_t idx) const {
        uint32_t sum{};
        while (idx > 0) {
            sum += bitArray[idx];
            idx -= idx & -idx;
        }
        return sum;
    }

    uint32_t rangeSum(const uint32_t idxStart, const uint32_t idxEnd) const {
        return sum(idxEnd) - sum(idxStart);
    }

    uint64_t countInversions(vector<int> arr) const {
        uint64_t sumInversion{};
        for (uint32_t i{}; i < arr.size(); ++i) {
            sumInversion += rangeSum(arr[i], size - 1);
            update(arr[i], 1);
        }
        return sumInversion;
    }

};

// Complete the insertionSort function below.
uint64_t insertionSort(const vector<int> &arr) {
    int maxValue{};
    for (const auto& v : arr) {
        if (maxValue < v) { maxValue = v; }
    }
    const BIT bit(maxValue + 1);
    const auto inversionsCount = bit.countInversions(arr);
    cout << inversionsCount << "\n";
    return inversionsCount;
}

// Code below this line is from challenge template, though modified to output to terminal
int main()
{
    int t;
    cin >> t;
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    for (int t_itr = 0; t_itr < t; t_itr++) {
        int n;
        cin >> n;
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        string arr_temp_temp;
        std::getline(cin, arr_temp_temp);

        vector<string> arr_temp = split_string(arr_temp_temp);

        vector<int> arr(n);

        for (auto i = 0; i < n; i++) {
            auto arr_item = stoi(arr_temp[i]);

            arr[i] = arr_item;
        }

        uint64_t result = insertionSort(arr);

        cout << result << "\n";
    }

    return 0;
}

vector<string> split_string(string input_string) {
    string::iterator new_end = unique(input_string.begin(), input_string.end(), [](const char& x, const char& y) {
        return x == y and x == ' ';
        });

    input_string.erase(new_end, input_string.end());

    while (input_string[input_string.length() - 1] == ' ') {
        input_string.pop_back();
    }

    vector<string> splits;
    char delimiter = ' ';

    size_t i = 0;
    size_t pos = input_string.find(delimiter);

    while (pos != string::npos) {
        splits.push_back(input_string.substr(i, pos - i));

        i = pos + 1;
        pos = input_string.find(delimiter, i);
    }

    splits.push_back(input_string.substr(i, std::min(pos, input_string.length()) - i + 1));

    return splits;
}

