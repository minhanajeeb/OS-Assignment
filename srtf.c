#include <stdio.h>
#include <string.h>

struct Process {
    char pid[5];
    int at, bt, rt, wt, tat, ct;
};

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process p[n];
    for (int i = 0; i < n; i++) {
        scanf("%s %d %d", p[i].pid, &p[i].at, &p[i].bt);
        p[i].rt = p[i].bt;
    }

    int completed = 0, time = 0;
    float totalWT = 0, totalTAT = 0;

    while (completed != n) {
        int idx = -1;
        int minRT = 1e9;

        for (int i = 0; i < n; i++) {
            if (p[i].at <= time && p[i].rt > 0 && p[i].rt < minRT) {
                minRT = p[i].rt;
                idx = i;
            }
        }

        if (idx != -1) {
            p[idx].rt--;
            time++;

            if (p[idx].rt == 0) {
                completed++;
                p[idx].ct = time;
                p[idx].tat = p[idx].ct - p[idx].at;
                p[idx].wt = p[idx].tat - p[idx].bt;
                totalWT += p[idx].wt;
                totalTAT += p[idx].tat;
            }
        } else {
            time++; 
        }
    }

    printf("Waiting Time:\n");
    for (int i = 0; i < n; i++) {
        printf("%s  %d\n", p[i].pid, p[i].wt);
    }

    printf("Turnaround Time:\n");
    for (int i = 0; i < n; i++) {
        printf("%s  %d\n", p[i].pid, p[i].tat);
    }

    printf("Average Waiting Time: %.1f\n", totalWT / n);
    printf("Average Turnaround Time: %.1f\n", totalTAT / n);

    return 0;
}
