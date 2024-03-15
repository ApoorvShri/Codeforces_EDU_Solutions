// Problem - https://codeforces.com/edu/course/2/lesson/5/1/practice/contest/279634/problem/B

#include<bits/stdc++.h>
using namespace std;

/*
class SegTree {
public:
  vector<int> seg, lazy;

  SegTree(int n) {
    seg.resize(4 * n);
    lazy.resize(4 * n, INT_MIN);
  }

  void update(int ind, int low, int high, int l, int r, int val) {
    seg[ind] = max(seg[ind], lazy[ind]);

    if (low != high) {
      lazy[2 * ind + 1] = max(lazy[2 * ind + 1], lazy[ind]);
      lazy[2 * ind + 2] = max(lazy[2 * ind + 2], lazy[ind]);
    }

    lazy[ind] = INT_MIN;

    if (low > r || high < l) return;

    if (low >= l && high <= r) {
      seg[ind] = max(seg[ind], val);

      if (low != high) {
        lazy[2 * ind + 1] = max(lazy[2 * ind + 1], val);
        lazy[2 * ind + 2] = max(lazy[2 * ind + 2], val);
      }

      return;
    }

    int mid = low + (high - low) / 2;

    update(2 * ind + 1, low, mid, l, r, val);
    update(2 * ind + 2, mid + 1, high, l, r, val);

    seg[ind] = max(seg[2 * ind + 1], seg[2 * ind + 2]);
  }

  int query(int ind, int low, int high, int pos) {
    seg[ind] = max(seg[ind], lazy[ind]);

    if (low != high) {
      lazy[2 * ind + 1] = max(lazy[2 * ind + 1], lazy[ind]);
      lazy[2 * ind + 2] = max(lazy[2 * ind + 2], lazy[ind]);
    }

    lazy[ind] = INT_MIN;

    if (low == high) return seg[ind];

    int mid = low + (high - low) / 2;

    if (pos <= mid) return query(2 * ind + 1, low, mid, pos);
    return query(2 * ind + 2, mid + 1, high, pos);
  }
};
*/

class SegTree {
public:
  vector<int> seg;

  SegTree(int n) {
    seg.resize(4 * n);
  }

  void update(int ind, int low, int high, int l, int r, int val) {
    if (low > r || high < l) return;

    if (low >= l && high <= r) {
      seg[ind] = max(seg[ind], val);
      return;
    }

    int mid = low + (high - low) / 2;

    update(2 * ind + 1, low, mid, l, r, val);
    update(2 * ind + 2, mid + 1, high, l, r, val);
  }

  int query(int ind, int low, int high, int pos) {
    if (low == high) return seg[ind];

    int mid = low + (high - low) / 2;

    if (pos <= mid) return max(seg[ind], query(2 * ind + 1, low, mid, pos));
    return max(seg[ind], query(2 * ind + 2, mid + 1, high, pos));
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
      int pos;
      cin >> pos;

      cout << st.query(0, 0, n - 1, pos) << endl;
    }
  }
}