// Problem - https://codeforces.com/edu/course/2/lesson/7/1/practice/contest/289390/problem/B

#include<bits/stdc++.h>
using namespace std;

class DSU {
public:
  vector<int> size, par, mn, mx;

  DSU(int n) {
    size.resize(n + 1);
    par.resize(n + 1);
    mn.resize(n + 1);
    mx.resize(n + 1);

    for (int i = 0; i <= n; i++) {
      size[i] = 1;
      par[i] = mn[i] = mx[i] = i;
    }
  }

  int findPar(int node) {
    if (node == par[node]) return node;

    return par[node] = findPar(par[node]);
  }

  void unionBySize(int u, int v) {
    u = findPar(u);
    v = findPar(v);

    if (u == v) return;
    if (size[v] > size[u]) swap(u, v);

    par[v] = u;
    size[u] += size[v];

    mn[u] = min(mn[u], mn[v]);
    mx[u] = max(mx[u], mx[v]);
  }

  void get(int node) {
    node = findPar(node);
    cout << mn[node] << " " << mx[node] << " " << size[node] << endl;
  }
};

int main() {
  int n, q;
  cin >> n >> q;

  DSU st(n);

  while (q--) {
    string type;
    cin >> type;

    if (type == "union") {
      int u, v;
      cin >> u >> v;

      st.unionBySize(u, v);
    }

    else {
      int node;
      cin >> node;

      st.get(node);
    }
  }
}