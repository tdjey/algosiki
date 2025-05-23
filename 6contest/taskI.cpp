#include <assert.h>

#include <algorithm>
#include <array>
#include <bitset>
#include <iostream>
#include <string>
#include <vector>

const int cN = 1002;
const int cK = 21;

int dp[cN][cN][cK];

void Solve() {
    std::string s1;
    std::string s2;
    int k;
    std::cin >> s1 >> s2 >> k;
    if (std::abs(static_cast<int>(s1.size()) - static_cast<int>(s2.size())) > k) {
        std::cout << -1;
        return;
    }
    const int cINF = 1e9 + 7;
    for (size_t i = 0; i <= s1.size(); ++i) {
        for (size_t j = 0; j <= s2.size(); ++j) {
            if (i != j) {
                dp[i][j][0] = cINF;
                continue;
            }
            if (i > 0) {
                dp[i][j][0] =
                    dp[i - 1][j - 1][0] + static_cast<int>(s1[i - 1] != s2[j - 1]);
            }
        }
    }
    for (int allowed_k = 1; allowed_k <= k; ++allowed_k) {
        for (size_t i = 0; i <= s1.size(); ++i) {
            for (size_t j = 0; j <= s2.size(); ++j) {
                if (i == 0 && j == 0) {
                    continue;
                }
                if (i == 0) {
                    dp[i][j][allowed_k] = 1 + dp[i][j - 1][allowed_k - 1];
                    continue;
                }
                if (j == 0) {
                    dp[i][j][allowed_k] = 1 + dp[i - 1][j][allowed_k - 1];
                    continue;
                }
                if (s1[i - 1] == s2[j - 1]) {
                    dp[i][j][allowed_k] = dp[i - 1][j - 1][allowed_k];
                } else {
                    dp[i][j][allowed_k] =
                        1 + std::min(dp[i - 1][j][allowed_k - 1],
                                     std::min(dp[i][j - 1][allowed_k - 1],
                                              dp[i - 1][j - 1][allowed_k]));
                }
            }
        }
    }

    int answer = cINF;
    for (int allowed_k = 0; allowed_k <= k; ++allowed_k) {
        answer =
            std::min(answer, std::max(0, dp[s1.size()][s2.size()][allowed_k] - k));
    }
    std::cout << answer;
}

signed main() { Solve(); }
