#include <stdio.h>
#include <stdlib.h> // For abs()
#include <limits.h> // For INT_MAX

#define MAX_REQUESTS 50

int requests[MAX_REQUESTS];
int n, head_start;

// --- 1. FCFS (First Come, First Serve) ---
void fcfs() {
    int total_movement = 0;
    int current_head = head_start;

    printf("\n--- FCFS Scheduling ---\n");
    printf("Head Movement Path: %d", current_head);

    for (int i = 0; i < n; i++) {
        int movement = abs(requests[i] - current_head);
        total_movement += movement;
        current_head = requests[i];
        printf(" -> %d", current_head);
    }

    printf("\nTotal Head Movement (FCFS): %d\n", total_movement);
}

// --- 2. SSTF (Shortest Seek Time First) ---
void sstf() {
    int total_movement = 0;
    int current_head = head_start;
    
    // We need an array to track if a request is finished
    int finished[MAX_REQUESTS] = {0}; // 0 = not done, 1 = done
    
    printf("\n--- SSTF Scheduling ---\n");
    printf("Head Movement Path: %d", current_head);

    for (int i = 0; i < n; i++) {
        int min_seek = INT_MAX;
        int next_req_index = -1;

        // Find the closest request
        for (int j = 0; j < n; j++) {
            // Check if this request is NOT finished
            if (finished[j] == 0) {
                int seek = abs(requests[j] - current_head);
                
                if (seek < min_seek) {
                    min_seek = seek;
                    next_req_index = j;
                }
            }
        }

        // Service the closest request
        total_movement += min_seek;
        current_head = requests[next_req_index];
        finished[next_req_index] = 1; // Mark as done
        printf(" -> %d", current_head);
    }

    printf("\nTotal Head Movement (SSTF): %d\n", total_movement);
}

// --- MAIN FUNCTION ---
int main() {
    printf("Enter number of disk requests: ");
    scanf("%d", &n);

    printf("Enter the requests (track numbers):\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &requests[i]);
    }

    printf("Enter the starting head position: ");
    scanf("%d", &head_start);

    fcfs(); // Run FCFS
    sstf(); // Run SSTF

    return 0;
}