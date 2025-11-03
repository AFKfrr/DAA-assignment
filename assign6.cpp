#include <stdio.h>
#include <stdlib.h>
typedef struct {
int itemID;
int weight;
int utility;
int isPerishable;
} Item;
int max(int a, int b) {
return a > b ? a : b;
}
int knapsackBruteForce(Item* items, int n, int capacity, int index) {
if (index == n || capacity <= 0) return 0;
int skip = knapsackBruteForce(items, n, capacity, index + 1);
int take = 0;
if (items[index].weight <= capacity)
take = items[index].utility + knapsackBruteForce(items, n, capacity - items[index].weight, index + 1);
return max(take, skip);
}
void knapsackDP(Item* items, int n, int capacity, int* maxUtility, int* selectedItems, int* selectedCount) {
int i, w;
int** dp = (int**)malloc((n + 1) * sizeof(int*));
for (i = 0; i <= n; i++) dp[i] = (int*)calloc(capacity + 1, sizeof(int));

7

for (i = 1; i <= n; i++) {
for (w = 0; w <= capacity; w++) {
dp[i][w] = dp[i-1][w];
if (items[i-1].weight <= w)
dp[i][w] = max(dp[i][w], dp[i-1][w - items[i-1].weight] + items[i-1].utility);
}
}
*maxUtility = dp[n][capacity];
*selectedCount = 0;
w = capacity;
for (i = n; i > 0 && *maxUtility > 0; i--) {
if (*maxUtility != dp[i-1][w]) {
selectedItems[(*selectedCount)++] = items[i-1].itemID;
*maxUtility -= items[i-1].utility;
w -= items[i-1].weight;
}
}
for (i = 0; i <= n; i++) free(dp[i]);
free(dp);
}
int compareItems(const void* a, const void* b) {
Item* itemA = (Item*)a;
Item* itemB = (Item*)b;
double ratioA = (double)itemA->utility / itemA->weight;
double ratioB = (double)itemB->utility / itemB->weight;
return (ratioB > ratioA) - (ratioB < ratioA);
}
void greedyKnapsack(Item* items, int n, int capacity, int* totalUtility, int* selectedItems, int* selectedCount) {
qsort(items, n, sizeof(Item), compareItems);
int i, weight = 0;
*totalUtility = 0;
*selectedCount = 0;
for (i = 0; i < n; i++) {
if (weight + items[i].weight <= capacity) {
weight += items[i].weight;
*totalUtility += items[i].utility;
selectedItems[(*selectedCount)++] = items[i].itemID;
}
}
}
int main() {
int numItems, truckCapacity;
scanf("%d %d", &numItems, &truckCapacity);
Item* items = (Item*)malloc(numItems * sizeof(Item));

8

for (int i = 0; i < numItems; i++) {
int w, u, p;
scanf("%d %d %d", &w, &u, &p);
items[i].weight = w;
items[i].utility = u;
items[i].isPerishable = p;
items[i].itemID = i + 1;
if (p) items[i].utility = (int)(items[i].utility * 1.5);
}
int* selectedDP = (int*)malloc(numItems * sizeof(int));
int selectedCountDP, maxUtilityDP;
knapsackDP(items, numItems, truckCapacity, &maxUtilityDP, selectedDP, &selectedCountDP);
printf("%d\n", maxUtilityDP);
for (int i = selectedCountDP - 1; i >= 0; i--) printf("%d ", selectedDP[i]);
printf("\n");
if (numItems <= 20) {
int brute = knapsackBruteForce(items, numItems, truckCapacity, 0);
printf("%d\n", brute);
}
int* selectedGreedy = (int*)malloc(numItems * sizeof(int));
int selectedCountGreedy, approxUtility;
greedyKnapsack(items, numItems, truckCapacity, &approxUtility, selectedGreedy, &selectedCountGreedy);
printf("%d\n", approxUtility);
for (int i = 0; i < selectedCountGreedy; i++) printf("%d ", selectedGreedy[i]);
printf("\n");
free(items);
free(selectedDP);
free(selectedGreedy);
return 0;
}
