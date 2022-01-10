#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#define TRUE 1
#define FALSE 0

/* NEED Change Before upload*/
#define INPUTFILE "Test_Case\\test_case_3-1\\input_3.txt"
//#define INPUTFILE  "../Test_Case/test_case_3-1/input_3.txt"
//#define INPUTFILE "input_3.txt"

#define OUTPUTFILE "output_3.txt"
#define DEBUG 0

FILE *f_read_ptr;
FILE *f_write_ptr;

struct Color{
	int have;
	int cost;
};
struct Color* color;
int** block;
int* size;
int* x;
int mincost,N,L;
void ans (void){
	int temp=0,i;
	for(i = 0 ;i<N;i++){
		// cost = bolcksize * colorcost
		temp+=size[i]*color[x[i]].cost;
	}
	if(temp < mincost){
		mincost = temp;		
	}
	return; 
}
int ok(int trace){
	int i;
	for(i = 0 ; i<trace ;i++){
		if(block[trace][i]==1){
			if(x[i] == x[trace]){
				return 0;
			}
		}
	}
	return 1;
}
void allpossible(int trace){
	int i;
	if(trace >N-1){
		ans();
	}
	else{
		for(i=0;i<L;i++){
			x[trace]=i;
			if(ok(trace)){
				if(color[x[trace]].have >= size[trace]){
					color[x[trace]].have -= size[trace];
					allpossible(trace+1);
					color[x[trace]].have += size[trace];
				}	
			}
		}	
	}
}

int stringToInt(char *contents){
  	int index = 0, count = 0, isNegative = FALSE;
  	while(*(contents + index) != '\0' && *(contents + index) != '\r' && *(contents + index) != ' '){
	  	if(*(contents + index) == '-'){
	  		isNegative = TRUE;
		}else{
			count = count*10 + (*(contents + index) - '0');
		}
	    index += 1;
	}
	if(isNegative){
		count = count* (-1);
	}
	return count;
}



int main(int argc, char const *argv[]) {

	if (!(f_read_ptr = fopen(INPUTFILE,"r"))){
		printf("Cannot open file : %s\n", INPUTFILE);
		exit(EXIT_FAILURE);
	}

	if((f_write_ptr = fopen(OUTPUTFILE,"r"))){
		fclose(f_write_ptr);
		printf("File %s have already exist.\nContinue to overwrite output file ? [Y/N] ",OUTPUTFILE);
		char temp;
		scanf(" %c",&temp);
		if (temp == 'Y' || temp == 'y'){
		    f_write_ptr = fopen(OUTPUTFILE,"w");
		}else{
		  printf("Override canceled\n");
		  fclose(f_read_ptr);
		  exit(EXIT_FAILURE);
		}
	} else {
		f_write_ptr = fopen(OUTPUTFILE,"w");
	}

	char endLineBuf = ' ';
	char *contents = (char*)malloc(sizeof(char)*5000000);
	int i,j;
	int a2,u,v,b,c,input_size,temp_max_cost = 0, index;
	char a1;
	
	
	// fscanf(fp,"%d %d %d\n",&n,&e,&l);
	index = 0;
	fscanf(f_read_ptr,"%[^\n]",contents);
	endLineBuf = fgetc(f_read_ptr);
	int n = stringToInt(contents);
	while(!isspace(contents[index++]));
	int e = stringToInt(&contents[index]);
	while(!isspace(contents[index++]));
	int l = stringToInt(&contents[index]);
	
	N=n;
	L=l;
	block = calloc(n,sizeof(int*));
	size = calloc(n,sizeof(int));
	color = (struct Color*)malloc(sizeof(struct Color)*l);
	x = (int*)malloc(sizeof(int)*n);
	mincost = 0;
	for(i = 0 ;i<n ;i++){
		fscanf(f_read_ptr,"%d ",&input_size);
		size[i] = input_size;
		mincost += size[i];
		block[i] = calloc(n,sizeof(int));
	}
	for(i = 0 ;i < e;i++){
		fscanf(f_read_ptr,"%d %d\n",&u,&v);
		block[u-1][v-1] = 1;
		block[v-1][u-1] = 1;
	}
	for(i = 0 ;i <l ;i++){
		fscanf(f_read_ptr,"%c%d %d %d\n",&a1,&a2,&b,&c);
		color[i].have = b;
		color[i].cost = c;
		if(color[i].cost > temp_max_cost){
			temp_max_cost = color[i].cost;
		}
	}
	mincost *= temp_max_cost;
	allpossible(0);	
	//printf("mincost=%d",mincost);
	fprintf(f_write_ptr, "%d", mincost);


	fclose(f_read_ptr);
	fclose(f_write_ptr);
	free(contents);
	printf("Complete !\n");
	return 0;
}
