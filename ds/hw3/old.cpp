#include <cmath>
#include <fstream>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <vector>

struct Vertex {
  int x, y;
  std::string name;

  void print() const { std::cout << name << " (" << x << ", " << y << ")"; }

  bool operator==(const Vertex &o) const { return x == o.x && y == o.y; }
  bool operator<(const Vertex &o) const {
    if (x == o.x) {
      return y < o.y;
    } else {
      return x < o.x;
    }
  }
};

using Vertices = std::map<std::string, Vertex>;

double distance(const Vertex &u, const Vertex &v) {
  return sqrt(pow(u.x - v.x, 2) + pow(u.y - v.y, 2));
}

// undirected edge
struct Edge {
  int u, v;

  Edge(int u, int v) : u(std::min(u, v)), v(std::max(u, v)) {}

  void print(const Vertices &V) const {
    std::cout << V[u].name << " - " << V[v].name;
  }

  bool operator==(const Edge &e) const {
    return (u == e.u && v == e.v) || (u == e.v && v == e.u);
  }
  bool operator<(const Edge &e) const {
    if (u != e.u)
      return u < e.u;
    return v < e.v;
  }
};

using Edges = std::set<Edge>;

void printVertices(const Vertices &V) {
  std::cout << "Vertices:" << std::endl;
  for (auto const &[name, _] : V) {
    std::cout << name << std::endl;
  }
}

void printEdges(const Vertices &V, const Edges &mst) {
  std::cout << "Edges:" << std::endl;

  for (const auto &e : mst) {
    e.print(V);
    std::cout << std::endl;
  }
}

void read_input(const std::string &filename, Vertices &V) {
  std::ifstream infile(filename);
  int n;
  std::string str;
  std::getline(infile, str);

  // parse str = "NewVertices: 10" -> 10
  n = std::stoi(str.substr(str.find(":") + 1));

  std::string name;
  int x, y;
  for (int i = 0; i < n; ++i) {

    infile >> name >> x >> y;

    V[name] = {x, y};
  }
}

struct PQCompare {
  bool operator()(const std::pair<int, double> &a,
                  const std::pair<int, double> &b) {
    return a.second > b.second;
  }
};

void prim_mst(const Vertices &V, Edges &mst) {
  int n = V.size();
  if (n == 0)
    return;

  std::vector<float> costs(n, std::numeric_limits<float>::max());
  std::vector<int> parent(n, -1);
  std::vector<bool> inMST(n, false);
  std::priority_queue<std::pair<int, double>,
                      std::vector<std::pair<int, double>>, PQCompare>
      pq;

  costs[0] = 0.0;
  pq.push({0, 0}); // {vertex, key}

  while (!pq.empty()) {
    int u = pq.top().first;
    pq.pop();

    if (inMST[u])
      continue;
    inMST[u] = true;

    for (int v = 0; v < n; ++v) {
      if (u == v || inMST[v])
        continue;

      double cost = distance(V[u], V[v]);

      if (cost < costs[v]) {
        costs[v] = cost;
        pq.push({v, costs[v]});
        parent[v] = u;
      }
    }
  }

  for (int i = 1; i < n; ++i) {
    if (parent[i] == -1)
      continue;
    mst.insert(Edge(i, parent[i]));
  }
}

void Lshape(std::map<std::string, Vertex> &V, Edges &mst) {
  printVertices(V);
  Edges newEdges;
  std::map<std::pair<int, int>, int> sp;
  int steinerCount = 1;

  for (const auto &edge : mst) {
    const Vertex &u = V[edge.u];
    const Vertex &v = V[edge.v];

    if (u.x != v.x && u.y != v.y) {
      int s;
      // find if the steiner point already exists
      if (sp.find({u.x, v.y}) != sp.end()) {
        s = sp[{u.x, v.y}];
      } else if (sp.find({v.x, u.y}) != sp.end()) {
        s = sp[{v.x, u.y}];
      } else {
        // Create a new Steiner point
        Vertex steiner = {u.x, v.y, "S" + std::to_string(steinerCount++)};

        V.push_back(steiner);
        s = V.size() - 1;

        sp.insert({{steiner.x, steiner.y}, s});
      }

      // TODO: if the steiner point lie on the other edge e1 = (v1, v2), replace
      // the edge with (v1, s) and (s, v2)

      // Create two new L-shaped edges
      newEdges.insert(Edge(edge.u, s));
      newEdges.insert(Edge(s, edge.v));

    } else {
      sp.insert({{u.x, u.y}, edge.u});
      sp.insert({{v.x, v.y}, edge.v});

      // Edge is already L-shaped
      newEdges.insert(edge);
    }
  }

  // Replace old edges with new L-shaped edges
  mst.clear();
  for (const auto &edge : newEdges) {
    mst.insert(edge);
  }
}

bool isOnEdge(const Vertex &v, const Vertex &u, const Vertex &w) {
  if (v.x == u.x && u.x == w.x) {
    return std::min(u.y, w.y) <= v.y && v.y <= std::max(u.y, w.y);
  } else if (v.y == u.y && u.y == w.y) {
    return std::min(u.x, w.x) <= v.x && v.x <= std::max(u.x, w.x);
  } else {
    return false;
  }
}

void splitEdgesAtVertices(Vertices &V, Edges &mst) {
  Edges newEdges;
  // std::vector<Edge> newEdges;
  for (const auto &edge : mst) {
    Vertex &u = V[edge.u];
    Vertex &v = V[edge.v];
    bool split = false;

    int n = V.size();

    for (int i = 0; i < n; ++i) {
      if (i == edge.u || i == edge.v)
        continue;
      if (isOnEdge(V[i], u, v)) {
        newEdges.insert(Edge(edge.u, i));
        newEdges.insert(Edge(i, edge.v));
        split = true;
        break;
      }
    }
    if (!split) {
      newEdges.insert(edge);
    }
  }

  // Replace old edges with new split edges
  mst.clear();
  for (const auto &edge : newEdges) {
    mst.insert(edge);
  }
}

int main() {
  Vertices V;
  Edges mst;

  read_input("input.txt", V);

  prim_mst(V, mst);

  Lshape(V, mst);

  splitEdgesAtVertices(V, mst);

  printVertices(V);
  printEdges(V, mst);
}
