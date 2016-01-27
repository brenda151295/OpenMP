#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

void Get_input(int* number_of_tosses);
float randNumGen(){

   int random_value = rand(); 
   float unit_random = random_value / (float) RAND_MAX; 
   return unit_random;
}

int main(int argc, char* argv[])
{
    int thread_count = strtol(argv[1], NULL, 10); 
    int number_of_tosses;
    int number_in_circle;
    long int divisions;

    double pi_estimate;
    
    divisions = number_of_tosses/thread_count;
    double x,y;
    int i;
    int count=0;
    double z;


    Get_input(&number_of_tosses);
    #pragma omp parallel firstprivate(x, y, z, i) reduction(+:count) num_threads(thread_count)
    {
        for (i=0; i<number_of_tosses; ++i)
        {
            x = randNumGen();
            y = randNumGen();
            z = ((x*x)+(y*y));
            if (z<=1)
            {
                ++count;
            }       
        }
    } 
    pi_estimate = ((double)count/(double)(number_of_tosses*thread_count))*4.0;
    printf("Pi: %f\n", pi_estimate);
    return 0;
}
void Get_input(int* number_of_tosses) {
  printf("Count: ");
  scanf("%d",number_of_tosses);
}