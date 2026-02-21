#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <ctype.h>
#include <string.h>

#define BUFFER_SIZE 1024

int main() {
    int pipefd[2];
    pid_t pid;

    if (pipe(pipefd) == -1) {
        printf("Pipe creation failed");
        exit(EXIT_FAILURE);
    }

    pid = fork();

    if (pid < 0) {
        printf("Fork failed");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {
        close(pipefd[0]);

        char filename[256];
        printf("Enter the filename to read: ");
        scanf("%s", filename);

        FILE *file = fopen(filename, "r");
        if (!file) {
            perror("Error opening file");
            close(pipefd[1]);
            exit(EXIT_FAILURE);
        }

        char line[BUFFER_SIZE];
        while (fgets(line, sizeof(line), file)) {
            write(pipefd[1], line, strlen(line));
        }
        fclose(file);
        close(pipefd[1]);
        exit(0);
    } else {
        close(pipefd[1]);
        wait(NULL);

        char buffer[BUFFER_SIZE];
        int bytesRead,i;
        int lines = 0, characters = 0, words = 0, vowels = 0;
        int inWord = 0;
        while ((bytesRead = read(pipefd[0], buffer, sizeof(buffer) - 1)) > 0) {
            printf("bytesRead:%d\n",bytesRead);
            buffer[bytesRead] = '\0';
            for (i = 0; buffer[i] != '\0'; i++) {
                characters++;
                if (buffer[i] == '\n') lines++;
                if (isspace(buffer[i])) {
                    inWord = 0;
                } else if (!inWord) {
                    inWord = 1;
                    words++;
                }
                char ch = tolower(buffer[i]);
                //if (strchr("aeiou", c)) vowels++;
                if(ch == 'a'||ch == 'e'||ch == 'i'||ch == 'o'||ch == 'u')
                {
                   vowels++;
                }
            }
        }
        close(pipefd[0]);

        printf("Analysis of the file content:\n");
        printf("Lines      : %d\n", lines);
        printf("Characters : %d\n", characters);
        printf("Words      : %d\n", words);
        printf("Vowels     : %d\n", vowels);
    }

    return 0;
}
