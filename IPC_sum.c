#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <sys/wait.h>
int main() {
    int i,n;
    printf("Enter the number of integers: ");
    scanf("%d", &n);
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
        int *sum = (int *)shmat(shmid, NULL, 0);
        if (sum == (void *)-1) {
            perror("Error attaching shared memory in child");
            return 1;
        }
        *sum = 0;
        printf("Enter %d integers: ", n);
        for (i = 0; i < n; ++i) {
            int num;
            scanf("%d", &num);
            *sum += num;
        }
        shmdt(sum);
        return 0;
    } else {
        wait(NULL);
        int *sum = (int *)shmat(shmid, NULL, 0);
        if (sum == (void *)-1) {
            perror("Error attaching shared memory in parent");
            return 1;
        }
        printf("Sum of integers: %d\n", *sum);
        shmdt(sum);
        shmctl(shmid, IPC_RMID, NULL);
    }
    return 0;
}
