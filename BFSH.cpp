#include <bits/stdc++.h>
using namespace std;

void readInput(const string &filename,
               map<string,int> &h,
               map<string, vector<string>> &graph,
               string &start,
               string &goal)
{
    ifstream fin(filename);
    fin >> start >> goal;
    fin.ignore();

    string line, u, v;
    int heuristic;

    while (getline(fin, line))
    {
        if (line.empty()) continue;

        stringstream ss(line);
        ss >> u >> heuristic;
        h[u] = heuristic;

        while (ss >> v)
            graph[u].push_back(v);
    }
    fin.close();
}

void printPQ(priority_queue<pair<int,string>,
             vector<pair<int,string>>,
             greater<pair<int,string>>> pq,
             ofstream &fout)
{
    if (pq.empty()) {
        fout << "rong";
        return;
    }

    while (!pq.empty())
    {
        fout << pq.top().second
             << pq.top().first << " ";
        pq.pop();
    }
}

void greedyBFS(map<string, vector<string>> &graph,
               map<string,int> &h,
               string start,
               string goal,
               const string &outputFile)
{
    ofstream fout(outputFile);

    priority_queue<
        pair<int,string>,
        vector<pair<int,string>>,
        greater<pair<int,string>>
    > pq;

    map<string,string> parent;
    set<string> visited;

    fout << "BEST-FIRST SEARCH\n\n";

    fout << left
         << setw(6) << "Buoc"
         << setw(18) << "Dinh lay ra"
         << setw(28) << "Them vao"
         << "Hang doi uu tien\n";

    fout << "--------------------------------------------------------------------------\n";

    // ===== BUOC 0 =====
    pq.push({h[start], start});
    fout << setw(6) << "0"
         << setw(18) << "-"
         << setw(28) << (start + to_string(h[start])) ;

    printPQ(pq, fout);
    fout << "\n";

    int step = 1;

    
    while (!pq.empty())
    {
        auto top = pq.top(); pq.pop();
        string u = top.second;

        if (visited.count(u)) continue;
        visited.insert(u);

        string layra = u + to_string(h[u]);

        fout << setw(6) << step++
             << setw(18) << layra;

        string themvao = "";

        for (string v : graph[u])
        {
            if (!visited.count(v))
            {
                parent[v] = u;
                pq.push({h[v], v});
                themvao += v + to_string(h[v]) + " ";
            }
        }

        fout << setw(28) << themvao;
        printPQ(pq, fout);
        fout << "\n";

        if (u == goal) break;
    }

    
    fout << "\nDuong di tim duoc:\n";

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
    map<string,int> h;
    string start, goal;

    readInput("input.txt", h, graph, start, goal);

    greedyBFS(graph, h, start, goal, "output.txt");

    return 0;
}
