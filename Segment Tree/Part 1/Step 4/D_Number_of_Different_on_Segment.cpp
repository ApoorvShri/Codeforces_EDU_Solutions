// Problem - https://codeforces.com/edu/course/2/lesson/4/4/practice/contest/274684/problem/D

#include <bits/stdc++.h>
using namespace std;

struct Node {
  long long ans;
  vector<int> cnt;

  Node() {
    ans = 0;
    cnt.resize(41);
  }
};

class SegTree {
public:
  vector<Node> seg;

  SegTree(int n) {
    seg.resize(4 * n);
  }

  Node NEUTRAL;

  Node single(int &val) {
    Node res;
    res.ans = 1;
    res.cnt[val] = 1;
    return res;
  }

  Node merge(Node &left, Node &right) {
    Node res;

    for (int i = 1; i < 41; i++) res.cnt[i] = left.cnt[i] + right.cnt[i];

    for (int i = 1; i < 41; i++) {
      if (res.cnt[i]) res.ans++;
    }

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

    seg[ind] = merge(seg[2 * ind + 1], seg[2 * ind + 2]);
  }

  Node query(int ind, int low, int high, int &l, int &r) {
    if (low > r || high < l) return NEUTRAL;

    if (low >= l && high <= r) return seg[ind];

    int mid = low + (high - low) / 2;

    Node left = query(2 * ind + 1, low, mid, l, r);
    Node right = query(2 * ind + 2, mid + 1, high, l, r);

    return merge(left, right);
  }

  void update(int ind, int low, int high, int &pos, int &val) {
    if (low == high) {
      seg[ind] = single(val);
      return;
    }

    int mid = low + (high - low) / 2;

    if (pos <= mid) update(2 * ind + 1, low, mid, pos, val);
    else update(2 * ind + 2, mid + 1, high, pos, val);

    seg[ind] = merge(seg[2 * ind + 1], seg[2 * ind + 2]);
  }
};

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

  int n, q;
  cin >> n >> q;

  vector<int> a(n);
  for (auto &it : a) cin >> it;

  SegTree st(n);
  st.build(0, 0, n - 1, a);

  while (q--) {
    int type;
    cin >> type;

    if (type == 1) {
      int l, r;
      cin >> l >> r;

      l--; r--;
      cout << st.query(0, 0, n - 1, l, r).ans << endl;
    }

    else {
      int pos, val;
      cin >> pos >> val;

      pos--;
      a[pos] = val;

      st.update(0, 0, n - 1, pos, val);
    }
  }
}