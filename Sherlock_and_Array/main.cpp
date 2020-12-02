#include <iostream>
#include <vector>
#include <string>

using std::cout;
using std::cin;
using std::string;
using std::vector;

string ltrim(const string&);
string rtrim(const string&);
vector<string> split(const string&);

class ContainsBalancedSumCheck {
    const vector<int>& arr;
    long total{};

    void generateTotal() {
        for (int i{}; i < arr.size(); ++i) {
            total += arr.at(i);
        }
    }

public:
    ContainsBalancedSumCheck(const vector<int>& arr)
        : arr{arr} {};

    bool checkContainsBalancedSum() {
        if (arr.size() < 2) { return true; }
        long leftSum {0};
        generateTotal();
        for (int i {0}; i < arr.size() - 1; ++i) {
            if ((leftSum) == (total - leftSum - arr.at(i))) {
                return true;
            }
            leftSum += arr.at(i);
        }
        return false;
    }
};

// Complete the balancedSums function below.
string balancedSums(vector<int> arr) {
    ContainsBalancedSumCheck testArray(arr);
    return testArray.checkContainsBalancedSum() ? "YES" : "NO";
}

// Code below this line is from challenge template, though modified to ouput to terminal
int main()
{
    string T_temp;
    std::getline(cin, T_temp);

    int T = std::stoi(ltrim(rtrim(T_temp)));

    for (int T_itr = 0; T_itr < T; T_itr++) {
        string n_temp;
        getline(cin, n_temp);

        int n = stoi(ltrim(rtrim(n_temp)));

        string arr_temp_temp;
        getline(cin, arr_temp_temp);

        vector<string> arr_temp = split(rtrim(arr_temp_temp));

        vector<int> arr(n);

        for (int i = 0; i < n; i++) {
            int arr_item = stoi(arr_temp[i]);

            arr[i] = arr_item;
        }

        string result = balancedSums(arr);

        cout << result << "\n";
    }

    return 0;
}

string ltrim(const string& str) {
    string s(str);

    s.erase(
        s.begin(),
        find_if(s.begin(), s.end(), [](int c) { return !std::isspace(c); })
    );

    return s;
}

string rtrim(const string& str) {
    string s(str);

    s.erase(
        find_if(s.rbegin(), s.rend(), [](int c) { return !std::isspace(c); }).base(),
        s.end()
    );

    return s;
}

vector<string> split(const string& str) {
    vector<string> tokens;

    string::size_type start = 0;
    string::size_type end = 0;

    while ((end = str.find(" ", start)) != string::npos) {
        tokens.push_back(str.substr(start, end - start));

        start = end + 1;
    }

    tokens.push_back(str.substr(start));

    return tokens;
}
