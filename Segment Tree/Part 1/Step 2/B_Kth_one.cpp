// Problem - https://codeforces.com/edu/course/2/lesson/4/2/practice/contest/273278/problem/B

#include<bits/stdc++.h>
using namespace std;

class SegTree {
public:
  vector<int> seg;

  SegTree(int n) {
    seg.resize(4 * n);
  }

  int op(int left, int right) {
    return left + right;
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

  int query(int ind, int low, int high, vector<int> &a, int k) {
    if (low == high) return low;
    int mid = low + (high - low) / 2;

    if (k <= seg[2 * ind + 1]) return query(2 * ind + 1, low, mid, a, k);
    return query(2 * ind + 2, mid + 1, high, a, k - seg[2 * ind + 1]);
  }

  void pointUpdate(int ind, int low, int high, vector<int> &a, int pos) {
    if (low == high) {
      seg[ind] = a[low];
      return;
    }

    int mid = low + (high - low) / 2;

    if (pos <= mid) pointUpdate(2 * ind + 1, low, mid, a, pos);
    else pointUpdate(2 * ind + 2, mid + 1, high, a, pos);

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
    int type, val;
    cin >> type >> val;

    if (type == 1) {
      a[val] = 1 - a[val];
      st.pointUpdate(0, 0, n - 1, a, val);
    }
    else cout << st.query(0, 0, n - 1, a, val + 1) << endl;
  }
}