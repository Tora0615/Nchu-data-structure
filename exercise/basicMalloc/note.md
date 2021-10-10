# malloc

## 基礎語法
```
//宣告變數與對應型態的指標變數
int *intptr;

// 動態記憶體配置
intptr = (int *)malloc(sizeof(int));
```



## 細部說明
* malloc( ) 是呼叫用來在記憶體 heap 區域動態配置記憶體
  * 回傳值
    * 記憶體可以取得 --> 回傳記憶體起始位置 (指標)
    * 記憶體無法取得 --> 回傳 NULL
  * 輸入值
    * 想要的記憶體大小，以 Byte 為單位
    * 通常這樣用：n * sizeof(int)
      * 表示 n 個 int 的大小

* (int *) 表示將指標轉型為正確的指標型態
  * 因為不同系統中預設 malloc 型態不同，可能會導致錯誤

## 記憶體 heap 區域說明

程式執行時，記憶體分配如下

![](./pic/memoryStruct.jpeg)

## malloc 失敗偵測
可在 malloc 同時加上判斷式，若失敗則退出程式。

### 寫法Ａ

```C
if((intptr = (int *)malloc(sizeof(int))) == NULL ||
(floatptr = (float *)malloc(sizeof(float))) == NULL){
  printf("malloc failed\n");
  exit(EXIT_FAILURE);   
}
```
### 寫法Ｂ
```c
if(!(intptr = (int *)malloc(sizeof(int))) ||
!( floatptr = (float *)malloc(sizeof(float)) ) ){
  printf("malloc failed\n");
  exit(EXIT_FAILURE);
}
```

* 註：
1. 只要遇到 exit( ) 就會退出程式，不論傳入值為何
2. EXIT_SUCCESS 為 0 ; EXIT_FAILURE 為 1
