// Problem - https://codeforces.com/edu/course/2/lesson/4/1/practice/contest/273169/problem/A

#include<bits/stdc++.h>
using namespace std;

class SegTree {
public:
  vector<long long> seg;

  SegTree(int n) {
    seg.resize(4 * n);
  }

  long long op(long long &x, long long &y) {
    return x + y;
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

  long long query(int ind, int low, int high, vector<int> &a, int l, int r) {
    if (high<l || low>r) return 0;
    if (low >= l && high <= r) return seg[ind];

    int mid = low + (high - low) / 2;

    long long left = query(2 * ind + 1, low, mid, a, l, r);
    long long right = query(2 * ind + 2, mid + 1, high, a, l, r);

    return op(left, right);
  }

  void pointUpdate(int ind, int low, int high, vector<int> &a, int pos, int val) {
    if (low == high) {
      seg[ind] = val;
      return;
    }

    int mid = low + (high - low) / 2;

    if (pos <= mid) pointUpdate(2 * ind + 1, low, mid, a, pos, val);
    else pointUpdate(2 * ind + 2, mid + 1, high, a, pos, val);

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

      st.pointUpdate(0, 0, n - 1, a, i, v);
      a[i] = v;
    }

    else {
      int l, r;
      cin >> l >> r;

      cout << st.query(0, 0, n - 1, a, l, r - 1) << endl;
    }
  }
}