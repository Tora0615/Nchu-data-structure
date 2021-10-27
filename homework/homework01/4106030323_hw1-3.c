#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TRUE 1
#define FALSE 0

FILE *f_write_ptr;
const char *filename_output = "HW2_output.txt";

void toSpareMatrix (int*,int,int);
void getItemPosition(int*, int, int);
int getItemCount(int*, int, int);
int* evolution(int*, int*, int, int);
int getNeighbors(int*, int, int, int);
void printArr(int*,int);
void saveToArray(int*, int, char*, int);

int main(int argc, char const *argv[]) {

  FILE *f_read_ptr;
  const char *filename_input = "../testData/input_2.txt"; // 要注意 input file path

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

  dataCount = (int)fgetc(f_read_ptr) - '0';  //char(ascii) to int
  endLineBuf = fgetc(f_read_ptr); //吃掉換行符號

  // 幾筆資料做幾次 陣列大小與存活年代數 的讀取
  int i;
  for (i = 0; i < dataCount; i++) {
    int size, generation;
    fscanf(f_read_ptr,"%d", &size);
    endLineBuf = fgetc(f_read_ptr); //吃掉兩數字間空白
    fscanf(f_read_ptr,"%d", &generation);
    char trash[100];
    fscanf(f_read_ptr,"%[^\n]",trash); //吃掉換行符號前雜值
    endLineBuf = fgetc(f_read_ptr); //吃掉換行符號
    //printf("%d %d\n",size,generation);

    int *arrData = (int*)malloc(sizeof(int)*size*size);  // 主 array
    int *tempArr = (int*)malloc(sizeof(int)*size*size);  // 暫存 array

    // 一行一行讀到 array
    int j;
    for (j =0; j<size; j++){
      char contents[200] = {' '};
      fscanf(f_read_ptr,"%[^\n]",contents); //讀一句存到contents
      endLineBuf = fgetc(f_read_ptr); //吃掉換行符號
      saveToArray(arrData, j*size, contents, size);
    }

    arrData = evolution(arrData,tempArr,generation,size);
    //printArr(arrData,size);
    // printf("\n");
    toSpareMatrix(arrData,size,size);
  }



  fclose(f_read_ptr);
  fclose(f_write_ptr);
  printf("Complete !\n");
  return 0;
}

// 把讀到的數值 (一句的資料) 存到陣列
void saveToArray(int *arr, int offset, char *data, int lineLen){
  int i;
  for(i=0; i<lineLen; i++){
    *(arr + offset + i) = *(data + i*2) - '0';
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

int getNeighbors(int *arr, int now_x, int now_y, int arr_size){
  int dir[8][2] = {
    //  左     左上      上      右上     右      右下       下      左下
    {0, -1}, {-1, -1}, {-1, 0}, {-1, 1}, {0, 1}, {1, 1}, {1, 0}, {1, -1}
  };
  int neighborCount = 0;
  int i;
  for (i = 0; i<8; i++){

    // 4、5、6、7、8 都死亡 --> return 4 就好
    if(neighborCount >= 4){
      break;
    }

    // 要讀得座標
    int read_x = now_x + dir[i][0];
    int read_y = now_y + dir[i][1];

    // xy大小
    int arr_x = arr_size;
    int arr_y = arr_size;

    // 某處值為 1 -> count++ ; need check range (不小於0 & 不大於size)
    if( *(arr + read_x*arr_size + read_y) == 1 && \
      read_y > -1 && read_x > -1 && \
      read_y < arr_y && read_x < arr_x){
      neighborCount++;
    }

  }
  return neighborCount;
}

// 傳入有資料的陣列、暫存陣列與要演化幾代
int* evolution(int *mainArr, int *tempArr, int generation, int size){
  int gen, i, j;
  for(gen = 0; gen < generation; gen++){
    for(i = 0; i<size; i++){
      for(j = 0; j<size; j++){

        // 0、1、4 (5、6、7、8) --> 死 (0)
        // 2 --> same
        // 3 --> 活 (1)
        switch (getNeighbors(mainArr, i, j, size)) {
           case 0: case 1: case 4:
              *(tempArr + i*size + j) = 0;
              break;
           case 2:
              *(tempArr + i*size + j) = *(mainArr + i*size + j);
              break;
           case 3:
              *(tempArr + i*size + j) = 1;
              break;
        }
      }
    }

    // mainArr <-- tempArr <-- newArr
    // 這只有利用內部的指標變數進行交換，因此要傳出去
    int* newArr = (int*)calloc(size*size,sizeof(int));  //malloc + 初始化 0 = calloc
    mainArr = tempArr;  // main 用 temp 覆蓋
    tempArr = newArr;
  }
  return mainArr;
}

// 印出第一行的基本資訊 (row, col, value)
int getItemCount(int* arr, int row, int col){
  int count = 0;
  for (int i = 0; i < row*col; i++) {
    if( *(arr + i) == 1 ){
      count++;
    }
  }
  return count;
}

// 印出非零項的位置與值
void getItemPosition(int* arr, int row, int col){
  int i=0, j=0;
  for (i = 0; i < row; i++) {
    for(j = 0; j < col; j++){
      if( *(arr + i*row + j) != 0 ){
        //printf("%d %d %d\n", i, j, getNeighbors(arr, i, j, row));
        fprintf(f_write_ptr,"%d %d %d\n", i, j, getNeighbors(arr, i, j, row));
      }
    }
  }
}

void toSpareMatrix (int* arr, int row, int col){
  //printf("%d %d %d\n",row,col,getItemCount(arr,row,col));
  fprintf(f_write_ptr,"%d %d %d\n",row,col,getItemCount(arr,row,col));
  getItemPosition(arr,row,col);
}


// (-1,-1)  (-1, 0)  (-1,1)
// (0, -1)  (0,  0)  (0, 1)
// (1, -1)  (1,  0)  (1, 1)



//陣列傳入函式，是新創立一個指向原本位置的指標變數
//若在裡面 swap 指標，會只有交換裡面
