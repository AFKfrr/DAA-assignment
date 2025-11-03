#include <stdio.h>
#include <string.h>

#define MAX_STR_LEN 25
#define MAX_SIZE 100
// Function to merge two sorted halves
void merge(char arr[][MAX_STR_LEN], int left, int mid, int right) {
char temp[MAX_SIZE][MAX_STR_LEN];
int i = left, j = mid + 1, k = 0;
while (i <= mid && j <= right) {
if (strcmp(arr[i], arr[j]) <= 0) {
strcpy(temp[k++], arr[i++]);
} else {
strcpy(temp[k++], arr[j++]);
}
}
while (i <= mid)
strcpy(temp[k++], arr[i++]);
while (j <= right)
strcpy(temp[k++], arr[j++]);
for (i = 0; i < k; i++)
strcpy(arr[left + i], temp[i]);
}
// Recursive merge sort function
void mergeSort(char arr[][MAX_STR_LEN], int left, int right) {
if (left >= right) return;
int mid = (left + right) / 2;
mergeSort(arr, left, mid);
mergeSort(arr, mid + 1, right);
merge(arr, left, mid, right);
}
int main() {
char timestamps[][MAX_STR_LEN] = { "2025-10-13 18:30:00", "2024-05-10 12:00:00", "2025-01-01 09:15:00", "2025-10-13 07:45:00"
};
int n = 4;

mergeSort(timestamps, 0, n - 1);
printf("Sorted timestamps:\n");
for (int i = 0; i < n; i++) {
printf("%s\n", timestamps[i]);
}
return 0;
}
