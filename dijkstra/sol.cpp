/**
*    author: lucasfcm9
*    created: 07.12.20 16:08:05
**/
#include <iostream>
#include <vector>
#include <bitset>
#include <queue>
#include <algorithm>
 
using namespace std;
 
const long long inf = LLONG_MAX;
const long long MAX = (int) 1e6 + 10;
long long dist[MAX];
long long parent[MAX];
bitset<MAX> processed;
vector<pair<long long, long long>> g[MAX];
 
void dijkstra(int s) {
  dist[s] = 0;
  parent[s] = s;
  processed.reset();
  priority_queue<pair<long long, long long>, vector<pair<long long, long long>>, greater<pair<long long, long long>>> pq;
  pq.push({0, s});
  while (!pq.empty()) {
    auto [d, u] = pq.top();
    pq.pop();
    if (processed[u]) {
      continue;
    }
    processed[u] = true;
    for (const auto& [v, w] : g[u]) {
      if (dist[v] > d + w) {
        dist[v] = d + w;
        parent[v] = u;
        pq.push({dist[v], v});
      }
    }
  }
}
 
void init() {
  for (int i = 0; i < MAX; i++) {
    dist[i] = LLONG_MAX;
    parent[i] = -1;
  }
}
 
int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  long long n, m;
  cin >> n >> m;
  init();
  for (int i = 0; i < m; i++) {
    long long x, y, w;
    cin >> x >> y >> w;
    g[x].push_back({y, w});
    g[y].push_back({x, w});
  }
  dijkstra(1);
  vector<long long> path;
  if (dist[n] == inf) {
    cout << -1 << '\n';
    return 0;
  }
  long long pred = n;
  while (pred != 1) {
    path.push_back(pred);
    pred = parent[pred];
  }
  reverse(path.begin(), path.end());
  cout << "1 ";
  for (int i = 0; i < (int) path.size(); i++) {
    if (i > 0) {
      cout << " ";
    }
    cout << path[i];
  }
  cout << '\n';
  return 0;
}
