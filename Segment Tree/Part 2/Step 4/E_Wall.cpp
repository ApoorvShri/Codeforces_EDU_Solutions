// Problem - https://codeforces.com/edu/course/2/lesson/5/4/practice/contest/280801/problem/E

#include<bits/stdc++.h>
using namespace std;

struct Node {
  int min, max;
};

class SegTree {
public:
  vector<Node> seg;

  SegTree(int n) {
    seg.resize(4 * n, { 0,0 });
  }

  void propagate(int ind, int len) {
    if (len != 1) {
      auto left = &seg[2 * ind + 1];
      auto right = &seg[2 * ind + 2];

      left->min = min(left->min, seg[ind].min);
      left->min = max(left->min, seg[ind].max);

      left->max = max(left->max, seg[ind].max);
      left->max = min(left->max, seg[ind].min);

      right->min = min(right->min, seg[ind].min);
      right->min = max(right->min, seg[ind].max);

      right->max = max(right->max, seg[ind].max);
      right->max = min(right->max, seg[ind].min);

      seg[ind] = { INT_MAX,0 };
    }
  }

  void update(int ind, int low, int high, int l, int r, int val, int type) {
    propagate(ind, high - low + 1);

    if (low > r || high < l) return;

    if (low >= l && high <= r) {
      if (type == 1) {
        seg[ind].min = max(seg[ind].min, val);
        seg[ind].max = max(seg[ind].max, val);
      }

      else {
        seg[ind].min = min(seg[ind].min, val);
        seg[ind].max = min(seg[ind].max, val);
      }

      return;
    }

    int mid = low + (high - low) / 2;

    update(2 * ind + 1, low, mid, l, r, val, type);
    update(2 * ind + 2, mid + 1, high, l, r, val, type);
  }

  void build(int ind, int low, int high, vector<int> &ans) {
    if (low == high) {
      ans[low] = min(seg[ind].min, seg[ind].max);
      return;
    }

    propagate(ind, high - low + 1);

    int mid = low + (high - low) / 2;

    build(2 * ind + 1, low, mid, ans);
    build(2 * ind + 2, mid + 1, high, ans);
  }
};

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

  int n, q;
  cin >> n >> q;

  SegTree st(n);

  while (q--) {
    int type, l, r, val;
    cin >> type >> l >> r >> val;

    st.update(0, 0, n - 1, l, r, val, type);
  }

  vector<int> ans(n);
  st.build(0, 0, n - 1, ans);

  for (int i = 0; i < n; i++) cout << ans[i] << "\n";
}