#include <stdio.h>
#include <stdlib.h>
void sort(int arr[], int n) {
    int temp;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}
void cscan(int request[], int n, int head, int disk_size) {
    sort(request, n); 
    int total_seek_time = 0;
    int head_index;
    for (head_index = 0; head_index < n; head_index++) {
        if (request[head_index] >= head)
            break;
    }
    for (int i = head_index; i < n; i++) {
        total_seek_time += abs(request[i] - head);
        head = request[i];
    }
    total_seek_time += abs(disk_size - head);
    for (int i = 0; i < head_index; i++) {
        total_seek_time += abs(request[i] - head);
        head = request[i];
    }
    printf("Total seek time using C-SCAN: %d\n", total_seek_time);
}
int main() {
    int n, head, disk_size;
    printf("Enter the number of requests: ");
    scanf("%d", &n);
    int request[n];
    printf("Enter the disk requests: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &request[i]);
    }
    printf("Enter the current head position: ");
    scanf("%d", &head);
    printf("Enter the disk size: ");
    scanf("%d", &disk_size);
    cscan(request, n, head, disk_size);
    return 0;
}

