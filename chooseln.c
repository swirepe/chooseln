#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>


#define BUFF_LENGTH 120
#define DEFAULT_LINES 1

void choose(char* inputName, int numLines);
double randDouble(void);

int main(int argc, char* argv[]){
    srand(time(NULL));
    
    int numLines = DEFAULT_LINES;
    char* inputName;
    
    switch(argc){
        case 2:
            inputName = argv[1];
            break;
        case 3: 
            numLines = atoi(argv[1]);
            inputName = argv[2];
            
            if(numLines < 1){
                fprintf(stderr, "Error: number of lines must be a number 1 or greater. (%d)\n", numLines);
                return 1;
            }
            
            break;
            
        default:
            printf("Usage:\n");
            printf("    chooseln filename         choose a line from a file at random.\n");
            printf("    chooseln x filename       choose x lines from a file at random.\n");       
        
            return 0;
            
    }
    
    
    choose(inputName, numLines);
}  // end of main


double randDouble(void){
    return (double)rand() / (double)RAND_MAX;
}


void choose(char* inputName, int numLines){
    double lineNumber = 1.0;
    
    char currentLine[BUFF_LENGTH];
    
    char** chosenLines = (char**)malloc(numLines* sizeof(char*));
    int i;
    for(i = 0; i < numLines; i++){
        chosenLines[i] = (char*)malloc(BUFF_LENGTH*sizeof(char));
    }
    
    
    FILE* fileDesc;
    if( ( fileDesc = fopen(inputName, "r")) == NULL ){
        fprintf( stderr, "Cannot open file: %s\n", inputName);
        exit(1);
    }else{
        while(fgets( currentLine, BUFF_LENGTH, fileDesc) != NULL){
           
           for(i = 0; i < numLines; i++){
               if( randDouble() < (1.0 / lineNumber) ){
                   strcpy(chosenLines[i], currentLine);     
               }
           }
                  
           lineNumber += 1.0;
        }
    }
    
    for(i = 0; i < numLines; i++){
        printf("%s", chosenLines[i]);
    }
    
} // end of choose
