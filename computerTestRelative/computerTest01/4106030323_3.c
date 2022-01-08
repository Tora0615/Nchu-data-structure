#include <stdlib.h>
#include <stdio.h>
#define TRUE 1
#define FALSE 0
#define INPUTFILE "TestCase\\test_case_3-1\\input_3.txt"









int main(void){
	FILE *f_read_ptr;
	if( !(f_read_ptr = fopen(INPUTFILE,"r")) ){
		printf("Faild to open file");
	}
	
	return 0;
}
