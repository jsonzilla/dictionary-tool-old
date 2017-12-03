#ifndef WORDTREE_H
#define WORDTREE_H

struct node {
	struct node *left;
	struct node *right;
	char *word;
	unsigned long total;
};

struct nodeNumber {
	struct nodeNumber *left;
	struct nodeNumber *right;
	int number;
	unsigned long total;
};

struct node* ScanWords(char *name);

struct node* ScanURL(char *name);

struct nodeNumber* ScanNumbers(char *name);

void PrintNumbers(struct nodeNumber *top);

void PrintTree(struct node *top);

void PrintNumbersCount(struct nodeNumber *top);

void PrintTreeCount(struct node *top);

#endif