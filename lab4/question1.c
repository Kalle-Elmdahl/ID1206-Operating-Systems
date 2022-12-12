#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#define CYLINDER 5000
#define REQUESTS 1000

int fcfs(int *arrayOfrequest, int start);
int sstf(int *arrayOfrequest, int start);
int scan(int *arrayOfrequest, int start);
int cscan(int *arrayOfrequest, int start);
int look(int *arrayOfrequest, int start);
int clook(int *arrayOfrequest, int start);

int arrayOfrequest[REQUESTS];

int main(int argc, char const *argv[])
{
    int start = atoi(argv[1]);
    srand(start);
    for (int i = 0; i < REQUESTS; i++)
    {
        arrayOfrequest[i] = rand() % CYLINDER;
    }

    printf("*TESTING FCFS*\n");
    printf("Head movements: %d\n\n", fcfs(arrayOfrequest, start));


    printf("*TESTING SSTF*\n");
    printf("Head movements: %d\n\n", sstf(arrayOfrequest, start));
    
    printf("*TESTING SCAN*\n");
    printf("Head movements: %d\n\n", scan(arrayOfrequest, start));
    //  printf("C-SCAN: %d\n", fcfs(arrayOfrequest, start));
    //  printf("LOOK: %d\n", fcfs(arrayOfrequest, start));
    //  printf("C-LOOK: %d\n", fcfs(arrayOfrequest, start));

    return 0;
}


int fcfs(int *arrayOfrequest, int start)
{
    int result = 0;
    for (int i = 0, current_position = start; i < REQUESTS; current_position = arrayOfrequest[i++])
    {
        result += abs(current_position - arrayOfrequest[i]);
    }
    return result;
}

int comp(const void *elem1, const void *elem2)
{
    int f = *((int *)elem1);
    int s = *((int *)elem2);
    if (f > s)
        return 1;
    if (f < s)
        return -1;
    return 0;
}

void printlog(int adj, int start, int * arr) {
    printf("adj-index: %d, start: %d, {adj-1: %d, adj: %d, adj+1: %d} \n", adj, start, arr[adj - 1], arr[adj], arr[adj + 1]);
}

/**
 * Shortest Seek Time First
 */
int sstf(int *arrayOfrequest, int start)
{

    // Initialize result and adj to 0
    int result = 0;
    int adj = 0;

    // Create a copy of the array of requests and sort it in ascending order
    int *sortedArray = malloc(REQUESTS * sizeof(int));
    memcpy(sortedArray, arrayOfrequest, REQUESTS * sizeof(int));
    qsort(sortedArray, REQUESTS, sizeof(*arrayOfrequest), comp);

    // Find the first request in the sorted array that is closer to the starting 
    // position than the previous request
    while (abs(sortedArray[adj + 1] - start) <= abs(sortedArray[adj] - start)) {
        adj++;
    }

    // Print some debugging information
    printlog(adj, start, sortedArray);

    // Initialize variables for processing requests
    int curr_val = sortedArray[adj];
    int left_pos = adj-1, right_pos = adj+1;

    // Add distance from starting position to first request
    result += abs(sortedArray[adj] - start);

    // Process requests until we have processed all requests
    int requests_processed = 0;

    while (left_pos >= 0 && right_pos < REQUESTS - 1)
    {
        // Calculate distances to requests to the left and right of the current request
        int dl = left_pos > 0 ? abs(sortedArray[left_pos - 1] - curr_val) : INFINITY;
        int dr = right_pos < (REQUESTS - 1) ? abs(sortedArray[right_pos + 1] - curr_val) : INFINITY;
        

        // Move to the request that is closer, and update variables accordingly
        if (dl < dr)
        {
            result += dl;
            left_pos--;
            curr_val = sortedArray[left_pos];
        }
        else
        {
            result += dr;
            right_pos++;
            curr_val = sortedArray[right_pos];
        }

        requests_processed ++;
    }


    // Return the total distance the disk head moved
    return result;
}


int calculateDirection(int *sortedArray, int start, int adj)
{
    if (sortedArray[adj] < start)
    { // direction left
        return 0;
    }
    else if (sortedArray[adj] > start)
    { // direction right
        printf("%d är mer än %d", sortedArray[adj], start);
        return 1;
    }
    else
    {
        int newAdj = 0;
        while (abs(sortedArray[adj + 1] - start) <= abs(sortedArray[adj] - start))
        newAdj++;
        return calculateDirection(sortedArray, adj, newAdj);
    }
}

int scan(int *arrayOfrequest, int start)
{
    // Initialize result and adj to 0
    int result = 0;
    int adj = 0;
    int direction = -1;

    // Create a copy of the array of requests, which we will sort
    int *sortedArray = malloc(REQUESTS * sizeof(int));
    memcpy(sortedArray, arrayOfrequest, REQUESTS * sizeof(int));
    qsort(sortedArray, REQUESTS, sizeof(*arrayOfrequest), comp);

    // Find the position in the sorted array that is closest to the starting position
    while (abs(sortedArray[adj + 1] - start) <= abs(sortedArray[adj] - start)) {
        adj++;
    }

    int current = start;
    for (int i = adj; i >= 0 && adj >= 0; i--) {
        result += abs(sortedArray[i] - current);
        current = sortedArray[i];
    }

    for (int i = adj + 1; i < REQUESTS && adj < REQUESTS ; i++) {
        result += abs(sortedArray[i] - current);
        current= sortedArray[i];
    }
    printlog(adj, start, sortedArray);
    return result;
}


int cscan(int *arrayOfrequest, int start)
{
    // Initialize result and adj to 0
    int result = 0;
    int adj = 0;
    int direction = -1;


    return -1;
}

int look(int *arrayOfrequest, int start)
{
    return -1;
}

int clook(int *arrayOfrequest, int start)
{
    return -1;
}
