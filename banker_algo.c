#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_PROCESSES 5
#define MAX_RESOURCES 4

typedef struct {
    int allocation[MAX_PROCESSES][MAX_RESOURCES];
    int max[MAX_PROCESSES][MAX_RESOURCES];
    int need[MAX_PROCESSES][MAX_RESOURCES];
    int available[MAX_RESOURCES];
} BankersAlgorithm;

typedef struct {
    int items[MAX_PROCESSES];
    int front;
    int rear;
} Queue;

void initializeQueue(Queue *q) {
    q->front = -1;
    q->rear = -1;
}

bool isEmpty(Queue *q) {
    return q->front == -1;
}

bool isFull(Queue *q) {
    return q->rear == MAX_PROCESSES - 1;
}

void enqueue(Queue *q, int value) {
    if (!isFull(q)) {
        if (isEmpty(q)) {
            q->front = 0;
        }
        q->rear++;
        q->items[q->rear] = value;
    }
}

int dequeue(Queue *q) {
    if (!isEmpty(q)) {
        int item = q->items[q->front];
        q->front++;
        if (q->front > q->rear) {
            q->front = q->rear = -1; // Reset the queue
        }
        return item;
    }
    return -1; // Queue is empty
}

void calculateNeed(BankersAlgorithm *ba) {
    int i, j;
    for (i = 0; i < MAX_PROCESSES; i++) {
        for (j = 0; j < MAX_RESOURCES; j++) {
            ba->need[i][j] = ba->max[i][j] - ba->allocation[i][j];
        }
    }
}

bool isSafe(BankersAlgorithm *ba) {
    int work[MAX_RESOURCES];
    bool finish[MAX_PROCESSES] = {false};
    Queue q;
    initializeQueue(&q);
    int count = 0, i, p, j;

    for (i = 0; i < MAX_RESOURCES; i++) {
        work[i] = ba->available[i];
    }

    while (count < MAX_PROCESSES) {
        bool found = false;
        for (p = 0; p < MAX_PROCESSES; p++) {
            if (!finish[p]) {
                bool canAllocate = true;
                for (j = 0; j < MAX_RESOURCES; j++) {
                    if (ba->need[p][j] > work[j]) {
                        canAllocate = false;
                        break;
                    }
                }
                if (canAllocate) {
                    for (j = 0; j < MAX_RESOURCES; j++) {
                        work[j] += ba->allocation[p][j];
                    }
                    enqueue(&q, p);
                    finish[p] = true;
                    found = true;
                    count++;
                }
            }
        }
        if (!found) {
            printf("System is not in a safe state.\n");
            return false;
        }
    }

    printf("System is in a safe state.\nSafe sequence is: ");
    while (!isEmpty(&q)) {
        printf("P%d ", dequeue(&q));
    }
    printf("\n");
    return true;
}

bool requestResources(BankersAlgorithm *ba, int processID, int request[]) {
    int j;
    for (j = 0; j < MAX_RESOURCES; j++) {
        if (request[j] > ba->need[processID][j]) {
            printf("Error: Process has exceeded its maximum claim.\n");
            return false;
        }
        if (request[j] > ba->available[j]) {
            printf("Process %d must wait; resources not available.\n", processID);
            return false;
        }
    }

    // Pretend to allocate the resources
    for (j = 0; j < MAX_RESOURCES; j++) {
        ba->available[j] -= request[j];
        ba->allocation[processID][j] += request[j];
        ba->need[processID][j] -= request[j];
    }

    // Check if the system is in a safe state
    if (isSafe(ba)) {
        return true;
    } else {
        // Rollback
        for (j = 0; j < MAX_RESOURCES; j++) {
            ba->available[j] += request[j];
            ba->allocation[processID][j] -= request[j];
            ba->need[processID][j] += request[j];
        }
        printf("Request cannot be granted; system would be unsafe.\n");
        return false;
    }
}

int main() {
    BankersAlgorithm ba;
    int i, j;

    // Input for allocation matrix
    printf("Enter the allocation matrix (%d processes, %d resources):\n", MAX_PROCESSES, MAX_RESOURCES);
    for (i = 0; i < MAX_PROCESSES; i++) {
        printf("Process %d: ", i);
        for (j = 0; j < MAX_RESOURCES; j++) {
            scanf("%d", &ba.allocation[i][j]);
        }
    }

    // Input for maximum matrix
    printf("Enter the maximum matrix (%d processes, %d resources):\n", MAX_PROCESSES, MAX_RESOURCES);
    for (i = 0; i < MAX_PROCESSES; i++) {
        printf("Process %d: ", i);
        for (j = 0; j < MAX_RESOURCES; j++) {
            scanf("%d", &ba.max[i][j]);
        }
    }

    // Input for available resources
    printf("Enter the available resources (%d values):\n", MAX_RESOURCES);
    for (i = 0; i < MAX_RESOURCES; i++) {
        scanf("%d", &ba.available[i]);
    }

    // Calculate the need matrix
    calculateNeed(&ba);

    int processID;
    int request[MAX_RESOURCES];

    printf("Enter the process ID (0 to %d): ", MAX_PROCESSES - 1);
    scanf("%d", &processID);

    if (processID < 0 || processID >= MAX_PROCESSES) {
        printf("Invalid process ID.\n");
        return 1;
    }

    printf("Enter the resource request for process %d (%d values): ", processID, MAX_RESOURCES);
    for (i = 0; i < MAX_RESOURCES; i++) {
        scanf("%d", &request[i]);
    }

    // Attempt to request resources
    if (requestResources(&ba, processID, request)) {
        printf("Resources allocated successfully to process %d.\n", processID);
    } else {
        printf("Failed to allocate resources to process %d.\n", processID);
    }

    // Print the need matrix
    printf("Need matrix:\n");
    for (i = 0; i < MAX_PROCESSES; i++) {
        for (j = 0; j < MAX_RESOURCES; j++) {
            printf("%d\t", ba.need[i][j]); // Corrected line
        }
        printf("\n");
    }

    return 0;
}
