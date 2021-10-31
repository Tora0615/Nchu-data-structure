#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TRUE 1
#define FALSE 0

FILE *f_write_ptr;
const char *filename_output = "HW3_output.txt";

typedef struct _point{
  int x;
  int y;
} point;

int getNeighbors(int*, int, int, int);
void printArr(int*,int);
void saveToArray(int*, int, char*, int);

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
  }/*else {
    f_write_ptr = fopen(filename_output,"w");
  }*/


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

    int *mapData = (int*)calloc(mapSize*mapSize,sizeof(int));

    // 一行一行讀到 array
    for (j =0; j<mapSize; j++){
      char contents[200] = {' '};
      fscanf(f_read_ptr,"%[^\n]",contents); //讀一句存到contents
      endLineBuf = fgetc(f_read_ptr); //吃掉換行符號
      saveToArray(mapData, j*mapSize, contents, mapSize);
    }

    printArr(mapData,mapSize);
    printf("\n");

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

// int getNeighbors(int *arr, int now_x, int now_y, int arr_size){
//   int dir[8][2] = {
//     //  左     左上      上      右上     右      右下       下      左下
//     {0, -1}, {-1, -1}, {-1, 0}, {-1, 1}, {0, 1}, {1, 1}, {1, 0}, {1, -1}
//   };
//
//   int i;
//   for (i = 0; i<8; i++){
//   }
// }






// (-1,-1)  (-1, 0)  (-1,1)
// (0, -1)  (0,  0)  (0, 1)
// (1, -1)  (1,  0)  (1, 1)



//陣列傳入函式，是新創立一個指向原本位置的指標變數
//若在裡面 swap 指標，會只有交換裡面
