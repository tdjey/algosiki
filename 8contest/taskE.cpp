#include <algorithm>
#include <array>
#include <cstring>
#include <iostream>
#include <queue>
#include <set>
#include <vector>

void Solve() {
  using std::vector;
  long long n;
  std::cin >> n;
  long long cost;
  const long long cINF = 1e17;
  const long long cREALINF = 100000;
  vector<std::array<long long, 3>> edges;
  for (long long i = 0; i < n; ++i) {
    for (long long j = 0; j < n; ++j) {
      std::cin >> cost;
      if (cost != cREALINF) {
        edges.push_back({i, j, cost});
      }
    }
  }
  vector<long long> dist(n, cINF);
  vector<long long> par(n, -1);
  dist[0] = 0;
  for (long long i = 0; i < n - 1; ++i) {
    for (auto [u, v, c] : edges) {
      if (dist[u] != -cINF && dist[v] > dist[u] + c) {
        dist[v] = dist[u] + c;
        par[v] = u;
      }
    }
  }
  vector<long long> old_dist = dist;
  for (auto [v, u, c] : edges) {
    if (dist[v] != cINF && dist[u] > dist[v] + c) {
      dist[u] = dist[v] + c;
      par[u] = v;
    }
  }
  long long cur_v = -1;
  for (long long i = 0; i < n; ++i) {
    if (old_dist[i] != dist[i]) {
      cur_v = i;
    }
  }
  if (cur_v == -1) {
    std::cout << "NO\n";
    return;
  }
  std::cout << "YES\n";
  vector<long long> path;
  vector<bool> used(n, false);
  while (!used[cur_v]) {
    path.push_back(cur_v);
    used[cur_v] = true;
    cur_v = par[cur_v];
  }
  path.push_back(cur_v);
  std::reverse(path.begin(), path.end());
  long long idx = 1;
  while (path[idx] != path[0]) {
    ++idx;
  }
  path.erase(path.begin() + idx + 1, path.end());
  std::cout << path.size() << "\n";
  for (long long u : path) {
    std::cout << u + 1 << " ";
  }
}

signed main() { Solve(); }
