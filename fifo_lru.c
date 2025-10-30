#include<stdio.h> 
#define Page_SIZE 10 
#define MAX_Frame 3 
int pages[Page_SIZE], frame[MAX_Frame], page_fault = 0, page_hit = 0, n, m; 
void display_frame(int k) { 
 printf("\nstep %d: ", k); 
 for (int i = 0; i < MAX_Frame; i++) { 
     if (frame[i] == -1) 
         printf("- "); 
     else 
         printf("%d ", frame[i]); 
 } 
 printf("\n"); 
} 
void reset() { 
 for (int i = 0; i < MAX_Frame; i++) { 
     frame[i] = -1; 
 } 
 page_fault = 0; 
 page_hit = 0; 
} 
void FIFO() { 
 int page, front = 0; 
 for (int i = 0; i < n; i++) { 
     page = pages[i]; 
     int found = 0; 
     for (int j = 0; j < MAX_Frame; j++) { 
         if (frame[j] == page) { 
             page_hit++; 
             found = 1; 
             break; 
         } 
     } 
     if (!found) { 
         page_fault++; 
         frame[front] = page; 
         front = (front + 1) % MAX_Frame; 
     } 
     display_frame(i + 1); 
 } 
 printf("Page Fault: %d",page_fault); 
} 
void LRU() { 
 int recent[MAX_Frame], page, min_index; 
 for (int i = 0; i < MAX_Frame; i++) { 
     recent[i] = -1; 
     frame[i] = -1; 
 } 
 for (int i = 0; i < n; i++) { 
     page = pages[i]; 
     int found = 0; 
     for (int j = 0; j < MAX_Frame; j++) { 
         if (frame[j] == page) { 
             page_hit++; 
             recent[j] = i; 
             found = 1; 
             break; 
         } 
     } 
     if (!found) { 
         page_fault++; 
         min_index = 0; 
         for (int j = 1; j < MAX_Frame; j++) { 
             if (recent[j] < recent[min_index]) { 
                 min_index = j; 
             } 
         } 
         frame[min_index] = page; 
         recent[min_index] = i; 
     } 
     display_frame(i + 1); 
 } 
 printf("Page Fault: %d",page_fault); 
}
void main() { 
 printf("Enter the number of pages: "); 
 scanf("%d", &n); 
 for (int i = 0; i < n; i++) { 
     printf("Enter page %d: ", i + 1); 
     scanf("%d", &pages[i]); 
 } 
 reset(); 
 printf("\nFIFO Page Replacement Algorithm\n"); 
 FIFO(); 
 reset(); 
 printf("\nLRU Page Replacement Algorithm\n"); 
LRU(); 
reset();  
}