#include <assert.h>

#include <algorithm>
#include <array>
#include <bitset>
#include <iostream>
#include <queue>
#include <string>
#include <vector>

bool CheckRestriction(std::vector<std::vector<char>>& restrictions, int row,
                      int col, int bit_value) {
  char symbol = (bit_value == 1) ? '+' : '-';
  return (restrictions[row][col] == '.' || restrictions[row][col] == symbol);
}

void Solve() {
  int n;
  int m;
  std::cin >> n >> m;
  std::vector<std::vector<char>> restrictions(n, std::vector<char>(m));
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      std::cin >> restrictions[i][j];
    }
  }
  std::vector<int> prev(1 << n, 1);
  for (int mask = 0; mask < (1 << n); ++mask) {
    for (int bit = 0; bit < n; ++bit) {
      if (!CheckRestriction(restrictions, bit, 0, ((mask >> bit) & 1))) {
        prev[mask] = 0;
        break;
      }
    }
  }
  const int cMOD = 1e9 + 7;
  std::vector<int> new_prev;
  for (int i = 1; i < m; ++i) {
    new_prev.assign(1 << n, 0);
    for (int prev_mask = 0; prev_mask < (1 << n); ++prev_mask) {
      if (prev[prev_mask] == 0) {
        continue;
      }
      for (int init_bit = 0; init_bit <= 1; ++init_bit) {
        int cur_mask = init_bit;
        if (!CheckRestriction(restrictions, 0, i, init_bit)) {
          continue;
        }
        bool flag = true;
        int prev_bit_value = init_bit;
        for (int bit = 1; bit < n; ++bit) {
          int bit_value = ((prev_mask >> bit) & 1) +
                          ((prev_mask >> (bit - 1)) & 1) + prev_bit_value;
          if (bit_value == 3 || bit_value == 0 ||
              !CheckRestriction(restrictions, bit, i, bit_value & 1)) {
            flag = false;
            break;
          }
          bit_value = bit_value & 1;
          cur_mask |= bit_value << bit;
          prev_bit_value = bit_value;
        }
        if (!flag) {
          continue;
        }
        new_prev[cur_mask] = (prev[prev_mask] + new_prev[cur_mask]) % cMOD;
      }
    }
    prev.swap(new_prev);
  }
  int answer = 0;
  for (int mask = 0; mask < (1 << n); ++mask) {
    answer = (answer + prev[mask]) % cMOD;
  }
  std::cout << answer;
}

signed main() { Solve(); }
