/**
*    author: lucasfcm9
*    created: 07.12.20 15:45:45
**/
#include <iostream>
#include <vector>

using namespace std;

struct Edge {
  int u, v, w;
};

const int MAX = 110;
const int inf = (int) 1e9;
int dist[MAX][MAX];

void FloydWarshall(int n, vector<Edge>& edges) {
  for (int u = 1; u <= n; u++) {
    for (int v = 1; v <= n; v++) {
      dist[u][v] = inf;
    }
  }
  for (int u = 1; u <= n; u++) {
    dist[u][u] = 0;
  }
  for (const auto& [u, v, w] : edges) {
    dist[u][v] = w;
  }
  for (int k = 1; k <= n; k++) {
    for (int u = 1; u <= n; u++) {
      for (int v = 1; v <= n; v++) {
        dist[u][v] = min(dist[u][v], max(dist[u][k], dist[k][v]));
      }
    }
  }

  // Caso queira ver a matriz de distâncias, descomente essa parte
  /* for (int u = 1; u <= n; u++) {
    for (int v = 1; v <= n; v++) {
      if (v > 1) {
        cout << " ";
      }
      cout << dist[u][v];
    }
    cout << '\n';
  } */
}

vector<int> Solve(int n, vector<Edge>& edges, vector<pair<int, int>>& p) {
  FloydWarshall(n, edges);
  vector<int> res;

  for (const auto& [u, v] : p) {
    res.emplace_back(u == v ? 0 : dist[u][v]);
  }
  return res;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int n, m;
  int test = 1; 
  while (cin >> n >> m, n | m) {
    vector<Edge> g;
    for (int i = 0; i < m; i++) {
      int u, v, w;
      cin >> u >> v >> w;
      g.push_back({u, v, w});
      g.push_back({v, u, w});
    }
    int kk;
    cin >> kk;
    vector<pair<int, int>> p;
    while (kk--) {
      int x, y;
      cin >> x >> y;
      p.push_back({x, y});
    }
    vector<int> res = Solve(n, g, p);
    cout << "Instancia " << test++ << '\n';
    for (const auto& each : res) {
      cout << each << '\n';
    }
    cout << '\n';
  }
  return 0;
}
