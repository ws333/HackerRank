#include <iostream>
using namespace std;
enum class Fruit { apple, orange, pear };
enum class Color { red, green, orange };

template <typename T> struct Traits;
// Code above this line is locked in the HackerRank online editor

// Challenge details: https://www.hackerrank.com/challenges/cpp-class-template-specialization/problem
#include <map>

map<int, string> fruitNames{ {0, "apple"}, {1, "orange"}, {2, "pear"} };
map<int, string> colorNames{ {0, "red"}, {1, "green"}, {2, "orange"} };

template <> struct Traits<Color> {
    static string name(const int key) {
        return (colorNames.count(key) ? colorNames[key] : "unknown");
    }
};

template <> struct Traits<Fruit> {
    static string name(const int key) {
        return (fruitNames.count(key) ? fruitNames[key] : "unknown");
    }
};

// Code below this line is locked in the HackerRank online editor
int main()
{
    int t = 0; std::cin >> t;

    for (int i = 0; i != t; ++i) {
        int index1; std::cin >> index1;
        int index2; std::cin >> index2;
        cout << Traits<Color>::name(index1) << " ";
        cout << Traits<Fruit>::name(index2) << "\n";
    }
}
