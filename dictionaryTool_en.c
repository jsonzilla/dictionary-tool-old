
#include <stdio.h> 
#include <ctype.h> 
#include <string.h> 
#include <stdlib.h>     
#include <time.h>
 
struct node { 
    struct node    *left;     
    struct node    *right;   
    char           *word;   
    unsigned long total;
}; 

struct nodeNumber { 
    struct nodeNumber    *left;    
    struct nodeNumber    *right;    
    int                  number; 
    unsigned long total;
};  


static struct node *root = NULL; 
static struct nodeNumber *rootNumber = NULL;

void inline memory_Erro(void) 
{ 
    fprintf(stderr, "Erro: out memory \n"); 
    exit(8); 
} 
 
char inline *save_string(char *string) 
{ 
    char *new_string; 
 
    new_string = malloc((unsigned) (strlen(string) + 1)); 
 
    if (new_string == NULL){ 
        memory_Erro(); 
        }
    strcpy(new_string, string); 
       return (new_string); 
} 

void inline enter(struct node **node, char *word) 
{ 
    int  result;        
 
    char *save_string(char *); 
 

    if ((*node) == NULL) { 
 

        (*node) = malloc(sizeof(struct node)); 
        if ((*node) == NULL) 
            memory_Erro(); 
 

        (*node)->left = NULL; 
        (*node)->right = NULL; 
        (*node)->word = save_string(word); 
        (*node)->total=1;
        return; 
    } 

    result = strcmp((*node)->word, word); 
 

    if (result == 0) {
        (*node)->total+=1;       
        return; 
        }
 

    if (result < 0) 
        enter(&(*node)->right, word); 
    else 
        enter(&(*node)->left, word); 
        } 

void inline enterNumber(struct nodeNumber **nodeNumber, int number) 
{ 
    if ((*nodeNumber) == NULL){ 
         (*nodeNumber) = malloc(sizeof(struct nodeNumber)); 
        if ((*nodeNumber) == NULL) 
            memory_Erro(); 
 
     
        (*nodeNumber)->left = NULL; 
        (*nodeNumber)->right = NULL; 
        (*nodeNumber)->number = number;
        (*nodeNumber)->total=1;
        return; 
    }

    int temp1 = (*nodeNumber)->number;
    int temp2 = number;
    if(temp1 == temp2){
        (*nodeNumber)->total+=1;
        return;                     
    }else if(temp1 > temp2){
         enterNumber(&(*nodeNumber)->right, number); 
    }else {
         enterNumber(&(*nodeNumber)->left, number);  
    }
    return;
    } 

void scanWord(char *name) 
{ 
    char word[1000];     
    int  index;         
    int  ch;         
    FILE *in_file;     
 
    in_file = fopen(name, "r"); 
    if (in_file == NULL) { 
        fprintf(stderr, "Erro: can not open %s\n", name); 
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
        for (index = 1; index < (sizeof(word)-1); ++index) { 
            ch = fgetc(in_file); 
            if (!isalpha(ch)){ 
                break; 
                }  
            word[index] = ch; 
        } 

        word[index] = '\0'; 
 
        enter(&root, word); 
    } 
    fclose(in_file); 
    } 
void scanUrl(char *name) 
{ 
    char word[1000];    
    int  index;       
    int  ch;        
    FILE *in_file;    
 
    in_file = fopen(name, "r"); 
    if (in_file == NULL) { 
        fprintf(stderr, "Erro: can not open %s\n", name); 
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
        for (index = 1; index < (sizeof(word)-1); ++index) { 
            ch = fgetc(in_file); 
            if((ch == ' ') || (ch == EOF)){
                   break;
                   }    
            word[index] = ch; 
        } 
        word[index] = '\0'; 
 
        enter(&root, word); 
    } 
    fclose(in_file); 
    } 

void scanNumb(char *name) 
{ 
    int  temp;
    FILE *in_file;      /* input file */ 
 
    in_file = fopen(name, "r"); 
    if (in_file == NULL) { 
        fprintf(stderr, "Erro: can not open %s\n", name); 
        exit(8); 
    }
    while(fscanf(in_file,"%d",&temp) != EOF){
          enterNumber(&rootNumber,temp);
          fseek(in_file,1,SEEK_CUR);
    }
    fclose(in_file); 
    } 
 
void print_number(struct nodeNumber *top) 
{ 
    if (top == NULL) 
        return;                
 
    print_number(top->left); 
    printf("%d\n",top->number); 
    print_number(top->right); 
}

void print_tree(struct node *top) 
{ 
    if (top == NULL) 
        return;              
 
    print_tree(top->left); 
    printf("%s\n",top->word); 
    print_tree(top->right); 
} 

void print_number_count(struct nodeNumber *top) 
{ 
    if (top == NULL) 
        return;            
    print_number_count(top->left); 
    printf("%10.d,%d\n",top->total,top->number); 
    print_number_count(top->right); 
}

void print_tree_count(struct node *top) 
{ 
    if (top == NULL) 
        return;         
 
    print_tree_count(top->left); 
    printf("%10.d,%s\n",top->total, top->word); 
    print_tree_count(top->right); 
}  
 
int main(int argc, char *argv[]) 
{
    time_t inicio, final;
    time(&inicio);
    if (argc != 3) { 
        fprintf(stderr, "Erro:Problem with the number of parameters\n"); 
        fprintf(stderr, "    on the command line\n"); 
        fprintf(stderr, "Use:\n"); 
        fprintf(stderr, "    dictionary*.exe option 'file_in' > 'file_out'\n"); 
        fprintf(stderr, "option:\n");
        fprintf(stderr, "    1 to seek words only\n");
        fprintf(stderr, "    2 to check urls\n");
        fprintf(stderr, "    3 to find numberss\n");
        fprintf(stderr, "    4 to seek only words and counting\n");
        fprintf(stderr, "    5 to check urls and counting\n");
        fprintf(stderr, "    6 to check numbers and counting\n");
        exit(8); 
    }; 
    int opcao = atoi(argv[1]);
    if(opcao == 1){
             scanWord(argv[2]);
             print_tree(root); 
             }
    else if(opcao == 2){
         scanUrl(argv[2]);
         print_tree(root); 
         }
    else if(opcao == 3){
         scanNumb(argv[2]);
         print_number(rootNumber); 
         }
    else if(opcao == 4){
         scanWord(argv[2]);
         print_tree_count(root); 
         }
    else if(opcao == 5){
         scanUrl(argv[2]);
         print_tree_count(root); 
         }
    else if(opcao == 6){
         scanNumb(argv[2]);
         print_number_count(rootNumber); 
         }
    else{
        fprintf(stderr, "option:\n");
        fprintf(stderr, "    1 to seek words only\n");
        fprintf(stderr, "    2 to check urls\n");
        fprintf(stderr, "    3 to find numberss\n");
        fprintf(stderr, "    4 to seek only words and counting\n");
        fprintf(stderr, "    5 to check urls and counting\n");
        fprintf(stderr, "    6 to check numbers and counting\n");
        }
    time(&final);
    double diferenca = difftime(final,inicio);
    
    printf("It took %.2lf seconds to run\n", diferenca);
    return (0); 
} 
