// Problem - https://codeforces.com/edu/course/2/lesson/4/3/practice/contest/274545/problem/E

#include<bits/stdc++.h>
using namespace std;

class SegTree {
public:
  vector<long long> seg;

  SegTree(int n) {
    seg.resize(4 * n);
  }

  long long op(long long left, long long right) {
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

  long long query(int ind, int low, int high, int l, int r) {
    if (low > r || high < l) return 0;
    if (low >= l && high <= r) return seg[ind];

    int mid = low + (high - low) / 2;

    long long left = query(2 * ind + 1, low, mid, l, r);
    long long right = query(2 * ind + 2, mid + 1, high, l, r);

    return op(left, right);
  }

  void pointUpdate(int ind, int low, int high, int pos, int val) {
    if (low == high) {
      seg[ind] += val;
      return;
    }

    int mid = low + (high - low) / 2;

    if (pos <= mid) pointUpdate(2 * ind + 1, low, mid, pos, val);
    else pointUpdate(2 * ind + 2, mid + 1, high, pos, val);

    seg[ind] = op(seg[2 * ind + 1], seg[2 * ind + 2]);
  }
};

int main() {
  int n, q;
  cin >> n >> q;

  SegTree st(n + 1);

  while (q--) {
    int type;
    cin >> type;

    if (type == 1) {
      int l, r, v;
      cin >> l >> r >> v;

      st.pointUpdate(0, 0, n, l, v);
      st.pointUpdate(0, 0, n, r, -v);
    }

    else {
      int i;
      cin >> i;

      cout << st.query(0, 0, n, 0, i) << endl;
    }
  }
}