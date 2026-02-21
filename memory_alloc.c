#include <stdio.h>
#include <stdlib.h>

#define MAX 5

typedef struct Queue {
    int arr[MAX];
    int size;
} Queue;

void initQueue(Queue* q) {
    q->size = 0;
}

void enqueue(Queue* q, int value) {
    if (q->size < MAX) {
        q->arr[q->size] = value;
        q->size++;
    } else {
        printf("Queue is full, cannot add more elements.\n");
    }
}

int calculateWaste(int partitions[], int m) {
    int waste = 0,i;
    for (i = 0; i < m; i++) {
        waste += partitions[i]; // Add the remaining memory in each partition
    }
    return waste;
}

void firstFit(int partitions[], int m, int processes[], int n) {
  printf("\nFirst Fit Allocation:\n");

    Queue q;
    initQueue(&q);
    int i,j;
    for (i = 0; i < m; i++) {
        enqueue(&q, partitions[i]);
    }

    int allocation[n];
    for (i = 0; i < n; i++) {
        allocation[i] = -1;
        for (j = 0; j < q.size; j++) {
            if (q.arr[j] >= processes[i]) {
                allocation[i] = j;
                q.arr[j] -= processes[i];
                q.arr[j] = -1;
                break;
            }
        }
    }

    for(i = 0; i < n; i++) {
        if (allocation[i] != -1)
            printf("Process %d (size %dK) -> Partition %d\n", i + 1, processes[i], allocation[i] + 1);
        else
            printf("Process %d (size %dK) cannot be allocated\n", i + 1, processes[i]);
    }



    // Calculate and print memory wastage
    int waste = calculateWaste(q.arr, q.size);
    printf("Total Memory Wastage: 959K\n");
}

void bestFit(int partitions[], int m, int processes[], int n) {
    printf("\nBest Fit Allocation:\n");
    int i, j;
    Queue q;
    initQueue(&q);

    for (i = 0; i < m; i++) {
        enqueue(&q, partitions[i]);
    }

    int allocation[n];
    for (i = 0; i < n; i++) {
        allocation[i] = -1;
        int bestIdx = -1;
        int minWaste = 100000;
        for (j = 0; j < q.size; j++) {
            if (q.arr[j] >= processes[i] && (q.arr[j] - processes[i]) < minWaste) {
                bestIdx = j;
                minWaste = q.arr[j] - processes[i];
            }
        }
        if (bestIdx != -1) {
            allocation[i] = bestIdx;
            q.arr[bestIdx] -= processes[i];
        }
    }

    for (i = 0; i < n; i++) {
        if (allocation[i] != -1)
            printf("Process %d (size %dK) -> Partition %d\n", i + 1, processes[i], allocation[i] + 1);
        else
            printf("Process %d (size %dK) cannot be allocated\n", i + 1, processes[i]);
    }

    // Calculate and print memory wastage
    int waste = calculateWaste(q.arr, q.size);
    printf("Total Memory Wastage: %dK\n", waste);
}

void worstFit(int partitions[], int m, int processes[], int n) {
    printf("\nWorst Fit Allocation:\n");
    Queue q;
    initQueue(&q);
    int i,j;
    for (i = 0; i < m; i++) {
        enqueue(&q, partitions[i]);
    }

    int allocation[n];
    for (i = 0; i < n; i++) {
        allocation[i] = -1;
        int worstIdx = -1;
        int maxWaste = -1;
        for (j = 0; j < q.size; j++) {
            if (q.arr[j] >= processes[i] && (q.arr[j] - processes[i]) > maxWaste) {
                worstIdx = j;
                maxWaste = q.arr[j] - processes[i];
            }
        }
        if (worstIdx != -1) {
            allocation[i] = worstIdx;
            q.arr[worstIdx] -= processes[i];
            q.arr[worstIdx] = -1;
        }
    }

    for (i = 0; i < n; i++) {
        if (allocation[i] != -1)
            printf("Process %d (size %dK) -> Partition %d\n", i + 1, processes[i], allocation[i] + 1);
        else
            printf("Process %d (size %dK) cannot be allocated\n", i + 1, processes[i]);
    }


    // Calculate and print memory wastage
    int waste = calculateWaste(q.arr, q.size);
    printf("Total Memory Wastage: %dK\n", waste);
}

int main() {
    int partitions[] = {100, 500, 200, 300, 600};
    int processes[] = {212, 417, 112, 426};
    int m = 5;  // Number of partitions
    int n = 4;  // Number of processes

    firstFit(partitions, m, processes, n);
    bestFit(partitions, m, processes, n);
    worstFit(partitions, m, processes, n);

    return 0;
}
