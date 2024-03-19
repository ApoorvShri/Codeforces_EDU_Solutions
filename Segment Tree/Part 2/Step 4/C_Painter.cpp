// Problem - https://codeforces.com/edu/course/2/lesson/5/4/practice/contest/280801/problem/C

#include<bits/stdc++.h>
using namespace std;

struct Node {
  int sum, cnt, start, end, lazy;
  Node() :sum(0), cnt(0), start(2), end(2), lazy(0) {}
};

class SegTree {
public:
  vector<Node> seg;

  SegTree(int n) {
    seg.resize(4 * n);
  }

  Node merge(Node left, Node right) {
    Node res;
    res.sum = left.sum + right.sum;
    res.cnt = left.cnt + right.cnt;
    if (left.end == 1 && right.start == 1) res.cnt--;
    res.start = left.start;
    res.end = right.end;
    return res;
  }

  void propagate(int ind, int low, int high) {
    if (seg[ind].lazy) {
      if (seg[ind].lazy == 1) {
        seg[ind].sum = high - low + 1;
        seg[ind].cnt = 1;
      }

      else seg[ind].sum = seg[ind].cnt = 0;

      seg[ind].start = seg[ind].lazy;
      seg[ind].end = seg[ind].lazy;

      if (low != high) seg[2 * ind + 1].lazy = seg[2 * ind + 2].lazy = seg[ind].lazy;

      seg[ind].lazy = 0;
    }
  }

  void update(int ind, int low, int high, int l, int r, int val) {
    propagate(ind, low, high);

    if (low > r || high < l) return;

    if (low >= l && high <= r) {
      seg[ind].lazy = val;
      propagate(ind, low, high);

      return;
    }

    int mid = low + (high - low) / 2;

    update(2 * ind + 1, low, mid, l, r, val);
    update(2 * ind + 2, mid + 1, high, l, r, val);

    seg[ind] = merge(seg[2 * ind + 1], seg[2 * ind + 2]);
  }

  Node query(int ind, int low, int high, int l, int r) {
    propagate(ind, low, high);

    if (low > r || high < l) return Node();

    if (low >= l && high <= r) return seg[ind];

    int mid = low + (high - low) / 2;

    Node left = query(2 * ind + 1, low, mid, l, r);
    Node right = query(2 * ind + 2, mid + 1, high, l, r);

    return merge(left, right);
  }
};

int main() {
  int n = 1e6, offset = 5e5;
  SegTree st(n);

  int q;
  cin >> q;

  while (q--) {
    char col;
    int x, len;
    cin >> col >> x >> len;

    int l = x + offset;
    int r = x + len - 1 + offset;

    if (col == 'B') st.update(0, 0, n - 1, l, r, 1);
    else st.update(0, 0, n - 1, l, r, 2);

    Node res = st.query(0, 0, n - 1, 0, n - 1);

    cout << res.cnt << " " << res.sum << endl;
  }
}