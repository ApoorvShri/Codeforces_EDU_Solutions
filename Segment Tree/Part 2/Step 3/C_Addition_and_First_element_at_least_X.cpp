// Problem - https://codeforces.com/edu/course/2/lesson/5/3/practice/contest/280799/problem/C

#include<bits/stdc++.h>
using namespace std;

using ll = long long;

class SegTree {
public:
  vector<ll> seg, lazy;

  SegTree(int n) {
    seg.resize(4 * n);
    lazy.resize(4 * n);
  }

  ll merge(ll left, ll right) {
    return max(left, right);
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
      lazy[ind] += val;
      propagate(ind, low, high);

      return;
    }

    int mid = low + (high - low) / 2;

    update(2 * ind + 1, low, mid, l, r, val);
    update(2 * ind + 2, mid + 1, high, l, r, val);

    seg[ind] = merge(seg[2 * ind + 1], seg[2 * ind + 2]);
  }

  int query(int ind, int low, int high, int x, int l) {
    propagate(ind, low, high);

    if (high < l || seg[ind] < x) return -1;

    if (low == high) return low;

    int mid = low + (high - low) / 2;

    int left = query(2 * ind + 1, low, mid, x, l);
    if (left != -1) return left;

    return query(2 * ind + 2, mid + 1, high, x, l);
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
      int x, l;
      cin >> x >> l;

      cout << st.query(0, 0, n - 1, x, l) << endl;
    }
  }
}