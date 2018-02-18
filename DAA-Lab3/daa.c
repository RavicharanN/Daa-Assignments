#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>

typedef struct {
    int x;
    int y;
    int markIfFound;
} point;

float distance(point a, point b) {
    int x = (a.x - b.x)*(a.x - b.x);
    int y = (a.y - b.y)*(a.y - b.y);
    float dist = (float)x + (float)y;
    dist = sqrt(dist);
    return dist;
}

int searchLeast(point *p,int n,int id,float * dist) {
    int leastIndex;
    int i;
    float least =  111111111111.1;
    for(i = 0; i<n ; i++) {
        if(p[i].markIfFound == 0 && dist[i] <= least) {
            leastIndex = i;
            least = dist[i];
        }
    }
    p[leastIndex].markIfFound = 1;
    return leastIndex;
}

void findLeast(point *p,int n,int id) {
    float *dist = (float *)malloc(n*sizeof(float));
    int i;
    for(i = 0;i<n;i++) {
        dist[i] = distance(p[id],p[i]);
    }
    for(i = 0;i<n;i++) {
        printf("%f\n",dist[i]);
    }
    int k = 3;
    while(k--) {
        int leastIndex = searchLeast(p,n,id,dist);
        printf("The closest element is (%d,%d)\n",p[leastIndex].x,p[leastIndex].y);
    }
    return;
}

int main() {
  int n,i,j;
  scanf("%d",&n);
  point *p = (point *)malloc(n*sizeof(point));
  for(i = 0;i<n;i++) {
      scanf("%d %d",&p[i].x,&p[i].y);
      p[i].markIfFound = 0;
  }
  int id = scanf("%d",&id);
  p[id].markIfFound = 1;
  findLeast(p,n,id);
  return 0;
}