// Problem - https://codeforces.com/edu/course/2/lesson/5/2/practice/contest/279653/problem/C

#include<bits/stdc++.h>
using namespace std;

class SegTree {
public:
  vector<int> seg, lazy;

  int NEUTRAL;

  SegTree(int n) {
    seg.resize(4 * n);
    lazy.resize(4 * n);

    NEUTRAL = (1 << 30) - 1;
  }

  void operation(int &left, int right) {
    left |= right;
  }

  int merge(int left, int right) {
    return left & right;
  }

  void propagate(int ind, int low, int high, int val) {
    operation(seg[ind], val);

    if (low != high) {
      operation(lazy[2 * ind + 1], val);
      operation(lazy[2 * ind + 2], val);
    }

    lazy[ind] = 0;
  }

/*
  void build(int ind, int low, int high) {
    if (low == high) {
      seg[ind] = 0;
      return;
    }

    int mid = low + (high - low) / 2;

    build(2 * ind + 1, low, mid);
    build(2 * ind + 2, mid + 1, high);

    seg[ind] = merge(seg[2 * ind + 1], seg[2 * ind + 2]);
  }
*/

  void update(int ind, int low, int high, int l, int r, int val) {
    propagate(ind, low, high, lazy[ind]);

    if (low > r || high < l) return;

    if (low >= l && high <= r) {
      propagate(ind, low, high, val);
      return;
    }

    int mid = low + (high - low) / 2;

    update(2 * ind + 1, low, mid, l, r, val);
    update(2 * ind + 2, mid + 1, high, l, r, val);

    seg[ind] = merge(seg[2 * ind + 1], seg[2 * ind + 2]);
  }

  int query(int ind, int low, int high, int l, int r) {
    propagate(ind, low, high, lazy[ind]);

    if (low > r || high < l) return NEUTRAL;

    if (low >= l && high <= r) return seg[ind];

    int mid = low + (high - low) / 2;

    int left = query(2 * ind + 1, low, mid, l, r);
    int right = query(2 * ind + 2, mid + 1, high, l, r);

    return merge(left, right);
  }
};

int main() {
  int n, q;
  cin >> n >> q;

  SegTree st(n);
  // st.build(0, 0, n - 1);

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