#include <stdio.h>
#include <string.h>
#define MAX 100
#define TITLE_LEN 100
// Structure to store movie details
struct Movie {
char title[TITLE_LEN];
double imdb_rating;
int release_year;
int watch_time_popularity;
};
// Swap two movies
void swap(struct Movie *a, struct Movie *b) {
struct Movie temp = *a; *a = *b; *b = temp;
}
// Partition function for quicksort
int partition(struct Movie movies[], int low, int high, char sort_param[]) {
struct Movie pivot = movies[high];
int i = low - 1;
for (int j = low; j < high; j++) {
int condition = 0;
// Choose comparison based on sort parameter
if (strcmp(sort_param, "IMDB_Rating") == 0) {
if (movies[j].imdb_rating > pivot.imdb_rating)
condition = 1;
} else if (strcmp(sort_param, "Release_Year") == 0) {
if (movies[j].release_year > pivot.release_year)
condition = 1;
} else if (strcmp(sort_param, "Watch_Time_Popularity") == 0) {

if (movies[j].watch_time_popularity > pivot.watch_time_popularity)
condition = 1;
}
if (condition) {
i++;
swap(&movies[i], &movies[j]);
}
}
swap(&movies[i + 1], &movies[high]);
return i + 1;
}
// Quicksort function
void quickSort(struct Movie movies[], int low, int high, char sort_param[]) {
if (low < high) {
int pi = partition(movies, low, high, sort_param);
quickSort(movies, low, pi - 1, sort_param);
quickSort(movies, pi + 1, high, sort_param);
}
}
int main() {
int n;
struct Movie movies[MAX];
char sort_param[30];
printf("Enter number of movies: ");
scanf("%d", &n);
printf("Enter movie details (Title IMDB_Rating Release_Year Watch_Time_Popularity):\n");
for (int i = 0; i < n; i++) {
scanf("%s %lf %d %d", movies[i].title, &movies[i].imdb_rating, &movies[i].release_year, &movies[i].watch_time_popularity);
}
printf("Enter sort parameter (IMDB_Rating / Release_Year / Watch_Time_Popularity): ");
scanf("%s", sort_param);
quickSort(movies, 0, n - 1, sort_param);

printf("\nSorted Movies (%s descending):\n", sort_param);
for (int i = 0; i < n; i++) {
printf("%s %.1f %d %d\n", movies[i].title, movies[i].imdb_rating, movies[i].release_year, movies[i].watch_time_popularity);
}
return 0;
}
