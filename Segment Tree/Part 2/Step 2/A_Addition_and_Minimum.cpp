// Problem - https://codeforces.com/edu/course/2/lesson/5/2/practice/contest/279653/problem/A

#include<bits/stdc++.h>
using namespace std;

class SegTree {
public:
  vector<long long> seg, lazy;

  SegTree(int n) {
    seg.resize(4 * n);
    lazy.resize(4 * n);
  }

  void propagate(int ind, int low, int high) {
    if (lazy[ind]) {
      seg[ind] += lazy[ind];

      if (low != high) {
        lazy[2 * ind + 1] += lazy[ind];
        lazy[2 * ind + 2] += lazy[ind];
      }

      lazy[ind] = 0;
    }
  }

  void update(int ind, int low, int high, int l, int r, int val) {
    propagate(ind, low, high);

    if (low > r || high < l) return;

    if (low >= l && high <= r) {
      seg[ind] += val;

      if (low != high) {
        lazy[2 * ind + 1] += val;
        lazy[2 * ind + 2] += val;
      }

      return;
    }

    int mid = low + (high - low) / 2;

    update(2 * ind + 1, low, mid, l, r, val);
    update(2 * ind + 2, mid + 1, high, l, r, val);

    seg[ind] = min(seg[2 * ind + 1], seg[2 * ind + 2]);
  }

  long long query(int ind, int low, int high, int l, int r) {
    propagate(ind, low, high);

    if (low > r || high < l) return LLONG_MAX;

    if (low >= l && high <= r) return seg[ind];

    int mid = low + (high - low) / 2;

    long long left = query(2 * ind + 1, low, mid, l, r);
    long long right = query(2 * ind + 2, mid + 1, high, l, r);

    return min(left, right);
  }
};

int main() {
  int n, q;
  cin >> n >> q;

  SegTree st(n);

  while (q--) {
    int type;
    cin >> type;

    if (type == 1) {
      int l, r, val;
      cin >> l >> r >> val;

      st.update(0, 0, n - 1, l, r - 1, val);
    }

    else {
      int l, r;
      cin >> l >> r;

      cout << st.query(0, 0, n - 1, l, r - 1) << endl;
    }
  }
}