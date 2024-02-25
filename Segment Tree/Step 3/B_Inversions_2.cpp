// Problem - https://codeforces.com/edu/course/2/lesson/4/3/practice/contest/274545/problem/B

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

  void build(int ind, int low, int high) {
    if (low == high) {
      seg[ind] = 1;
      return;
    }

    int mid = low + (high - low) / 2;

    build(2 * ind + 1, low, mid);
    build(2 * ind + 2, mid + 1, high);

    seg[ind] = op(seg[2 * ind + 1], seg[2 * ind + 2]);
  }

  int query(int ind, int low, int high, int k) {
    if (low == high) return low;

    int mid = low + (high - low) / 2;

    if (seg[2 * ind + 1] >= k) return query(2 * ind + 1, low, mid, k);
    return query(2 * ind + 2, mid + 1, high, k - seg[2 * ind + 1]);
  }

  void pointUpdate(int ind, int low, int high, int pos) {
    if (low == high) {
      seg[ind] = 0;
      return;
    }

    int mid = low + (high - low) / 2;

    if (pos <= mid) pointUpdate(2 * ind + 1, low, mid, pos);
    else pointUpdate(2 * ind + 2, mid + 1, high, pos);

    seg[ind] = op(seg[2 * ind + 1], seg[2 * ind + 2]);
  }
};

int main() {
  int n;
  cin >> n;

  vector<int> a(n), ans(n);
  for (auto &it : a) cin >> it;

  SegTree st(n);
  st.build(0, 0, n - 1);

  for (int i = n - 1; i >= 0; i--) {
    ans[i] = st.query(0, 0, n - 1, i + 1 - a[i]);
    st.pointUpdate(0, 0, n - 1, ans[i]);
  }

  for (auto &it : ans) cout << it + 1 << " ";
  cout << endl;
}