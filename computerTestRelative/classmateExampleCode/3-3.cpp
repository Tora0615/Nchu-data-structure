#include <stdio.h>
#include <stdlib.h>

//==========================================================================================================//
//	The structure of orders :																				//
// 	[id] 			use to distinguish orders																//
//	[arrival] 		indicates the time when the order arrived.												//
//  [deadline] 		indicates how long the meal can be waited for.											//
//  [cookingTime] 	indicates how long the order need to be prepare.										//
//  [completeTime] 	indicates how early the order can be completed. (arrival+cookingTime)					//
//  [idleTime] 		indicates how many time remaining after the order is completed. (deadline-completeTime)	//
//	[next]			point to the next order.																//
//==========================================================================================================//
struct Order_struct{
	int id;
	int arrival;
	int deadline;
	int cookingTime;
	int completeTime;
	int idleTime;
	struct Order_struct *next;
};

//  Head pointer  //
Order_struct *head=NULL; 

//  Read input file.  //
int readOrder(){
	int n,i;
	Order_struct *tail ;
	//  read n, assuming open file must be successful.  //
	//  ( You can make code for exception handling. )   //
	FILE *fp = fopen("input_3.txt","r");
	fscanf(fp, "%d", &n);
	//  read orders  //
	for (i=0;i<n;i++){ 
		Order_struct *temp = (Order_struct *) malloc(sizeof(struct Order_struct)); 
		fscanf(fp, "%d %d %d %d", &temp->id, &temp->arrival, &temp->deadline, &temp->cookingTime);
		temp->completeTime = temp->arrival + temp->cookingTime; 
		temp->idleTime = temp->deadline - temp->completeTime;
		//  Remove orders that cannot be completed,  //
		//  the total number of orders(n) minus 1.   //
		if ( temp->completeTime > temp->deadline ){
			free(temp);
			continue;
			n-=1;
		} 
		//  connect list  //
		if (head==NULL){
			head = temp;
			tail = temp;
		}
		else{		
			tail->next = temp;
			tail = tail->next;
		}	
	}
	tail->next=NULL;
	//  close file //
	fclose(fp);
	return n;
}

//  Show the contents of the order list  //
void show(){
	Order_struct *tmp=head;
	printf("\n// Current list //\n");
	while( tmp != NULL ){
		printf("%d %3d %3d %3d %3d %3d\n", tmp->id, tmp->arrival, tmp->deadline, tmp->cookingTime, tmp->completeTime, tmp->idleTime);
		tmp=tmp->next;
	}
}

//==========================================================================================================//
//  Insertion sort  :                     																	// 
//  (You can choose the sort method you like.)  															//
//	You have to make the node with the earlier CompleteTime be in the front.								//
//	If the CompleteTime is equal, compare the IdleTime.														//
//==========================================================================================================//
void sort(){
	Order_struct *sorted = NULL;
	Order_struct *current = head;
	while(current!=NULL){
		Order_struct *next = current->next;
		//  Special case where 'sorted' is NULL.  //
		if(sorted==NULL){
			sorted = current;
			head = current->next;
			current->next = NULL;
		}
		// If the inserted node is smaller than the starting point. //
		else if( sorted->completeTime > current->completeTime || (sorted->completeTime == current->completeTime && sorted->idleTime > current->idleTime) ){
			Order_struct* tmpNext=sorted;
			sorted=current;
			head=current->next;
			current->next=tmpNext;	
		}
		// For normal cases, find the right place to insert.
		else{
			Order_struct* now = sorted;
			//  use completeTime as key to sort  //
			while( now->next!=NULL && now->next->completeTime < current->completeTime )
				now = now->next;
			//  if completeTime is equal, use idleTime as key to sort.  //
			while(now->next!=NULL && now->next->completeTime == current->completeTime && now->next->idleTime < current->idleTime )
				now = now->next;
			//  Insert node  //	
			Order_struct* tmp=now->next;
			now->next = current;
			head = current->next;
			current->next=tmp;
		}
		//  point to the next.  //
		current = next;
	}
	//  Head pointer points to the sorted order list.  //
	head=sorted;
} 

//  Delete the node which idleTime is less than 0.  //
int deleteNode(int num){
	Order_struct *previous=NULL, *current=head;
	while(current!=NULL){
		//  After updating, the order that could not be completed should be removed.       //
		//  The 'next' ptr of previous should point to the next node of the current node.  //
		if(current->idleTime<0){
			Order_struct *tmp=current;
			//  Delete the first node.  //
			if (current==head){
				head = current->next;
				current = head;
			}
			//	Delete the node exclude first node.  //
			else{
				previous = current->next;
				current = previous->next;
			}
			//  Release the memory of the deleted node  //
			free(tmp);
			//  The total number of order minus 1.  // 
			num-=1;	
		}
		//  If Current->idleTime > 0, find the next node.  //
		else{
			previous=current;
			current=current->next;
		}
	}
	return num;
}

int main(){
	//  initial n, sort the order list.  //
	int n=readOrder();
	sort();
	//  Schedule the orders.  //
	int time=0, maxJob=0;
	while(n>0){
		//  Select the best order now. (After sorting.)  //
		Order_struct* temp = head;
		time = temp->completeTime;
		head = head->next;
		//  The maximum number of jobs that can be completed plus 1.  // 
		maxJob+=1;
		//	Update order list.  //
		temp = head;
		while( temp!=NULL ){
			if (temp->arrival < time){
				temp->arrival = time;
				temp->completeTime = temp->arrival + temp->cookingTime;
				temp->idleTime = temp->deadline - temp->completeTime;
			}
			temp=temp->next;
		}
		//  Delete the node which idleTime is less than 0.  //
		n=deleteNode(n);
		//  plz sort again after update.  //
		sort();
		n--;	
	}
	//  print out the answer.  //
	printf("%d\n",maxJob);
	return 0;
}
