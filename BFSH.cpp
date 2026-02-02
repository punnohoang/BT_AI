#include <bits/stdc++.h>
using namespace std;

void readInput(const string &filename, map<string, int> &h, map<string, vector<string>> &graph, string &start, string &goal){
	ifstream fin(filename);

	fin >> start >> goal;

	int n;
	fin >> n;
	fin.ignore();

	string line, u, v;
	int heuristic;

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

		while (ss >> v)
			graph[u].push_back(v);
	}

	fin.close();
}

void printListL(priority_queue<pair<int, string>, vector<pair<int, string>>, greater<pair<int, string>>> pq, ofstream &fout){
	while (!pq.empty())
	{
		fout << pq.top().second << "(" << pq.top().first << ")";
		pq.pop();
		if (!pq.empty())
			fout << ", ";
	}
}

void greedyBFS(map<string, vector<string>> &graph, map<string, int> &h, string start, string goal, const string &outputFile){
	ofstream fout(outputFile);

	priority_queue<
		pair<int, string>,
		vector<pair<int, string>>,
		greater<pair<int, string>>>
		L;

	set<string> visited;
	map<string, string> parent;

	parent[start] = "";

	fout << left
		 << setw(20) << "Phat trien TT"
		 << setw(35) << "Trang thai ke"
		 << "Danh sach L\n";
	fout << "-----------------------------------------------------------------------\n";

	L.push({h[start], start});
	fout << setw(20) << ""
		 << setw(35) << ""
		 << start << "(" << h[start] << ")" << "\n";

	while (!L.empty())
	{
		auto cur = L.top();
		L.pop();
		string u = cur.second;

		if (visited.count(u))
			continue;
		visited.insert(u);

		fout << setw(20) << (u + "(" + to_string(h[u]) + ")");

		if (u == goal)
		{
			fout << setw(35) << "TTKT-DUNG\n";
			break;
		}

		string ke = "";
		for (string v : graph[u])
		{
			if (!visited.count(v) && !parent.count(v))
			{
				parent[v] = u;
				ke += v + "(" + to_string(h[v]) + "), ";
				L.push({h[v], v});
			}
		}

		if (!ke.empty())
			ke.erase(ke.size() - 2);

		fout << setw(35) << ke;
		printListL(L, fout);
		fout << "\n";
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

int main(){
	map<string, vector<string>> graph;
	map<string, int> h;
	string start, goal;

	readInput("input.txt", h, graph, start, goal);
	greedyBFS(graph, h, start, goal, "output.txt");

	return 0;
}
