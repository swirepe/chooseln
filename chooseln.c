#include <stdlib.h>
#include <stdio.h>

#define BUFF_LENGTH 120
#define DEFAULT_LINES 1

int main(int argc, char* argv[]){
    if(argc == 1){
        printf("Usage:\n");
        printf("    chooseln filename         choose a line from a file at random.\n");
        printf("    chooseln x filename       choose x lines from a file at random.\n");       
    
        return 0;
    }
    
    int numLines = DEFAULT_LINES;
    char* inputName;
    
    
    if(argc == 2){
        inputName = argv[1];
    }
    
    if(argc == 3){ 
        numLines = atoi(argv[1]);
        inputName = argv[2]);
    }
}  // end of main
