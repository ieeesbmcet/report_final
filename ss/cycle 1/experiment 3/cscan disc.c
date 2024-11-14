/*Here’s a concise algorithm for the provided C program that implements the C-SCAN (Circular SCAN) disk scheduling algorithm:

### Extremely Brief Algorithm: C-SCAN Disk Scheduling

1. **Input:** Read `max` (max cylinders), `n` (number of requests), and `req[]` (request array).
2. **Validation:** Check if any request exceeds `max - 1`; if yes, terminate.
3. **Sort:** Sort the request array `req[]`.
4. **Input Current Head Position:** Read the current position of the head.
5. **Process Requests:**
   - Move from the head to the end of the requests.
   - Jump to the start (cylinder 0), then process remaining requests.
6. **Calculate Seek Time:** Accumulate total seek time.
7. **Output:** Print total seek time and seek sequence.

This version encapsulates the core logic of the C-SCAN algorithm in a highly succinct format.*/

//c scan

#include <stdio.h>

int main() {
    int head, current, req[20], n, i, j, seektime = 0, max, flag = 0, seq[20], c = 0, temp;
    printf("Enter the Max number of Cylinders: ");
    scanf("%d", &max);
    printf("Enter the Number of Requests: ");
    scanf("%d", &n);
    printf("Enter the requests: ");
    for (i = 0; i < n; i++) {
        scanf("%d", &req[i]);
        if (req[i] > max - 1)
            flag = 1;
    }
    if (flag == 1)
        printf("Process cannot complete");
    else {
        for (i = 0; i < n - 1; i++) {
            for (j = 0; j < n - i - 1; j++) {
                if (req[j] > req[j + 1]) {
                    temp = req[j];
                    req[j] = req[j + 1];
                    req[j + 1] = temp;
                }
            }
        }
        printf("Enter the current position of the head: ");
        scanf("%d", &head);
        j = 0;
        while (req[j] <= head) {
            j++;
        }
        for (i = j; i < n; i++) {
            seektime += req[i] - head;
            head = req[i];
            seq[c] = req[i];
            c++;
        }
        seektime += (max - 1) - req[n - 1];
        seektime += max - 1;
        head = 0;
        for (i = 0; i < j; i++) {
            seektime += req[i] - head;
            head = req[i];
            seq[c] = req[i];
            c++;
        }
        printf("Seektime = %d\n", seektime);
        printf("Seek Sequence: ");
        for (i = 0; i < c; i++)
            printf("%d->", seq[i]);
    }
    return 0;
}