#include <iostream>
#include <vector>
#include <string>
#include <cassert>
#include <algorithm>

using std::cin;
using std::string;
using std::vector;
using std::cout;
using std::max_element;

class StackWithMax {
    vector<int> stack;

public:

    void Push(int value) {
        stack.push_back(value);
    }

    int Pop() {
        assert(stack.size());
        int last = stack.back();
        stack.pop_back();
        return last;
    }

    int Max() const {
        assert(stack.size());
        return *max_element(stack.begin(), stack.end());
    }
};

int main() {
    int num_queries = 0;
    cin >> num_queries;

    string query;
    string value;

    StackWithMax stack;

    int max = 0;

    for (int i = 0; i < num_queries; ++i) {
        cin >> query;
        if (query == "push") {
            cin >> value;
            if (std::stoi(value) > max)
                max = std::stoi(value);
            stack.Push(std::stoi(value));
        }
        else if (query == "pop") {
            int v = stack.Pop();
            if (v == max)
                max = stack.Max();
        }
        else if (query == "max") {
            cout << max << "\n";
        }
        else {
            assert(0);
        }
    }
    return 0;
}