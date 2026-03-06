#include <stdio.h>

struct Process {
    int pid;        // Process ID
    int at;         // Arrival Time
    int bt;         // Burst Time
    int ct;         // Completion Time
    int tat;        // Turnaround Time
    int wt;         // Waiting Time
};

// Function to sort processes by Arrival Time
void sortByArrival(struct Process p[], int n) {
    struct Process temp;
    for (int i = 0; i < n-1; i++) {
        for (int j = i+1; j < n; j++) {
            if (p[i].at > p[j].at) {
                temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }
}

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process p[n];

    // Input processes
    for (int i = 0; i < n; i++) {
        p[i].pid = i+1;
        printf("Enter Arrival Time of P%d: ", p[i].pid);
        scanf("%d", &p[i].at);
        printf("Enter Burst Time of P%d: ", p[i].pid);
        scanf("%d", &p[i].bt);
    }

    // Sort by Arrival Time
    sortByArrival(p, n);

    int current_time = 0;
    float totalWT = 0, totalTAT = 0;

    // Calculate CT, TAT, WT
    for (int i = 0; i < n; i++) {
        if (current_time < p[i].at) {
            current_time = p[i].at; // CPU idle until process arrives
        }
        p[i].ct = current_time + p[i].bt;
        p[i].tat = p[i].ct - p[i].at;
        p[i].wt = p[i].tat - p[i].bt;
        current_time = p[i].ct;

        totalWT += p[i].wt;
        totalTAT += p[i].tat;
    }

    // Display results
    printf("\nFCFS Scheduling Results:\n");
    printf("PID\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].pid, p[i].at, p[i].bt, p[i].ct, p[i].tat, p[i].wt);
    }

    printf("\nAverage Turnaround Time = %.2f", totalTAT/n);
    printf("\nAverage Waiting Time = %.2f\n", totalWT/n);

    return 0;
}