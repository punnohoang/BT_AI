#include <bits/stdc++.h>
using namespace std;

// ===== Ð?C INPUT =====
void readInput(
    map<string, vector<string>>& graph,
    string& start,
    string& goal
) {
    ifstream fin("input.txt");
    fin >> start >> goal;
    fin.ignore();

    string line, u, v;
    while (getline(fin, line)) {
        stringstream ss(line);
        ss >> u;
        while (ss >> v)
            graph[u].push_back(v);
    }
    fin.close();
}

// ===== IN STACK =====
void printStack(stack<string> st, ofstream& fout) {
    vector<string> tmp;
    while (!st.empty()) {
        tmp.push_back(st.top());
        st.pop();
    }
    reverse(tmp.begin(), tmp.end());
    for (string x : tmp) fout << x << " ";
}

// ===== DFS =====
bool dfs(
    map<string, vector<string>>& graph,
    string start,
    string goal,
    map<string, string>& parent
) {
    ofstream fout("output_dfs.txt");

    stack<string> st;
    map<string,bool> visited;

    st.push(start);
    parent[start] = "";

    fout << "===== DFS (STACK) =====\n";
    fout << "Bat dau: " << start << "\n";
    fout << "Ket thuc: " << goal << "\n\n";
    fout << "Buoc | Dinh xet | Danh sach ke | Stack\n";
    fout << "-------------------------------------------\n";

    int step = 1;

    while (!st.empty()) {
        string u = st.top(); st.pop();

        if (visited[u]) continue;
        visited[u] = true;

        fout << setw(4) << step++ << " | "
             << setw(8) << u << " | ";

        for (string v : graph[u]) fout << v << " ";
        fout << " | ";

        if (u == goal) break;

        for (auto it = graph[u].rbegin(); it != graph[u].rend(); ++it) {
            if (!visited[*it]) {
                parent[*it] = u;
                st.push(*it);
            }
        }

        printStack(st, fout);
        fout << "\n";
    }

    fout << "\nDuong di DFS:\n";
    vector<string> path;
    for (string cur = goal; cur != ""; cur = parent[cur])
        path.push_back(cur);
    reverse(path.begin(), path.end());

    for (int i = 0; i < path.size(); i++) {
        fout << path[i];
        if (i < path.size() - 1) fout << " -> ";
    }
    fout << "\n";

    fout.close();
    return true;
}

// ===== MAIN =====
int main() {
    map<string, vector<string>> graph;
    map<string, string> parent;
    string start, goal;

    readInput(graph, start, goal);
    dfs(graph, start, goal, parent);

    return 0;
}

