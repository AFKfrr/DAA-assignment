#include <stdio.h>

#include <limits.h>

#define MAX 100

#define INF 999999

// Global variables

int V, E;

int graph[MAX][MAX];

int hospitals[MAX];

int numHospitals;

10

// Function to find the nearest hospital using Dijkstra void dijkstra(int start, int dist[], int parent[]) {

int visited[MAX] = {0};

for (int i = 0; i < V; i++) {

dist[i] = INF;

parent[i] = -1;

}

dist[start] = 0;

for (int count = 0; count < V - 1; count++) {

int min = INF, u = -1;

// Find unvisited vertex with smallest distance

11

for (int i = 0; i < V; i++) {

if (!visited[i] && dist[i] < min) { min = dist[i]; u = i;

}

}

if (u == -1)

break;

visited[u] = 1;

// Relax edges

for (int v = 0; v < V; v++) {

if (!visited[v] && graph[u][v] != INF && dist[u] + graph[u][v] < dist[v]) {

12

dist[v] = dist[u] + graph[u][v];

parent[v] = u;

}

}

}

}

// Function to check if a node is a hospital

int isHospital(int node) {

for (int i = 0; i < numHospitals; i++)

if (hospitals[i] == node)

return 1;

return 0;

}

13

// Function to find nearest hospital

int findNearestHospital(int dist[]) {

int minDist = INF, nearest = -1;

for (int i = 0; i < numHospitals; i++) {

int h = hospitals[i];

if (dist[h] < minDist) { minDist = dist[h]; nearest = h;

}

}

return nearest;

}

// Function to print path

void printPath(int parent[], int dest) {

14

int path[MAX];

int count = 0;

int temp = dest; while (temp != -1) {

path[count++] = temp;

temp = parent[temp];

}

printf("Path: ");

for (int i = count - 1; i >= 0; i--)

printf("%d ", path[i]);

printf("\n");

}

15

int main() {

printf("Enter number of intersections (vertices): "); scanf("%d", &V);

for (int i = 0; i < V; i++)

for (int j = 0; j < V; j++)

graph[i][j] = INF;

printf("Enter number of roads (edges): "); scanf("%d", &E);

printf("Enter edges (u v travel_time):\n");

for (int i = 0; i < E; i++) {

int u, v, w; scanf("%d %d %d", &u, &v, &w);

16

graph[u][v] = graph[v][u] = w;

}

printf("Enter number of hospitals: "); scanf("%d", &numHospitals);

printf("Enter hospital locations:\n");

for (int i = 0; i < numHospitals; i++) scanf("%d", &hospitals[i]);

int start;

printf("Enter ambulance start location: "); scanf("%d", &start);

int dist[MAX], parent[MAX];

17

dijkstra(start, dist, parent);

int nearest = findNearestHospital(dist);

if (nearest == -1 || dist[nearest] == INF) {

printf("No hospital reachable.\n");

} else {

printf("\nInitial shortest travel time: %d\n", dist[nearest]);

printPath(parent, nearest);

}

// Update edge weight

int u, v, newWeight;

printf("\nEnter edge to update (u v newWeight): "); scanf("%d %d %d", &u, &v, &newWeight);

graph[u][v] = graph[v][u] = newWeight;

18

// Recalculate after update dijkstra(start, dist, parent); nearest = findNearestHospital(dist);

if (nearest == -1 || dist[nearest] == INF) {

printf("No hospital reachable after update.\n");

} else {

printf("\nAfter update shortest travel time: %d\n", dist[nearest]);

printPath(parent, nearest);

}

return 0;

}
