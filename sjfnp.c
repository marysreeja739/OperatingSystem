#include <stdio.h>
#include <stdlib.h>

#define MAX_PROCESSES 100

typedef struct {
    int process_id;
    int burst_time;
    int arrival_time;
    int waiting_time;
    int turnaround_time;
} Process;

typedef struct {
    Process processes[MAX_PROCESSES];
    int front;
    int rear;
    int count;
} Queue;

void enqueue(Queue *q, Process p) {
    if (q->count == MAX_PROCESSES) {
        printf("Queue is full!\n");
        return;
    }
    q->processes[q->rear] = p;
    q->rear = (q->rear + 1) % MAX_PROCESSES;
    q->count++;
}

Process dequeue(Queue *q) {
    Process p = {0, 0, 0, 0, 0};
    if (q->count == 0) {
        printf("Queue is empty!\n");
        return p;
    }
    p = q->processes[q->front];
    q->front = (q->front + 1) % MAX_PROCESSES;
    q->count--;
    return p;
}

void sortQueueByBurstTime(Queue *q) {
   int i,j;
    for (i = 0; i < q->count - 1; i++) {
        for (j = i + 1; j < q->count; j++) {
            int currentIndex = (q->front + i) % MAX_PROCESSES;
            int nextIndex = (q->front + j) % MAX_PROCESSES;
            if (q->processes[currentIndex].burst_time > q->processes[nextIndex].burst_time) {
                Process temp = q->processes[currentIndex];
                q->processes[currentIndex] = q->processes[nextIndex];
                q->processes[nextIndex] = temp;
            }
        }
    }
}

void calculateTimes(Queue *q) {
    int waiting_time = 0;
    int turnaround_time = 0;
    int current_time = 0;
    int n = q->count,i,j;

    sortQueueByBurstTime(q);

    for (i = 0; i < n; i++) {
        Process p = dequeue(q);
        p.waiting_time = current_time - p.arrival_time;
        p.turnaround_time = p.waiting_time + p.burst_time;
        waiting_time += p.waiting_time;
        turnaround_time += p.turnaround_time;
        current_time += p.burst_time;

        printf("Process ID: %d, Burst Time: %d, Arrival Time: %d, Waiting Time: %d, Turnaround Time: %d\n",
               p.process_id, p.burst_time, p.arrival_time, p.waiting_time, p.turnaround_time);
    }

    printf("Average waiting time: %.2f\n", (float)waiting_time / n);
    printf("Average turnaround time: %.2f\n", (float)turnaround_time / n);
}

int main() {
    Queue q = {{0}, 0, 0, 0};
    int n,i;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    for (i = 0; i < n; i++) {
        Process p;
        p.process_id = i + 1;
        printf("Enter burst time for process %d: ", i + 1);
        scanf("%d", &p.burst_time);
        p.arrival_time = 0;
        enqueue(&q, p);
    }

    calculateTimes(&q);

    return 0;
}
