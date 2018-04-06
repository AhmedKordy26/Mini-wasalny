#include "shortest_path.h"
shortest_path::shortest_path()
{
	cunt = 0;
	id.clear();
	cities.clear();
	for (int i = 0; i < 10008; ++i) v_graph[i].clear();
}

void shortest_path::Input(int NumCities, int NumEdges, string ArrCities[], string Arrcity1[], string Arrcity2[], int ArrCost[])
{
	N_cities = NumCities, N_edges = NumEdges;
	for (int i = 0; i < NumCities; ++i)
	{
		cities[ArrCities[i]] = cunt;
		id[cunt] = ArrCities[i];
		cunt++;
	}
	for (int i = 0; i < NumEdges; ++i)
	{
		v_graph[cities[Arrcity1[i]]].push_back({ cities[Arrcity2[i]], ArrCost[i] });
		v_graph[cities[Arrcity2[i]]].push_back({ cities[Arrcity1[i]], ArrCost[i] });
	}
}

void shortest_path::TestShow()
{
	for (int c = 0; c < N_cities; c++)
	{
		cout << "****" << id[c] << "*****\n";
		for (auto u : v_graph[c])
		{
			cout << id[u.first] << " " << u.second << "\n";
		}
		cout << "--------------------------------\n";
	}
}
bool shortest_path::IsEdge(string City1, string City2)
{
	for (auto u : v_graph[cities[City1]])
	{
		if (id[u.first] == City2)
		{
			return true;
		}
	}
	return false;
}
int shortest_path::FindEdge(string City1, string City2, int cost)
{
	int z = 0;//position of City2 In The Vector Of City1
	bool found = 0;
	for (auto u : v_graph[cities[City1]])
	{
		if (id[u.first] == City2&&u.second == cost)
		{
			found = 1;
			break;
		}
		++z;
	}
	if (found)
		return z;
	else return -1;
}
void shortest_path::AddEdge(string city1, string city2, int cost)
{
	v_graph[cities[city1]].push_back({ cities[city2], cost });
	v_graph[cities[city2]].push_back({ cities[city1], cost });
}
void shortest_path::AddCity(string city)
{
	cities[city] = cunt;
	id[cunt] = city;
	++N_cities;
	cunt++;
}
void shortest_path::RemoveEdge(string city1, string city2, int cost)
{
	int Find = FindEdge(city1, city2, cost);
	if (Find != -1)
		v_graph[cities[city1]].erase(v_graph[cities[city1]].begin() + Find);
	Find = FindEdge(city2, city1, cost);
	if (Find != -1)
		v_graph[cities[city2]].erase(v_graph[cities[city2]].begin() + Find);
	return;
}

void shortest_path::UpdateCost(string city1, string city2, int old_cost, int new_cost)
{
	int Find = FindEdge(city1, city2, old_cost);
	// erasing The Old Cost between city1 and city2 
	v_graph[cities[city1]].erase(v_graph[cities[city1]].begin() + Find);
	//  Assigning the new cost from city1 to city2
	v_graph[cities[city1]].push_back({ cities[city2], new_cost });

	Find = FindEdge(city2, city1, old_cost);
	// erasing The Old Cost between city2 and city1
	v_graph[cities[city2]].erase(v_graph[cities[city2]].begin() + Find);
	//  Assigning the new cost from city1 to city2
	v_graph[cities[city2]].push_back({ cities[city1], new_cost });

	return;
}
void shortest_path::RemoveNode(string city)
{
	temp.clear();
	for (auto u : v_graph[cities[city]])
	{
		temp.push_back({ u.first, u.second });  
	}
	for (auto u:temp)
	{
		RemoveEdge(city, id[u.first], u.second);
	}
	int pos = cities[city];
	v_graph[pos].clear();
	id.erase(pos);
	cities.erase(city);
}

void shortest_path::dijkstra(int source, int distenation)
{
	int e[10008] = {}, par[10008] = {};
	bool vis[10008] = {};
	bool found = false;
	for (int i = 0; i <= 10000; ++i) e[i] = 10000000;
	e[source] = 0;
	pq.push({ e[source], source });
	while (!pq.empty())
	{
		int a = pq.top().second;
		pq.pop();
		if (a == distenation) { found = true; }
		if (vis[a]) continue;
		vis[a] = true;
		for (auto u : v_graph[a])
		{
			if (e[a] + u.second < e[u.first])
			{
				e[u.first] = e[a] + u.second;
				pq.push({ -1 * e[u.first], u.first });
				par[u.first] = a;
			}
		}
	}
	show_path(found, distenation, e, source, par);
}
void shortest_path::spfa(int source, int distenation)
{
	int e[10008] = {}, par[10008] = {};
	bool vis[10008] = {};
	bool found = false;
	for (int i = 0; i <= 10000; ++i) e[i] = 100000000;
	e[source] = 0;
	q.push(source);
	while (!q.empty())
	{
		int a = q.front();
		q.pop();
		if (a == distenation) { found = true; }
		vis[a] = false;
		for (auto u : v_graph[a])
		{
			if (e[a] + u.second < e[u.first])
			{
				e[u.first] = (e[a] + u.second);
				if (!vis[u.first]) {
					vis[u.first] = true;
					q.push(u.first);
				}
				par[u.first] = a;
			}
		}
	}
	show_path(found, distenation, e, source, par);
}

void shortest_path::show_path(bool found, int distenation, int* e, int source, int* par)
{
	if (!found) { cout << "there is no path between these two cities\n"; return; }
	cout << "the cost is equal = " << e[distenation] << "\n";
	vector<string>path;
	int d = distenation;
	while (true)
	{
		path.push_back(id[d]);
		d = par[d];
		if (d == source) break;
	}
	if (source != distenation)
		path.push_back(id[source]);
	cout << "the number of cities which you will path throw them to reach to city (" << id[distenation] << ") from (" << id[source] << ") is:\n";
	cout << path.size() << "\nthe shortest path is :\n";
	reverse(path.begin(), path.end());
	for (auto u : path) cout << u << " ";
	cout << "\n";
	path.clear();
}
void shortest_path::belman_ford(int source, int distenation)
{
	int e[10008] = {}, par[10008] = {};//e = edges ,
	bool vis[10008] = {};
	bool found = false;
	for (int i = 0; i <= 10000; ++i) e[i] = 100000000;
	e[source] = 0;
	for (int i = 1; i <= N_cities - 1; ++i)
	{
		for (int a = 0; a <= 10000; ++a)
		{
			if (id.count(a))
			{
				for (auto u : v_graph[a])
				{
					if (a == distenation) found = true;
					if (e[a] + u.second < e[u.first])
					{
						e[u.first] = e[a] + u.second;
						par[u.first] = a;
					}
				}
			}
		}
	}
	show_path(found, distenation, e, source, par);
}
void shortest_path::algos(string source,string distination,int numalgo)
{
	int so = cities[source], di = cities[distination];
	if (numalgo == 1)
	{
		cout << "Dijkstra : \n";
		dijkstra(so, di);
		cout << "\n";
	}
	else if (numalgo == 2)
	{
		cout << "Shortest Path Fast Algorithm : \n";
		spfa(so, di);
		cout << "\n";
	}
	else if (numalgo == 3)
	{
		cout << "Bellman ford : \n";
		belman_ford(so, di);
		cout << "\n";
	}
	else if (numalgo == 4)
	{
		cout << "Floyed Warshall : \n";
		Floyed_Warchall(so, di);
		cout << "\n";
	}
	else if (numalgo == 5)
	{
		for (int i = 1; i <= 4; i++)
			algos(source, distination, i);
	}
	return;
}
void shortest_path::fill_matrix()
{
	for (int i = 0; i < N_cities; i++) // initializing the adjacency matrix with infinity except the self edges
	{
		for (int j = 0; j < N_cities; j++)
		{
			Floyd_Arr[i][j] = -1;          // Floyd_Arr Is used In Printing The Path
			if (i == j)adj_matrix[i][j] = 0;
			else
				adj_matrix[i][j] = oo;
		}
	}
	for (int i = 0; i < N_cities; i++)// filling up the adjacency matrix
	{
		for (int j = 0; j < (int)v_graph[i].size(); j++)
		{
			//if (adj_matrix[i][v_graph[i][j].first]>v_graph[i][j].second)
			if (v_graph[i][j].second < adj_matrix[i][v_graph[i][j].first])//Assigning The Least Value
			adj_matrix[i][v_graph[i][j].first] = v_graph[i][j].second;
		}
	}
}
void shortest_path::Print_Floyd_Path(int Source, int Distination)
{
	if (Floyd_Arr[Source][Distination] == -1)
	{
		cout << id[Source] << " " << id[Distination] << "\n";
		return;
	}
	Print_Floyd_Path(Source, Floyd_Arr[Source][Distination]); 
	Print_Floyd_Path(Floyd_Arr[Source][Distination], Distination);
}
void shortest_path::Floyed_Warchall(int i, int j)
{
	// The Algorithm works on connected Graphs
	fill_matrix();
	for (int i = 0; i < N_cities; i++) // k Will Act As Intermediate node
	for (int j = 0; j < N_cities; j++)// i And j Traverse The Adjacency matrix
	for (int k = 0; k < N_cities; k++)
	{
		if (!id.count(i) || !id.count(j) || !id.count(k))continue; 
		if (adj_matrix[i][k] + adj_matrix[k][j] < adj_matrix[i][j])
		{
			adj_matrix[i][j] = adj_matrix[i][k] + adj_matrix[k][j];
			Floyd_Arr[i][j] = k;  // This Arr is For Printing The Path
		}
	}
	if (adj_matrix[i][j] == oo)
	{
		cout << "There's No Path Between " << id[i] << " And " << id[j] << "\n"; return;
	}
	cout << "The Cost Between " << id[i] << " And " << id[j] << " is " << adj_matrix[i][j] << "\n";
	Print_Floyd_Path(i, j);
}
void shortest_path::Show_All_Paths()
{
	bool callfloyd = 0;
	for (int i = 0; i < N_cities; i++)
	{
		for (int j = 0; j < N_cities; j++)
		{
			cout << "Between " << id[i] << " And " << id[j] << " : \n";
			if (i == j){ cout << "The Path Is " << id[i] << " With Cost 0\n\n"; continue; }
		    if (!callfloyd)
			{
				Floyed_Warchall(i, j); callfloyd = 1;
			}
			else if (callfloyd)
			{
				if (adj_matrix[i][j] == oo)
				{
					cout << "There's No Path Between " << id[i] << " And " << id[j] << "\n";
				}
				else
				{
					Print_Floyd_Path(i, j);
					cout << "With Cost " << adj_matrix[i][j] << "\n";
				}
			}
			cout << "\n\n";
		}
	}
}
shortest_path::~shortest_path()
{
	cunt = 0;
	id.clear();
	cities.clear();
	for (int i = 0; i < 10008; ++i) v_graph[i].clear();
}

/*
void shortest_path::kruskal(int source, int distenation)
{
struct union_find
{
vector<int>par, id;
union_find(int n)
{
par.resize(n + 5), id.resize(n + 5, 0);
for (int i = 0; i <= n; ++i) par[i] = i;
}
int root(int x)
{
if (par[x] == x) return x;
return par[x] = root(par[x]);
}
void link(int x, int y)
{
if (id[x] > id[y]) swap(x, y);
par[x] = y;
if (id[x] == id[y]) ++id[y];
}
bool union_set(int x, int y)
{
x = root(x), y = root(y);
if (x != y)
{
link(x, y);
}
return (x != y);
}
};
vector<pair<int, pair<int, int>>>graph;
vector<pair<int, int>>cur_graph[10005];
for (int i = 0; i < 10000; ++i)
{
cur_graph[i].clear();
for (auto u : v_graph[i])
graph.push_back({ u.second, { i, u.first } });
}
sort(graph.begin(), graph.end());
bool found1 = false, found2 = false;
union_find copy(graph.size());
for (auto k : graph)
{
if (!copy.union_set(k.second.first, k.second.second))
{
if (k.second.first == source || k.second.second == source) found1 = true;
if (k.second.first == distenation || k.second.second == distenation) found2 = true;
cur_graph[k.second.first].push_back({ k.second.second, k.first });
cur_graph[k.second.second].push_back({ k.second.first, k.first });
}
}
if (!found1 || !found2)
{
cout << "there is no path between these two cities\n\n";
return;
}
bool vis[10008] = {};
int e[10008] = {}, parent[100008] = {};
q.push(source);
e[source] = 0;
vis[source] = true;
while (!q.empty())
{
int a = q.front();
q.pop();
for (auto u : cur_graph[a])
{
if (vis[u.first]) continue;
vis[u.first] = true;
e[u.first] = (e[a] + u.second);
parent[u.first] = a;
q.push(u.first);
}
}
show_path(true, distenation, e, source, parent);
graph.clear();
}
*/