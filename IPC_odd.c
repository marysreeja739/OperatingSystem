#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <sys/wait.h>
int main() {
    int shmid = shmget(IPC_PRIVATE, sizeof(int), IPC_CREAT | 0666);
    if (shmid == -1) {
        perror("Error creating shared memory");
        return 1;
    }
    pid_t pid = fork();
    if (pid < 0) {
        perror("Fork failed");
        return 1;
    }
    if (pid == 0) {
        int *N = (int *)shmat(shmid, NULL, 0);
        if (N == (void *)-1) {
            perror("Error attaching shared memory in child");
            return 1;
        }
        printf("Enter a number (N): ");
        scanf("%d", N);
        shmdt(N);
        return 0;
    } else {
        wait(NULL);
        int *N = (int *)shmat(shmid, NULL, 0);
        if (N == (void *)-1) {
            perror("Error attaching shared memory in parent");
            return 1;
        }
        if (*N % 2 == 0)
            printf("The number %d is Even.\n", *N);
        else
            printf("The number %d is Odd.\n", *N);
        shmdt(N);
        shmctl(shmid, IPC_RMID, NULL);
    }
    return 0;
}
