// Problem - https://codeforces.com/edu/course/2/lesson/5/3/practice/contest/280799/problem/B

#include<bits/stdc++.h>
using namespace std;

class SegTree {
public:
  vector<int> seg;
  vector<bool> lazy;

  SegTree(int n) {
    seg.resize(4 * n);
    lazy.resize(4 * n);
  }

  int merge(int left, int right) {
    return left + right;
  }

  void propagate(int ind, int low, int high) {
    if (lazy[ind]) {
      seg[ind] = high - low + 1 - seg[ind];

      if (low != high) {
        lazy[2 * ind + 1] = !lazy[2 * ind + 1];
        lazy[2 * ind + 2] = !lazy[2 * ind + 2];
      }

      lazy[ind] = 0;
    }
  }

  void update(int ind, int low, int high, int l, int r) {
    propagate(ind, low, high);

    if (low > r || high < l) return;

    if (low >= l && high <= r) {
      lazy[ind] = !lazy[ind];
      propagate(ind, low, high);

      return;
    }

    int mid = low + (high - low) / 2;

    update(2 * ind + 1, low, mid, l, r);
    update(2 * ind + 2, mid + 1, high, l, r);

    seg[ind] = merge(seg[2 * ind + 1], seg[2 * ind + 2]);
  }

  int query(int ind, int low, int high, int k) {
    if (low == high) return low;

    int mid = low + (high - low) / 2;

    propagate(2 * ind + 1, low, mid);
    propagate(2 * ind + 2, mid + 1, high);

    seg[ind] = merge(seg[2 * ind + 1], seg[2 * ind + 2]);

    if (k <= seg[2 * ind + 1]) return query(2 * ind + 1, low, mid, k);
    return query(2 * ind + 2, mid + 1, high, k - seg[2 * ind + 1]);
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
      int l, r;
      cin >> l >> r;

      st.update(0, 0, n - 1, l, r - 1);
    }

    else {
      int k;
      cin >> k;

      cout << st.query(0, 0, n - 1, k + 1) << endl;
    }
  }
}