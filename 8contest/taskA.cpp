#include <algorithm>
#include <cstring>
#include <iostream>
#include <queue>
#include <set>
#include <vector>

void Dijkstra(int n, int start,
              std::vector<std::vector<std::pair<int, int>>>& graph,
              std::vector<int>& dist) {
  using std::vector;
  const int cINF = 2009000999;
  dist.assign(n, cINF);
  std::set<std::pair<int, int>> sorted;
  dist[start] = 0;
  sorted.emplace(0, start);
  while (!sorted.empty() && sorted.begin()->first != cINF) {
    int v = sorted.begin()->second;
    sorted.erase(sorted.begin());
    for (auto [u, edge_cost] : graph[v]) {
      if (dist[u] > dist[v] + edge_cost) {
        auto it = sorted.find({dist[u], u});
        if (it != sorted.end()) {
          sorted.erase(it);
        }
        dist[u] = dist[v] + edge_cost;
        sorted.emplace(dist[u], u);
      }
    }
  }
}

void Solve() {
  using std::vector;
  int n;
  int m;
  std::cin >> n >> m;
  vector<vector<std::pair<int, int>>> graph(n, vector<std::pair<int, int>>());
  int f;
  int s;
  int cost;
  for (int i = 0; i < m; ++i) {
    std::cin >> f >> s >> cost;
    graph[f].emplace_back(s, cost);
    graph[s].emplace_back(f, cost);
  }
  int start;
  std::cin >> start;
  vector<int> dist;
  Dijkstra(n, start, graph, dist);
  for (int u : dist) {
    std::cout << u << " ";
  }
}

int main() {
  int t;
  std::cin >> t;
  while (t-- != 0) {
    Solve();
  }
}
