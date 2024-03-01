#include<bits/stdc++.h>
using namespace std;

struct Node {
  long long sum;
  int cnt;
};

class SegTree {
public:
  vector<Node> seg;

  SegTree(int n) {
    seg.resize(4 * n);
  }

  Node merge(Node left, Node right) {
    if (left.cnt & 1) return { left.sum - right.sum,left.cnt + right.cnt };
    return { left.sum + right.sum,left.cnt + right.cnt };
  }

  void build(int ind, int low, int high, vector<int> &a) {
    if (low == high) {
      seg[ind] = { a[low],1 };
      return;
    }

    int mid = low + (high - low) / 2;

    build(2 * ind + 1, low, mid, a);
    build(2 * ind + 2, mid + 1, high, a);

    seg[ind] = merge(seg[2 * ind + 1], seg[2 * ind + 2]);
  }

  Node query(int ind, int low, int high, int l, int r) {
    if (low > r || high < l) return { 0,0 };
    if (low >= l && high <= r) return seg[ind];

    int mid = low + (high - low) / 2;

    Node left = query(2 * ind + 1, low, mid, l, r);
    Node right = query(2 * ind + 2, mid + 1, high, l, r);

    return merge(left, right);
  }

  void pointUpdate(int ind, int low, int high, int pos, int val) {
    if (low == high) {
      seg[ind] = { val,1 };
      return;
    }

    int mid = low + (high - low) / 2;

    if (pos <= mid) pointUpdate(2 * ind + 1, low, mid, pos, val);
    else pointUpdate(2 * ind + 2, mid + 1, high, pos, val);

    seg[ind] = merge(seg[2 * ind + 1], seg[2 * ind + 2]);
  }
};

int main() {
  int n;
  cin >> n;

  vector<int> a(n);
  for (auto &it : a) cin >> it;

  SegTree st(n);
  st.build(0, 0, n - 1, a);

  int q;
  cin >> q;

  while (q--) {
    int type;
    cin >> type;

    if (type) {
      int l, r;
      cin >> l >> r;

      cout << st.query(0, 0, n - 1, l - 1, r - 1).sum << endl;
    }
    else {
      int i, j;
      cin >> i >> j;

      a[i - 1] = j;
      st.pointUpdate(0, 0, n - 1, i - 1, j);
    }
  }
}