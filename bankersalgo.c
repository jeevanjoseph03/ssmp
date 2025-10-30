#include<stdio.h>

int main() {
    // --- Data Structures ---
    int allocated[10][10], max[10][10], need[10][10];
    int available[10], finished[10] = {0}; 
    int p, r; // p = processes, r = resources
    int safe_sequence[10];
    int count = 0; 

    // --- 1. Get Input ---
    printf("Enter the number of processes: ");
    scanf("%d", &p); // Using p

    printf("Enter the number of resources: ");
    scanf("%d", &r); // Using r

    printf("\nEnter the Allocated Resources table:\n");
    for (int i = 0; i < p; i++) {
        for (int j = 0; j < r; j++) {
            scanf("%d", &allocated[i][j]);
        }
    }

    printf("\nEnter the Maximum Demand table:\n");
    for (int i = 0; i < p; i++) {
        for (int j = 0; j < r; j++) {
            scanf("%d", &max[i][j]);
        }
    }

    printf("\nEnter the Available Resources vector: ");
    for (int i = 0; i < r; i++) {
        scanf("%d", &available[i]);
    }

    // --- 2. Calculate Need Matrix ---
    // Need = Max - Allocated
    for (int i = 0; i < p; i++) {
        for (int j = 0; j < r; j++) {
            need[i][j] = max[i][j] - allocated[i][j];
        }
    }

    // --- 3. Safety Algorithm ---
    while (count < p) {
        int found = 0; 
        
        // Loop through all processes (using 'i' for the process loop)
        for (int i = 0; i < p; i++) {
            
            // Check if process 'i' is NOT finished
            if (finished[i] == 0) {
                int j;
                
                // Check if its needs can be met
                for (j = 0; j < r; j++) {
                    if (need[i][j] > available[j]) {
                        break; // Cannot meet need
                    }
                }

                // If inner loop completed, all needs are met
                if (j == r) { 
                    
                    // "Execute" process 'i'
                    for (int k = 0; k < r; k++) {
                        available[k] += allocated[i][k];
                    }
                    
                    safe_sequence[count] = i;
                    count++;
                    finished[i] = 1;
                    found = 1;
                }
            }
        } // end of process loop

        if (found == 0) {
            printf("\nSystem is in an UNSAFE state.\n");
            return 1; 
        }
    } // end of while loop

    // --- 4. Print Safe Sequence ---
    printf("\nSystem is in a SAFE state.\nSafe Sequence is: ");
    for (int i = 0; i < p; i++) {
        printf("P%d", safe_sequence[i]);
        if (i < p - 1) {
            printf(" -> ");
        }
    }
    printf("\n");

    return 0; 
}