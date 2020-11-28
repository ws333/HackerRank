#include <iostream>
#include <vector>
#include <deque>

using std::cout;

// Challenge details: https://www.hackerrank.com/challenges/deque-stl/problem
// Using vector as printKMax parameter instead of raw array because of dynamic input size.
// All other parameters and variable names are as in the original challenge template.

// The object que of type deque<int> is used to store the indexes of useful elements in every window
// i.e. the greatest number in current window is always in front,
// maintaining a non increasing order of values from front to back
// Time complexity of printKMax is O(n + k)
// Space complexity of printKMax is O(k)

void printKMax(std::vector<int> arr, int n, int k) {
    if (arr.empty()) { return; }

    std::deque<int> que;
    que.push_front(0);

    // First populate que with useful elements in first window and output max element
    for (auto i {1}; i < k; ++i)
    {
        while (!que.empty() && arr.at(que.back()) < arr.at(i)) {
            que.pop_back();
        }
        if (que.empty() || i != que.front()) { que.push_back(i); }
    }
    cout << arr.at(que.front()) << " ";

    // Iterate through rest of array and output max element in each window
    for (auto i {k}; i < n - 1; ++i)
    {
        if (que.front() <= i - k) { que.pop_front(); }
        while (!que.empty() && arr.at(que.back()) < arr.at(i)) {
            que.pop_back();
        }
        if (que.empty() || i != que.front()) { que.push_back(i); }

        cout << arr.at(que.front()) << " ";
    }

    // Output max element from last window
    if (k < n)
    {
        int max{};
        for (auto i {n - k}; i < n; ++i) {
            if (max < arr.at(i)) { max = arr.at(i); }
        }
        cout << max << " ";
    }
    cout << "\n";
}

// Modified to use scanf instead of cin (scanf_s not supported here) to optimize reading of input data.
int main() {
    int t;
    scanf("%d", &t);
    while (t > 0) {
        int n, k;
        scanf("%d%d", &n, &k);
        std::vector<int> arr(n);
        for (auto i = 0; i < n; i++)
            scanf("%d", &arr.at(i));
        printKMax(arr, n, k);
        --t;
    }
    return 0;
}
