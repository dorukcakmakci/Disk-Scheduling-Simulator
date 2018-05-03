#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double find_mean(int *arr, int size){
    double result = 0;
    for(int i = 0; i < size; i++){
        result += arr[i];
    }
    result /= size;
    return result;
}

double find_stddev(int * arr, int size){

    double mean = find_mean(arr,size);
    double result = 0;
    for(int j = 0; j < size; j++){
        result += pow(arr[j] - mean,2);
    }
    result /= size;
    result = sqrt(result);
    return result;
}


void FCFS(int N, char* filename){

    FILE* fptr;
    int time[100];
    int *cylinder;
    cylinder = malloc(100 * sizeof(int));

    fptr = fopen(filename, "r");

    if(fptr == NULL){
        printf("ERROR: Can not open the file...\n");
        return;
    }

    int i = 0;
    int linecount = 0;

    while(!feof(fptr)){
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


    if(linecount != 100){
        time[linecount] = -1;
        cylinder[linecount] = -1;
    }
    for (int j = 0; j <= linecount; j++){
        if(j != linecount)
            printf("Request %d => Time: %d   Cylinder => %d\n", (j+1), time[j], cylinder[j]);
        else
            printf("Request Ended => Time: %d   Cylinder => %d\n", time[j], cylinder[j]);
    }

    int elapsedTime = 0;
    int oldElapsedTime = 0;
    int numberOfRequestsFinished = 0;
   
    int *requestGrantTime;
    requestGrantTime = malloc(100*sizeof(int));
    
    int currentIndex = 0;
    int currentCylinder = 1;

    while(numberOfRequestsFinished < linecount){
        //printf("Elapsed Time: %d\n", elapsedTime);

        if(elapsedTime < time[currentIndex]){
            elapsedTime++;
            printf("1\n");
            continue;
        }
        if(currentCylinder == cylinder[currentIndex]){
            requestGrantTime[currentIndex] = elapsedTime - oldElapsedTime + time[currentIndex];
            oldElapsedTime = elapsedTime;
           printf("%d-------\n", numberOfRequestsFinished);
            fflush(stdout);
            numberOfRequestsFinished++;
            currentIndex++;
            printf("2\n");
        }
        else if(currentCylinder < cylinder[currentIndex]){
            while(currentCylinder < cylinder[currentIndex]){
                currentCylinder++;
                elapsedTime++;
            }
            printf("3\n");
        }
        else if(currentCylinder > cylinder[currentIndex]){
            while(currentCylinder > cylinder[currentIndex]){
                currentCylinder--;
                elapsedTime++;
            }
            printf("4\n");
        }
    }

    printf("FCFS\n----\nElapsed time: %d\nAverage wait time: %f\nStandard deviation of wait times: %f\n", elapsedTime, find_mean(requestGrantTime, linecount), find_stddev(requestGrantTime, linecount));
    fflush(stdout);

    fclose(fptr);

    free(requestGrantTime);
    

     
}

int getMinimumNotTraversedIndex(int * request, int * granted, int headLocation, int size){
    int result = -1;
    int min = 999999;
    for(int i = 0; i < size; i++){
        if(granted[i] == 1){
            continue;
        }
        else{
            if(abs(request[i] - headLocation) < min){
                result = i;
                min = abs(request[i] - headLocation);
            }
        }
    }
    return result;
}

void SSTF(int N, char* filename){

    FILE* fptr;
    int time[100];
    int *cylinder;
    cylinder = malloc(100*sizeof(int));

    fptr = fopen(filename, "r");

    if(fptr == NULL){
        printf("ERROR: Can not open the file...\n");
        return;
    }

    int i = 0;
    int linecount = 0;
    
    while(!feof(fptr)){
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


    if(linecount != 100){
        time[linecount] = -1;
        
    }
        cylinder[linecount] = -1;
    
    for (int j = 0; j <= linecount; j++){
        if(j != linecount)
            printf("Request %d => Time: %d   Cylinder => %d\n", (j+1), time[j], cylinder[j]);
        else
            printf("Request Ended => Time: %d   Cylinder => %d\n", time[j], cylinder[j]);
    }

    int elapsedTime = 0;
    int oldElapsedTime = 0;
    int numberOfRequestsFinished = 0;
   
    int *requestGrantTime;
    requestGrantTime = malloc(100*sizeof(int));

    int *grantRequest;
    grantRequest =  malloc(100*sizeof(int));

    for(int i = 0; i < 100; i++){
        if(i >= linecount)
            grantRequest[i] = 1;
        else 
            grantRequest[i] = 0;
    }
    
    int currentIndex = 0;
    int currentCylinder = 1;

    while(numberOfRequestsFinished < linecount){

        if(elapsedTime < time[currentIndex]){
            elapsedTime++;
            printf("1\n");
            continue;
        }
        if(currentCylinder == cylinder[currentIndex]){
            requestGrantTime[currentIndex] = elapsedTime - oldElapsedTime + time[currentIndex];
            oldElapsedTime = elapsedTime;
            printf("%d-------\n", numberOfRequestsFinished);
            fflush(stdout);
            numberOfRequestsFinished++;
            currentIndex = getMinimumNotTraversedIndex(cylinder,  grantRequest, currentCylinder, linecount);
            grantRequest[currentIndex] = 1;
            printf("2\n");
        }
        else if(currentCylinder < cylinder[currentIndex]){
            while(currentCylinder < cylinder[currentIndex]){
                currentCylinder++;
                elapsedTime++;
            }
            printf("3\n");
        }
        else if(currentCylinder > cylinder[currentIndex]){
            while(currentCylinder > cylinder[currentIndex]){
                currentCylinder--;
                elapsedTime++;
            }
            printf("4\n");
        }
    }

    printf("SSTF\n----\nElapsed time: %d\nAverage wait time: %f\nStandard deviation of wait times: %f\n", elapsedTime, find_mean(requestGrantTime, linecount), find_stddev(requestGrantTime, linecount));
    fflush(stdout);

    fclose(fptr);

    free(requestGrantTime); 
    free(cylinder);
    free(grantRequest); 
}

int *getMaximumAndMinimumNotTraversedIndex(int * request, int * granted, int size){
    int *result = malloc(2*sizeof(int));
    int max = -1;
    int min = 999999;
    for(int i = 0; i < size; i++){
        if(granted[i] == 1){
            continue;
        }
        else{
            if(request[i] > max){
                result[1] = i;
                max = request[i];
            }
            if(request[i] <  min){
                result[0] = i;
                min = request[i];
            }
        }
    }
    return result;
}

void LOOK(int N, char* filename){
    
    FILE* fptr;
    int time[100];
    int cylinder[100];

    fptr = fopen(filename, "r");

    if(fptr == NULL){
        printf("ERROR: Can not open the file...\n");
        return;
    }

    int i = 0;
    int linecount = 0;
    
    while(!feof(fptr)){
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


    if(linecount != 100){
        time[linecount] = -1;
        cylinder[linecount] = -1;
    }
    for (int j = 0; j <= linecount; j++){
        if(j != linecount)
            printf("Request %d => Time: %d   Cylinder => %d\n", (j+1), time[j], cylinder[j]);
        else
            printf("Request Ended => Time: %d   Cylinder => %d\n", time[j], cylinder[j]);
    }

    int elapsedTime = 0;
    int oldElapsedTime = 0;
    int numberOfRequestsFinished = 0;
   
    int *requestGrantTime;
    requestGrantTime = malloc(100*sizeof(int));

    int *grantRequest;
    grantRequest =  malloc(100*sizeof(int));

    for(int i = 0; i < 100; i++){
        if(i >= linecount)
            grantRequest[i] = 1;
        else 
            grantRequest[i] = 0;
    }
    int * max_min_indices = getMaximumAndMinimumNotTraversedIndex(cylinder,  grantRequest, linecount);
    int currentIndex = 0;
    int currentCylinder = 1;

    while(numberOfRequestsFinished < linecount){

        if(elapsedTime < time[currentIndex]){
            elapsedTime++;
            printf("1\n");
            continue;
        }
        if(currentCylinder < max_min_indices[1]){
            while(currentCylinder < max_min_indices[1]){
                currentCylinder++;
                elapsedTime++;
                if(currentCylinder == cylinder[currentIndex]){
                    requestGrantTime[currentIndex] = elapsedTime - oldElapsedTime + time[currentIndex];
                    oldElapsedTime = elapsedTime;
                    printf("%d-------\n", numberOfRequestsFinished);
                    fflush(stdout);
                    numberOfRequestsFinished++;
                    currentIndex = getMinimumNotTraversedIndex(cylinder,  grantRequest, currentCylinder, linecount);
                    printf("2\n");
                }
            }
            printf("3\n");
        }
        else if(currentCylinder > max_min_indices[0]){
            while(currentCylinder > max_min_indices[0]){
                currentCylinder--;
                elapsedTime++;
                if(currentCylinder == cylinder[currentIndex]){
                    requestGrantTime[currentIndex] = elapsedTime - oldElapsedTime + time[currentIndex];
                    oldElapsedTime = elapsedTime;
                    printf("%d-------\n", numberOfRequestsFinished);
                    fflush(stdout);
                    numberOfRequestsFinished++;
                    currentIndex = getMinimumNotTraversedIndex(cylinder,  grantRequest, currentCylinder, linecount);
                    printf("2\n");
                }
            }
            printf("4\n");
        }
    }

    printf("SSTF\n----\nElapsed time: %d\nAverage wait time: %f\nStandard deviation of wait times: %f\n", elapsedTime, find_mean(requestGrantTime, linecount), find_stddev(requestGrantTime, linecount));
    fflush(stdout);

    fclose(fptr);

    free(requestGrantTime); 
    free(cylinder);
    free(grantRequest);

     
}

void CLOOK(int N, char* filename){
 
    FILE* fptr;
    int time[100];
    int cylinder[100];

    fptr = fopen(filename, "r");

    if(fptr == NULL){
        printf("ERROR: Can not open the file...\n");
        return;
    }

    int i = 0;
    int linecount = 0;
    
    while(!feof(fptr)){
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


    if(linecount != 100){
        time[linecount] = -1;
        cylinder[linecount] = -1;
    }
    for (int j = 0; j <= linecount; j++){
        if(j != linecount)
            printf("Request %d => Time: %d   Cylinder => %d\n", (j+1), time[j], cylinder[j]);
        else
            printf("Request Ended => Time: %d   Cylinder => %d\n", time[j], cylinder[j]);
    }

    //TODO

    fclose(fptr);

     
}

int main(int argc, char ** argv){

    //get the arguments
    if(argc == 1 || argc == 2 || argc > 3 ){
        printf("Arguments are insufficient.\n");
        return -1;
    }
    
    int N = argv[1];
    char * filename = argv[2];
   

    //Use FCFS to schedule
    //FCFS(N, filename);
    
    //Use SSTF to schedule
    SSTF(N, filename);

    //Use LOOK to schedule
    //LOOK(N, filename);

    //Use CLOOK to schedule
    //CLOOK(N, filename);
    return 0;
}
