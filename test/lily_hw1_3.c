# include<stdio.h>
# include<stdlib.h>
# include<string.h>
struct step{
	int x;
	int y;
	int c;//cost
};
struct step que[14400];
int coordinate[10][10] ,map[3][3] ,visit_map[120][120] ,allpossible[130][6];
int p = 0;
int energy(int index ,int** list ,int N){//count load cost ex 1->2->3 it would be list[0][1]+list[1][2]+list[2][3]
	int i = 0 ,cost = 0,tempindex = 0 ,lastindex = 0;
	lastindex = allpossible[index][i];//the name of point
	cost += list[0][lastindex]; //because must start at 0->? point
	for(i = 1 ;i < N ;i++){
		tempindex = allpossible[index][i];
		cost += list[lastindex][tempindex];
		lastindex = tempindex;
	}
	return cost;

}
void Pswap(int *num ,int i ,int j){
	int temp;
	temp=num[i];
	num[i]=num[j];
	num[j]=temp;
}
void perm(int* num ,int i ,int N){
  	int j;
	for(j = i ;j < N ;j++){
		Pswap(num,i,j);
		perm(num,i+1,N);
		Pswap(num,i,j);
	}
	if(i == N && j == N){
		int k;
		for(k = 0 ;k < N ;k++){
			allpossible[p][k]=num[k];//save all permutation
		}
		p++;
	}
}
void swap(int child ,int parent){
	int temp;
	temp = que[child].x;
	que[child].x = que[parent].x;
	que[parent].x = temp;
	temp = que[child].y;
	que[child].y = que[parent].y;
	que[parent].y = temp;
	temp = que[child].c;
	que[child].c = que[parent].c;
	que[parent].c = temp;
}
int pop(int tail ,int end_x ,int end_y){
	int i = 1;
	if(que[1].x == end_x && que[1].y == end_y){//if que[head] is destination return 1
		return 1;
	}
	swap(1,tail);
	que[tail].x = -1;
	que[tail].y = -1;
	que[tail].c = -1;
	while(i < tail){
		if(que[i].c > que[2*i].c && que[2*i].c <= que[2*i+1].c && 2*i < tail){//the parent is larger than it's child and the right one is smaller
			swap(i,2*i);
			i *= 2;
		}
		else if(que[i].c > que[2*i+1].c && que[2*i].c > que[2*i+1].c && 2*i+1 < tail){//the parent is larger than it's child and the left one is smaller
			swap(i,2*i+1);
			i = (2*i)+1;
		}
		else{
			return 0;
		}
	}
	return 0;
}
void heapque(int index){//made the bfs's head must be smallest
	int parent = 0 ,flag = 1;
	int temp = index;
	while(flag && index != 1){
		if(index % 2 == 0){
			parent = index / 2;
			if(que[index].c < que[parent].c){
				swap(index ,parent);
			}
			else{
				flag = 0;
			}
		}
		else{
			parent = (index-1) / 2;
			if(que[index].c < que[parent].c){
				swap(index ,parent);
			}
			else{
				flag = 0;
			}
		}
		index = parent;
	}
}
int bfs(int s_x ,int s_y ,int end_x ,int end_y ,int size){//a bfs which head is the smallest cost
	int cost = 0 ,head = 1 ,tail = 2 ,i = 0 ,j = 0,now_x = 0 ,now_y = 0 ,next_x = 0 ,next_y = 0 ,next_c = 0 ,exit = 0;
	int dx[8] = {0 ,1 ,1 ,1  ,0  ,-1 ,-1 ,-1};//6->3->2->1->4->7->8->9 keyboard
	int dy[8] = {1 ,1 ,0 ,-1 ,-1 ,-1 ,0  ,1};
	que[head].x = s_x;
	que[head].y = s_y;
	que[head].c = cost;
	visit_map[s_x][s_y] = 1;
	while(!exit){
		now_x = que[head].x;
		now_y = que[head].y;
		for(i = 0 ;i < 8 ;i++){
			next_x = que[head].x + dx[i];
			next_y = que[head].y + dy[i];
			next_c = abs(map[next_x][next_y] - map[now_x][now_y]);
			if( (next_x >= 0) && (next_x < size) && (next_y >= 0) && (next_y < size)){
				if(visit_map[next_x][next_y] == 0){//never visit
					que[tail].x = next_x;
					que[tail].y = next_y;
					que[tail].c = que[head].c + next_c;
					visit_map[next_x][next_y] = 1;
					heapque(tail);
					tail++;
				}
				else{//visit but find other shortcuts
					for(j = 1 ;j < tail ;j++){
						if(que[j].x == next_x && que[j].y == next_y){
							if(que[j].c > (que[head].c + next_c)){
								que[j].c = que[head].c + next_c;
								heapque(j);
							}
							break;
						}
					}
				}
			}
		}
		--tail;//before -- tail is next step index after -- tail is actual index of stack[tail]
		exit = pop(tail,end_x,end_y);

	}
	return que[head].c;
}
int main(){
	FILE *fp1;
	fp1 = fopen("../testData/input_3.txt","r");
	if(fp1 == NULL){
		printf("open file failed\n");
	}
	else{
		FILE *fp2;
		int i = 0 ,j = 0 ,k = 0 ,how_much_test = 0 ,destination = 0 ,size = 0 ,cost = 0 ,s_x = 0 ,s_y = 0;
		fp2 = fopen("output_3.txt","w");
		fscanf(fp1,"%d",&how_much_test);
		for(k = 0 ;k < how_much_test ;k++){
			fprintf(fp2,"#%d\n",k+1);
			for(i = 0 ;i <10 ;i++){
				memset(coordinate[i],0,10);
			}
			for(i = 0 ;i <120 ;i++){
				memset(map[i],0,120);
				memset(visit_map[i],0,120);
			}
			fscanf(fp1,"%d %d",&destination ,&size);
			fscanf(fp1,"%d %d",&s_x,&s_y);
			coordinate[0][0] = s_x;
			coordinate[0][1] = s_y;
			for(i = 1 ;i <= destination ;i++){
				fscanf(fp1,"%d %d",&coordinate[i][0],&coordinate[i][1]);
			}
			for(i = 0 ;i < size ;i++){
				for(j = 0 ; j < size ;j++){
					fscanf(fp1,"%d",&map[i][j]);
				}
			}
			if(destination == 1){//if only a destination to go
				cost = bfs(coordinate[0][0] ,coordinate[0][1] ,coordinate[1][0] ,coordinate[1][1] ,size);
			}
			else{
				int l;
				destination++;
				int ** list = (int **)malloc(sizeof(int*)* destination);
				for(i = 0 ;i < destination ;i++){
					list[i] = (int*)malloc(sizeof(int)* destination);
				}
				for(i = 0 ;i < destination ;i++){
					for(j = 0 ;j < destination ;j++){
						if(i == j){
							list[i][j] = 0;//list[i][j] = the least cost of point i -> point j ,so if i == j means the cost of point to the same point ,and that must be 0
						}
						else{
							list[i][j] = bfs(coordinate[i][0] ,coordinate[i][1] ,coordinate[j][0] ,coordinate[j][1] ,size);
							for(l = 0 ;l < 120 ;l++){
								memset(visit_map[l],0,120);
							}
							for(l = 0 ;l < 14400 ;l++){
								que[l].x=0;
								que[l].y=0;
								que[l].c=0;
							}
						}
					}
				}
				p = 0;//p is to count how many permutation of destination!
				int* permutation = (int*)malloc(sizeof(int)*(destination-1));//because line 186 des++
				for(i = 0 ;i < destination-1 ;i++){
					permutation[i] = i+1;//per[0] == 1 means point 1
				}
				perm(permutation,0,destination-1);
				cost = energy(0,list,destination-1);//energy is to count final cost of startpoint -> point x -> point y
				for(i = 1 ;i < p ;i++){
					if(cost > energy(i,list,destination-1)){//if find different sequence can made cost smaller
						cost = energy(i,list,destination-1);
					}
				}
			}
			fprintf(fp2,"cost:%d\n",cost);
		}

	}

	int data[] = {1,5,8,6,7,4,2,4,3};
	int i, j;
	for (i = 0; i < 3; i++) {
		for (j = 0; j < 3; j++) {
			map[i][j] = data[i*3+j];
		}
	}
	int cost = bfs(0 ,0 ,2 ,2,3);
	printf("%d\n", cost);
	return 0;
}
