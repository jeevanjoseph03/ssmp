#include <stdio.h>

// Global variables
int burst[20], arrival[20], waiting[20], turnaround[20], p[20], completion[20];
int n;
float avg_waiting = 0, avg_turnaround = 0;

void input() {
    printf("Enter No. of Processes: ");
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        printf("Enter Arrival time for P%d: ", i + 1);
        scanf("%d", &arrival[i]);
        printf("Enter Burst time for P%d: ", i + 1);
        scanf("%d", &burst[i]);
        p[i] = i; // Store original process index (P0, P1, P2...)
    }
}

// Sorts the processes based on Arrival Time
void sort() {
    int temp_p;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            // Sort by arrival time
            if (arrival[p[i]] > arrival[p[j]]) { 
                // Swap the process indices
                temp_p = p[j];
                p[j] = p[i];
                p[i] = temp_p;
            }
        }
    }
}

// Calculates WT and TAT
void calculateTimes() {
    int time = 0; // This is the current completion time
    
    for (int i = 0; i < n; i++) {
        int idx = p[i]; // Get the next process to run (from sorted list)

        // Check if CPU is idle
        if (time < arrival[idx]) {
            time = arrival[idx];
        }

        // Calculate times for this process
        completion[idx] = time + burst[idx];
        turnaround[idx] = completion[idx] - arrival[idx];
        waiting[idx] = turnaround[idx] - burst[idx];

        // Update total time and averages
        time = completion[idx]; // Update clock to new completion time
        avg_waiting += waiting[idx];
        avg_turnaround += turnaround[idx];
    }
    
    avg_waiting /= n;
    avg_turnaround /= n;
}

// Prints the table in the order of execution
void printTable() {
    printf("\n--- FCFS Execution Order ---\n");
    printf("\tProcess\t\tArrival\t\tBurst\t\tWaiting\t\tTurn Around\n");
    
    for (int i = 0; i < n; i++) {
        int idx = p[i]; // Get the process index from the sorted list
        
        printf("\tP%d\t\t%d\t\t%d\t\t%d\t\t%d\n",
               idx + 1,          // Process ID
               arrival[idx],     // Arrival Time
               burst[idx],       // Burst Time
               waiting[idx],     // Waiting Time
               turnaround[idx]); // Turn Around Time
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