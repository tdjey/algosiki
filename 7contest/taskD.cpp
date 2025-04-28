#include <algorithm>
#include <cstring>
#include <iostream>
#include <set>
#include <vector>

using std::vector;

const int cN = 1e5 + 228;

vector<int> arr[cN];
vector<int> rev_arr[cN];
vector<int> top_arr;
bool used[cN];

void Topsort(int v) {
  used[v] = true;
  for (int u : arr[v]) {
    if (!used[u]) {
      Topsort(u);
    }
  }
  top_arr.push_back(v);
}

int cur = 0, color[cN];

void DfsColor(int v, int cur_color) {
  color[v] = cur_color;
  used[v] = true;
  for (int u : rev_arr[v]) {
    if (!used[u]) {
      DfsColor(u, cur_color);
    }
  }
}

int main() {
  int n;
  int m;
  std::cin >> n >> m;
  int f;
  int s;
  for (int i = 0; i < m; i++) {
    std::cin >> f >> s;
    f--, s--;
    arr[f].push_back(s);
    rev_arr[s].push_back(f);
  }
  for (int i = 0; i < n; i++) {
    if (!used[i]) {
      Topsort(i);
    }
  }

  reverse(top_arr.begin(), top_arr.end());
  memset(used, 0, sizeof used);

  for (int i = 0; i < n; i++) {
    if (!used[top_arr[i]]) {
      DfsColor(top_arr[i], cur++);
    }
  }
  
  std::cout << cur << "\n";
  for (int i = 0; i < n; ++i) {
    std::cout << color[i] + 1 << " ";
  }
}
