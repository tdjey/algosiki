#include <algorithm>
#include <array>
#include <cstring>
#include <iostream>
#include <numeric>
#include <queue>
#include <set>
#include <vector>

long long GetPar(long long u, std::vector<long long>& par) {
  if (par[u] != u) {
    par[u] = GetPar(par[u], par);
  }
  return par[u];
}

void Merge(long long u, long long v, std::vector<long long>& par) {
  u = GetPar(u, par);
  v = GetPar(v, par);
  par[u] = v;
}

void Solve() {
  using std::vector;
  long long n;
  long long m;
  std::cin >> n >> m;
  vector<std::array<long long, 3>> edges;
  long long cost;
  long long f;
  long long s;
  for (long long i = 0; i < m; ++i) {
    std::cin >> f >> s >> cost;
    edges.push_back({cost, f - 1, s - 1});
  }
  std::sort(edges.begin(), edges.end());
  vector<long long> par(n);
  std::iota(par.begin(), par.end(), 0);
  long long answer = 0;
  for (auto [edge_cost, u, v] : edges) {
    if (GetPar(u, par) == GetPar(v, par)) {
      continue;
    }
    answer += edge_cost;
    Merge(u, v, par);
  }
  std::cout << answer;
}

signed main() { Solve(); }
