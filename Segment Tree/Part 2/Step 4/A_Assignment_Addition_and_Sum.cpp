// Problem - https://codeforces.com/edu/course/2/lesson/5/4/practice/contest/280801/problem/A

#include<bits/stdc++.h>
using namespace std;

using ll = long long;

class SegTree {
public:
  vector<ll> seg, assign, add;
  ll NO_OP;

  SegTree(int n) {
    NO_OP = LLONG_MIN;

    seg.resize(4 * n);
    assign.resize(4 * n, NO_OP);
    add.resize(4 * n), NO_OP;
  }

  ll op(ll left, ll right) {
    if (left == NO_OP) return right;
    return left + right;
  }

  ll merge(ll left, ll right) {
    return left + right;
  }

  void propagate(int ind, int low, int high) {
    if (assign[ind] != NO_OP) {
      seg[ind] = (high - low + 1) * assign[ind];

      if (low != high) {
        assign[2 * ind + 1] = assign[2 * ind + 2] = assign[ind];

        add[2 * ind + 1] = add[2 * ind + 2] = NO_OP;
      }

      assign[ind] = NO_OP;
    }

    if (add[ind] != NO_OP) {
      seg[ind] += (high - low + 1) * add[ind];

      if (low != high) {
        add[2 * ind + 1] = op(add[2 * ind + 1], add[ind]);
        add[2 * ind + 2] = op(add[2 * ind + 2], add[ind]);
      }

      add[ind] = NO_OP;
    }
  }

  void update(int ind, int low, int high, int l, int r, int val, int type) {
    propagate(ind, low, high);

    if (low > r || high < l) return;

    if (low >= l && high <= r) {
      if (type == 1) {
        assign[ind] = val;
        add[ind] = NO_OP;
      }

      else add[ind] = op(add[ind], val);

      propagate(ind, low, high);

      return;
    }

    int mid = low + (high - low) / 2;

    update(2 * ind + 1, low, mid, l, r, val, type);
    update(2 * ind + 2, mid + 1, high, l, r, val, type);

    seg[ind] = merge(seg[2 * ind + 1], seg[2 * ind + 2]);
  }

  ll query(int ind, int low, int high, int l, int r) {
    propagate(ind, low, high);

    if (low > r || high < l) return 0;

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

  while (q--) {
    int type;
    cin >> type;

    if (type != 3) {
      int l, r, val;
      cin >> l >> r >> val;

      st.update(0, 0, n - 1, l, r - 1, val, type);
    }

    else {
      int l, r;
      cin >> l >> r;

      cout << st.query(0, 0, n - 1, l, r - 1) << endl;
    }
  }
}