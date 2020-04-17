
#include <stdio.h>
#include <string.h>
#include <pthread.h>

#define ARRAY_COUNT(arr) (sizeof (arr) / sizeof *(arr))

typedef union {
    struct {    // Function parameters
        float *array;
        size_t size;
    };
    struct {    // Function return value
        float result;
    };
} arrayAverageParam_u;

void *arrayAverage(void *param) {
    arrayAverageParam_u *_param = param;
    // From now on we can use _param to access the struct

    int i;
    float avg = 0.0f;
    for(i = 0; i < _param->size; ++i)
        avg += _param->array[i];

    if(i)
        avg /= i;

    // Store the result, overwriting the parameters
    _param->result = avg;

    return NULL;
}

int main()
{
    float array[] = {97.5f, 98.5f, 65.5, 75.5f};

    // Fill the struct with parameters
    arrayAverageParam_u param = {
        .array = array,
        .size = ARRAY_COUNT(array),
    };

    pthread_t thread;
    pthread_create(&thread, NULL, arrayAverage, &param);

    pthread_join(thread, NULL);

    // Retrieve the result from the struct
    printf("The average of the marks  is %g\n", param.result);

    return 0;
}
