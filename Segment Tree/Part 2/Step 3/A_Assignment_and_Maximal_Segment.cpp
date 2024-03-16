// Problem - https://codeforces.com/edu/course/2/lesson/5/3/practice/contest/280799/problem/A

#include<bits/stdc++.h>
using namespace std;

using ll = long long;

struct SegTreeNode {
  ll ans, sum, pref, suf;
};

class SegTree {
public:
  vector<SegTreeNode> seg;
  vector<ll> lazy;

  SegTreeNode empty;
  ll noOperation;

  SegTree(int n) {
    empty = { 0,0,0,0 };
    noOperation = LLONG_MAX;

    seg.resize(4 * n, empty);
    lazy.resize(4 * n, noOperation);
  }

  // void operation(SegTreeNode &left,ll right){
  //   left.ans = left.pref = left.suf = max((high - low + 1) * lazy[ind], 0ll);
  //   left.sum = (high - low + 1) * lazy[ind];
  // }

  SegTreeNode merge(SegTreeNode left, SegTreeNode right) {
    return {
      max({left.ans,right.ans,left.suf + right.pref}),
      left.sum + right.sum,
      max(left.pref,left.sum + right.pref),
      max(right.suf,right.sum + left.suf)
    };
  }

  void propagate(int ind, int low, int high) {
    if (lazy[ind] != noOperation) {
      seg[ind].ans = seg[ind].pref = seg[ind].suf = max((high - low + 1) * lazy[ind], 0ll);
      seg[ind].sum = (high - low + 1) * lazy[ind];

      if (low != high) {
        lazy[2 * ind + 1] = lazy[2 * ind + 2] = lazy[ind];
      }

      lazy[ind] = noOperation;
    }
  }

  // void build(int ind, int low, int high) {
  //   if (low == high) {
  //     seg[ind] = empty;
  //     return;
  //   }

  //   int mid = low + (high - low) / 2;

  //   build(2 * ind + 1, low, mid);
  //   build(2 * ind + 2, mid + 1, high);

  //   seg[ind] = merge(seg[2 * ind + 1], seg[2 * ind + 2]);
  // }

  void update(int ind, int low, int high, int l, int r, int val) {
    propagate(ind, low, high);

    if (low > r || high < l) return;

    if (low >= l && high <= r) {
      lazy[ind] = val;
      propagate(ind, low, high);

      return;
    }

    int mid = low + (high - low) / 2;

    update(2 * ind + 1, low, mid, l, r, val);
    update(2 * ind + 2, mid + 1, high, l, r, val);

    seg[ind] = merge(seg[2 * ind + 1], seg[2 * ind + 2]);
  }

  SegTreeNode query(int ind, int low, int high, int l, int r) {
    propagate(ind, low, high);

    if (low > r || high < l) return empty;

    if (low >= l && high <= r) return seg[ind];

    int mid = low + (high - low) / 2;

    SegTreeNode left = query(2 * ind + 1, low, mid, l, r);
    SegTreeNode right = query(2 * ind + 2, mid + 1, high, l, r);

    return merge(left, right);
  }
};

int main() {
  int n, q;
  cin >> n >> q;

  SegTree st(n);
  // st.build(0, 0, n - 1);

  while (q--) {
    int l, r, val;
    cin >> l >> r >> val;

    st.update(0, 0, n - 1, l, r - 1, val);

    cout << st.query(0, 0, n - 1, 0, n - 1).ans << endl;
  }
}