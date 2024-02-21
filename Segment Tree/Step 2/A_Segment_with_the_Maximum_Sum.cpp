// Problem - https://codeforces.com/edu/course/2/lesson/4/2/practice/contest/273278/problem/A

#include<bits/stdc++.h>
using namespace std;

struct Node {
  long long ans, pref, suf, sum;
};

class SegTree {
public:
  vector<Node> seg;

  SegTree(int n) {
    seg.resize(4 * n);
  }

  Node neutralVal = { 0,0,0,0 };

  Node single(int val) {
    Node res;
    res.ans = res.pref = res.suf = max(0, val);
    res.sum = val;
    return res;
  }

  Node op(Node &left, Node &right) {
    Node res;
    res.ans = max({ left.ans,right.ans,left.suf + right.pref });
    res.pref = max(left.pref, left.sum + right.pref);
    res.suf = max(right.suf, right.sum + left.suf);
    res.sum = left.sum + right.sum;
    return res;
  }

  void build(int ind, int low, int high, vector<int> &a) {
    if (low == high) {
      seg[ind] = single(a[low]);
      return;
    }

    int mid = low + (high - low) / 2;

    build(2 * ind + 1, low, mid, a);
    build(2 * ind + 2, mid + 1, high, a);

    seg[ind] = op(seg[2 * ind + 1], seg[2 * ind + 2]);
  }

  // Node query(int ind, int low, int high, vector<int> &a, int l, int r) {
  //   if (high<l || low>r) return neutralVal;

  //   if (low >= l && high <= r) return seg[ind];

  //   int mid = low + (high - low) / 2;

  //   Node left = query(2 * ind + 1, low, mid, a, l, r);
  //   Node right = query(2 * ind + 2, mid + 1, high, a, l, r);

  //   return op(left, right);
  // }

  void pointUpdate(int ind, int low, int high, vector<int> &a, int pos, int val) {
    if (low == high) {
      seg[ind] = single(val);
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
  cout << st.seg[0].ans << endl;

  while (m--) {
    int i, v;
    cin >> i >> v;

    st.pointUpdate(0, 0, n - 1, a, i, v);
    cout << st.seg[0].ans << endl;
  }
}