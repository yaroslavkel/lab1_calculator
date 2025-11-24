#include "calc.h"
int is_valid_operator(char op){
	return op == '+' || op == '-' || op == '*' || op == '%';
}
int calculate(int a, char op, int b){
	switch(op){
		case '+':
			return a + b;
		case '-':
			return a - b;
		case '*':
			return a * b;
		case '%':
			if (b!=0){
				return a % b;
			}
			else {
				return 0;
			}
		default:
			return 0;
	}
}
