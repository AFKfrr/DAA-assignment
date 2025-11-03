#include <stdio.h>
#include <string.h>

#define MAX_ITEMS 10

struct Item {
char name[50];
double weight;
double value;

8

int priority;
int divisible;
double ratio; // value/weight
double eff_ratio; // (value/weight)/priority
};

// Sort items by effective ratio (descending)
void sortItems(struct Item items[], int n) {
for (int i = 0; i < n - 1; i++) {
for (int j = 0; j < n - i - 1; j++) {
if (items[j].eff_ratio < items[j + 1].eff_ratio) {
struct Item temp = items[j];
items[j] = items[j + 1];
items[j + 1] = temp;
}
}
}
}

int main() {
double capacity;
printf("Enter boat capacity (kg): ");
scanf("%lf", &capacity);

struct Item items[MAX_ITEMS] = {
{"Rescue_Radio", 3.0, 100, 1, 0, 0, 0},

9

{"Medical_Supplies", 5.0, 150, 2, 1, 0, 0}, {"Canned_Food", 4.0, 60, 3, 1, 0, 0}, {"Bedding", 6.0, 70, 4, 0, 0, 0}, {"Fuel_Canister", 8.0, 200, 2, 1, 0, 0}
};
int n = 5;

// Compute ratios
for (int i = 0; i < n; i++) {
items[i].ratio = items[i].value / items[i].weight;
items[i].eff_ratio = items[i].ratio / items[i].priority;
}

// Sort by effective ratio descending
sortItems(items, n);

printf("\nItems sorted by (value/weight)/priority:\n");
printf("%-18s %-8s %-8s %-10s %-14s %-14s %-10s\n", "Item", "Weight", "Value", "Priority", "Val/Wt", "Eff_Ratio", "Type");
printf("--------------------------------------------------------------------------\n");

for (int i = 0; i < n; i++) {
printf("%-18s %-8.2f %-8.2f %-10d %-14.2f %-14.2f %-10s\n", items[i].name, items[i].weight, items[i].value, items[i].priority, items[i].ratio, items[i].eff_ratio, items[i].divisible ? "Divisible" : "Fixed");

10

}

// Greedy selection
double totalValue = 0, totalWeight = 0;
printf("\nSelected items:\n");
printf("------------------------------------------------------\n");

for (int i = 0; i < n && capacity > 0; i++) {
double take = 0;
double valueTaken = 0;

if (items[i].weight <= capacity) {
take = items[i].weight;
valueTaken = items[i].value;
} else if (items[i].divisible) {
take = capacity;
valueTaken = items[i].ratio * take;
} else {
continue;
}

capacity -= take;
totalWeight += take;
totalValue += valueTaken;

printf("- %s: %.2f kg (Value: %.2f)\n", items[i].name, take, valueTaken);

11

}

printf("\n===== Summary Report =====\n");
printf("Total weight carried: %.2f kg\n", totalWeight);
printf("Total utility value carried: %.2f units\n", totalValue);

return 0;
}
