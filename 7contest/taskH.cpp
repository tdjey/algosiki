#include <assert.h>

#include <algorithm>
#include <array>
#include <bitset>
#include <iostream>
#include <set>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using std::vector;

int Dfs(int v, int par, vector<bool>& used,
        vector<vector<std::pair<int, int>>>& graph,
        vector<std::pair<int, int>>& equations) {
  used[v] = true;
  for (auto [u, s] : graph[v]) {
    if (used[u]) {
      if (u != par && equations[v].second == equations[u].second) {
        return (s - equations[v].first - equations[u].first) / 2 *
               equations[v].second;
      }
      continue;
    }
    equations[u] = {s - equations[v].first, -equations[v].second};
    int resp = Dfs(u, v, used, graph, equations);
    if (resp != -1) {
      return resp;
    }
  }
  return -1;
}

void Calc(int v, vector<vector<std::pair<int, int>>>& graph,
          vector<int>& values) {
  for (auto [u, s] : graph[v]) {
    if (values[u] != 0) {
      continue;
    }
    values[u] = s - values[v];
    Calc(u, graph, values);
  }
}

signed main() {
  std::cin.tie(nullptr);
  std::ios_base::sync_with_stdio(false);
  int n;
  int m;
  std::cin >> n >> m;
  if (n == 1) {
    std::cout << 1;
    return 0;
  }
  if (n == 2) {
    std::cout << "1 2";
    return 0;
  }
  int f;
  int s;
  int sum = 0;
  vector<vector<std::pair<int, int>>> graph(n);
  for (int i = 0; i < m; ++i) {
    std::cin >> f >> s >> sum;
    --f;
    --s;
    graph[f].emplace_back(s, sum);
    graph[s].emplace_back(f, sum);
  }
  vector<std::pair<int, int>> equations(n, {0, 0});
  vector<bool> used(n, false);
  equations[0].second = 1;
  int answer = Dfs(0, -1, used, graph, equations);
  if (answer == -1) {
    vector<int> pos_eq;
    vector<int> neg_eq;
    for (auto [u, v] : equations) {
      if (v > 0) {
        pos_eq.push_back(u);
      } else {
        neg_eq.push_back(u);
      }
    }

    std::sort(pos_eq.begin(), pos_eq.end());
    std::sort(neg_eq.begin(), neg_eq.end());

    int answer1 = n - *pos_eq.rbegin();
    int answer2 = *neg_eq.rbegin() - n;

    vector<int> values(n);
    values[0] = answer1;

    Calc(0, graph, values);

    std::sort(values.begin(), values.end());
    values.erase(std::unique(values.begin(), values.end()), values.end());

    if (static_cast<int>(values.size()) != n || values[0] <= 0 ||
        values.back() > n) {
      answer = answer2;
    } else {
      answer = answer1;
    }
  }
  
  vector<int> values(n);
  values[0] = answer;
  Calc(0, graph, values);
  for (int u : values) {
    std::cout << u << " ";
  }
}
