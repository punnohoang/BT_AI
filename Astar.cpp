#include <bits/stdc++.h>
using namespace std;

void readInput(const string &filename,
               map<string,int> &h,
               map<string, vector<pair<string,int>>> &graph,
               string &start,
               string &goal)
{
    ifstream fin(filename);
    fin >> start >> goal;

    int n;
    fin >> n;
    fin.ignore();

    string line, u, v;
    int heuristic, cost;

    for (int i = 0; i < n; i++)
    {
        getline(fin, line);
        if (line.empty())
        {
            i--;
            continue;
        }

        stringstream ss(line);
        ss >> u >> heuristic;
        h[u] = heuristic;

        while (ss >> v >> cost)
            graph[u].push_back({v, cost});
    }

    fin.close();
}

void Astar(map<string, vector<pair<string,int>>> &graph,
                       map<string,int> &h,
                       string start,
                       string goal,
                       const string &outputFile)
{
    ofstream fout(outputFile);

    list<string> L;
    map<string,int> g, f;
    map<string,string> parent;
    set<string> closed;

    g[start] = 0;
    f[start] = h[start];
    parent[start] = "";

    L.push_back(start);

    fout << "TT   TTK   k(u,v)  h(v)   g(v)   f(v)      Danh sach L\n";
    fout << "--------------------------------------------------------------------------\n";

    while (!L.empty())
    {
        string u = L.front();
        L.pop_front();

        if (u == goal){
			fout << left << setw(5) << u;
            break;
    	}

        closed.insert(u);

        vector<string> block;

        for (auto edge : graph[u])
        {
            string v = edge.first;
            int cost = edge.second;

            if (closed.count(v))
                continue;

            int newG = g[u] + cost;

            if (!g.count(v) || newG < g[v])
            {
                g[v] = newG;
                f[v] = g[v] + h[v];
                parent[v] = u;

                L.remove(v);

                auto it = L.begin();
                while (it != L.end() && f[*it] <= f[v])
                    ++it;

                L.insert(it, v);

                stringstream ss;

                if (block.empty())
                    ss << left << setw(5) << u;
                else
                    ss << "     ";

                ss << left
                   << setw(6) << v
                   << setw(8) << cost
                   << setw(8) << h[v]
                   << setw(8) << g[v]
                   << setw(5) << f[v];

                block.push_back(ss.str());
            }
        }

        for (int i = 0; i < block.size(); i++)
        {
            fout << block[i];

            if (i == block.size() - 1)
            {
                fout << "   ";
                for (auto node : L)
                    fout << node << f[node] << ",";
            }

            fout << "\n";
        }
    }

    fout << "TTKT/dung, duong di ";

    vector<string> path;
    for (string t = goal; t != ""; t = parent[t])
        path.push_back(t);

    for (int i = 0; i < path.size(); i++)
    {
        fout << path[i];
        if (i < path.size() - 1)
            fout << " <- ";
    }

    fout << ", do dai " << g[goal];

    fout.close();
}


int main()
{
    map<string, vector<pair<string,int>>> graph;
    map<string,int> h;
    string start, goal;

    readInput("inputAs.txt", h, graph, start, goal);

    Astar(graph, h, start, goal, "outputAs.txt");

    return 0;
}