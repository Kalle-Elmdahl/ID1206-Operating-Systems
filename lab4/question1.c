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

    printf("FCFS: %d\n", fcfs(arrayOfrequest, start));
    printf("SSTF: %d\n", sstf(arrayOfrequest, start));
    //  printf("SCAN: %d\n", fcfs(arrayOfrequest, start));
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

/**
 * Shortest Seek Time First
 */
int sstf(int *arrayOfrequest, int start)
{
    int result = 0;
    int *sortedArray = malloc(REQUESTS * sizeof(int));

    memcpy(sortedArray, arrayOfrequest, REQUESTS * sizeof(int));
    qsort(sortedArray, REQUESTS, sizeof(*arrayOfrequest), comp);

    int adj = 0;
    while (abs(sortedArray[adj + 1] - start) <= abs(sortedArray[adj] - start))
        adj++;

    printf("adj: %d, start: %d, {%d, %d, %d}", adj, start, sortedArray[adj - 1], sortedArray[adj], sortedArray[adj + 1]);

    // Traverse the list to the left and record distances
    // Current position: pos

    // <--[shortest] + []-->

    //  start : 12
    // [5, 10, 11, 14]

    int curr_val = sortedArray[adj];
    int left_pos = adj, right_pos = adj;
    result += abs(sortedArray[adj] - start); // result = 1

    while (left_pos > 0 || right_pos < REQUESTS - 1)
    {

        int dl = left_pos > 0 ? abs(sortedArray[left_pos - 1] - curr_val) : INFINITY;
        int dr = right_pos < (REQUESTS - 1) ? abs(sortedArray[right_pos + 1] - curr_val) : INFINITY;

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
    }

    /*
        int adj_igen = 0;
        for (int i = 0; i < REQUESTS; i++)
        {
            int dist = arrayOfrequest[i] - start;
            if (dist < arrayOfrequest[adj_igen])
            {
                adj_igen = i;
            }
        }

        printf("adj_igen = %d \n", adj_igen);
        */

    // 1. Calculate distance from head to each point

    // 2. Sort according to distance to each point (from head)

    // 3. Traverse the path and calculate the distance _between the points_ traversed

    // 4. accumulate distances, current position is new head

    return result;
}

int calculateDirection(int *sortedArray, int start)
{
    if (sortedArray[adj] < start)
    { // direction left
        direction = 0;
    }
    else if (sortedArray[adj] > start)
    { // direction right
        direction = 1;
    }
    else
    {
        
    }
}

int scan(int *arrayOfrequest, int start)
{
    int result = 0;
    int *sortedArray = malloc(REQUESTS * sizeof(int));
    int direction;

    memcpy(sortedArray, arrayOfrequest, REQUESTS * sizeof(int));
    qsort(sortedArray, REQUESTS, sizeof(*arrayOfrequest), comp);

    int adj = 0;
    while (abs(sortedArray[adj + 1] - start) <= abs(sortedArray[adj] - start))
        adj++;

    direction = calculateDirection(*sortedArray, start);
    printf("adj: %d, start: %d, {%d, %d, %d}", adj, start, sortedArray[adj - 1], sortedArray[adj], sortedArray[adj + 1]);
    return -1;
}


int cscan(int *arrayOfrequest, int start)
{
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
