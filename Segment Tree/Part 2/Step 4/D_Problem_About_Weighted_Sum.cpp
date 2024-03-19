// Problem - https://codeforces.com/edu/course/2/lesson/5/4/practice/contest/280801/problem/D

#include<bits/stdc++.h>
using namespace std;

struct Node {
  long long sum, wtSum, len, lazy;
};

class SegTree {
public:
  vector<Node> seg;

  SegTree(int n) {
    seg.resize(4 * n);
  }

  Node merge(Node left, Node right) {
    return {
      left.sum + right.sum,
      left.wtSum + right.wtSum + left.len * right.sum,
      left.len + right.len,
      0
    };
  }

  void propagate(int ind) {
    seg[ind].sum += seg[ind].len * seg[ind].lazy;

    seg[ind].wtSum += seg[ind].len * (seg[ind].len + 1) / 2 * seg[ind].lazy;

    if (seg[ind].len != 1) {
      seg[2 * ind + 1].lazy += seg[ind].lazy;
      seg[2 * ind + 2].lazy += seg[ind].lazy;
    }

    seg[ind].lazy = 0;
  }

  void build(int ind, int low, int high, vector<int> &a) {
    if (low == high) {
      seg[ind].sum = seg[ind].wtSum = a[low];
      seg[ind].len = 1;

      return;
    }

    int mid = low + (high - low) / 2;

    build(2 * ind + 1, low, mid, a);
    build(2 * ind + 2, mid + 1, high, a);

    seg[ind] = merge(seg[2 * ind + 1], seg[2 * ind + 2]);
  }

  void update(int ind, int low, int high, int l, int r, int val) {
    propagate(ind);

    if (low > r || high < l) return;

    if (low >= l && high <= r) {
      seg[ind].lazy += val;
      propagate(ind);

      return;
    }

    int mid = low + (high - low) / 2;

    update(2 * ind + 1, low, mid, l, r, val);
    update(2 * ind + 2, mid + 1, high, l, r, val);

    seg[ind] = merge(seg[2 * ind + 1], seg[2 * ind + 2]);
  }

  Node query(int ind, int low, int high, int l, int r) {
    propagate(ind);

    if (low > r || high < l) return { 0,0,0 };

    if (low >= l && high <= r) return seg[ind];

    int mid = low + (high - low) / 2;

    Node left = query(2 * ind + 1, low, mid, l, r);
    Node right = query(2 * ind + 2, mid + 1, high, l, r);

    return merge(left, right);
  }
};

int main() {
  int n, q;
  cin >> n >> q;

  vector<int> a(n);
  for (auto &it : a) cin >> it;

  SegTree st(n);
  st.build(0, 0, n - 1, a);

  while (q--) {
    int type;
    cin >> type;

    if (type == 1) {
      int l, r, val;
      cin >> l >> r >> val;

      st.update(0, 0, n - 1, l - 1, r - 1, val);
    }

    else {
      int l, r;
      cin >> l >> r;

      cout << st.query(0, 0, n - 1, l - 1, r - 1).wtSum << endl;
    }
  }
}