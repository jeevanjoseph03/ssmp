#include <stdio.h> 
#include <stdlib.h> 
int n, disk_size, requests[100]; 
void fcfs(int head) { 
 int seek_count = 0; 
 int distance, cur_track, sequence[100], count = 0; 
 sequence[count++] = head; 
 for (int i = 0; i < n; i++) { 
  cur_track = requests[i]; 
  distance = abs(cur_track - head); 
  seek_count += distance; 
  head = cur_track; 
  sequence[count++] = requests[i]; 
 } 
 printf("Sequence: "); 
 for (int i = 0; i < count; i++) { 
  printf("%d ", sequence[i]); 
 } 
 printf("\nFCFS Total Seek Count: %d\n", seek_count); 
} 
void sstf(int head) { 
 int seek_count = 0; 
 int distance, cur_track; 
 int completed[n], count = 0, sequence[100]; 
 sequence[count++] = head; 
 for (int i = 0; i < n; i++) 
  completed[i] = 0; 
 for (int i = 0; i < n; i++) { 
  int min = 10000, index = -1; 
  for (int j = 0; j < n; j++) { 
   if (!completed[j]) { 
    distance = abs(requests[j] - head); 
    if (distance < min) { 
     min = distance; 
     index = j; 
    } 
   } 
  } 
  seek_count += min; 
  head = requests[index]; 
  completed[index] = 1; 
  sequence[count++] = requests[index]; 
 } 
 printf("Sequence: "); 
 for (int i = 0; i < count; i++) { 
  printf("%d ", sequence[i]); 
 } 
 printf("\nSSTF Total Seek Count: %d\n", seek_count); 
} 
void scan(int head) { 
 int seek_count = 0; 
 int distance, cur_track, count = 0, sequence[100]; 
 sequence[count++] = head; 
 for (int i = 0; i < n; i++) { 
  for (int j = i + 1; j < n; j++) { 
   if (requests[i] > requests[j]) { 
    int temp = requests[i]; 
    requests[i] = requests[j]; 
    requests[j] = temp; 
   } 
  } 
 } 
 int index; 
 for (index = 0; index < n; index++) { 
  if (requests[index] > head) break; 
 } 
 for (int i = index; i < n; i++) { 
  cur_track = requests[i]; 
  distance = abs(cur_track - head); 
  seek_count += distance; 
  head = cur_track; 
  sequence[count++] = requests[i]; 
 } 
 if (index < n) { 
  seek_count += abs(disk_size - 1 - head); 
  head = disk_size - 1; 
  sequence[count++] = head; 
 } 
 for (int i = index - 1; i >= 0; i--) { 
  cur_track = requests[i]; 
  distance = abs(cur_track - head); 
  seek_count += distance; 
  head = cur_track; 
  sequence[count++] = requests[i]; 
 } 
 printf("Sequence: "); 
 for (int i = 0; i < count; i++) { 
  printf("%d ", sequence[i]); 
 } 
 printf("\nSCAN Total Seek Count: %d\n", seek_count); 
} 
int main() { 
 int head; 
 printf("Enter the number of requests: "); 
 scanf("%d", &n); 
printf("Enter the request queue: "); 
for (int i = 0; i < n; i++) { 
scanf("%d", &requests[i]); 
} 
printf("Enter the initial head position: "); 
scanf("%d", &head); 
printf("Enter the disk size: "); 
scanf("%d", &disk_size); 
printf("\nFCFS:\n"); 
fcfs(head); 
printf("\nSSTF:\n"); 
sstf(head); 
printf("\nSCAN:\n"); 
scan(head); 
return 0; 
}