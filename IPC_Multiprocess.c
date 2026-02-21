#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <sys/wait.h>
int isArmstrong(int num) {
    int originalNum = num;
    int sum = 0;
    while (num > 0) {
        int digit = num % 10;
        sum += digit * digit * digit;
        num /= 10;
    }
      return sum == originalNum;
}
int sumOfDigits(int num) {
    int sum = 0;
    while (num > 0) {
        sum += num % 10;
        num /= 10;
    }
    return sum;
}
int factorial(int num) {
    if (num == 0 || num == 1) {
        return 1;
    }
    long fact = 1,i;
    for (i = 2; i <= num; i++) {
        fact *= i;
    }
    return fact;
}
int main() {
    int shmid = shmget(IPC_PRIVATE, sizeof(int), IPC_CREAT | 0666);
    if (shmid == -1) {
        perror("Shared memory creation failed");
        return 1;
    }
    pid_t pid1 = fork();
    if (pid1 == 0) {
        int *N = (int *)shmat(shmid, NULL, 0);
        if (N == (void *)-1) {
            perror("Shared memory attach failed in child");
            return 1;
        }
        printf("Enter a number: ");
        scanf("%d", N);
        shmdt(N);
        return 0;
    } else {
        wait(NULL);
        int *N = (int *)shmat(shmid, NULL, 0);
        if (N == (void *)-1) {
            perror("Shared memory attach failed in parent");
            return 1;
        }
        pid_t pid2 = fork();
        if (pid2 == 0) {
            if (isArmstrong(*N))
                printf("%d is an Armstrong number.\n", *N);
            else
                printf("%d is not an Armstrong number.\n", *N);
            return 0;
        }
        pid_t pid3 = fork();
        if (pid3 == 0) {
            printf("Sum of digits: %d\n",sumOfDigits(*N));
            return 0;
        }
        pid_t pid4 = fork();
        if (pid4 == 0) {
            printf("Factorial of %d: %d\n", *N, factorial(*N));
            return 0;
        }
        wait(NULL);
        wait(NULL);
        wait(NULL);
        shmdt(N);
        shmctl(shmid, IPC_RMID, NULL);
    }
    return 0;
}
