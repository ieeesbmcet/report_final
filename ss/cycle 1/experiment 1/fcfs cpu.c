/*Here’s an even shorter version of the FCFS CPU scheduling algorithm:

### Short Algorithm
1. **Input**: Read number of processes and their burst times.
2. **Calculate Waiting Time**: Set `wait_time[0] = 0`; for `i = 1` to `x-1`, compute `wait_time[i] = wait_time[i-1] + burst_time[i-1]`.
3. **Calculate Turnaround Time**: For each process, compute `turnaround_time[i] = burst_time[i] + wait_time[i]`.
4. **Output**: Print process details and average waiting and turnaround times.*/

#include<stdio.h>

void main() {
    int x, wait_time[50], burst_time[50], turnaround_time[50], total_wt = 0, total_tat = 0;

    printf("Enter the no of processes:");
    scanf("%d", & x);

    printf("Enter the burst time:\n");
    for (int i = 0; i < x; i++) {
        printf("processor [%d]=", i + 1);
        scanf("%d", & burst_time[i]);
    }

    wait_time[0] = 0;

    for (int i = 1; i < x; i++) {
        wait_time[i] = burst_time[i - 1] + wait_time[i - 1];
    }
    
    printf("PROCESS\t  BURST TIME\t WAITING TIME\t TURNAROUND TIME\n");
    for (int i = 0; i < x; i++) {
        turnaround_time[i] = burst_time[i] + wait_time[i];
        total_wt = (total_wt + wait_time[i]);
        total_tat = (total_tat + turnaround_time[i]);
        printf("p[%d]\t\t%d\t\t%d\t\t%d\n", i + 1, burst_time[i], wait_time[i], turnaround_time[i]);
    }
    float average_wt = (float) total_wt / x;
    float average_tat = (float) total_tat / x;
    printf("average waiting time=%f\n", average_wt);
    printf("average turnaround time=%f", average_tat);
}
