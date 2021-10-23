#include <stdio.h>
#include <stdlib.h>

#define FALSE 0
#define TRUE  1

typedef struct _sexType{

  // 會讀取是 female or male，並轉成 array index 的樣式
  // 其資料格式是 %u (unsigned int)
  // (如 print person1.sexInfo.sex 會印出 1 (male))
  enum tagField {female, male} sex;

  // 其中一個賦值後，會蓋掉其他的
  union {
    int children;
    int beard;
  } u;
} sexType;

typedef struct _humanBeing{
  char name[10];
  int age;
  float salary;
  sexType sexInfo;
} humanBeing;

int main(int argc, char const *argv[]) {
  humanBeing person1, person2;

  person1.sexInfo.sex = male;  //只能是 enum 中定義的 male or female，不然會噴錯
  person1.sexInfo.u.beard = FALSE;
  // person1.sexInfo.u.children = 4; //錯誤寫法，會蓋掉 beard 的值，但不會噴錯

  person2.sexInfo.sex = female;
  person2.sexInfo.u.children = 4;

  printf("%d\n",person1.sexInfo.sex);

  return 0;
}
