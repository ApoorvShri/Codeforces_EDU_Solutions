// Problem - https://codeforces.com/edu/course/2/lesson/4/3/practice/contest/274545/problem/D

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

  // void build(int ind, int low, int high) {
  //   if (low == high) {
  //     seg[ind] = 1;
  //     return;
  //   }

  //   int mid = low + (high - low) / 2;

  //   build(2 * ind + 1, low, mid);
  //   build(2 * ind + 2, mid + 1, high);

  //   seg[ind] = op(seg[2 * ind + 1], seg[2 * ind + 2]);
  // }

  int query(int ind, int low, int high, int l, int r) {
    if (low > r || high < l) return 0;
    if (low >= l && high <= r) return seg[ind];

    int mid = low + (high - low) / 2;

    int left = query(2 * ind + 1, low, mid, l, r);
    int right = query(2 * ind + 2, mid + 1, high, l, r);

    return left + right;
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
  int n;
  cin >> n;

  vector<int> a(2 * n), prev(n + 1, -1), ans(n + 1);
  for (auto &it : a) cin >> it;

  SegTree st(2 * n);

  for (int i = 0; i < 2 * n; i++) {
    if (prev[a[i]] == -1) {
      st.pointUpdate(0, 0, 2 * n - 1, i, 1);
      prev[a[i]] = i;
    }
    else {
      st.pointUpdate(0, 0, 2 * n - 1, prev[a[i]], 0);
      ans[a[i]] += st.query(0, 0, 2 * n - 1, prev[a[i]], i);
    }
  }

  for (int i = 1; i <= n; i++) prev[i] = -1;

  for (int i = 2 * n - 1; i >= 0; i--) {
    if (prev[a[i]] == -1) {
      st.pointUpdate(0, 0, 2 * n - 1, i, 1);
      prev[a[i]] = i;
    }
    else {
      st.pointUpdate(0, 0, 2 * n - 1, prev[a[i]], 0);
      ans[a[i]] += st.query(0, 0, 2 * n - 1, i, prev[a[i]]);
    }
  }

  for (int i = 1; i <= n; i++) cout << ans[i] << " ";
  cout << endl;
}