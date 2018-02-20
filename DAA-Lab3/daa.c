#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>

float time_eval = 0;

typedef struct {     
    int x;            // x coordinate
    int y;            // y cordinate
    int markIfFound;  // If the least element is found mark it and search for the second least. 
} point;

float distance(point a, point b) {  // computes the distance between 2 points.
    int x = (a.x - b.x)*(a.x - b.x);
    int y = (a.y - b.y)*(a.y - b.y);
    float dist = (float)x + (float)y;
    dist = sqrt(dist);
    time_eval += 5;
    return dist;
}

int searchLeast(point *p,int n,int id,float * dist) {  // Linear search - for the least element
    int leastIndex;
    int i;
    float least =  111111111111.1;
    for(i = 0; i<n ; i++) {
        time_eval += 3;
        if(p[i].markIfFound == 0 && dist[i] <= least) {
            leastIndex = i;
            least = dist[i];
            time_eval += 3;
        }
    }
    p[leastIndex].markIfFound = 1;
    time_eval += 2;
    return leastIndex;
}

void findLeast(point *p,int n,int id) {
    float *dist = (float *)malloc(n*sizeof(float)); // Create the an array to store the distances of every point from the identifier.
    int i;
    for(i = 0;i<n;i++) {
        time_eval += 3;
        dist[i] = distance(p[id],p[i]);  // 'distance' function computes the distance and returns a floating point value.
    }
    for(i = 0;i<n;i++) {
        time_eval += 3;
        // printf("%f\n",dist[i]);  // Print the distances from the identifier.
    }
    int k = 3;
    time_eval += 1;
    while(k--) {  // Runs for 3 times.
        time_eval += 3;
        int leastIndex = searchLeast(p,n,id,dist);  // Find the least index - This runs for 3 times to find the least 3 elements.
        printf("The closest element is (%d,%d)\n",p[leastIndex].x,p[leastIndex].y);
    }
    return;
}

int main() {
  int n,i,j,id;
  scanf("%d",&n);
  point *p = (point *)malloc(n*sizeof(point));
  // Custom Input - For testing
//   for(i = 0;i<n;i++) {
//       scanf("%d %d",&p[i].x,&p[i].y);
//       p[i].markIfFound = 0;
//   }
//   id = scanf("%d",&id);
  // End of block
  // Best case block
  p[0].x = 0;
  p[0].y = 0;
  for(i = 1;i<n;i++) {
      p[i].x = i;
      p[i].y = i;
      time_eval += 3;
  }
  id = 0;
  // End of block - Best case.
  // Worst case block
//   p[0].x = 0;
//   p[0].y = 0;
//   for(i = n-1;i>=1;i--) {
//       p[i].x = i;
//       p[i].y = i;
//       time_eval += 5;
//   }
//   id = 0;
  // End of block - Worst case.
  
  p[id].markIfFound = 1;
  findLeast(p,n,id);  // Core function.
  time_eval += 2;
  time_eval = time_eval/(float)10000;
  printf("Time taken for computation is %f\n",time_eval);
  return 0;
}