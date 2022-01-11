#include <stdio.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0
#define INPUTFILE "TestData\\9\\input_9-2.txt"

FILE *f_read_ptr;
FILE *f_write_ptr;

typedef struct _order{
	int id;
	int arrive;
	int deadline;
	int cooktime;
	int state;		
	/*  0 : haven't done yet, 
		1 : can do, 
		-1 : can't do */
}order;

int orderCount;
order *orderList;

int canDo(){
	int i;
	for(i=0; i<orderCount; i++){
		/* 0 : haven't done yet -> can do*/
		if(orderList[i].state == 0){
			return TRUE;
		}
	}
	return FALSE;
}


void calculateOrder(){
	int i, nowtime;
	/* have someone haven't done yet */
	while(canDo()){
		int target = -1;
		/* all order find one to do */
		for(i=0; i<orderCount; i++){
			if(orderList[i].state == 0){
				/* delete can't do*/
				if(orderList[i].arrive + orderList[i].cooktime > orderList[i].deadline){
					orderList[i].state = -1 ;
				}
				/* find target */
				else{
					/* first target MUST haven't done*/
					if(target == -1 && orderList[target].state != 1){
						target = i;
					}else{
						/* current done time <  target done time -> update target */
						if(orderList[target].arrive + orderList[target].cooktime 
							> orderList[i].arrive + orderList[i].cooktime){
							target = i;
						}
						/* if done time equal -> choose deadline earlier one*/
						else if(orderList[target].arrive + orderList[target].cooktime 
									== orderList[i].arrive + orderList[i].cooktime){
							if(orderList[target].deadline > orderList[i].deadline){
								target = i;
							}	
						}
					}
				}
			}
		}
		/* set target's state to 1*/
		orderList[target].state = 1;
		
		/* change all arrive time */
		nowtime = orderList[target].arrive + orderList[target].cooktime;
		for(i=0; i<orderCount; i++){
			orderList[i].arrive = nowtime;
		}
	}
}

int main(void){
	/* read file */
	if ( !(f_read_ptr = fopen(INPUTFILE,"r")) ){
		printf("Cannot open file : %s\n", INPUTFILE);
		return 0;
	}
	
	/* read data count */
	fscanf(f_read_ptr,"%d\n",&orderCount);
	
	/* init order array and save it */
	int i;
	orderList = (order*)malloc(sizeof(order) * orderCount);
	for(i=0; i<orderCount; i++){
		int id, arrive, deadline, cooktime;
		fscanf(f_read_ptr,"%d %d %d %d\n", &id, &arrive, &deadline, &cooktime);
		orderList[i].id = id;
		orderList[i].arrive = arrive;
		orderList[i].deadline = deadline;
		orderList[i].cooktime = cooktime;
		orderList[i].state = 0;
	}
	
	/* calculate best */
	calculateOrder();
	
	/* if state is 1, add can do order count and print answer */
	int canDoCount = 0;
	for(i=0; i<orderCount; i++){
		if(orderList[i].state == 1){
			canDoCount += 1;
		}
	}
	printf("%d",canDoCount);
	
	fclose(f_read_ptr);
	return 0;
}
