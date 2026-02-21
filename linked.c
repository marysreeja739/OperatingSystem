#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FILES 10
#define MAX_BLOCKS 20

typedef struct Block {
    int blockNumber; // Block number
    struct Block* next; // Pointer to the next block
} Block;

typedef struct {
    char filename[20];
    Block* head; // Pointer to the head of the linked list of blocks
} File;

typedef struct {
    File files[MAX_FILES];
    int fileCount; // Number of files
} FileSystem;

// Function to initialize the file system
void initFileSystem(FileSystem* fs) {
    fs->fileCount = 0;
}

// Function to create a new file
void createFile(FileSystem* fs, const char* filename) {
    if (fs->fileCount >= MAX_FILES) {
        printf("File system is full! Cannot create more files.\n");
        return;
    }
    strcpy(fs->files[fs->fileCount].filename, filename);
    fs->files[fs->fileCount].head = NULL; // Initialize head to NULL
    fs->fileCount++;
    printf("File '%s' created successfully.\n", filename);
}

// Function to allocate blocks to a file
void allocateBlocks(FileSystem* fs, const char* filename, int blocks[], int numBlocks) {
    for (int i = 0; i < fs->fileCount; i++) {
        if (strcmp(fs->files[i].filename, filename) == 0) {
            Block* current = NULL;
            for (int j = 0; j < numBlocks; j++) {
                Block* newBlock = (Block*)malloc(sizeof(Block));
                newBlock->blockNumber = blocks[j];
                newBlock->next = NULL;

                if (fs->files[i].head == NULL) {
                    fs->files[i].head = newBlock; // First block
                } else {
                    current->next = newBlock; // Link the new block
                }
                current = newBlock; // Move to the new block
            }
            printf("Allocated %d blocks to file '%s'.\n", numBlocks, filename);
            return;
        }
    }
    printf("File '%s' not found!\n", filename);
}

// Function to display the linked list of blocks for a file
void displayFileIndex(FileSystem* fs, const char* filename) {
    for (int i = 0; i < fs->fileCount; i++) {
        if (strcmp(fs->files[i].filename, filename) == 0) {
            printf("File: %s\n", fs->files[i].filename);
            printf("Allocated Blocks: ");
            Block* current = fs->files[i].head;
            while (current != NULL) {
                printf("%d ", current->blockNumber);
                current = current->next;
            }
            printf("\n");
            return;
        }
    }
    printf("File '%s' not found!\n", filename);
}

// Function to free allocated memory for a file
void freeFile(File* file) {
    Block* current = file->head;
    while (current != NULL) {
        Block* temp = current;
        current = current->next;
        free(temp);
    }
    file->head = NULL; // Reset head to NULL
}

int main() {
    FileSystem fs;
    initFileSystem(&fs);

    int choice;
    char filename[20];
    int blocks[MAX_BLOCKS];
    int numBlocks;

    while (1) {
        printf("\n1. Create File\n2. Allocate Blocks\n3. Display File Index\n4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter filename: ");
                scanf("%s", filename);
                createFile(&fs, filename);
                break;
            case 2:
                printf("Enter filename to allocate blocks: ");
                scanf("%s", filename);
                printf("Enter number of blocks to allocate: ");
                scanf("%d", &numBlocks);
                printf("Enter block numbers (space-separated): ");
                for (int i = 0; i < numBlocks; i++) {
                    scanf("%d", &blocks[i]);
                }
                allocateBlocks(&fs, filename, blocks, numBlocks);
                break;
            case 3:
                printf("Enter filename to display index: ");
                scanf("%s", filename);
                displayFileIndex(&fs, filename);
                break;
            case 4:
                // Free all allocated memory before exiting
                for (int i = 0; i < fs.fileCount; i++) {
                    freeFile(&fs.files[i]);
                }
                exit(0);
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }

    return 0;
}
