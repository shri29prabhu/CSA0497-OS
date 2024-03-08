#include <stdio.h>
#include <stdlib.h>
int calculateFCFS(int head, int requests[], int n) {
    int totalMovement = 0;
    for (int i = 0; i < n; i++) {
        int movement = abs(requests[i] - head);
        head = requests[i];
        totalMovement += movement;
    }
    return totalMovement;
}
int main() {
    int head, n;
    printf("Enter the initial head position: ");
    scanf("%d", &head);
    printf("Enter the number of disk requests: ");
    scanf("%d", &n);
    int requests[n];
    printf("Enter the disk request queue:\n");
    for (int i = 0; i < n; i++) {
        printf("Request %d: ", i + 1);
        scanf("%d", &requests[i]);
    }
    int totalMovement = calculateFCFS(head, requests, n);
    printf("Total head movement using FCFS: %d\n", totalMovement);
    return 0;
}

