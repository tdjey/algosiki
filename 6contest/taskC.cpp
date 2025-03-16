#include <assert.h>

#include <algorithm>
#include <iostream>
#include <vector>

const int cN = 1e5 + 228;
const int cLOG = 50;
const int cINF = 1e9;

int dp[cN][cLOG];

void Solve() {
    int n;
    int k;
    std::cin >> n >> k;
    if (k > cLOG) {
        int ans = 0;
        while (n > (1 << ans)) {
            ++ans;
        }
        std::cout << ans;
        return;
    }
    for (int i = 1; i <= n; ++i) {
        dp[i][0] = cINF;
        dp[i][1] = i - 1;
    }
    dp[1][0] = 0;
    dp[2][2] = 1;
    dp[2][3] = 1;
    dp[3][2] = 2;
    dp[3][3] = 2;

    for (int i = 4; i < cLOG; ++i) {
        dp[2][i] = dp[2][2];
        dp[3][i] = dp[3][3];
    }

    for (int j = 2; j <= k; ++j) {
        for (int i = 4; i <= n; ++i) {
            int l = 0;
            int r = i - 1;
            while (r - l > 1) {
                int mid = (l + r) >> 1;
                if (dp[mid + 1][j - 1] <= dp[i - 1 - mid][j]) {
                    l = mid;
                } else {
                    r = mid;
                }
            }
            dp[i][j] =
                1 + std::min(std::max(dp[l + 1][j - 1], dp[i - 1 - l][j]),
                             std::max(dp[l + 2][j - 1], dp[i - 1 - (l + 1)][j]));
        }
    }
    if (dp[n][k] == cINF) {
        std::cout << -1;
    } else {
        std::cout << dp[n][k];
    }
}

signed main() { Solve(); }
