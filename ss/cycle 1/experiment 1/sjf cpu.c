/*
Here’s an ultra-concise version of the Shortest Job First (SJF) scheduling algorithm:

### Ultra-Concise Algorithm: Shortest Job First (SJF)

1. **Input:** Read `n` and burst times `bt[]`.
2. **Sort:** Sort processes by burst time.
3. **Calculate:**
   - For each process:
     - Compute `ct[i]`, `tat[i]`, `wt[i]`.
4. **Output:** Print PID, Burst Time, Turnaround Time, Waiting Time.

This version retains only the core steps for clarity and brevity.*/

#include <stdio.h>

struct process {
    int pid, bt, ct, wt, tat;
}
p[20], s;
int main() {
    int n, i, j;
    printf("\nEnter the number of processes: ");
    scanf("%d", & n);
    for (i = 0; i < n; i++) {
        p[i].pid = i;
        printf("Enter the burst time for Process %d: ", i);
        scanf("%d", & p[i].bt);
    }
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (p[j].bt > p[j + 1].bt) {
                s = p[j];
                p[j] = p[j + 1];
                p[j + 1] = s;
            }
        }
    }
    p[0].ct = p[0].bt;
    p[0].tat = p[0].ct;
    p[0].wt = 0;
    for (i = 1; i < n; i++) {
        p[i].ct = p[i - 1].ct + p[i].bt;
        p[i].tat = p[i].ct;
        p[i].wt = p[i].tat - p[i].bt;
    }
    printf("\nProcess execution order: ");
    for (i = 0; i < n; i++) {
        printf("P%d -> ", p[i].pid);
    }
    printf("\n");
    printf("\nPID\tBurst Time\tTurnaround Time\tWaiting Time\n");
    for (i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\n", p[i].pid, p[i].bt, p[i].tat, p[i].wt);
    }
    return 0;
}












