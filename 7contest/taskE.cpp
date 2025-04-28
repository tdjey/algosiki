#include <assert.h>

#include <algorithm>
#include <array>
#include <bitset>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

using std::vector;

struct Node {
  int depth = 0;
  int up;
  bool used = false;
};

void Dfs(int v, int par_edge, vector<Node>& nodes,
         vector<vector<std::pair<int, int>>>& graph, vector<int>& answer) {
  nodes[v].used = true;
  nodes[v].up = nodes[v].depth;
  for (auto [u, idx] : graph[v]) {
    if (nodes[u].used) {
      if (idx != par_edge) {
        nodes[v].up = std::min(nodes[v].up, nodes[u].depth);
      }
      continue;
    }
    nodes[u].depth = nodes[v].depth + 1;
    Dfs(u, idx, nodes, graph, answer);
    nodes[v].up = std::min(nodes[v].up, nodes[u].up);
    if (nodes[u].up > nodes[v].depth) {
      answer.push_back(idx);
    }
  }
}

signed main() {
  int n;
  int m;
  std::cin >> n >> m;
  int f;
  int s;
  vector<vector<std::pair<int, int>>> graph(n);
  for (int i = 0; i < m; ++i) {
    std::cin >> f >> s;
    --f;
    --s;
    graph[f].emplace_back(s, i);
    graph[s].emplace_back(f, i);
  }
  vector<Node> nodes(n);
  vector<int> answer;
  for (int i = 0; i < n; ++i) {
    if (!nodes[i].used) {
      Dfs(i, -1, nodes, graph, answer);
    }
  }
  std::sort(answer.begin(), answer.end());

  std::cout << answer.size() << "\n";
  for (int u : answer) {
    std::cout << u + 1 << " ";
  }
}
