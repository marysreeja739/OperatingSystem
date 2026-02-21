#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FILES 10
#define MAX_BLOCKS 20

typedef struct {
    char filename[20];
    int index[MAX_BLOCKS]; // Index block containing pointers to data blocks
    int blockCount; // Number of blocks allocated to the file
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
    fs->files[fs->fileCount].blockCount = 0;
    fs->fileCount++;
    printf("File '%s' created successfully.\n", filename);
}

// Function to allocate blocks to a file
void allocateBlocks(FileSystem* fs, const char* filename, int blocks[], int numBlocks) {
    for (int i = 0; i < fs->fileCount; i++) {
        if (strcmp(fs->files[i].filename, filename) == 0) {
            if (fs->files[i].blockCount + numBlocks > MAX_BLOCKS) {
                printf("Not enough blocks available to allocate to file '%s'.\n", filename);
                return;
            }
            for (int j = 0; j < numBlocks; j++) {
                fs->files[i].index[fs->files[i].blockCount] = blocks[j];
                fs->files[i].blockCount++;
            }
            printf("Allocated %d blocks to file '%s'.\n", numBlocks, filename);
            return;
        }
    }
    printf("File '%s' not found!\n", filename);
}

// Function to display the index blocks of a file
void displayFileIndex(FileSystem* fs, const char* filename) {
    for (int i = 0; i < fs->fileCount; i++) {
        if (strcmp(fs->files[i].filename, filename) == 0) {
            printf("File: %s\n", fs->files[i].filename);
            printf("Allocated Blocks: ");
            for (int j = 0; j < fs->files[i].blockCount; j++) {
                printf("%d ", fs->files[i].index[j]);
            }
            printf("\n");
            return;
        }
    }
    printf("File '%s' not found!\n", filename);
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
                exit(0);
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }

    return 0;
}
