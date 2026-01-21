#include <bits/stdc++.h>
using namespace std;

// NHOM 15 BAI TAP THUAT TOAN BFS
// -.-

void readInput(
    const string &filename,
    map<string, vector<string>> &graph,
    string &start,
    string &goal)
{
    ifstream fin(filename);
    fin >> start >> goal;
    fin.ignore();

    string line, u, v;
    while (getline(fin, line))
    {
        stringstream ss(line);
        ss >> u;
        while (ss >> v)
            graph[u].push_back(v);
    }
    fin.close();
}

void printQueue(queue<string> q, ofstream &fout)
{
    while (!q.empty())
    {
        fout << q.front() << " ";
        q.pop();
    }
}

void bfs(
    map<string, vector<string>> &graph,
    string start,
    string goal,
    const string &outputFile)
{
    ofstream fout(outputFile);

    queue<string> q;
    map<string, string> parent;

    q.push(start);
    parent[start] = "";

    fout << "BFS (NHOM 15)\n";
    fout << "Bat dau: " << start << "\n";
    fout << "Ket thuc: " << goal << "\n\n";

    fout << left
         << setw(5) << "Buoc"
         << setw(10) << "Dinh"
         << setw(20) << "Danh sach ke"
         << "Queue\n";
    fout << "---------------------------------------------\n";

    int step = 1;

    while (!q.empty())
    {
        string u = q.front();
        q.pop();

        fout << setw(5) << step++
             << setw(10) << u;
        for (string v : graph[u])
            fout << v << " ";
        fout << setw(20 - graph[u].size() * 2) << " ";
        if (u == goal)
        {
            printQueue(q, fout);
            fout << "\n";
            break;
        }
        for (string v : graph[u])
        {
            if (!parent.count(v))
                parent[v] = u;
            q.push(v);
        }
        printQueue(q, fout);
        fout << "\n";
    }
    fout << "\nDuong di BFS (NHOM 15):\n";
    vector<string> path;
    for (string cur = goal; cur != ""; cur = parent[cur])
        path.push_back(cur);
    reverse(path.begin(), path.end());
    for (int i = 0; i < path.size(); i++)
    {
        fout << path[i];
        if (i < path.size() - 1)
            fout << " -> ";
    }
    fout << "\n";
    fout.close();
}

int main()
{
    map<string, vector<string>> graph;
    string start, goal;

    readInput("input.txt", graph, start, goal);
    bfs(graph, start, goal, "output_bfs.txt");

    return 0;
}
