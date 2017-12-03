
#include <stdio.h> 
#include <stdlib.h>     
#include <time.h>

#include "wordtree.h"

int main(int argc, char *argv[]) {
 	struct node* root = NULL;
  struct nodeNumber* rootNumber = NULL;

	time_t inicio, final;
	time(&inicio);
	if (argc != 3) {
		fprintf(stderr, "Error: Problem with the number of parameters\n");
		fprintf(stderr, "    on the command line\n");
		fprintf(stderr, "Use:\n");
		fprintf(stderr, "    dicttool option 'file_in' > 'file_out'\n");
		fprintf(stderr, "option:\n");
		fprintf(stderr, "    1 to seek words only\n");
		fprintf(stderr, "    2 to check urls\n");
		fprintf(stderr, "    3 to find numberss\n");
		fprintf(stderr, "    4 to seek only words and counting\n");
		fprintf(stderr, "    5 to check urls and counting\n");
		fprintf(stderr, "    6 to check numbers and counting\n");
		exit(8);
	};
	int option = atoi(argv[1]);
	switch (option) {
		case 1:{
			ScanWords(root, argv[2]);
			PrintTree(root);
			break;
		}
		case 2: {
			ScanURL(root, argv[2]);
			PrintTree(root);
			break;
		}
		case 3: {
			ScanNumbers(root, argv[2]);
			PrintNumbers(rootNumber);
			break;
		}
		case 4: {
			ScanWords(root, argv[2]);
			PrintTreeCount(root);
			break;
		}
		case 5: {
			ScanURL(root, argv[2]);
			PrintTreeCount(root);
			break;
		}
		case 6: {
			ScanNumbers(root, argv[2]);
			PrintNumbersCount(rootNumber);
			break;
		}
		default: {
			fprintf(stderr, "option:\n");
			fprintf(stderr, "    1 to seek words only\n");
			fprintf(stderr, "    2 to check urls\n");
			fprintf(stderr, "    3 to find numberss\n");
			fprintf(stderr, "    4 to seek only words and counting\n");
			fprintf(stderr, "    5 to check urls and counting\n");
			fprintf(stderr, "    6 to check numbers and counting\n");
		}
	}
	
	time(&final);
	double diff = difftime(final, inicio);

	printf("It took %.2lf seconds to run\n", diff);
	return (0);
}
