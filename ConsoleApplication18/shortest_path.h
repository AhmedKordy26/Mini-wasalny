#include "Header.h"
#pragma once
class shortest_path
{
	int cunt;
	unordered_map<int, string>id;
	unordered_map<string, int>cities;
	vector<pair<int, int>>v_graph[10018];
	vector<pair<int, int>>temp;
	vector<pair<int, int>>::iterator it;
	vector<pair<int, int>>::iterator it2;
	queue<int>q;
	priority_queue<pair<int, int>>pq;
	int cost, cost1, cost2;
	int N_cities, N_edges;
	int adj_matrix[MAXSIZE][MAXSIZE];
	int Floyd_Arr[MAXSIZE][MAXSIZE];
public:
	shortest_path();
	void Input(int, int, string[], string[], string[], int[]);
	void show_path(bool, int, int*, int, int*);
	int FindEdge(string, string, int);
	bool IsEdge(string, string);
	void AddEdge(string, string, int);
	void AddCity(string);
	void RemoveEdge(string, string, int);
	void update_map();
	void TestShow();
	void UpdateCost(string, string, int, int);
	void RemoveNode(string);
	void algos(string ,string ,int);
	//void kruskal(int ,int);
	void dijkstra(int, int);
	void spfa(int, int);
	void belman_ford(int, int);
	void fill_matrix();
	void Print_Floyd_Path(int Source, int Distination);
	void Floyed_Warchall(int i, int j);
	void Show_All_Paths();
	~shortest_path();
};
