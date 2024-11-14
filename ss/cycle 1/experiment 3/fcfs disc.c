/*Here’s a concise algorithm for the provided C program that implements the FCFS (First-Come, First-Served) disk scheduling algorithm:

### Extremely Brief Algorithm: FCFS Disk Scheduling

1. **Input:** Read `t` (total tracks), `n` (number of requests), `arr[]` (track requests), and `head` (initial head position).
2. **Process Requests:** 
   - For each request in `arr[]`:
     - Calculate distance from the current track to the requested track.
     - Accumulate total seek count.
     - Update the previous track to the current request.
3. **Output:** Print seek sequence and total number of seek operations.

This version captures the core process of the FCFS algorithm in the most concise form possible.*/
// disk fcfs

#include <stdio.h>
#include <math.h>

#define MAX 20

void FCFS(int arr[], int head, int size) {
    int seek_count = 0;
    int cur_track, prev_track = head, distance;
    
    
    // Seek sequence would be the same as request array sequence
    printf("Seek Sequence is\n");
    for(int i = 0; i < size; i++) {
        cur_track = arr[i];
        // calculate absolute distance
        distance = fabs(prev_track - cur_track);
        // increase the total count
        seek_count += distance;
        // accessed track is now new head
        prev_track = cur_track;
        printf("%d-> ", arr[i]);
    }

    printf("\nTotal number of seek operations: %d\n", seek_count);
}

int main() {
    int arr[MAX], head, n, i, t;
    printf("Enter the total no. of tracks: ");
    scanf("%d", &t);
    printf("Enter the no. of requests: ");
    scanf("%d", &n);
    printf("Enter the track requests: ");
    for(i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }
    printf("Enter the position of read write head: ");
    scanf("%d", &head);
    FCFS(arr, head, n);
    return 0;
}
