#include<stdio.h>

int refString[30], frame[30], time[30], pageFaults = 0, nr, nf, hit = 0;

void input() {
    printf("Enter no. of Reference Strings: ");
    scanf("%d", &nr);
    printf("Enter Reference String values:\n");
    for (int i = 0; i < nr; i++) {
        scanf("%d", &refString[i]);
    }
    printf("Enter no. of Frames: ");
    scanf("%d", &nf);
}

void lru() {
    int flag1, flag2, i, j, pos, min_time;
    for (i = 0; i < nf; i++) {
        frame[i] = -1;
    }

    for (i = 0; i < nr; i++) {
        flag1 = flag2 = 0;
        for (j = 0; j < nf; j++) {
            if (frame[j] == refString[i]) {
                hit++;
                time[j] = i; 
                flag1 = flag2 = 1;
                break;
            }
        }
        if (flag1 == 0) {
            for (j = 0; j < nf; j++) {
                if (frame[j] == -1) {
                    pageFaults++;
                    frame[j] = refString[i];
                    time[j] = i; 
                    flag2 = 1;
                    break;
                }
            }
        }
        if (flag2 == 0) {
            pageFaults++;
            min_time = time[0];
            pos = 0;
            for (j = 1; j < nf; j++) {
                if (time[j] < min_time) {
                    min_time = time[j];
                    pos = j;
                }
            }
            frame[pos] = refString[i];
            time[pos] = i;
        }
    }
}

void print() {
    printf("\n  No. of Page Faults: %d\n", pageFaults);
    printf("  No. of Page Hits: %d\n", hit);
    printf("  Final Frame Status: \n");
    for (int i = 0; i < nf; i++) {
        if(frame[i] != -1) {
            printf("    %d\n", frame[i]);
        } else {
            printf("    -1\n");
        }
    }
}

int main() {
    input();
    lru();
    print();
    return 0;
}