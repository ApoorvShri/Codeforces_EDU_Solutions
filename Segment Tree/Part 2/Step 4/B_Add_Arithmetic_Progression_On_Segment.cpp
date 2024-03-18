// Problem - https://codeforces.com/edu/course/2/lesson/5/4/practice/contest/280801/problem/B

#include<bits/stdc++.h>
using namespace std;

struct Node {
  long long sum, a, d, dl;
};

class SegTree {
public:
  vector<Node> seg;

  SegTree(int n) {
    seg.resize(4 * n);
  }

  void propagate(int ind, int low, int high) {
    seg[ind].sum += (2 * seg[ind].a + (low + high) * seg[ind].d - 2 * seg[ind].dl) * (high - low + 1) / 2;

    if (low != high) {
      seg[2 * ind + 1].a += seg[ind].a;
      seg[2 * ind + 1].d += seg[ind].d;
      seg[2 * ind + 1].dl += seg[ind].dl;

      seg[2 * ind + 2].a += seg[ind].a;
      seg[2 * ind + 2].d += seg[ind].d;
      seg[2 * ind + 2].dl += seg[ind].dl;
    }

    seg[ind].a = 0;
    seg[ind].d = 0;
    seg[ind].dl = 0;
  }

  void update(int ind, int low, int high, int l, int r, int a, int d) {
    propagate(ind, low, high);

    if (low > r || high < l) return;

    if (low >= l && high <= r) {
      seg[ind].a += a;
      seg[ind].d += d;
      seg[ind].dl += 1ll * d * l;

      propagate(ind, low, high);
      return;
    }

    int mid = low + (high - low) / 2;

    update(2 * ind + 1, low, mid, l, r, a, d);
    update(2 * ind + 2, mid + 1, high, l, r, a, d);
  }

  long long query(int ind, int low, int high, int pos) {
    propagate(ind, low, high);

    if (low == high) return seg[ind].sum;

    int mid = low + (high - low) / 2;

    if (pos <= mid) return query(2 * ind + 1, low, mid, pos);
    return query(2 * ind + 2, mid + 1, high, pos);
  }
};

int main() {
  int n, q;
  cin >> n >> q;

  SegTree st(n);

  while (q--) {
    int type;
    cin >> type;

    if (type == 1) {
      int l, r, a, d;
      cin >> l >> r >> a >> d;

      st.update(0, 0, n - 1, l - 1, r - 1, a, d);
    }

    else {
      int pos;
      cin >> pos;

      cout << st.query(0, 0, n - 1, pos - 1) << endl;
    }
  }
}