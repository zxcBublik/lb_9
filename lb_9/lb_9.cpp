#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <iostream>
#include <vector>
#include <time.h>
#include <queue>
using namespace std;
struct node {
	int index;
	struct node* next_node;
};
struct Graph {
	vector<node*>vertexes;
};
void BFS_list(Graph* G, int start);
vector<int> BFS(vector<vector<int>>& M, int start);
void print_G(Graph* G);
void add_el(struct Graph* G, int vertex, int new_index);
void DFS_recurs_matrix(vector<vector<int>>& M, vector<int>& visited, int count, int depth);
void DFS_recurs_list(struct Graph* G, vector<int>& visited, int count, int depth);

int main()
{
	srand(time(0));
	clock_t start, end;
	setlocale(LC_ALL, "Russian");
	Graph G;
	int sizeM = 0, number = 0;
	cout << "Введите количество вершин у графа:\n";
	cin >> sizeM;
	G.vertexes.resize(sizeM, nullptr);
	cout << "Матрица смежности:\n";
	vector <vector<int>> M(sizeM, vector<int>(sizeM, 0));
	for (int i = 0; i < sizeM; i++) {
		for (int j = i; j < sizeM; j++) {
			if (i == j) {
				M[i][j] = 0;
			}
			else {
				M[i][j] = rand() % 2;
				M[j][i] = M[i][j];
			}
		}
		for (int j = 0; j < sizeM; j++) {
			printf("%3d ", M[i][j]);
			if (M[i][j]) {
				if (i == j) {
					continue;
				}
				add_el(&G, i, j);
			}
		}
		cout << '\n';
	}
	cout << "Список смежности:\n";
	print_G(&G);

	cout << "Введите номер вершины:\n";
	cin >> number;
	number--;



	cout << "Поиск расстояний в графе через обход в ширину:\n";

	cout << "Для матрицы:\n";
	start = clock();
	BFS(M, number);
	end = clock();
	double time_spend = (double)(end - start) / CLOCKS_PER_SEC;
	cout << "Время работы: " << time_spend << "\n";

	cout << "Для списка смежности:\n";
	start = clock();
	BFS_list(&G, number);
	end = clock();
	time_spend = (double)(end - start) / CLOCKS_PER_SEC;
	cout << "\nВремя работы: " << time_spend << "\n\n";



	cout << "Поиск расстояний в графе используя обход в глубину:\n";

	cout << "Для матрицы:\n";
	vector<int> visited(sizeM, -1);
	start = clock();
	DFS_recurs_matrix(M, visited, number, 0);
	end = clock();

	cout << "Расстояния от вершины " << number + 1 << ":\n";
	for (int i = 0; i < sizeM; i++) {
		cout << "До " << i + 1 << ": " << visited[i] << '\n';
	}

	time_spend = (double)(end - start) / CLOCKS_PER_SEC;
	cout << "Время работы: " << time_spend << '\n';

	cout << "Для списка:\n";
	visited.assign(sizeM, -1);
	start = clock();
	DFS_recurs_list(&G, visited, number, 0);
	end = clock();

	cout << "Расстояния от вершины " << number + 1 << ":\n";
	for (int i = 0; i < G.vertexes.size(); i++) {
		cout << "До " << i + 1 << ": " << visited[i] << '\n';
	}

	time_spend = (double)(end - start) / CLOCKS_PER_SEC;
	cout << "\nВремя работы: " << time_spend << '\n';

	cout << "\n\n\nМассив расстояний:\n";
	vector<vector<int>> tmp_arr(M.size(), vector<int>(M.size(), 0));
	for (int i = 0; i < M.size(); i++) {
		tmp_arr[i] =  (BFS(M, i));
		for (int j = 0; j < M.size(); j++) {
			printf("%2d", tmp_arr[i][j]);
		}
		cout << '\n';
	}
}

vector<int> BFS(vector<vector<int>>& M, int start) {
	vector<int> visited(M.size(), -1);
	queue<int> q;

	q.push(start);
	visited[start] = 0;

	while (!q.empty()) {
		int current = q.front();
		q.pop();

		for (int i = 0; i < M.size(); i++) {
			if (M[current][i] == 1 && visited[i] == -1) {
				visited[i] = visited[current] + 1;
				q.push(i);
			}
		}
	}
	/*cout << "Расстояние от вершины " << start + 1 << ":\n";
	for (int i = 0; i < M.size(); i++)
		cout << "До " << i + 1 << ": " << visited[i] << '\n';*/
	return visited;
}

void BFS_list(Graph* G, int start) {
	vector<int> visited(G->vertexes.size(), -1);
	queue<int> q;

	q.push(start);
	visited[start] = 0;

	while (!q.empty()) {
		int current = q.front();
		q.pop();
		node* tmp = G->vertexes[current];
		while (tmp != nullptr) {
			if (visited[tmp->index] == -1) {
				visited[tmp->index] = visited[current] + 1;
				q.push(tmp->index);
			}
			tmp = tmp->next_node;
		}
	}
	cout << "Расстояние от вершины " << start + 1 << ":\n";
	for (int i = 0; i < G->vertexes.size(); i++) {
		cout << "До " << i + 1 << ": " << visited[i] << '\n';
	}
}

void DFS_recurs_matrix(vector<vector<int>>& M, vector<int>& visited, int current, int depth) {
	visited[current] = depth;
	for (int i = 0; i < M.size(); i++) {
		if (M[current][i] && (visited[i] == -1 || depth < visited[i]) ) {
			DFS_recurs_matrix(M, visited, i, depth+1);
		}
	}
}

void DFS_recurs_list(struct Graph* G, vector<int>& visited, int current, int depth) {
	visited[current] = depth;
	node* tmp = G->vertexes[current];
	while (tmp != nullptr) {
		if (visited[tmp->index] == -1 || depth < visited[tmp->index]) {
			DFS_recurs_list(G, visited, tmp->index, depth + 1);
		}
		tmp = tmp->next_node;
	}
}

void add_el(struct Graph* G, int vertex, int new_index) {
	node* p = (node*)malloc(sizeof(node));
	p->index = new_index;
	if (G->vertexes[vertex] == nullptr) {
		G->vertexes[vertex] = p;
		p->next_node = nullptr;
	}
	else {
		node* tmp = G->vertexes[vertex];
		while (tmp->next_node != nullptr) {	
			tmp = tmp->next_node;
		}
		tmp->next_node = p;
		p->next_node = nullptr;
	}
}

void print_G(Graph* G) {
	for (int i = 0; i < G->vertexes.size(); i++) {
		node* tmp = G->vertexes[i];
		cout << "Вершина " << i + 1 << ": ";
		while (tmp != nullptr) {
			cout << tmp->index + 1 << " ";
			tmp = tmp->next_node;
		}
		cout << '\n';
	}
}