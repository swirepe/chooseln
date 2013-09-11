#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <unistd.h>


#define BUFF_LENGTH 2048
#define DEFAULT_LINES 1


int SKIP_BLANKS = 0;
char** g_chosenLines;
char g_currentLine[BUFF_LENGTH];
int g_numLines = DEFAULT_LINES;
double g_lineNumber = 1.0;


void usage(char* progname);
double randDouble(void);
void initChosenLines(void);
void choose(FILE* inputStream);
void chooseFromStdin(void);
void chooseFromFile(char* inputName);
void reportChosen(void);

int isBlank(char* line);
char* trimcpy(char *str);
void ltrim(char *str);
void rtrim(char *str);



int main(int argc, char* argv[]){
    srand(time(NULL));
    
    int opt;

    
    while ((opt = getopt(argc, argv, "shl:")) != -1) {
        switch (opt) {
            case 'l':
                g_numLines = atoi(optarg);
                break;
            case 's':
                SKIP_BLANKS = 1;
                break;
            case 'h':
                usage(argv[0]);
                exit(EXIT_SUCCESS);
            default: /* '?' */
                usage(argv[0]);
                exit(EXIT_FAILURE);
            }
    }
    

    
    if(g_numLines < 1){
        fprintf(stderr, "Error: number of lines must be a number 1 or greater. (%d)\n", g_numLines);
        exit(EXIT_FAILURE);
    }
            
    
    initChosenLines();
    
    
    if(optind == argc){
        chooseFromStdin();
    }else{
        int i;
        for( i = optind; i < argc; i++){
            if( (strncmp(argv[i],"-",1) == 0) ){
                chooseFromStdin();
            }else{
                chooseFromFile(argv[i]);
            }
        }
    }
    
    reportChosen();
    
    
}  // end of main


void usage(char* progname){
    printf("%s: Sample with replacement.\n", progname);
    printf("Usage:\n");
    printf("    %s -h                       This message.\n", progname);
    printf("    %s                          Choose a line from stdin at random.\n", progname);
    printf("    %s -s                       Choose a line from stdin at random, skipping blanks.\n", progname);
    printf("    %s -l 3                     Choose 3 lines from stdin at random.\n", progname);
    printf("    %s -l 3 -                   Choose 3 lines from stdin at random.\n", progname);
    printf("    %s filename                 Choose a line from a file at random.\n", progname);
    printf("    %s -l 3 filename            Choose 3 lines from a file at random.\n", progname);
    printf("    %s file1 file2  ...         Choose a line from all files combined at random.\n", progname);
    printf("    %s -l 3 file1 file2  ...    Choose 3 lines from all files combined at random.\n", progname);
    printf("    %s -l 3 -s file1 file2  ... Choose 3 lines from all files combined at random, skipping blank lines.\n\n", progname);
    printf("Note: All arguments must come before filenames, if any.\n");
    printf("Note: Any filename can be substituted with '-' for stdin.\n");
} // end of usage


double randDouble(void){
    return (double)rand() / (double)RAND_MAX;
}


void initChosenLines(void){
    g_chosenLines = (char**)malloc(g_numLines* sizeof(char*));
    int i;
    for(i = 0; i < g_numLines; i++){
        g_chosenLines[i] = (char*)malloc(BUFF_LENGTH*sizeof(char));
    }
}


int isBlank(char* line){
  int retval = 0;
  char* trimmed = trimcpy(line);
  if(strlen(trimmed) == 0){
      retval = 1;
  }
  free(trimmed);
  return retval;
}


void rtrim(char *str){
    size_t n;
    n = strlen(str);
    while (n > 0 && isspace((unsigned char)str[n - 1])) {
        n--;
    }
    str[n] = '\0';
}
 
void ltrim(char *str){
    size_t n;
    n = 0;
    while (str[n] != '\0' && isspace((unsigned char)str[n])) {
        n++;
    }
    memmove(str, str + n, strlen(str) - n + 1);
}
 
char* trimcpy(char *str){
      char* newstr = (char*)malloc(strlen(str)*sizeof(char));
      strcpy(newstr, str);
      rtrim(newstr);
      ltrim(newstr);
      return newstr;
}



void choose(FILE* inputStream){
    int i;
    while(fgets( g_currentLine, BUFF_LENGTH, inputStream) != NULL){
       if( (SKIP_BLANKS == 1) && isBlank(g_currentLine) == 1){
            continue;   
       }
       for(i = 0; i < g_numLines; i++){
           if( randDouble() < (1.0 / g_lineNumber) ){
               strcpy(g_chosenLines[i], g_currentLine);     
           }
       }
              
       g_lineNumber += 1.0;
    }
}



void chooseFromFile(char* inputName){
    int i;
    FILE* fileDesc;
    if( ( fileDesc = fopen(inputName, "r")) == NULL ){
        fprintf( stderr, "Cannot open file: %s\n", inputName);
        // exit(1);
    }else{
        choose(fileDesc);
        fclose(fileDesc);
    }
    
} // end of chooseFromFile



void chooseFromStdin(void){
    static int beenHere = 0;
    if( beenHere == 0 ){
        choose(stdin);
        beenHere = 1;
    }
}


void reportChosen(void){
    int i;
    for(i = 0; i < g_numLines; i++){
        printf("%s", g_chosenLines[i]);
    }
}
