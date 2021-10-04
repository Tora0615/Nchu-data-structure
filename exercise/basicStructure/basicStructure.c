#include <stdio.h>
#include <stdlib.h>

// typedef 用法
// typedef int newInt;  //為 int 取了一個叫 newInt 的別名

// struct 用法
// struct student {
//   int no;
//   char name[20];
// };

// struct 自我參考結構寫法 (會指向與本身相同的結構體)
// struct node {
//   int data;
//   struct node *pointer;  // 宣告結構體 node 的指標變數 pointer (前面要記得加 struct)
// };

// typedef + struct + 自我參考結構的混合寫法
typedef struct Node {
  int data;
  struct Node *next;
} node;
// ---> 宣告結構體 Node，並將別名取為 node，其中有指向自我參考結構的指標


int main(int argc, char const *argv[]) {
  // 宣告兩個節點
  node a;
  node b;

  // 資料與指標賦值
  a.data = 1;
  a.next = &b;
  b.data = 2;
  b.next = NULL;

  // 印出
  printf("data : %d, addr : %p\n", a.data, a.next );
  printf("data : %d, addr : %p\n", b.data, b.next );


  return 0;
}
