#include <vector>
#include <iostream>

using std::vector;

vector<vector<int> > graph;
vector<vector<int>> graph_t;
vector<bool> used;
vector<bool> usedd;
vector<int> order;
vector<int> component;
int big = 1000000000;
int n_people;

void DFS(int vertex) {
    used[vertex] = true;
    for (size_t index = 1; index < graph[vertex].size(); ++index) {
        int to = graph[vertex][index];
        if (used[to] == false) {
            DFS(to);
        }
    }
    order.push_back(vertex);
}

void MaxComponent(int vertex) {
    usedd[vertex] = true;
    component.push_back(vertex);
    for (size_t index = 1; index < graph_t[vertex].size(); ++index) {
        int to = graph_t[vertex][index];
        if (usedd[to] == false) {
            MaxComponent(to);
        }
    }
}

void Read() {
    int n_plays;
    std::cin >> n_people >> n_plays;

    graph.resize(n_people + 1, vector<int>(1, 0));
    graph_t.resize(n_people + 1, vector<int>(1, 0));
    order.reserve(n_people + 1);
    component.reserve(n_people + 1);
    used.resize(n_people + 1, false);

    for (int index = 0; index < n_plays; ++index) {
        int first, second, result;
        std::cin >> first >> second >> result;
        if (result == 1) {
            graph[first].push_back(second);
            graph_t[second].push_back(first);
        }
        if (result == 2) {
            graph[second].push_back(first);
            graph_t[first].push_back(second);
        }
    }
}

int FindComponent() {
    size_t mm = big;
    usedd.resize(n_people + 1, false);
    for (int index = 1; index <= n_people; ++index) {
        if (used[index] == false) {
            DFS(index);
            int vertex = order.back();
            MaxComponent(vertex);
            if (component.size() < mm) {
                mm = component.size();
            }
            component.clear();
            usedd.assign(n_people + 1, false);
        }
    }
    return static_cast<int>(mm);
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    Read();
    int best = FindComponent();
    std::cout << (n_people - best + 1);
    return 0;
}
