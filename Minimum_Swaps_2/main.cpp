#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using std::cout;
using std::cin;
using std::vector;
using std::string;

vector<string> split_string(string);

// Challenge details: https://www.hackerrank.com/challenges/minimum-swaps-2/problem

// Challenge: complete the minimumSwaps function below.
int minimumSwaps(vector<int> arr) {
    int swaps{};
    const auto size{ arr.size() };
    for (auto i{0}; i < size - 1; ++i) {
        if (arr.at(i) != i + 1) {
            auto temp = arr.at(i);
            auto it = find(arr.begin() + i, arr.end(), i + 1);
            arr.at(i) = *it;
            *it = temp;
            ++swaps;
        }
    }
    return swaps;
}

// Code below is from challenge template, though modified to output to terminal 
int main()
{

    int n;
    cin >> n;
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    string arr_temp_temp;
    getline(cin, arr_temp_temp);

    vector<string> arr_temp = split_string(arr_temp_temp);

    vector<int> arr(n);

    for (int i = 0; i < n; i++) {
        int arr_item = stoi(arr_temp[i]);

        arr[i] = arr_item;
    }

    int res = minimumSwaps(arr);

    cout << res << "\n";

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
