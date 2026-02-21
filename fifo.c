#include <stdio.h>
#include <stdlib.h>

#define MAX_FRAMES 10
#define MAX_PAGES 50

typedef struct {
    int items[MAX_FRAMES];
    int front, rear, size;
} Queue;

void initQueue(Queue *q, int capacity) {
    q->front = 0;
    q->rear = -1;
    q->size = 0;
    for (int i = 0; i < capacity; i++) {
        q->items[i] = -1; // Initialize frames with -1 (empty)
    }
}

int isFull(Queue *q, int capacity) {
    return q->size == capacity;
}

int isEmpty(Queue *q) {
    return q->size == 0;
}

void enqueue(Queue *q, int page, int capacity) {
    if (isFull(q, capacity)) {
        q->front = (q->front + 1) % capacity; // Remove oldest page
    } else {
        q->size++;
    }
    q->rear = (q->rear + 1) % capacity;
    q->items[q->rear] = page;
}

int isPageInQueue(Queue *q, int page, int capacity) {
    for (int i = 0; i < capacity; i++) {
        if (q->items[i] == page) {
            return 1; // Page found
        }
    }
    return 0; // Page not found
}

void fifoPageReplacement(int pages[], int n, int capacity) {
    Queue q;
    initQueue(&q, capacity);
    int pageFaults = 0;

    for (int i = 0; i < n; i++) {
        int page = pages[i];

        // Check if page is already in queue
        if (!isPageInQueue(&q, page, capacity)) {
            enqueue(&q, page, capacity);
            pageFaults++;
        }

        // Print current frame state
        printf("Step %d: ", i + 1);
        for (int j = 0; j < capacity; j++) {
            if (q.items[j] == -1)
                printf("- ");
            else
                printf("%d ", q.items[j]);
        }
        printf("\n");
    }
    printf("Total Page Faults: %d\n", pageFaults);
}

int main() {
    int n, capacity;
    int pages[MAX_PAGES];

    printf("Enter number of pages: ");
    scanf("%d", &n);

    printf("Enter reference string: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &pages[i]);
    }

    printf("Enter number of frames: ");
    scanf("%d", &capacity);

    fifoPageReplacement(pages, n, capacity);
    return 0;
}
