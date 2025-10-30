#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// --- Global Variables ---
FILE *fp1, *fp2, *fp3, *fp4, *fp5;
int locctr, start, optab_count = 0, symtab_count = 0;
char label[20], opcode[20], operand[20];

// OPTAB structure
struct optab {
    char opcode[10];
    char hexacode[10];
} ot[30];

// SYMTAB structure
struct symtab {
    char label[20];
    int addr;
} st[30];

// --- Function to read OPTAB ---
void read_optab() {
    // Read from optab.txt until end of file
    while (fscanf(fp2, "%s %s", ot[optab_count].opcode, ot[optab_count].hexacode) != EOF) {
        optab_count++;
    }
}

// --- Main Function ---
int main() {
    int i, flag; // Loop counter and a flag

    // 1. Open all files
    fp1 = fopen("input.txt", "r");
    fp2 = fopen("optab.txt", "r");
    fp3 = fopen("intermediate.txt", "w");
    fp4 = fopen("symtab.txt", "w");
    fp5 = fopen("length.txt", "w");

    // 2. Load OPTAB into memory
    read_optab();

    // 3. Handle the START line
    // Read the first line: LABEL OPCODE OPERAND
    fscanf(fp1, "%s %s %s", label, opcode, operand);

    if (strcmp(opcode, "START") == 0) {
        // Get start address from operand (convert hex string to int)
        start = (int)strtol(operand, NULL, 16);
        locctr = start;
        // Write the first line to the intermediate file
        fprintf(fp3, "%X\t%s\t%s\t%s\n", locctr, label, opcode, operand);
        // Read the *next* line before starting the loop
        fscanf(fp1, "%s %s %s", label, opcode, operand);
    } else {
        locctr = 0; // If no START, assume 0
    }

    // 4. Main loop: Process lines until END
    while (strcmp(opcode, "END") != 0) {
        // Write current line to intermediate file
        fprintf(fp3, "%X\t%s\t%s\t%s\n", locctr, label, opcode, operand);

        // --- Handle SYMTAB ---
        // If there is a label (not "-")
        if (strcmp(label, "-") != 0) {
            // Search SYMTAB for duplicate
            for (i = 0; i < symtab_count; i++) {
                if (strcmp(st[i].label, label) == 0) {
                    printf("Error: Duplicate symbol '%s'\n", label);
                    exit(1);
                }
            }
            // If new, add to SYMTAB
            strcpy(st[symtab_count].label, label);
            st[symtab_count].addr = locctr;
            symtab_count++;
        }

        // --- Handle LOCCTR ---
        flag = 0;
        // Search OPTAB
        for (i = 0; i < optab_count; i++) {
            if (strcmp(opcode, ot[i].opcode) == 0) {
                locctr += 3; // All instructions are 3 bytes
                flag = 1;
                break;
            }
        }

        // If not in OPTAB, check directives
        if (flag == 0) {
            if (strcmp(opcode, "WORD") == 0) {
                locctr += 3; // 1 word = 3 bytes
            } else if (strcmp(opcode, "RESW") == 0) {
                locctr += (3 * atoi(operand)); // 3 * number of words
            } else if (strcmp(opcode, "RESB") == 0) {
                locctr += atoi(operand); // 1 * number of bytes
            } else if (strcmp(opcode, "BYTE") == 0) {
                if (operand[0] == 'C') {
                    // C'EOF' -> strlen is 5. Bytes are E,O,F (3). (5 - 3 = 2) WRONG
                    // Correct: length is strlen - 3
                    locctr += (strlen(operand) - 3);
                } else if (operand[0] == 'X') {
                    // X'F1' -> strlen is 4. Bytes are F1 (1). (4 - 3) / 2 = 0.5 WRONG
                    // Correct: (length of hex string) / 2
                    locctr += (strlen(operand) - 3) / 2;
                }
            }
        }

        // Read the next line for the next loop iteration
        fscanf(fp1, "%s %s %s", label, opcode, operand);
    }

    // 5. Write the END line
    fprintf(fp3, "%X\t%s\t%s\t%s\n", locctr, label, opcode, operand);

    // 6. Write SYMTAB to its file
    for (i = 0; i < symtab_count; i++) {
        fprintf(fp4, "%s\t%X\n", st[i].label, st[i].addr);
    }

    // 7. Write program length
    fprintf(fp5, "Program Length: %X\n", locctr - start);

    // 8. Close all files
    fclose(fp1);
    fclose(fp2);
    fclose(fp3);
    fclose(fp4);
    fclose(fp5);

    printf("Pass 1 complete. Check intermediate.txt and symtab.txt\n");
    return 0;
}