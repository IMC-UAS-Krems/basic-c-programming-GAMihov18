#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    // initialize random number generator
    srand(time(NULL));
    int minrand = 1;
    int maxrand = 100;
    size_t arraySize[2];

    if (argc != 3)
    {
        printf("Incorrect usage. You provided %d arguments. The correct number of arguments is 2\n", argc-1);
        return 1;
    }
    int converted;
    for (size_t i = 1; i < (size_t)argc; i++)
    {
        converted = atoi(argv[i]);
        if (converted<=0)
        {
            printf("Incorrect usage. The parameters you provided are not positive integers\n");
            return 1;
        }
        arraySize[i-1] = converted;
    }

    int **array = (int **)malloc(arraySize[0] * sizeof(int *));
    if (array == NULL)
    {
        printf("Memory allocation failed\n");
        return 1;
    }
    
    for (size_t i = 0; i < arraySize[0]; i++)
    {
        array[i] = (int *)malloc(arraySize[1] * sizeof(int));
        if (array[i] == NULL)
        {
            printf("Memory allocation failed\n");
            return 1;
        }
        for (size_t j = 0; j < arraySize[1]; j++)
        {
            array[i][j] = (rand() % (maxrand - minrand + 1)) + minrand;
        }
    }
    FILE *file = fopen("matrix.txt", "w");
    if (file == NULL) {
        printf("Error: Could not open file.\n");
        return 1;
    }
    for (size_t i = 0; i < arraySize[0]; i++)
    {
        for (size_t j = 0; j < arraySize[1]; j++)
        {
            fprintf(file, "%d ", array[i][j]);
        }
        fprintf(file, "\n");
        free(array[i]);
    }
    free(array);
    fclose(file);
    return 0;
}
