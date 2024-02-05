#include <vector>
#include <iostream>
#include <algorithm>

using std::vector;

int min = 1000000001;
int timer = 0;

struct Pair {
    int to_;
    int value_;
};

vector<vector<Pair>> graph;
vector<bool> used;
vector<int> tin;
vector<int> fup;


void DFS(int from, int patron) {
    used[from] = true;
    tin[from] = fup[from] = timer++;
    for (size_t index = 1; index < graph[from].size(); ++index) {
        int to = graph[from][index].to_;
        int val = graph[from][index].value_;
        if (to == patron) continue;
        if (used[to]) {
            fup[from] = std::min(fup[from], tin[to]);
        } else {
            DFS(to, from);
            fup[from] = std::min(fup[from], fup[to]);
            if (fup[to] > tin[from]) {
                if (val < min) {
                    min = val;
                }
            }
        }
    }
}

int main() {
    int n_cities, n_roads;
    std::cin >> n_cities >> n_roads;
    graph.resize(n_cities + 1, vector<Pair>(1, {0, 0}));
    for (int index = 0; index < n_roads; ++index) {
        int from, to, value;
        std::cin >> from >> to >> value;
        graph[from].push_back({to, value});
        graph[to].push_back({from, value});
    }
    used.resize(n_cities + 1, false);
    tin.resize(n_cities + 1);
    fup.resize(n_cities + 1);
    int begin = 1;
    DFS(begin, -1);
    if (min == 1000000001) {
        std::cout << -1;
    } else {
        std::cout << min;
    }
    return 0;
}
