#include <stdio.h>

int burst[20], n, waiting[20], turnaround[20], priority[20], p[20];
float avg_waiting = 0, avg_turnaround = 0;

void input() {
    printf("Enter No. of Processes: ");
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        printf("Enter Burst time for P%d: ", i + 1);
        scanf("%d", &burst[i]);
        printf("Enter Priority for P%d: ", i + 1);
        scanf("%d", &priority[i]);
        p[i] = i; // Store process index
    }
}

void sort() {
    int temp;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (priority[p[i]] > priority[p[j]]) {
                temp = p[j];
                p[j] = p[i];
                p[i] = temp;
            }
        }
    }
}

void calculateTimes() {
    int time = 0;
    for (int i = 0; i < n; i++) {
        int process_index = p[i];
        waiting[process_index] = time;
        turnaround[process_index] = waiting[process_index] + burst[process_index];
        time += burst[process_index];
        avg_waiting += waiting[process_index];
        avg_turnaround += turnaround[process_index];
    }
    avg_waiting /= n;
    avg_turnaround /= n;
}

void printTable() {
    printf("\n\tProcess\t\tPriority\tBurst Time\tWaiting Time\tTurn Around Time\n");
    for (int i = 0; i < n; i++) {
        int process_index = p[i];
        printf("\tP%d\t\t%d\t\t%d\t\t%d\t\t%d\n",
            process_index + 1,
            priority[process_index],
            burst[process_index],
            waiting[process_index],
            turnaround[process_index]);
    }
}

int main() {
    input();
    sort();
    calculateTimes();
    printTable();
    printf("\nAverage Waiting Time is: %.2f", avg_waiting);
    printf("\nAverage Turn Around Time is: %.2f\n", avg_turnaround);
    return 0;
}