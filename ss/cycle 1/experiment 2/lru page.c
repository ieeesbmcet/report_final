/* Algorithm: LRU Page Replacement

1. Input: Read `n`, `reference[]`, `fsize`.
2. Initialize: Load the first `fsize` references into `frame[]`, count faults.
3. Process:
   - For each remaining reference:
     - Check if it's in `frame[]`.
     - If not, record a fault and replace the least recently used page.
4. Output: Print total faults, miss ratio, and hit ratio.
*/

// PROGRAM: LRU (Least Recently Used)

#include <stdio.h>

int main() {
    int reference[50], frame[50], fsize, i, j, flag = 0, c = 0, n, fault = 0, k, recent[50], temp, flag1 = 0;
    float miss, hit;

    printf("Enter the number of references: ");
    scanf("%d", &n);
    printf("Enter the references: ");
    for (i = 0; i < n; i++)
        scanf("%d", &reference[i]);
    printf("Enter the frame size: ");
    scanf("%d", &fsize);

    for (i = 0; i < fsize; i++) {
        fault++;
        frame[i] = reference[i];
        recent[i] = reference[i];
        c++;
    }
    recent[c] = 0;

    for (i = fsize; i < n; i++) {
        for (k = 0; k < c; k++) {
            recent[c] = 0;
        }
        flag1 = 0;
        for (j = 0; j < fsize; j++) {
            recent[c] = 0;
        }
        flag1 = 0;
        for (j = 0; j < fsize; j++) {
            recent[c] = 0;
        }
        flag1 = 0;
        for (j = 0; j < fsize; j++) {
            if (frame[j] == reference[i]) 
                flag = 1;
        }
        if (flag != 1) {
            fault++;
            frame[c] = reference[i];
            c++;
        }
        if (c == fsize)
            c = 0;
        flag = 0;
    }

    printf("Total number of faults = %d\n", fault);
    miss = ((float)fault / n) * 100;
    hit = ((float)(n - fault) / n) * 100;
    printf("Total number of references = %d\n", n);
    printf("Miss ratio = %.2f%%\n", miss);
    printf("Hit ratio = %.2f%%\n", hit);

    return 0;
}
