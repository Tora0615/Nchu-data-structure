#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define SIZE 500
#define INPUTFILE "TestCase\\test_case_2-0\\input_1.txt"
#define TRUE 1
#define FALSE 0

char stack[SIZE], ansStack[SIZE];
int top, ansTop;

int getLevel(char input){
  if(input == ')' || input == '('){
  	/* ')' in stack*/
    if(stack[top] == ')'){
      return 0;
    }
    return 4;
  }
  else if(input == '*' || input == '%' || input == '/'){
    return 3;
  }
  else if(input == '+' || input == '-'){
    return 2;
  }
  else if(input == '>' || input == '<'){
    return 1;
  }
  else if(input == '&' || input == '^' || input == '|'){
    return 0;
  }
  else{
    return 0;
  }
}

void push(char input){
	//printf("called push\n");
	stack[++top] = input;
}

void pushToAns(char input){
	//printf("called pushToAns\n");
	ansStack[++ansTop] = input;
}

char pop(){
	//printf("called pop\n");
	return stack[top--];
}

char popAns(){
	//printf("called popAns\n");
	return ansStack[ansTop--];
}


void processItem(char input){
	//printf("%c\n",input);  return;
	
	/* is words (a-z & A-Z) */
	if( (input >= 'A' && input <= 'Z') || (input >= 'a' && input <= 'z') ){
		pushToAns(input);
	}
	/* is operand */
	else{
		/* '(' case -> pop until meet ')' */
		if(input == '('){
			while (TRUE){
		        char temp = pop();
		        if (temp == ')') {
		          break;
		        }
		        pushToAns(' ');
		        pushToAns(temp);
		      }
		}
		/* '\0' operand AKA end of line*/
		else if ( input == '\0'){
	      while (top != -1){
	        pushToAns(' ');
	        pushToAns(pop());
	      }
	    }
		/* other operand*/
		else{
			/* input >= stackTop -> push*/
			if(getLevel(input) >= getLevel(stack[top])){
				push(input);
			}
			/* input < stackTop -> pop until condition change*/
			else{
				while(getLevel(input) < getLevel(stack[top]) && top != -1){
					pushToAns(' ');
					pushToAns(pop());
				}
				/* final push */
				push(input);
			}
			if(input != ')'){
		    	pushToAns(' ');
		    }
		}
	}
}


void prefix(char *content){
	// printf("%s\n", content);
	int len = strlen(content);
	int i;
	
	/* reverse read */
	for(i=len-1; i>-1 ; i--){
		processItem(content[i]);
		//printf("~%s\t\t%s\n", ansStack, stack);
	}
	processItem('\0');
	
	/* print result */
	while(ansTop != -1){
		printf("%c",popAns());
		//printf(" ");
	}
	printf("\n");
}


int main(void){
	FILE *f_read_ptr;
	if(!(f_read_ptr = fopen(INPUTFILE,"r"))){
		printf("open file failed");
		return 0;
	}
	int dataCount, i;
	fscanf(f_read_ptr, "%d\n", &dataCount);
	char *content = (char*)malloc(sizeof(char)*500);
	char charbuf = ' ';
	for(i=0 ; i<dataCount ; i++){
		top = -1;
		ansTop = -1;
		stack[0] = '\0';
		ansStack[0] = '\0';
		fscanf(f_read_ptr, "%[^\n]", content);
		charbuf = getc(f_read_ptr);
		prefix(content);
	}
	fclose(f_read_ptr);
	return 0;
}



// reverse read -> to postorder -> reverse print (ansStack pop)
