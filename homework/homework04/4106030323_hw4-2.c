#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include<limits.h>
#define TRUE 1
#define FALSE 0

/* NEED Change Before upload*/
//#define INPUTFILE "Test_Case\\test_case_2-3\\input_2.txt"
//#define INPUTFILE  "../Test_Case/test_case_2-1/input_2.txt"
#define INPUTFILE "input_2.txt"

#define OUTPUTFILE "output_2.txt"
#define DEBUG 0

FILE *f_read_ptr;
FILE *f_write_ptr;

typedef struct data *list;
struct data{
	int point;
	int cost;
	list next;
};

list map[10001];
int report[10001][10001], top = 0, past[10001];
void initial(int);
void build(int);
int walk(int, int, int);
void add_point(int, int, int);

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
	//printf("count %d\n",count);
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
	}  else {
		f_write_ptr = fopen(OUTPUTFILE,"w");
	}

	int i = 0, j = 0, point, times, total = 0;
	long long int min = INT_MAX;
	char endLineBuf = ' ';
	char *contents = (char*)malloc(sizeof(char)*5000000);
	
	fscanf(f_read_ptr,"%[^\n]",contents);
	endLineBuf = fgetc(f_read_ptr);
	int index = 0;
	int location = stringToInt(contents);
	while(!isspace(contents[index++]));
	int location_count = stringToInt(&contents[index]);
	
	initial(location);
	while(i < location-1){
		index = 0;
		fscanf(f_read_ptr,"%[^\n]",contents);
		endLineBuf = fgetc(f_read_ptr);
		int u = stringToInt(contents);
		while(!isspace(contents[index++]));
		int v = stringToInt(&contents[index]);
		while(!isspace(contents[index++]));
		int p = stringToInt(&contents[index]);
		//printf("-%d %d %d\n", u,v,p);
		report[u][v] = p;
		report[v][u] = p;
		add_point(u,v,p);
		add_point(v,u,p);
		i++;
	}
 
	while(j < location_count){
		index = 0;
		fscanf(f_read_ptr,"%[^\n]",contents);
		endLineBuf = fgetc(f_read_ptr);
		int point = stringToInt(contents);
		while(!isspace(contents[index++]));
		int times = stringToInt(&contents[index]);
		map[point]->cost = times;
		j++;
	}
	build(location);
 
	for(i = 1;i <= location; i++){
		for(j = 1; j<= location;j++){
			if(map[j]->cost){
				total += (report[i][j]*2*map[j]->cost);
			}
		}
		if(total < min){
			min = total;
		}
		total = 0;
	}
	//printf("%lld\n",min);
	fprintf(f_write_ptr, "%lld\n", min);	
 
 	for(i = 1; i <= location; i++){
		for(j = 1; j <= location; j++){
			if(map[j]->cost){
				total += (report[i][j]*2*map[j]->cost);
			}
		}
		if(total == min){
			//printf("%d ",i);
			fprintf(f_write_ptr, "%d ",i);	
		}
		total = 0;
	}

	fclose(f_read_ptr);
	fclose(f_write_ptr);
	free(contents);
	printf("Complete !\n");
	return 0;
}

 

void initial(int location){
	int j, i;
	for(j = 1;j <= location; j++){
		map[j] = (list)malloc(sizeof(struct data));
		
		map[j]->cost = 0;
		map[j]->point = -1;
		map[j]->next = NULL;
	}
	
	for(i = 1;i <= location;i++){
		for(j = 1;j <= location;j++){
			report[i][j] = 0;
		}
	}
}

void add_point(int a, int b, int value){
	list temp, find = map[a];
	
	while(find->next){
		find = find->next;
	}
	
	temp = (list)malloc(sizeof(struct data));
	temp->point = b;
	temp->cost = value;
	temp->next = NULL;
	find->next = temp;
}

int walk(int i, int a, int count){
	past[a] = 1;
	list find = map[a];
	find = find->next; 
	
	while(find){
		if( !past[find->point] ){
			report[i][find->point] = walk(i, find->point, count + find->cost);
		}
		find = find->next;
	}
	return count;
}

void build(int location){
	int i = 1, j = 1, count = 0;
	while(i <= location){
		for(j = 0; j <= location; j++){
			past[j] = 0;
		}
		walk(i, i, count);
		i++;
	}
}
