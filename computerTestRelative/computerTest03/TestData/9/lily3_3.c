# include <stdio.h>
# include <stdlib.h>
struct Overcook{
	int id;
	int a;
	int e;
	int c;
	int state;
};
struct Overcook* oc;
int n,tot;
int check(){
	int i;
	for(i=0;i<n;i++){
		if(oc[i].state == 0){
			return 1;
		}
	}
	return 0;
}
void overcook(){
	int i,index=0,nowtime;
	while(check()){
		for(i=0;i<n;i++){
			if(oc[i].state ==0&& oc[i].state != 1 && oc[i].a+oc[i].c <= oc[i].e){
				index =i;
				break;
			}
		}
		for(i=0 ;i<n;i++){
			if(oc[i].a+oc[i].c > oc[i].e && oc[i].state != 1){
				oc[i].state = -1; 
			}
			if(oc[i].state != -1&& oc[i].state != 1){
				if(oc[index].a+oc[index].c > oc[i].a+oc[i].c){
					index = i;
				}
				if(oc[index].a+oc[index].c == oc[i].a+oc[i].c && oc[index].e > oc[i].e){
					index = i;
				}
			}
		}
		nowtime = oc[index].a+oc[index].c;
		for(i=0;i<n;i++){
			if(nowtime > oc[i].a){
				oc[i].a=nowtime;
			}
		}
		oc[index].state = 1;
		printf("i : %d\n",index);
	}
}
int main(){
	FILE* fp;
	fp =fopen("input_9-1.txt","r");
	if(fp==NULL){
		printf("open file failed\n");
	}
	else{
		int i,num,id,atime,etime,ctime;
		fscanf(fp,"%d\n",&num);
		oc = (struct Overcook*)malloc(sizeof(struct Overcook)*num);
		n=num;
		tot=0;
		for(i=0;i<num;i++){
			fscanf(fp,"%d %d %d %d\n",&id,&atime,&etime,&ctime);
			oc[i].id = id;
			oc[i].a = atime;
			oc[i].e = etime;
			oc[i].c = ctime;
			oc[i].state = 0;
		}
		overcook();
		for(i=0;i<n;i++){
			if(oc[i].state == 1){
				tot++;
			}
		}
		printf("%d",tot);
	}
	fclose(fp);
	return 0;
} 
