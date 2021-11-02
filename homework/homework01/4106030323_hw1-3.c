#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TRUE 1
#define FALSE 0
#define MAX 1
#define OPER <




typedef struct _point{
  int x;
  int y;
} point;

typedef struct _node {
  int x;
  int y;
  int cost;
  int isPassed;
  int isSpecial;
  int height;
}node;

FILE *f_write_ptr;
const char *filename_output = "HW3_output.txt";
node *queue ;

int getNeighbors(int*, int, int, int);
void printArr(int*,int);
void saveToArray(int*, int, char*, int);
int heightAbs(int, int);
int isFull();
int isEmpty();
void queueFull();
void swapNode(node*, int, int);
node deleteFromHeap(node*);
void addToHeap(node*, node);
void printStructArr(node*,int);
int bfs(point, point, int,node[]);
int rear = 0;  //後面    1開始存，
int front = 1;  //前面
int multiply = 2;




int main(int argc, char const *argv[]) {

  FILE *f_read_ptr;
  const char *filename_input = "../testData/input_3.txt"; // 要注意 input file path

  // input file open
  if (!(f_read_ptr = fopen(filename_input,"r"))){
    printf("Cannot open file : %s\n", filename_input);
    exit(EXIT_FAILURE);
  }

  // open output file with fool proof.
  if((f_write_ptr = fopen(filename_output,"r"))){
    fclose(f_write_ptr);
    printf("File %s have already exist.\nContinue to overwrite output file ? [Y/N] ",filename_output);
    char temp;
    scanf(" %c",&temp);
    if (temp == 'Y' || temp == 'y'){
        f_write_ptr = fopen(filename_output,"w");
    }else{
      printf("Override canceled\n");
      fclose(f_read_ptr);
      exit(EXIT_FAILURE);
    }
  }else {
    f_write_ptr = fopen(filename_output,"w");
  }


  // from input file read line
  char endLineBuf = ' ';
  int dataCount = 0;

  //幾筆資料
  dataCount = (int)fgetc(f_read_ptr) - '0';  //char(ascii) to int
  endLineBuf = fgetc(f_read_ptr); //吃掉換行符號

  // 幾筆資料做幾次 陣列大小與存活年代數 的讀取
  int i;
  for (i = 0; i < dataCount; i++) {
    int end_count, mapSize;
    char trash[100];

    fscanf(f_read_ptr,"%d", &end_count);
    endLineBuf = fgetc(f_read_ptr); //吃掉兩數字間空白
    fscanf(f_read_ptr,"%d", &mapSize);
    fscanf(f_read_ptr,"%[^\n]",trash); //吃掉換行符號前雜值
    endLineBuf = fgetc(f_read_ptr); //吃掉換行符號

    point start;
    fscanf(f_read_ptr,"%d", &start.x);
    endLineBuf = fgetc(f_read_ptr); //吃掉兩數字間空白
    fscanf(f_read_ptr,"%d", &start.y);
    fscanf(f_read_ptr,"%[^\n]",trash); //吃掉換行符號前雜值
    endLineBuf = fgetc(f_read_ptr); //吃掉換行符號

    point end[end_count];
    int j;
    for (j = 0; j < end_count; j++) {
      fscanf(f_read_ptr,"%d", &end[j].x);
      endLineBuf = fgetc(f_read_ptr); //吃掉兩數字間空白
      fscanf(f_read_ptr,"%d", &end[j].y);
      fscanf(f_read_ptr,"%[^\n]",trash); //吃掉換行符號前雜值
      endLineBuf = fgetc(f_read_ptr); //吃掉換行符號
    }

    //有存進去
    // for (j = 0; j < end_count; j++) {
    //   printf("%d %d\n", end[j].x, end[j].y);
    // }


    int *mapData = (int*)calloc(mapSize*mapSize,sizeof(int));

    // 一行一行讀到 array
    for (j =0; j<mapSize; j++){
      char contents[200] = {' '};
      fscanf(f_read_ptr,"%[^\n]",contents); //讀一句存到contents
      endLineBuf = fgetc(f_read_ptr); //吃掉換行符號
      saveToArray(mapData, j*mapSize, contents, mapSize);
    }

    //printArr(mapData,mapSize);
    //printf("\n");


    queue = calloc(MAX, sizeof(node));
    node template[mapSize*mapSize];

    // 初始化
    int k,l;
    for (k = 0; k < mapSize; k++) {
      for (l = 0; l < mapSize; l++) {
        template[k*mapSize+l].x = k ;
        template[k*mapSize+l].y = l ;
        template[k*mapSize+l].cost = 0 ;
        template[k*mapSize+l].isPassed = 0 ;
        template[k*mapSize+l].isSpecial = 0 ;
        template[k*mapSize+l].height = *(mapData + k*mapSize + l);
      }
    }

    // printStructArr(template,mapSize);
    // printf("%d\n",bfs(start,end[0],mapSize,template));
    // // 歸零
    // rear = 0;  //後面    1開始存，
    // front = 1;  //前面
    // multiply = 2;

    //int totalCost = bfs(start,end[0],mapSize,template);


    int totalCost;
    if(end_count == 1){//if only a end_count to go
      totalCost = bfs(start,end[0],mapSize,template);

      // 歸零
      rear = 0;  //後面    1開始存，
      front = 1;  //前面
      multiply = 2;
      free(queue);
    }else{
      int i,j;
      point pointBox[end_count+1];
      pointBox[0] = start;
      for (i = 0; i < end_count; i++) {
        pointBox[i+1] = end[i];
      }
      int pointToPoint[(end_count+1)*(end_count+1)];

      for (i = 0; i < end_count+1; i++) {
        for (j = 0; j < end_count+1; j++) {
          rear = 0;  //後面    1開始存，
          front = 1;  //前面
          multiply = 2;
          queue = calloc(MAX, sizeof(node));
          //printf("%d\n",bfs(pointBox[i],pointBox[j],mapSize,template));
          //pointToPoint[i * (end_count+1) + j] = bfs(pointBox[i],pointBox[j],mapSize,template);
        }
      }

      for (i = 0; i < end_count+1; i++) {
        for (j = 0; j < end_count+1; j++) {
          //printf("%d\n",pointToPoint[i *(end_count+1) + j]);
        }
      }
    }
    // printf("#%d\n",i);
    // printf("cost:%d\n",totalCost);
    fprintf(f_write_ptr,"#%d\n",i);
    fprintf(f_write_ptr,"cost:%d\n",totalCost);


  }



  fclose(f_read_ptr);
  fclose(f_write_ptr);
  printf("Complete !\n");
  return 0;
}

// 把讀到的數值 (一句的資料) 存到陣列
void saveToArray(int *arr, int offset, char *data, int lineLen){
  int i;
  int temp = 0;
  int count = 0;
  for(i=0; i< strlen(data) ; i++){
    char Buf = ' ';
    char contents[20] = {' '};
    if( *(data + i) ==  ' ' || *(data + i) ==  '\0' || *(data + i) ==  '\r'){
      *(arr + offset + count) = temp;
      count += 1;
      temp = 0;
    }else{
      temp = temp * 10 + (*(data + i) - '0');
    }
  }
}

// 印出陣列
void printArr(int *arr,int size){
  int i,j;
  for (i = 0; i < size; i++) {
    for (j = 0; j < size; j++){
      printf("%d ", *(arr + i*size + j));
    }
    printf("\n");
  }
}

int heightAbs(int a, int b){
  if (a>b){
    return a-b;
  }else{
    return b-a;
  }
}



int isFull(){
  if(rear == MAX * multiply / 2 - 1){
    return TRUE;
  }
  return FALSE;
}

int isEmpty(){
  if(front == rear){
    return TRUE;
  }
  return FALSE;
}

void queueFull(){
  //加倍
  queue = realloc(queue, sizeof(node) * MAX * multiply);
  multiply *= 2;
}

void swapNode(node *arr, int index1, int index2){
  node temp;
  temp = *(arr+index1);
  *(arr+index1) = *(arr+index2);
  *(arr+index2) = temp;
}

node deleteFromHeap(node *arr){
  node returnVal;
  // root and rear swap
  swapNode(arr, rear, front);
  // delete rear
  returnVal = queue[rear--];
  // root sink
  int index = 1;
  while( (index*2 < rear) && ((arr + index*2)->cost OPER (arr + index)->cost || (arr + index*2+1)->cost OPER (arr + index)->cost) ){
    // 下沉要比較，最大堆積要沉到比較大那邊
    if( (arr + index*2)->cost OPER (arr + index*2 + 1)->cost ){
      swapNode(arr, index, index*2 );
      index = index * 2;
    }else{
      swapNode(arr, index, index*2+1 );
      index = index * 2 + 1;
    }
  }
  return returnVal;
}

void addToHeap(node *arr, node value){
  // check heap size
  if(isFull()){
    queueFull();
  }
  // Add to tail
  *(arr + ++rear) = value;
  // compare and float to root    // >=1
  int index = rear;
  while( (index/2 >= front) && ((arr + index)->cost OPER (arr + index/2)->cost) ){
    swapNode(arr, index, index/2 );
    index = index / 2 ;
  }
}

void printStructArr(node *arr,int size){
  int i,j;
  for (i = 0; i < size; i++) {
    for (j = 0; j < size; j++){
      printf("%d ", (arr + i*size+j)->x);
      printf("%d ", (arr + i*size+j)->y);
      printf("%d ", (arr + i*size+j)->cost);
      printf("%d ", (arr + i*size+j)->isPassed);
      printf("%d ", (arr + i*size+j)->isSpecial);
      printf("%d ", (arr + i*size+j)->height);
      printf("\n");
    }
  }
}


int bfs(point start, point end, int size,node array[]){

  if(start.x == end.x && start.y == end.y){
    return 0;
  }

  int dir[8][2] = {
    //  左     左上      上       右上     右      右下       下      左下
    {0, -1}, {-1, -1}, {-1, 0}, {-1, 1}, {0, 1}, {1, 1}, {1, 0}, {1, -1}
  };

  //printf("%d %d ,%d %d\n",start.x,start.y,end.x,end.y);
  //printf("s~%d\n",size);

  addToHeap(queue, array[start.x *size + start.y]);

  node temp ;
  while(TRUE){
    temp = deleteFromHeap(queue);
    while(temp.isPassed){
      temp = deleteFromHeap(queue);
    }

    array[temp.x *size + temp.y].isPassed = TRUE;  //走過標記


    //printf("temp : %d %d\n",temp.x,temp.y);
    if(temp.x == end.x && temp.y == end.y){
      break;
    }
    int i;
    for(i=0;i<8;i++){
      int tempX = temp.x + dir[i][0];
      int tempY = temp.y + dir[i][1];
      //printf("tempXY : %d %d",tempX,tempY);
      if(tempX > -1 && tempY > -1 && tempX < size && tempY < size ){
        array[tempX *size + tempY].cost \
            = heightAbs(array[tempX *size + tempY].height, temp.height) \
                + temp.cost;
        //printf(" cost:%d",array[tempX *size + tempY].cost);
        //printf("here1\n");
        //printf("%d %d\n",tempX,tempY);
        addToHeap(queue, array[tempX *size + tempY]);
        //printf("here2\n");
      }
      //printf("\n");
    }
    //printStructArr(queue,size);
  }
  //printStructArr(queue,size);
  return temp.cost;
}






// (-1,-1)  (-1, 0)  (-1,1)
// (0, -1)  (0,  0)  (0, 1)
// (1, -1)  (1,  0)  (1, 1)



//陣列傳入函式，是新創立一個指向原本位置的指標變數
//若在裡面 swap 指標，會只有交換裡面
