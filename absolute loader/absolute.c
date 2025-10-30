#include <stdio.h>
#include <string.h>
#include <stdlib.h> // For strtol (string to long)

int main() {
    FILE *fp;
    char line[100];
    char name[7], start_addr_str[7];
    char t_addr_str[7], t_len_str[3], obj_code[70];
    char byte_str[3]; // To hold one byte like "1A"
    int t_addr, t_len;

    fp = fopen("input.txt", "r");
    if (fp == NULL) {
        printf("Error: Could not open input.txt\n");
        return 1;
    }

    printf("--- Absolute Loader Simulation ---\n");

    // Read line by line from the file
    while (fgets(line, 100, fp) != NULL) {
        
        // --- Header Record ---
        if (line[0] == 'H') {
            // H^COPY^001000^00107A
            sscanf(line, "H^%6s^%6s", name, start_addr_str);
            printf("Loading Program: %s\n", name);
            printf("Starting Address: 0x%s\n", start_addr_str);
            printf("\nADDRESS\tCODE\n");
        } 
        
        // --- Text Record ---
        else if (line[0] == 'T') {
            // T^001000^1E^141033481039...
            // Parse the line using sscanf
            sscanf(line, "T^%6s^%2s^%s", t_addr_str, t_len_str, obj_code);

            // Convert hex strings to integers
            t_addr = (int)strtol(t_addr_str, NULL, 16);
            t_len = (int)strtol(t_len_str, NULL, 16);

            // Loop through the object code string, two chars at a time
            for (int i = 0; i < t_len * 2; i += 2) {
                // Grab one byte (e.g., "14")
                byte_str[0] = obj_code[i];
                byte_str[1] = obj_code[i + 1];
                byte_str[2] = '\0'; // Null-terminate the string
                
                // Print the simulated "loading"
                printf("0x%X\t%s\n", t_addr, byte_str);
                
                t_addr++; // Go to the next memory address
            }
        } 
        
        // --- End Record ---
        else if (line[0] == 'E') {
            printf("\nEnd of program.\n");
            break; // Stop loading
        }
    }

    fclose(fp);
    return 0;
}