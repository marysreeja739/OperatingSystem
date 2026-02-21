#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_FRAMES 10
#define MAX_PAGES 50

typedef struct {
    int items[MAX_FRAMES];
    int size;
} Queue;

void initQueue(Queue *q, int capacity) {
    q->size = 0;
    for (int i = 0; i < capacity; i++) {
        q->items[i] = -1; // Initialize frames with -1 (empty)
    }
}

int isPageInQueue(Queue *q, int page, int capacity) {
    for (int i = 0; i < capacity; i++) {
        if (q->items[i] == page) {
            return 1; // Page found
        }
    }
    return 0; // Page not found
}

int findOptimalReplacementIndex(Queue *q, int pages[], int n, int currentIndex, int capacity) {
    int farthest = -1, replaceIndex = -1;
    for (int i = 0; i < capacity; i++) {
        int j;
        for (j = currentIndex + 1; j < n; j++) {
            if (q->items[i] == pages[j]) {
                if (j > farthest) {
                    farthest = j;
                    replaceIndex = i;
                }
                break;
            }
        }
        if (j == n) return i; // If a page is never used again, replace it
    }
    return replaceIndex;
}

void optimalPageReplacement(int pages[], int n, int capacity) {
    Queue q;
    initQueue(&q, capacity);
    int pageFaults = 0;

    for (int i = 0; i < n; i++) {
        int page = pages[i];

        // Check if page is already in queue
        if (!isPageInQueue(&q, page, capacity)) {
            if (q.size < capacity) {
                q.items[q.size++] = page; // Fill empty slots
            } else {
                int replaceIndex = findOptimalReplacementIndex(&q, pages, n, i, capacity);
                q.items[replaceIndex] = page; // Replace optimal page
            }
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

    optimalPageReplacement(pages, n, capacity);
    return 0;
}
