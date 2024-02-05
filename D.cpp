#include <vector>
#include <iostream>
#include <algorithm>

using std::vector;

int64_t mod = 123456789;
vector<vector<int64_t>> matrix;

int64_t Dynamics(const vector<int> &keys, size_t from, size_t to) {
    if (matrix[from][to] == 0) {
        for (size_t index = from; index < to; ++index) {
            if (index == from || keys[index] != keys[index - 1]) {
                matrix[from][to] += (Dynamics(keys, from, index)
                        * Dynamics(keys, index + 1, to)) % mod;
                matrix[from][to] = matrix[from][to] % mod;
            }
        }
    }
    return matrix[from][to];
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    size_t number;
    std::cin >> number;

    vector<int> keys;
    keys.resize(number);
    for (auto &key : keys) {
        std::cin >> key;
    }

    std::sort(keys.begin(), keys.end());

    matrix.resize(number + 1, vector<int64_t>(number + 1, 0));
    for (size_t index = 0; index <= number; ++index) {
        matrix[index][index] = 1;
    }
    for (size_t index = 0; index < number; ++index) {
        matrix[index][index + 1] = 1;
    }

    int64_t result = Dynamics(keys, 0, number);
    std::cout << result;
    return 0;
}
