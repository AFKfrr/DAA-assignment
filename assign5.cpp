#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>
#define MAXN 100
#define INF 1e9
typedef struct {
int to;
double base_cost;
double current_cost;
} Edge;
typedef struct {
Edge edges[MAXN];
int edge_count;
} Node;
Node graph[MAXN];
int reverse_adj[MAXN][MAXN];
int reverse_count[MAXN];
double min_cost[MAXN];
int next_hop[MAXN];
int stage_start[MAXN];
int nodes_per_stage[MAXN];
int total_nodes, num_stages;
// Recompute cost for one node
double recompute(int u) {
double best = INF;
int best_node = -1;
for (int i = 0; i < graph[u].edge_count; i++) {
int v = graph[u].edges[i].to;

double cost = graph[u].edges[i].current_cost + min_cost[v];
if (cost < best) {
best = cost;
best_node = v;
}
}
next_hop[u] = best_node;
return best;
}
int main() {
printf("Enter number of stages: ");
scanf("%d", &num_stages);
total_nodes = 0;
printf("Enter number of nodes in each stage (%d values): ", num_stages);
for (int i = 0; i < num_stages; i++) {
scanf("%d", &nodes_per_stage[i]);
stage_start[i] = total_nodes;
total_nodes += nodes_per_stage[i];
}
// Initialize graph
for (int i = 0; i < total_nodes; i++) {
graph[i].edge_count = 0;
reverse_count[i] = 0;
}
int E;
printf("Enter number of edges: ");
scanf("%d", &E);
printf("Enter edges (u v cost):\n");
for (int i = 0; i < E; i++) {
int u, v;
double cost;
scanf("%d %d %lf", &u, &v, &cost);
graph[u].edges[graph[u].edge_count].to = v;
graph[u].edges[graph[u].edge_count].base_cost = cost;
graph[u].edges[graph[u].edge_count].current_cost = cost;
graph[u].edge_count++;
reverse_adj[v][reverse_count[v]++] = u;
}
// Initialize DP
for (int i = 0; i < total_nodes; i++) {
min_cost[i] = INF;

next_hop[i] = -1;
}
int last_stage = num_stages - 1;
for (int k = 0; k < nodes_per_stage[last_stage]; k++) {
int node = stage_start[last_stage] + k;
min_cost[node] = 0.0;
}
// Backward DP from last stage
for (int stage = num_stages - 2; stage >= 0; stage--) {
for (int k = 0; k < nodes_per_stage[stage]; k++) {
int u = stage_start[stage] + k;
min_cost[u] = recompute(u);
}
}
printf("\n--- Optimal Costs from Stage 0 ---\n");
for (int k = 0; k < nodes_per_stage[0]; k++) {
int u = stage_start[0] + k;
if (min_cost[u] >= INF / 2)
printf("Node %d: unreachable\n", u);
else
printf("Node %d: cost = %.3lf\n", u, min_cost[u]);
}
// Path reconstruction
int source;
printf("\nEnter a source node ID (in stage 0) to print path (-1 to skip): ");
scanf("%d", &source);
if (source >= 0 && source < total_nodes) {
if (min_cost[source] >= INF / 2) {
printf("No route from node %d.\n", source);
} else {
printf("Path: ");
int current = source;
double total = 0;
while (current != -1) {
printf("%d", current);
int next = next_hop[current];
if (next == -1) break;
// Add edge cost
double edge_cost = 0;
for (int i = 0; i < graph[current].edge_count; i++) {
if (graph[current].edges[i].to == next) {

edge_cost = graph[current].edges[i].current_cost;
break;
}
}
total += edge_cost;
printf(" -> ");
current = next;
}
printf("\nTotal cost: %.3lf\n", total);
}
}
// Live updates
int updates;
printf("\nEnter number of live updates: ");
scanf("%d", &updates);
while (updates-- > 0) {
int u, v;
double mult;
printf("Enter update (u v multiplier): ");
scanf("%d %d %lf", &u, &v, &mult);
// Update edge cost
for (int i = 0; i < graph[u].edge_count; i++) {
if (graph[u].edges[i].to == v) {
graph[u].edges[i].current_cost = graph[u].edges[i].base_cost * mult;
}
}
// Recompute affected nodes
double new_cost = recompute(u);
if (fabs(new_cost - min_cost[u]) > 1e-6) {
min_cost[u] = new_cost;
// Propagate backward
int queue[MAXN], front = 0, rear = 0;
queue[rear++] = u;
while (front < rear) {
int node = queue[front++];
for (int i = 0; i < reverse_count[node]; i++) {
int pred = reverse_adj[node][i];
double updated = recompute(pred);
if (fabs(updated - min_cost[pred]) > 1e-6) {
min_cost[pred] = updated;
queue[rear++] = pred;
}

}
}
}
}
printf("\n--- Updated Optimal Costs ---\n");
for (int k = 0; k < nodes_per_stage[0]; k++) {
int u = stage_start[0] + k;
if (min_cost[u] >= INF / 2)
printf("Node %d: unreachable\n", u);
else
printf("Node %d: cost = %.3lf\n", u, min_cost[u]);
}
return 0;
}
