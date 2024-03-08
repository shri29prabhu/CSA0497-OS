#include <stdio.h>
#include <stdlib.h>
void sortRequests(int requests[], int numRequests) {
    int i, j, temp;
    for (i = 0; i < numRequests - 1; i++) {
        for (j = 0; j < numRequests - i - 1; j++) {
            if (requests[j] > requests[j + 1]) {
                temp = requests[j];
                requests[j] = requests[j + 1];
                requests[j + 1] = temp;
            }
        }
    }
}
void scanDisk(int requests[], int numRequests, int head, char direction) {
    int totalHeadMovement = 0;
    int currentHead = head;
    sortRequests(requests, numRequests);
    int headIndex = 0;
    while (headIndex < numRequests && requests[headIndex] < head) {
        headIndex++;
    }
    if (direction == 'r') {
        for (int i = headIndex; i < numRequests; i++) {
            printf("Move from %d to %d\n", currentHead, requests[i]);
            totalHeadMovement += abs(currentHead - requests[i]);
            currentHead = requests[i];
        }
        for (int i = headIndex - 1; i >= 0; i--) {
            printf("Move from %d to %d\n", currentHead, requests[i]);
            totalHeadMovement += abs(currentHead - requests[i]);
            currentHead = requests[i];
        }
    }
    else if (direction == 'l') {
        for (int i = headIndex - 1; i >= 0; i--) {
            printf("Move from %d to %d\n", currentHead, requests[i]);
            totalHeadMovement += abs(currentHead - requests[i]);
            currentHead = requests[i];
        }
        for (int i = headIndex; i < numRequests; i++) {
            printf("Move from %d to %d\n", currentHead, requests[i]);
            totalHeadMovement += abs(currentHead - requests[i]);
            currentHead = requests[i];
        }
    }
    printf("Total head movement: %d\n", totalHeadMovement);
}
int main() {
    int numRequests, head, i;
    char direction;
    printf("Enter the number of disk requests: ");
    scanf("%d", &numRequests);
    int requests[numRequests];
    printf("Enter the disk requests: ");
    for (i = 0; i < numRequests; i++) {
        scanf("%d", &requests[i]);
    }
    printf("Enter the initial head position: ");
    scanf("%d", &head);
    printf("Enter the direction (l for left, r for right): ");
    scanf(" %c", &direction);
    scanDisk(requests, numRequests, head, direction);
    return 0;
}

