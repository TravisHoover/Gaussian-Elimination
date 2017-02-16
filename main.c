
#include <stdio.h>
#include <pthread.h>

int size;
float A[10][10];
float B[10];
float mult;

pthread_mutex_t lock;

struct thread_arg {
    int id;
    float div;
};

void *calculate(void *arg) {
    struct thread_arg * input = arg;
    int id = input->id;
    float div = input->div;

        pthread_mutex_lock(&lock);
        for(int i = 0; i < size; i++) {
            A[id][i] /= div;
        }
        B[id] /= div;

        for(int j = 0; j < size; j++) {
            if(j != id) {
                mult = A[j][id];
                for(int k = 0; k < size; k++) {
                    A[j][k] -= mult * A[id][k];
                }
                B[j] -= mult * B[id];
            }
        }
        pthread_mutex_unlock(&lock);

    printf("%.6f \n", B[id]);

    return 0;
};

int main()
{

//************* Program Input ************************
    printf( "\nInput the number of items: ");       //
    scanf("%d", &size);                             //
                                                    //
    printf ("\nInput matrix A: \n");                //
    for(int i = 0; i < size; i++)                   //
        for(int j = 0; j < size; j++)               //
            scanf("%f", &A[i][j]);                  //
                                                    //
    printf ("\nInput matrix B: \n");                //
    for(int i = 0; i < size; i++)                   //
        scanf("%f", &B[i]);                         //
//****************************************************

    struct thread_arg args[size];
    pthread_t thread[size];

    printf( "\nThe X values are: \n");
    for(int i = 0; i < size; i++) {
        args[i].id = i;
        args[i].div = A[i][i];
        pthread_create(&thread[i], NULL, &calculate, &args[i]);
        pthread_join(thread[i], NULL);
    }
    return 0;
}
