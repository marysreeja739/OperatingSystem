#include <stdio.h>
#include <stdlib.h>

#define MAX 10
#define QUEUE_SIZE 10

struct Process {
    int id;
    int burstTime;
    int arrivalTime;
    int remainingTime;
    int completionTime;
    int waitingTime;
    int turnAroundTime;
};

struct Queue {
    struct Process processQueue[QUEUE_SIZE];
    int front, rear;
};

void enqueue(struct Queue* q, struct Process p) {
    if (q->rear == QUEUE_SIZE - 1) {
        printf("Queue is full\n");
        return;
    }
    q->processQueue[q->rear] = p;
    q->rear++;
}

struct Process dequeue(struct Queue* q) {
    if (q->front == q->rear) {
        printf("Queue is empty\n");
        struct Process empty = {0};
        return empty;
    }
    struct Process p = q->processQueue[q->front];
    q->front++;
    return p;
}

int isQueueEmpty(struct Queue* q) {
    return q->front == q->rear;
}

void calculateTimes(struct Process proc[], int n) {
    int totalWaitingTime = 0, totalTurnaroundTime = 0;
    int i;
    for (i = 0; i < n; i++) {
        proc[i].turnAroundTime = proc[i].completionTime - proc[i].arrivalTime;
        proc[i].waitingTime = proc[i].turnAroundTime - proc[i].burstTime;
        totalWaitingTime += proc[i].waitingTime;
        totalTurnaroundTime += proc[i].turnAroundTime;
    }

    printf("\nProcess\tBurst Time\tArrival Time\tCompletion Time\tWaiting Time\tTurnaround Time\n");
    for (i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", proc[i].id, proc[i].burstTime, proc[i].arrivalTime, proc[i].completionTime, proc[i].waitingTime, proc[i].turnAroundTime);
    }

    printf("\nAverage Waiting Time: %.2f\n", (float)totalWaitingTime / n);
    printf("Average Turnaround Time: %.2f\n", (float)totalTurnaroundTime / n);
}

void sjfPreemptive(struct Process proc[], int n) {
    int completed = 0, currentTime = 0, minTime, shortest = -1;
    int remainingProcesses = n;
    struct Queue readyQueue;
    readyQueue.front = readyQueue.rear = 0;
    int i;
    for (i = 0; i < n; i++) {
        proc[i].remainingTime = proc[i].burstTime;
    }

    while (completed < n) {
        minTime = 9999;
        shortest = -1;

        for (i = 0; i < n; i++) {
            if (proc[i].arrivalTime <= currentTime && proc[i].remainingTime > 0 && proc[i].remainingTime < minTime) {
                minTime = proc[i].remainingTime;
                shortest = i;
            }
        }

        if (shortest == -1) {
            currentTime++;
            continue;
        }

        proc[shortest].remainingTime--;
        currentTime++;

        if (proc[shortest].remainingTime == 0) {
            proc[shortest].completionTime = currentTime;
            completed++;
        }
    }

    calculateTimes(proc, n);
}

int main() {
    int n,i;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process proc[n];

    for (i = 0; i < n; i++) {
        proc[i].id = i + 1;
        printf("\nEnter arrival time and burst time for process %d: ", proc[i].id);
        scanf("%d%d", &proc[i].arrivalTime, &proc[i].burstTime);
    }

    sjfPreemptive(proc, n);

    return 0;
}
