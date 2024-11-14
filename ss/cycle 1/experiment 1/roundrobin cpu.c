
/*

### Very Short Algorithm: Round Robin CPU Scheduling

1. **Input:**
   - Read `n` (processes) and `ts` (time slice).
   - For each process, read burst time `bt`.

2. **Initialize Queue:** Enqueue all process IDs.

3. **Execution:**
   - While queue is not empty:
     - Dequeue process `id`.
     - If `bt[id] > ts`, update time and enqueue `id` again; else set `bt[id]` to `0`.

4. **Calculate Waiting Time:** `wt[i] = tat[i] - original_bt[i]`.

5. **Output:** Print PID, Burst Time, Turnaround Time, Waiting Time.

*/

#include <stdio.h>

#define MAX 20
int rq[20], front = 0, rear = -1;
struct process {
    int pid, bt, btcopy, wt, tat;
}
p[20], s;

void enqueue(int pid) {
    if (rear > MAX - 1) return;
    else {
        rear = rear + 1;
        rq[rear] = pid;
    }
}

int dequeue() {
    int ele, i;
    if (rear == -1) return -1;
    else {

        ele = rq[0];
        for (i = 0; i <= rear; i++) rq[i] = rq[i + 1];
        rear--;
        return ele;
    }
}

int main() {
    int n, i, j, sum = 0, ts, id, ct = 0;
    printf("\nEnter the no. of processes : ");
    scanf("%d", & n);
    printf("\nEnter the Time Slice : ");
    scanf("%d", & ts);
    for (i = 0; i < n; i++) {
        p[i].pid = i;
        printf("\nEnter the burst time for Process %d : ", i);
        scanf("%d", & p[i].bt);
        p[i].btcopy = p[i].bt;
    }
    for (i = 0; i < n; i++) {
        enqueue(i);
    }
    id = dequeue();
    printf("\nExecution order: ");
    printf(" P%d->", id);
    while (id != -1) {
        if (p[id].bt > ts) {
            ct = ct + ts;
            p[id].tat = ct;
            p[id].bt = p[id].bt - ts;
            if (p[id].bt != 0)
                enqueue(p[id].pid);
        } else

        {
            ct = ct + p[id].bt;
            p[id].tat = ct;
            p[id].bt = 0;
        }
        id = dequeue();
        if (id != -1)
            printf(" P%d->", id);
    }
    for (i = 0; i < n; i++)
        p[i].wt = p[i].tat - p[i].btcopy;
    printf("\n\n\n\tPID\t\tBurst Time\t\t Turnaround Time\t Waiting Time\n");
    for (i = 0; i < n; i++)
        printf("\n\t%d\t\t\t%d\t\t\t%d\t\t\t%d", p[i].pid, p[i].btcopy, p[i].tat, p[i].wt);
    printf("\n");
    return 0;
}







































