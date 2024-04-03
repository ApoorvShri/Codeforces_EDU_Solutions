// Problem - https://codeforces.com/edu/course/2/lesson/7/1/practice/contest/289390/problem/A

#include<bits/stdc++.h>
using namespace std;

class DSU {
public:
  vector<int> size, par;

  DSU(int n) {
    size.resize(n + 1, 1);

    par.resize(n + 1);
    for (int i = 0; i <= n; i++) par[i] = i;
  }

  int findPar(int node) {
    if (node == par[node]) return node;

    return par[node] = findPar(par[node]);
  }

  void unionBySize(int u, int v) {
    u = findPar(u);
    v = findPar(v);

    if (u == v) return;

    if (size[u] > size[v]) {
      par[v] = u;
      size[u] += size[v];
    }

    else {
      par[u] = v;
      size[v] += size[u];
    }
  }
};

int main() {
  int n, q;
  cin >> n >> q;

  DSU st(n);

  while (q--) {
    string type;
    int u, v;
    cin >> type >> u >> v;

    if (type == "union") st.unionBySize(u, v);

    else {
      if (st.findPar(u) == st.findPar(v)) cout << "YES" << endl;
      else cout << "NO" << endl;
    }
  }
}