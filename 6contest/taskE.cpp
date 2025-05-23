#include <assert.h>

#include <algorithm>
#include <bitset>
#include <iostream>
#include <string>
#include <vector>

void Solve() {
    int n;
    int m;
    std::cin >> n >> m;
    std::vector<int> cost(n);
    std::vector<int> weight(n);
    for (int& w : weight) {
        std::cin >> w;
    }
    for (int& c : cost) {
        std::cin >> c;
    }
    const int cINF = 1e9 + 228;
    std::vector<std::vector<int>> dp(n, std::vector<int>(m + 1, -cINF));
    if (weight[0] <= m) {
        dp[0][weight[0]] = cost[0];
    }
    dp[0][0] = 0;
    for (int i = 1; i < n; ++i) {
        dp[i] = dp[i - 1];
        for (int j = m; j >= weight[i]; --j) {
            if (dp[i - 1][j - weight[i]] + cost[i] > dp[i][j]) {
                dp[i][j] = dp[i - 1][j - weight[i]] + cost[i];
            }
        }
    }

    int ans = 0;
    int ans_idx = 0;
    for (int i = 0; i <= m; ++i) {
        if (dp[n - 1][i] > ans) {
            ans = dp[n - 1][i];
            ans_idx = i;
        }
    }
    for (int i = n - 1; i >= 1; --i) {
        if (dp[i][ans_idx] != dp[i - 1][ans_idx]) {
            std::cout << i + 1 << "\n";
            ans_idx -= weight[i];
        }
    }
    if (ans_idx != 0) {
        std::cout << 1;
    }
}

signed main() { Solve(); }
