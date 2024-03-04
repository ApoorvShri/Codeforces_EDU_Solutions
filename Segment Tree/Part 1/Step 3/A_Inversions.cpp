// Problem - https://codeforces.com/edu/course/2/lesson/4/3/practice/contest/274545/problem/A

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

  // void build(int ind, int low, int high, vector<int> &a) {
  //   if (low == high) {
  //     seg[ind] = { a[low],a[low] };
  //     return;
  //   }

  //   int mid = low + (high - low) / 2;

  //   build(2 * ind + 1, low, mid, a);
  //   build(2 * ind + 2, mid + 1, high, a);

  //   seg[ind] = op(seg[2 * ind + 1], seg[2 * ind + 2]);
  // }

  int query(int ind, int low, int high, int l, int r) {
    if (high<l || low>r) return 0;
    if (low >= l && high <= r) return seg[ind];

    int mid = low + (high - low) / 2;
    int left = query(2 * ind + 1, low, mid, l, r);
    int right = query(2 * ind + 2, mid + 1, high, l, r);

    return left + right;
  }

  void pointUpdate(int ind, int low, int high, int pos) {
    if (low == high) {
      seg[ind] = 1;
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

  vector<int> a(n);
  for (auto &it : a) cin >> it;

  SegTree st(n);

  for (int i = 0; i < n; i++) {
    cout << st.query(0, 0, n - 1, a[i], n - 1) << " ";
    st.pointUpdate(0, 0, n - 1, a[i] - 1);
  }

  cout << endl;
}