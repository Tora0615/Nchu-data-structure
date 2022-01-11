#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#define TRUE 1
#define FALSE 0
#define INPUTFILE "TestData\\6\\input_6-1.txt"

FILE *f_read_ptr;


struct Direction{
	int x;
	int y;
};
struct Queue{
	int x;
	int y;
	int cost;
}; 
struct Direction* direction;
struct Queue* queue;
int** map;
int** visit;
int** walk;
int** pointToPointDistence;
int size,numofd;
int* possible;
int minCost;
int ok(int point){
	int i;
	for(i=0;i<point;i++){
		if(possible[i]==possible[point]){
			return 0;
		}
	}
	return 1;
}


void getP2Pmin(int point){
	int i,j;
	if(point > numofd){
		int temp =0;
		temp += pointToPointDistence[0][possible[0]];
		for(j=0;j<numofd;j++){
			temp += pointToPointDistence[possible[j]][possible[j+1]];
		}
		if(temp < minCost){
			minCost = temp;
		}
	}
	else{
		for(j=0;j<numofd+1;j++){
			possible[point] = j+1;
			if(ok(point)){
				getP2Pmin(point+1);
			}
		}
	}
	return;
}
int dij(int startX,int startY,int endX,int endY){
	int nowX,nowY,nextX,nextY,nextc,i,j,head=0,tail=1,min,index;
	struct Queue swap;
	int dx[8]={0,-1,-1,-1,0,1,1,1};
	int dy[8]={1,1,0,-1,-1,-1,0,1};
	queue[0].x = startX;
	queue[0].y = startY;
	queue[0].cost=0;
	visit[startX][startY]=1;
	walk[startX][startY] = 1;
	while(1){
		nowX=queue[head].x;
		nowY=queue[head].y;
		walk[nowX][nowY] = 1;
		visit[nowX][nowY]=1;
		
		/* target visited -> break */
		if(walk[endX][endY] == 1){
			break;
		}
		
		/* eight direction */
		for(i=0;i<8;i++){
			nextX = nowX + dx[i];
			nextY = nowY + dy[i];
			if(nextX >=0 && nextX < size && nextY>=0 && nextY <size){
				nextc = abs(map[nowX][nowY] - map[nextX][nextY]);
				if(visit[nextX][nextY] == 0){
					queue[tail].x = nextX;
					queue[tail].y = nextY;
					queue[tail].cost = queue[head].cost + nextc;
					visit[nextX][nextY]=1;
					tail++;
				} 
				else if(visit[nextX][nextY] == 1 && walk[nextX][nextY] == 0){
					for(j=head+1 ;j<tail;j++){
						if(queue[j].x == nextX && queue[j].y == nextY){
							if(queue[j].cost > queue[head].cost + nextc){
								queue[j].cost=queue[head].cost + nextc;
							}
						}
					}
				}
			}
		}
		head++;
		min = queue[head].cost;
		index =head;
		for(i = head+1;i<tail;i++){
			if(min > queue[i].cost){
				min = queue[i].cost;
				index =i;
			}
		}
		swap = queue[head];
		queue[head] = queue[index];
		queue[index] = swap;
	}
	
	/* reset walk and visit to 0*/
	for(i=0;i<size;i++){
		for(j=0;j<size;j++){
			walk[i][j]=0;
			visit[i][j] =0;
		}
	}
	/* return ans */
	return queue[head].cost;
}
int main(){
	if( !(f_read_ptr = fopen(INPUTFILE,"r")) ){
		printf("file open failed\n");
		return 0;
	}
	
	int d,n,dx,dy,startX,startY,i,j,height;
	fscanf(f_read_ptr,"%d %d",&d,&n);
	
	size=n;
	numofd=d-1;
	map=calloc(n,sizeof(int*));
	visit=calloc(n,sizeof(int*));
	walk=calloc(n,sizeof(int*));
	direction = (struct Direction*)malloc(sizeof(struct Direction)*n);
	queue = (struct Queue*)malloc(sizeof(struct Queue)*n*n*8);
	pointToPointDistence =calloc(d+1,sizeof(int*));
	
	/* init*/
	for(i=0;i<d+1;i++){
		pointToPointDistence[i] =calloc(d+1,sizeof(int));
	}
	for(i=0;i<n;i++){
		map[i]=calloc(n,sizeof(int));
		visit[i]=calloc(n,sizeof(int));
		walk[i]=calloc(n,sizeof(int));
	}
	fscanf(f_read_ptr,"%d %d",&startX,&startY);
	for(i=0;i<d;i++){
		fscanf(f_read_ptr,"%d %d",&dx,&dy);
		direction[i].x = dx;
		direction[i].y = dy;
	}
	for(i = 0 ;i<n;i++){
		for(j=0;j<n;j++){
			fscanf(f_read_ptr,"%d",&height);
			map[i][j] = height;
		}
	}
	
	// get point to point cost
	for(i = 0;i<d ;i++){
		pointToPointDistence[0][i+1] = dij(startX,startY,direction[i].x,direction[i].y);
		pointToPointDistence[i+1][0] = pointToPointDistence[0][i+1];
		for(j=1;j<d;j++){
			if(i>=j){
				continue;
			}
			else{
				pointToPointDistence[i+1][j+1] = dij(direction[i].x,direction[i].y,direction[j].x,direction[j].y);
				pointToPointDistence[j+1][i+1] = pointToPointDistence[i+1][j+1];
			}
		}	
	}
	possible=calloc(d,sizeof(int));
	minCost = INT_MAX;
	
	/* calculate point to point total min sum */
	getP2Pmin(0);
	printf("%d",minCost);
	
	fclose(f_read_ptr);
	return 0;
}
