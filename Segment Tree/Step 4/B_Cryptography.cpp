// Problem - https://codeforces.com/edu/course/2/lesson/4/4/practice/contest/274684/problem/B

#include<bits/stdc++.h>
using namespace std;

using vi = vector<int>;

class SegTree {
public:
  vector<vi> seg;
  int mod;

  SegTree(int n, int m) {
    seg.resize(4 * n);
    mod = m;
  }

  vi merge(vi &l, vi &r) {
    return { (l[0] * r[0] + l[1] * r[2]) % mod,(l[0] * r[1] + l[1] * r[3]) % mod,(l[2] * r[0] + l[3] * r[2]) % mod,(l[2] * r[1] + l[3] * r[3]) % mod };
  }

  void build(int ind, int low, int high, vector<vi> &a) {
    if (low == high) {
      seg[ind] = a[low];
      return;
    }

    int mid = low + (high - low) / 2;

    build(2 * ind + 1, low, mid, a);
    build(2 * ind + 2, mid + 1, high, a);

    seg[ind] = merge(seg[2 * ind + 1], seg[2 * ind + 2]);
  }

  vi query(int ind, int low, int high, int &l, int &r) {
    if (low > r || high < l) return { 1,0,0,1 };
    if (low >= l && high <= r) return seg[ind];

    int mid = low + (high - low) / 2;

    vi left = query(2 * ind + 1, low, mid, l, r);
    vi right = query(2 * ind + 2, mid + 1, high, l, r);

    return merge(left, right);
  }
};

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

  int mod, n, q;
  cin >> mod >> n >> q;

  vector<vi> a(n, vi(4));
  for (auto &mat : a) for (auto &it : mat) cin >> it;

  SegTree st(n, mod);
  st.build(0, 0, n - 1, a);

  while (q--) {
    int l, r;
    cin >> l >> r;
    l--; r--;

    vi res = st.query(0, 0, n - 1, l, r);
    cout << res[0] << " " << res[1] << "\n" << res[2] << " " << res[3] << "\n\n";
  }
}