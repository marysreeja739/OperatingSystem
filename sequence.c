#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FILES 10
#define MAX_BLOCKS 20

typedef struct {
    char filename[20];
    int startBlock; // Starting block number
    int blockCount; // Number of blocks allocated
} File;

typedef struct {
    File files[MAX_FILES];
    int fileCount; // Number of files
    int totalBlocks; // Total number of blocks available
} FileSystem;

// Function to initialize the file system
void initFileSystem(FileSystem* fs, int totalBlocks) {
    fs->fileCount = 0;
    fs->totalBlocks = totalBlocks;
}

// Function to create a new file
void createFile(FileSystem* fs, const char* filename) {
    if (fs->fileCount >= MAX_FILES) {
        printf("File system is full! Cannot create more files.\n");
        return;
    }
    strcpy(fs->files[fs->fileCount].filename, filename);
    fs->files[fs->fileCount].startBlock = -1; // Initialize startBlock to -1
    fs->files[fs->fileCount].blockCount = 0; // Initialize blockCount to 0
    fs->fileCount++;
    printf("File '%s' created successfully.\n", filename);
}

// Function to allocate blocks to a file
void allocateBlocks(FileSystem* fs, const char* filename, int numBlocks) {
    for (int i = 0; i < fs->fileCount; i++) {
        if (strcmp(fs->files[i].filename, filename) == 0) {
            // Check if there are enough contiguous blocks available
            if (fs->files[i].startBlock != -1) {
                printf("File '%s' already has allocated blocks.\n", filename);
                return;
            }

            // Find a starting block
            int startBlock = -1;
            for (int j = 0; j <= fs->totalBlocks - numBlocks; j++) {
                int found = 1;
                for (int k = 0; k < numBlocks; k++) {
                    // Check if the block is already allocated
                    for (int m = 0; m < fs->fileCount; m++) {
                        if (fs->files[m].startBlock == j + k) {
                            found = 0;
                            break;
                        }
                    }
                    if (!found) break;
                }
                if (found) {
                    startBlock = j;
                    break;
                }
            }

            if (startBlock == -1) {
                printf("Not enough contiguous blocks available to allocate to file '%s'.\n", filename);
                return;
            }

            // Allocate blocks
            fs->files[i].startBlock = startBlock;
            fs->files[i].blockCount = numBlocks;
            printf("Allocated %d blocks to file '%s' starting from block %d.\n", numBlocks, filename, startBlock);
            return;
        }
    }
    printf("File '%s' not found!\n", filename);
}

// Function to display the allocated blocks for a file
void displayFileIndex(FileSystem* fs, const char* filename) {
    for (int i = 0; i < fs->fileCount; i++) {
        if (strcmp(fs->files[i].filename, filename) == 0) {
            printf("File: %s\n", fs->files[i].filename);
            printf("Allocated Blocks: ");
            for (int j = 0; j < fs->files[i].blockCount; j++) {
                printf("%d ", fs->files[i].startBlock + j);
            }
            printf("\n");
            return;
        }
    }
    printf("File '%s' not found!\n", filename);
}

int main() {
    FileSystem fs;
    int totalBlocks;

    printf("Enter total number of blocks in the file system: ");
    scanf("%d", &totalBlocks);
    initFileSystem(&fs, totalBlocks);

    int choice;
    char filename[20];
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
                allocateBlocks(&fs, filename, numBlocks);
                break;
            case 3:
                printf("Enter filename to display index: ");
                scanf("%s", filename);
                displayFileIndex(&fs, filename);
                break;
            case 4:
                exit(0);
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }

    return 0;
}
