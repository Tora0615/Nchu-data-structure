# 基礎結構用法
## typedef 用法
```typedef int newInt;```  

說明：為 int 取了一個叫 newInt 的別名

## struct 用法
```
struct student {
  int no;
  char name[20];
};
```

## struct 自我參考結構寫法
```
struct node {
  int data;
  struct node *pointer;  // 宣告結構體 node 的指標變數 pointer
  // 前面的 struct 要記得加
};
```
說明：會指向與本身相同的結構體


## typedef + struct + 自我參考結構的混合寫法
```
typedef struct Node {
  int data;
  struct Node *next;
} node;
```
說明：宣告結構體 Node，並將別名取為 node，其中有指向自我參考結構的指標
