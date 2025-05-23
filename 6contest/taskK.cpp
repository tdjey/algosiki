#include <assert.h>

#include <algorithm>
#include <array>
#include <bitset>
#include <iostream>
#include <queue>
#include <string>
#include <vector>

void Solve() {
  int n;
  std::cin >> n;
  std::vector<int> arr(n);
  for (int& u : arr) {
    std::cin >> u;
    u *= -1;
  }
  const int cINF = (1LL << 31) - 1;
  std::vector<std::pair<int, int>> dp(n + 1, {cINF, -1});
  std::vector<int> par(n + 1, -1);
  dp[0] = {-cINF, -1};
  int length = 0;

  for (int idx = 0; idx < n; ++idx) {
    int i = arr[idx];
    auto it = std::upper_bound(dp.begin(), dp.end(), std::make_pair(i, -1));
    if (it != dp.end()) {
      *it = {i, idx};
      length = std::max(length, static_cast<int>(it - dp.begin()));
      par[idx] = (--it)->second;
    }
  }
  std::vector<int> ans;
  length = dp[length].second;
  while (length != -1) {
    ans.push_back(length + 1);
    length = par[length];
  }
  std::cout << ans.size() << "\n";
  std::reverse(ans.begin(), ans.end());
  for (int i : ans) {
    std::cout << i << " ";
  }
}

signed main() { Solve(); }
