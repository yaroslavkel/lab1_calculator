#include <stdio.h>
#include <stdlib.h>
#include "decrypt.h"
char* decrypt(int* results, int count, int key){
	char* text = malloc(count + 1);
	for (int i = 0; i < count; i++){
		int ch = result[i] - key;
		if (ch >= 32 && ch <= 126){
			text[i] = ch;
		}
		else {
			text[i] = '?';
		}
	text[count] = '\0';
	return text;
}
void print_result(int* results, int count, char* text){
	for (int i = 0; i < count; i++){
		printf("Ответ №%d\n: %d\n", i + 1, results[i]);
	}
	printf("Результирующая строка: %s\n", text);
}
