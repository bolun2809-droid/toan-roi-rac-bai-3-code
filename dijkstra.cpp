/*
 * BAI TAP: THUAT TOAN DIJKSTRA TIM DUONG DI NGAN NHAT TREN DO THI VO HUONG
 * BIEU DIEN DO THI BANG DANH SACH KE (ADJACENCY LIST)
 * 
 * Do thi de bai: 7 dinh (1..7), 13 canh vo huong co trong so.
 * Dinh nguon: s = 1, Dinh dich: t = 5.
 */

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <iomanip>
#include <string>

using namespace std;

const int INF = 1e9; // Vo cung (Infinity)

// Cau truc luu thong tin mot canh ke: (dinh ke, trong so)
struct Edge {
    int to;
    int weight;
};

// Ham in danh sach ke cua do thi
void printAdjList(int n, const vector<vector<Edge>>& adj) {
    cout << "\n============================================================\n";
    cout << "         BIEU DIEN DO THI DUOI DANG DANH SACH KE\n";
    cout << "============================================================\n";
    for (int u = 1; u <= n; ++u) {
        cout << "Dinh " << u << ": ";
        if (adj[u].empty()) {
            cout << "(Khong co dinh ke)";
        } else {
            for (size_t i = 0; i < adj[u].size(); ++i) {
                cout << "-> (" << adj[u][i].to << ", w=" << adj[u][i].weight << ") ";
            }
        }
        cout << "\n";
    }
    cout << "============================================================\n\n";
}

// Thuat toan Dijkstra tim duong di ngan nhat tu s den t
void dijkstra(int n, const vector<vector<Edge>>& adj, int s, int t) {
    vector<int> dist(n + 1, INF);       // dist[v]: Khoang cach ngan nhat tu s den v
    vector<int> parent(n + 1, -1);      // parent[v]: Dinh lien truoc cua v tren duong di
    vector<bool> visited(n + 1, false); // visited[v]: Danh dau dinh da co dinh nhan (thuoc tap S)

    // Hang doi uu tien min-heap luu cap (khoang cach d, dinh u)
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    dist[s] = 0;
    pq.push(make_pair(0, s));

    cout << ">>> QUA TRINH CHAY TUNG BUOC THUAT TOAN DIJKSTRA <<<\n";
    int step = 0;

    while (!pq.empty()) {
        pair<int, int> top = pq.top();
        int d = top.first;
        int u = top.second;
        pq.pop();

        if (visited[u]) continue;
        visited[u] = true;
        step++;

        cout << "\n[Buoc " << step << "] Chon dinh u = " << u << " co d[" << u << "] = " << d << " nho nhat:\n";
        cout << "   -> Co dinh nhan dinh " << u << " (dua vao tap S).\n";

        bool updated = false;
        // Duyet qua danh sach ke cua dinh u
        for (size_t i = 0; i < adj[u].size(); ++i) {
            int v = adj[u][i].to;
            int w = adj[u][i].weight;

            if (!visited[v] && dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                parent[v] = u;
                pq.push(make_pair(dist[v], v));
                cout << "   -> Cap nhat dinh ke " << v << ": d[" << v << "] = " 
                     << dist[u] << " + " << w << " = " << dist[v] 
                     << ", parent[" << v << "] = " << u << "\n";
                updated = true;
            }
        }
        if (!updated) {
            cout << "   -> Khong co cap nhat moi cho cac dinh ke chua xet.\n";
        }
    }

    cout << "\n============================================================\n";
    cout << "                    KET QUA CUOI CUNG\n";
    cout << "============================================================\n";

    if (dist[t] == INF) {
        cout << "Khong co duong di tu dinh " << s << " den dinh " << t << "!\n";
        return;
    }

    cout << "Do dai duong di ngan nhat tu " << s << " den " << t << " la: " << dist[t] << "\n";

    // Truy vet duong di tu t nguoc ve s
    vector<int> path;
    for (int curr = t; curr != -1; curr = parent[curr]) {
        path.push_back(curr);
    }
    reverse(path.begin(), path.end());

    cout << "Duong di ngan nhat: ";
    for (size_t i = 0; i < path.size(); ++i) {
        cout << path[i];
        if (i + 1 < path.size()) cout << " -> ";
    }
    cout << "\n";

    cout << "Chi tiet trong so: ";
    for (size_t i = 0; i + 1 < path.size(); ++i) {
        int u_curr = path[i];
        int v_next = path[i + 1];
        int w_edge = dist[v_next] - dist[u_curr];
        cout << "w(" << u_curr << ", " << v_next << ")=" << w_edge;
        if (i + 2 < path.size()) cout << " + ";
    }
    cout << " = " << dist[t] << "\n\n";

    // In cay duong di ngan nhat (Shortest Path Tree - SPT)
    cout << "============================================================\n";
    cout << "       CAY DUONG DI NGAN NHAT (SPT) GOC TAI DINH " << s << "\n";
    cout << "============================================================\n";
    cout << left << setw(18) << "Canh cay (p - v)" << setw(15) << "Trong so" << setw(20) << "Khoang cach d[v]" << "\n";
    cout << string(55, '-') << "\n";
    for (int v = 1; v <= n; ++v) {
        if (v != s && parent[v] != -1) {
            int p = parent[v];
            int w_edge = dist[v] - dist[p];
            string edgeStr = "(" + to_string(p) + " - " + to_string(v) + ")";
            cout << left << setw(18) << edgeStr << setw(15) << w_edge << setw(20) << dist[v] << "\n";
        }
    }
    cout << "============================================================\n";
}

int main() {
    cout << "============================================================\n";
    cout << "       CHUONG TRINH DIJKSTRA VOI DANH SACH KE\n";
    cout << "============================================================\n";
    cout << "Chon che do chay:\n";
    cout << "1. Chay voi do thi de bai (7 dinh, 13 canh, s = 1, t = 5)\n";
    cout << "2. Nhap do thi tu ban phim\n";
    cout << "Lua chon cua ban (1 hoac 2): ";

    int choice;
    if (!(cin >> choice)) return 0;

    int n, m, s, t;
    vector<vector<Edge>> adj;

    if (choice == 1) {
        // Du lieu mac dinh theo de bai
        n = 7;
        m = 13;
        s = 1;
        t = 5;
        adj.resize(n + 1);

        vector<vector<int>> default_edges = {
            {1, 7, 18}, {1, 2, 22}, {1, 3, 10}, {1, 4, 30},
            {7, 2, 23},
            {2, 3, 11}, {2, 4, 15}, {2, 5, 16},
            {3, 4, 24}, {3, 6, 25},
            {4, 5, 33}, {4, 6, 16},
            {5, 6, 19}
        };

        for (size_t i = 0; i < default_edges.size(); ++i) {
            int u = default_edges[i][0];
            int v = default_edges[i][1];
            int w = default_edges[i][2];
            adj[u].push_back({v, w});
            adj[v].push_back({u, w});
        }
        cout << "\n-> Da tai du lieu do thi de bai: n = 7, m = 13, s = 1, t = 5.\n";
    } else {
        cout << "\nNhap so dinh n va so canh m: ";
        cin >> n >> m;
        adj.resize(n + 1);

        cout << "Nhap " << m << " dong, moi dong gom (u, v, w):\n";
        for (int i = 0; i < m; ++i) {
            int u, v, w;
            cin >> u >> v >> w;
            adj[u].push_back({v, w});
            adj[v].push_back({u, w});
        }

        cout << "Nhap dinh nguon s va dinh dich t: ";
        cin >> s >> t;
    }

    // In danh sach ke
    printAdjList(n, adj);

    // Chay thuat toan Dijkstra
    dijkstra(n, adj, s, t);

    return 0;
}