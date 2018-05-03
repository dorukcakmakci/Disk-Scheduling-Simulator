#include <stdio.h>

int main(int argc, char ** argv){

    //get the arguments
    if(argc == 1 || argc == 2 || argc > 3 ){
        printf("Arguments are insufficient.\n");
        return -1;
    }
    int N = argv[1];
    char * filename = argv[2];

    //Use FCFS to schedule
    FCFS(N, filename);

    //Use SSTF to schedule
    SSTF(N, filename);

    //Use LOOK to schedule
    LOOK(N, filename);

    //Use CLOOK to schedule
    CLOOK(N, filename);

    return 0;
}

void FCFS(int N, char* filename){
    FILE* fptr;
    double mean = 0;
    double stdDev = 0;

    double time[100];
    double cylinder[100];

    fptr = fopen(filename, "r");

    if(fptr == NULL){
        printf("ERROR: Can not open the file...\n");
        return;
    }

    int i = 0;
    int linecount = 0;
    while(!feof(fptr)){
        fscanf(fptr, "%d", &time[linecount]);
        if( i == 0){
            fscanf(fptr, "%d", &time[linecount]);
            i++;
        }
        else if (i == 1){
            fscanf(fptr, "%d", &cylinder[linecount]);
            i--;
            linecount++;
        }
    }

    if(linecount != 99){
        time[linecount+1] = -1;
        cylinder[linecount+1] = -1;
    }


    //TODO

    fclose(filename);
}

void SSTF(int N, char* filename){
    FILE* fptr;
    double mean = 0;
    double stdDev = 0;

    double time[100];
    double cylinder[100];

    fptr = fopen(filename, "r");

    if(fptr == NULL){
        printf("ERROR: Can not open the file...\n");
        return;
    }

    int i = 0;
    int linecount = 0;
    while(!feof(fptr)){
        fscanf(fptr, "%d", &time[linecount]);
        if( i == 0){
            fscanf(fptr, "%d", &time[linecount]);
            i++;
        }
        else if (i == 1){
            fscanf(fptr, "%d", &cylinder[linecount]);
            i--;
            linecount++;
        }
    }

    if(linecount != 99){
        time[linecount+1] = -1;
        cylinder[linecount+1] = -1;
    }

    //TODO

    fclose(filename);
}

void LOOK(int N, char* filename){
    FILE* fptr;
    double mean = 0;
    double stdDev = 0;

    double time[100];
    double cylinder[100];

    fptr = fopen(filename, "r");

    if(fptr == NULL){
        printf("ERROR: Can not open the file...\n");
        return;
    }

    int i = 0;
    int linecount = 0;
    while(!feof(fptr)){
        fscanf(fptr, "%d", &time[linecount]);
        if( i == 0){
            fscanf(fptr, "%d", &time[linecount]);
            i++;
        }
        else if (i == 1){
            fscanf(fptr, "%d", &cylinder[linecount]);
            i--;
            linecount++;
        }
    }

    if(linecount != 99){
        time[linecount+1] = -1;
        cylinder[linecount+1] = -1;
    }
    //TODO

    fclose(filename);
}

void CLOOK(int N, char* filename){
    FILE* fptr;
    double mean = 0;
    double stdDev = 0;

    double time[100];
    double cylinder[100];

    fptr = fopen(filename, "r");

    if(fptr == NULL){
        printf("ERROR: Can not open the file...\n");
        return;
    }

    int i = 0;
    int linecount = 0;
    while(!feof(fptr)){
        fscanf(fptr, "%d", &time[linecount]);
        if( i == 0){
            fscanf(fptr, "%d", &time[linecount]);
            i++;
        }
        else if (i == 1){
            fscanf(fptr, "%d", &cylinder[linecount]);
            i--;
            linecount++;
        }
    }

    if(linecount != 99){
        time[linecount+1] = -1;
        cylinder[linecount+1] = -1;
    }

    //TODO

    fclose(filename);
}