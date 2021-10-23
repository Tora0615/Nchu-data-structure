## notes

### 01

#### 中序轉後續
1. 遇運算元 (數字) 直接輸出 (print)
2. 堆疊 (push) 運算子與左括號
  * 要比 stack 中優先度高再 push 進去
3. 堆疊 (stack) 中運算子優先順序大於讀入的運算子優先順序的話 :
  * 直接輸出堆疊中的運算子
  * 再將讀入的運算子置入堆疊
4. 遇右括號輸出堆疊中的運算子至左括號
5. 左括號優先度在外面與堆疊中不同

#### 實際魔改版本
1. 原本的中轉後的一些邏輯需要更改
  * ')' 與 '(' 調換
    * 整份程式碼都需要更改 (有 getLevel ＆ processItem)
  * 讀進來的一句，一個一個掃描的方向由 左到右 改成 右到左
    * i = 0; i < len ; i++ --> i = len -1 ; i > -1 ; i--
    * 讀到最左邊後再丟一個 '\0' 給 processItem
      * 是用來偵測是否讀完一句，要一直 pop 用
        * while (stack != empty) --> pop
      * 因為原本的是內容讀完後會丟 '\r' or '\0' 進去
  * 負號判斷邏輯也要更改 :
    * 原本左讀到右 : - 左方是符號，就是負號 (or在最一開始也是)
    * 右讀到左 : - 右方是數字，就是負號 (or在最一開始也是)
2. 魔改中轉後輸出的結果再反向印出就是答案了
  * 可以用另一個 stack 暫存要輸出的內容，最後再 pop 印出

#### 正常中轉後


#### 其他筆記們
* char array pointer 取值 --> *(ptr+i)
* scanf :
  * %[] 讀入一个字符集
  * "%[^=]" 读入任意多的字符,直到遇到"="停止
* 陣列宣告兩方法
  * char *stringBuf = (char*) malloc(sizeof(char)*101);
  * char stringBuf[101];
* '\0' 傳入 function 會變成 Null --> 不能這樣用

## 參考資料們

### 第一題
https://magiclen.org/arithmetic/

### 第二題
https://openhome.cc/Gossip/AlgorithmGossip/LifeGame.htm

### 第三題



## 踩雷記錄
'\0' 無法傳入 function 或 print
會被視為 null



// 讀數字 or 運算子
void getUnit(){
  看一次讀幾個
}

int lastIsChar = FALSE;

void posfix (input) {

  if (isdigit(input)){
    print("%c", input)
  }

  else{   //運算子
    // 判斷
    if( input == ')' ){
      while (true){
        char temp = pop();
        if (temp == '(') {
          break;
        }
        printf("%c",temp);
      }
    }

    //大於 push，小於等於一直pop
    while ( stack[top] 優先 > input 優先 ){
      pop()
    }
    push()  //input 優先 > stack 優先 --> push
  }

}
