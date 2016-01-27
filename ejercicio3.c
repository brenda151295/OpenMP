#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

void count_sort (int a[], int n, int thread_count);
void print_v(int a[], int n);

int main(int argc, char* argv[])
{
    int thread_count = strtol(argv[1], NULL, 10); 
    int *a;     //array
    int n ;      //size of a
    int i;

    printf("Size of array: ");
    scanf("%d",&n);
    a = malloc(n*sizeof(int));
    printf("%d\n", n);
    printf("%s\n", "ARRAY: ");
    for (i = 0; i < n; i++)
        scanf("%d", &a[i]);
    
    print_v(a,n);
    count_sort(a,n,thread_count);
    print_v(a,n);

    return 0;
}


void count_sort(int a[], int n, int thread_count)
{
    int i, j, count;
    int *temp = malloc(n*sizeof(int));

    #pragma omp parallel for shared(a, n, temp) private(i, j, count) num_threads(thread_count)
    for (i = 0; i < n; i++) {
        count = 0;
        for (j = 0; j < n; j++)
            if (a[j] < a[i])
                count++;
            else if (a[j] == a[i] && j < i)
                count++;
        temp[count] = a[i];
    }

    #pragma omp parallel for shared(a, n, temp) private(i)
    //memcpy
    for (i = 0; i < n; i++)
        a[i] = temp[i];

    free(temp);
}

void print_v(int a[], int n)
{
    int i;
    for (i = 0; i < n; i++)
        printf("%d", a[i]);
    printf("%s\n", "");

}