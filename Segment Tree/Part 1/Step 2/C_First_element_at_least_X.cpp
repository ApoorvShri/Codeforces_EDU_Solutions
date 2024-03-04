// Problem - https://codeforces.com/edu/course/2/lesson/4/2/practice/contest/273278/problem/C

#include<bits/stdc++.h>
using namespace std;

class SegTree {
public:
  vector<int> seg;

  SegTree(int n) {
    seg.resize(4 * n);
  }

  int op(int left, int right) {
    return max(left, right);
  }

  void build(int ind, int low, int high, vector<int> &a) {
    if (low == high) {
      seg[ind] = a[low];
      return;
    }

    int mid = low + (high - low) / 2;

    build(2 * ind + 1, low, mid, a);
    build(2 * ind + 2, mid + 1, high, a);

    seg[ind] = op(seg[2 * ind + 1], seg[2 * ind + 2]);
  }

  int query(int ind, int low, int high, int x) {
    if (seg[ind] < x) return -1;
    if (low == high) return low;

    int mid = low + (high - low) / 2;

    if (seg[2 * ind + 1] >= x) return query(2 * ind + 1, low, mid, x);
    return query(2 * ind + 2, mid + 1, high, x);
  }

  void pointUpdate(int ind, int low, int high, int pos, int val) {
    if (low == high) {
      seg[ind] = val;
      return;
    }

    int mid = low + (high - low) / 2;

    if (pos <= mid) pointUpdate(2 * ind + 1, low, mid, pos, val);
    else pointUpdate(2 * ind + 2, mid + 1, high, pos, val);

    seg[ind] = op(seg[2 * ind + 1], seg[2 * ind + 2]);
  }
};

int main() {
  int n, m;
  cin >> n >> m;

  vector<int> a(n);
  for (auto &it : a) cin >> it;

  SegTree st(n);
  st.build(0, 0, n - 1, a);

  while (m--) {
    int type;
    cin >> type;

    if (type == 1) {
      int i, v;
      cin >> i >> v;

      st.pointUpdate(0, 0, n - 1, i, v);
      a[i] = v;
    }

    else {
      int x;
      cin >> x;

      cout << st.query(0, 0, n - 1, x) << endl;
    }
  }
}