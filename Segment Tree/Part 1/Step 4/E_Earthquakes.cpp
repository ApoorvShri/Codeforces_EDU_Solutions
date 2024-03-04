// Problem - https://codeforces.com/edu/course/2/lesson/4/4/practice/contest/274684/problem/E

#include <bits/stdc++.h>
using namespace std;

class SegTree {
public:
  vector<int> seg;

  SegTree(int n) {
    seg.resize(4 * n, INT_MAX);
  }

  int query(int ind, int low, int high, int &l, int &r, int &p) {
    if (low > r || high < l || seg[ind]>p) return 0;

    if (low == high) {
      seg[ind] = INT_MAX;
      return 1;
    }

    int mid = low + (high - low) / 2;

    int left = query(2 * ind + 1, low, mid, l, r, p);
    int right = query(2 * ind + 2, mid + 1, high, l, r, p);

    seg[ind] = min(seg[2 * ind + 1], seg[2 * ind + 2]);

    return left + right;
  }

  void update(int ind, int low, int high, int &pos, int &val) {
    if (low == high) {
      seg[ind] = val;
      return;
    }

    int mid = low + (high - low) / 2;

    if (pos <= mid) update(2 * ind + 1, low, mid, pos, val);
    else update(2 * ind + 2, mid + 1, high, pos, val);

    seg[ind] = min(seg[2 * ind + 1], seg[2 * ind + 2]);
  }
};

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

  int n, q;
  cin >> n >> q;

  SegTree st(n);

  while (q--) {
    int type;
    cin >> type;

    if (type == 1) {
      int pos, val;
      cin >> pos >> val;

      st.update(0, 0, n - 1, pos, val);
    }

    else {
      int l, r, p;
      cin >> l >> r >> p;

      r--;
      cout << st.query(0, 0, n - 1, l, r, p) << endl;
    }
  }
}