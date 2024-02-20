// Problem - https://codeforces.com/edu/course/2/lesson/4/1/practice/contest/273169/problem/C

#include<bits/stdc++.h>
using namespace std;

struct Node {
  int minVal, cnt;
};

class SegTree {
public:
  vector<Node> seg;

  SegTree(int n) {
    seg.resize(4 * n);
  }

  Node op(Node &x, Node &y) {
    Node ans;
    ans.minVal = min(x.minVal, y.minVal);

    if (x.minVal == y.minVal) ans.cnt = x.cnt + y.cnt;
    else if (x.minVal < y.minVal) ans.cnt = x.cnt;
    else ans.cnt = y.cnt;

    return ans;
  }

  void build(int ind, int low, int high, vector<int> &a) {
    if (low == high) {
      seg[ind].minVal = a[low];
      seg[ind].cnt = 1;
      return;
    }

    int mid = low + (high - low) / 2;

    build(2 * ind + 1, low, mid, a);
    build(2 * ind + 2, mid + 1, high, a);

    seg[ind] = op(seg[2 * ind + 1], seg[2 * ind + 2]);
  }

  Node query(int ind, int low, int high, vector<int> &a, int l, int r) {
    if (high<l || low>r) {
      Node ans;
      ans.minVal = INT_MAX;
      ans.cnt = 0;
      return ans;
    }

    if (low >= l && high <= r) return seg[ind];

    int mid = low + (high - low) / 2;

    Node left = query(2 * ind + 1, low, mid, a, l, r);
    Node right = query(2 * ind + 2, mid + 1, high, a, l, r);

    return op(left, right);
  }

  void pointUpdate(int ind, int low, int high, vector<int> &a, int pos, int val) {
    if (low == high) {
      seg[ind].minVal = val;
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

      Node res = st.query(0, 0, n - 1, a, l, r - 1);
      cout << res.minVal << " " << res.cnt << endl;
    }
  }
}