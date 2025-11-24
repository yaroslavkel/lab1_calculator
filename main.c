#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <decrypt.h>
#include <calc.h>
int is_valid_number(const char* str){
	if (str == NULL || *str == '\0'){
		return 0;
	}
	if (*str == '-' || *str == '+'){
		str++;
	}
	while (*str){
		if (!isdigit(*str)){
			return 0;
			str++;
		}
	}
	return 1;
}
int find_key_index(int argc, char** argv){
	for (int i = 1; i < argc; i++){
		if (strcmp(argv[i], "-k") == 0){
			return i;
		}
	}
	return -1;
}
int validate_arguments(int argc, char** argv, int key_index){
	if (argc < 6){
		fprintf(stderr, "Ошибка: недостаточно аргументов\n");
		return 0;
	}
	if (key_index == -1){
		fprintf(stderr, "Ошибка: флаг -k не найден\n");
		return 0;
	}
	if (key_index == argc - 1){
		fprintf(stderr, "Ошибка: отсутствует значение ключа после -k\n");
		return 0;
	}
	if (key_index + 2 < argc){
		fprintf(stderr, "Ошибка: обнаружены аргументы после ключа\n");
		return 0;
	}
	if (!is_valid_number(argv[key_index + 1])){
		fprintf(stderr, "Ошибка: ключ должен быть целым числом\n");
		return 0;
	}
	int expr_count = key_index - 1;
	if (expr_count < 3 || expr_count % 3 != 0){
		fprintf(stderr, "Ошибка: неверное количество аргументов в выражениях\n");
		fprintf(stderr, "Каждое выражение требует 3 аргумента: число оператор число\n");
		return 0;
	}
	for (int i = 1; i < key_index, i+=3){
		if (!is_valid_number(argv[i])){
			fprintf(stderr, "Ошибка: неверный формат числа, число должно быть целым '%s'\n", argv[i]);
			return 0;
		}
		if (strlen(argv[i + 1]) != 1 || is_valid_operator(argv[i + 1][0])){
			fprintf(stderr, "Ошибка: неверный оператор '%s'\n", argv[i + 1]);
			frpintf(stderr, "Допустимые операторы: + - * %%\n ");
			return 0;
		}
		if (!is_valid_number(argv[i + 2])){
			fprintf(stderr, "Ошибка: неверный формат числа, число должно быть целым '%s'\n", argv[i + 2]);
			return 0;
		}
		if (argv[i + 1][0] == '%' && atoi(argv[i + 2]) == 0){
			fprintf(stderr, "Ошибка: деление на ноль в выражении %s %s %s\n", argv[i], argv[i + 1], argv[i + 2]);
			return 0;
		}
	}
	return 1;
}
int main(int argc, char** argv){
	int key_index = find_key_index(argc, argv);
	if (!validate_arguments(argc, argv, key_index)){
		fprintf(stderr, "Использование: %s <выражения> -k <ключ>\n", argv[0]);
		fprintf(stderr, "Пример: %s 41 + 33 111 - 8 -k 2\n", argv[0]);
	       return 1;
	}
	int key = atoi(argv[key_index + 1]);
	int expr_count = (key_index - 1) / 3;
	int* results = malloc(expr_count * sizeof(int));
	if (results == NULL){
		fprintf(stderr, "Ошибка: не удалось выделить память\n");
		return 1;
	}
	for (int i = 0; i < expr_count; i++){
		int pos = 1 + i * 3;
		int a = atoi(argv[pos]);
		char op = argv[pos + 1][0];
		int b = atoi(argv[pos + 2]);
		results[i] = calculate(a, op, b);
	}
	char* text = decrypt(results, expr_count, key);
	if (text == NULL){
		fprintf(stderr, "Ошибка: не удалось дешифровать результаты\n");
		free(results);
		return 1;
	}
	print_results(results, expr_count, text);
	free(results);
	free(text);
	return 0;
}	

