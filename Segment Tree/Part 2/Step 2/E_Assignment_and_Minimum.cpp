// Problem - https://codeforces.com/edu/course/2/lesson/5/2/practice/contest/279653/problem/E

#include<bits/stdc++.h>
using namespace std;

using ll = long long;

class SegTree {
public:
  vector<ll> seg, lazy;

  int NEUTRAL;

  SegTree(int n) {
    seg.resize(4 * n);
    lazy.resize(4 * n);

    NEUTRAL = INT_MAX;
  }

  // void operation(ll &left,ll right){
  //   left+=right;
  // }

  ll merge(ll left, ll right) {
    return min(left, right);
  }

  void propagate(int ind, int low, int high) {
    if (lazy[ind]) {
      if (low != high) {
        seg[2 * ind + 1] = seg[2 * ind + 2] = seg[ind];
        lazy[2 * ind + 1] = lazy[2 * ind + 2] = 1;
      }

      lazy[ind] = 0;
    }
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
    propagate(ind, low, high);

    if (low > r || high < l) return;

    if (low >= l && high <= r) {
      seg[ind] = val;
      lazy[ind] = 1;
      return;
    }

    int mid = low + (high - low) / 2;

    update(2 * ind + 1, low, mid, l, r, val);
    update(2 * ind + 2, mid + 1, high, l, r, val);

    seg[ind] = merge(seg[2 * ind + 1], seg[2 * ind + 2]);
  }

  ll query(int ind, int low, int high, int l, int r) {
    propagate(ind, low, high);

    if (low > r || high < l) return NEUTRAL;

    if (low >= l && high <= r) return seg[ind];

    int mid = low + (high - low) / 2;

    ll left = query(2 * ind + 1, low, mid, l, r);
    ll right = query(2 * ind + 2, mid + 1, high, l, r);

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