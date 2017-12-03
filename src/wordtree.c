#include "wordtree.h"

#include <stdio.h> 
#include <stdlib.h>

#define ERROR_MEMORY_MESSAGE "Error: out memory \n"
#define ERROR_NOT_OPEN "Error: can not open %s\n"

void MemoryError(void) {
	fprintf(stderr, ERROR_MEMORY_MESSAGE);
	exit(8);
}

char* SaveString(char *string) {
	char* new_string;
	new_string = malloc((unsigned)(strlen(string) + 1));

	if (new_string == NULL) {
		MemoryError();
	}
	strcpy(new_string, string);
	return (new_string);
}

void InsertNode(struct node **node, char *word) {
	if ((*node) == NULL) {
		(*node) = malloc(sizeof(struct node));
		if ((*node) == NULL) {
			MemoryError();
		}

		(*node)->left = NULL;
		(*node)->right = NULL;
		(*node)->word = SaveString(word);
		(*node)->total = 1;
		return;
	}

	int result = strcmp((*node)->word, word);

	if (result == 0) {
		(*node)->total += 1;
		return;
	}

	if (result < 0)
		InsertNode(&(*node)->right, word);
	else
		InsertNode(&(*node)->left, word);
}

void InsertNumberNode(struct nodeNumber **node, int number) {
	if ((*node) == NULL) {
		(*node) = malloc(sizeof(struct nodeNumber));
		if ((*node) == NULL) {
			MemoryError();
		}

		(*node)->left = NULL;
		(*node)->right = NULL;
		(*node)->number = number;
		(*node)->total = 1;
		return;
	}

	int temp1 = (*node)->number;
	int temp2 = number;
	if (temp1 == temp2) {
		(*node)->total += 1;
		return;
	}
	else if (temp1 > temp2) {
		InsertNumberNode(&(*node)->right, number);
	}
	else {
		InsertNumberNode(&(*node)->left, number);
	}
	return;
}

void ScanWords(struct node* root, char *name) {
	char word[1000];
	int  index;
	int  ch;
	FILE *in_file;

	in_file = fopen(name, "r");
	if (in_file == NULL) {
		fprintf(stderr, ERROR_NOT_OPEN, name);
		exit(8);
	}
	while (1) {
		while (1) {
			ch = fgetc(in_file);
			if (isalpha(ch) || (ch == EOF)) {
				break;
			}
		}
		if (ch == EOF) {
			break;
		}
		word[0] = ch;
		for (index = 1; index < (sizeof(word) - 1); ++index) {
			ch = fgetc(in_file);
			if (!isalpha(ch)) {
				break;
			}
			word[index] = ch;
		}

		word[index] = '\0';

		InsertNode(&root, word);
	}
	fclose(in_file);
}

void ScanURL(struct node* root, char *name) {
	char word[1000];
	int  index;
	int  ch;
	FILE *in_file;

	in_file = fopen(name, "r");
	if (in_file == NULL) {
		fprintf(stderr, ERROR_NOT_OPEN, name);
		exit(8);
	}
	while (1) {
		while (1) {
			ch = fgetc(in_file);
			if (isalpha(ch) || (ch == EOF)) {
				break;
			}
		}
		if (ch == EOF) {
			break;
		}
		word[0] = ch;
		for (index = 1; index < (sizeof(word) - 1); ++index) {
			ch = fgetc(in_file);
			if ((ch == ' ') || (ch == EOF)) {
				break;
			}
			word[index] = ch;
		}
		word[index] = '\0';

		InsertNode(&root, word);
	}
	fclose(in_file);
}

void ScanNumbers(struct nodeNumber* rootNumber, char *name) {
	int  temp;
	FILE *in_file;

	in_file = fopen(name, "r");
	if (in_file == NULL) {
		fprintf(stderr, ERROR_NOT_OPEN, name);
		exit(8);
	}
	while (fscanf(in_file, "%d", &temp) != EOF) {
		InsertNumberNode(&rootNumber, temp);
		fseek(in_file, 1, SEEK_CUR);
	}
	fclose(in_file);
}

void PrintNumbers(struct nodeNumber *top) {
	if (top == NULL)
		return;

	PrintNumbers(top->left);
	printf("%d\n", top->number);
	PrintNumbers(top->right);
}

void PrintTree(struct node *top) {
	printf("--ini\n");
	if (top == NULL)
		return;
	printf("--end\n");
	PrintTree(top->left);
	printf("%s\n", top->word);
	PrintTree(top->right);
}

void PrintNumbersCount(struct nodeNumber *top) {
	if (top == NULL)
		return;

	PrintNumbersCount(top->left);
	printf("%10.ul,%ul\n", top->total, top->number);
	PrintNumbersCount(top->right);
}

void PrintTreeCount(struct node *top) {
	if (top == NULL)
		return;

	PrintTreeCount(top->left);
	printf("%10.ul,%s\n", top->total, top->word);
	PrintTreeCount(top->right);
}
