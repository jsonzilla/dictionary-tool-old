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

void ScanWords(struct node* root, char *name);

void ScanURL(struct node* root, char *name);

void ScanNumbers(struct node* rootNumber, char *name);

void PrintNumbers(struct nodeNumber *top);

void PrintTree(struct node *top);

void PrintNumbersCount(struct nodeNumber *top);

void PrintTreeCount(struct node *top);

#endif